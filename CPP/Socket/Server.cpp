//
// Created by Krisw on 2026/4/15.
//

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <direct.h>
#pragma comment(lib, "Ws2_32.lib")
using socket_t = SOCKET;
#define CLOSE_SOCKET closesocket
#define CHDIR _chdir
#define GET_SOCKET_ERROR() WSAGetLastError()
#define IS_WOULD_BLOCK(err) ((err) == WSAEWOULDBLOCK)
#define STR_CASE_CMP _stricmp
#else
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
using socket_t = int;
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define CLOSE_SOCKET close
#define CHDIR chdir
#define GET_SOCKET_ERROR() errno
#define IS_WOULD_BLOCK(err) ((err) == EAGAIN || (err) == EWOULDBLOCK)
#define STR_CASE_CMP strcasecmp
#endif

#include <ctype.h>
#include <errno.h>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

socket_t initListenFd(unsigned short port);
int epollRun(socket_t lfd);

socket_t acceptClient(socket_t lfd);
int recvHttpRequest(socket_t cfd);

int parseRequestLine(const char *line, socket_t cfd);
const char *getFileType(const char *name);
int sendDir(const char *dirName, socket_t cfd);
int sendFile(const char *fileName, socket_t cfd);
int sendHeadMsg(socket_t cfd, int status, const char *descr, const char *type, int length);

int hexToDec(char c);
void decodeMsg(char *to, char *from);
int setNonBlock(socket_t fd);
int sendAll(socket_t fd, const char *buf, int len);

int setNonBlock(socket_t fd) {
#ifdef _WIN32
    u_long mode = 1;
    return ioctlsocket(fd, FIONBIO, &mode);
#else
    int flag = fcntl(fd, F_GETFL, 0);
    if (flag == -1) {
        return -1;
    }
    return fcntl(fd, F_SETFL, flag | O_NONBLOCK);
#endif
}

int sendAll(socket_t fd, const char *buf, int len) {
    int sent = 0;
    while (sent < len) {
        int ret = send(fd, buf + sent, len - sent, 0);
        if (ret > 0) {
            sent += ret;
            continue;
        }
        if (ret == SOCKET_ERROR && IS_WOULD_BLOCK(GET_SOCKET_ERROR())) {
            continue;
        }
        return -1;
    }
    return 0;
}

socket_t initListenFd(unsigned short port) {
    socket_t lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == INVALID_SOCKET) {
        perror("socket");
        return INVALID_SOCKET;
    }

    int opt = 1;
    int ret = setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &opt, sizeof opt);
    if (ret == SOCKET_ERROR) {
        perror("setsockopt");
        CLOSE_SOCKET(lfd);
        return INVALID_SOCKET;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    ret = bind(lfd, (struct sockaddr *) &addr, sizeof addr);
    if (ret == SOCKET_ERROR) {
        perror("bind");
        CLOSE_SOCKET(lfd);
        return INVALID_SOCKET;
    }

    ret = listen(lfd, 128);
    if (ret == SOCKET_ERROR) {
        perror("listen");
        CLOSE_SOCKET(lfd);
        return INVALID_SOCKET;
    }
    return lfd;
}

int epollRun(socket_t lfd) {
    std::vector<socket_t> clients;

    while (1) {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(lfd, &readSet);

        socket_t maxFd = lfd;
        for (socket_t client : clients) {
            FD_SET(client, &readSet);
            if (client > maxFd) {
                maxFd = client;
            }
        }

        int num = select((int) maxFd + 1, &readSet, NULL, NULL, NULL);
        if (num == SOCKET_ERROR) {
            perror("select");
            return -1;
        }

        if (FD_ISSET(lfd, &readSet)) {
            socket_t cfd = acceptClient(lfd);
            if (cfd != INVALID_SOCKET) {
                clients.push_back(cfd);
            }
            --num;
        }

        for (size_t i = 0; i < clients.size() && num > 0;) {
            socket_t cfd = clients[i];
            if (!FD_ISSET(cfd, &readSet)) {
                ++i;
                continue;
            }

            --num;
            int ret = recvHttpRequest(cfd);
            if (ret <= 0) {
                CLOSE_SOCKET(cfd);
                clients.erase(clients.begin() + i);
            } else {
                ++i;
            }
        }
    }
    return 0;
}

socket_t acceptClient(socket_t lfd) {
    socket_t cfd = accept(lfd, NULL, NULL);
    if (cfd == INVALID_SOCKET) {
        perror("accept");
        return INVALID_SOCKET;
    }

    if (setNonBlock(cfd) == SOCKET_ERROR) {
        perror("setNonBlock");
        CLOSE_SOCKET(cfd);
        return INVALID_SOCKET;
    }

    printf("accept client fd: %lld\n", (long long) cfd);
    return cfd;
}

int recvHttpRequest(socket_t cfd) {
    printf("start receiving data...\n");
    int len = 0, total = 0;
    char tmp[1024] = {0};
    char buf[4096] = {0};
    while ((len = recv(cfd, tmp, sizeof tmp, 0)) > 0) {
        if (total + len < (int) sizeof buf) {
            memcpy(buf + total, tmp, len);
        }
        total += len;
    }

    if (len == SOCKET_ERROR && IS_WOULD_BLOCK(GET_SOCKET_ERROR())) {
        if (total <= 0) {
            return 1;
        }

        char *pt = strstr(buf, "\r\n");
        if (pt == NULL) {
            return -1;
        }
        int reqLen = (int) (pt - buf);
        buf[reqLen] = '\0';
        parseRequestLine(buf, cfd);
        return 0;
    } else if (len == 0) {
        return 0;
    } else {
        perror("recv");
        return -1;
    }
}

int parseRequestLine(const char *line, socket_t cfd) {
    char method[12] = {0};
    char path[1024] = {0};
    sscanf(line, "%11[^ ] %1023[^ ]", method, path);
    printf("method: %s, path: %s\n", method, path);
    if (STR_CASE_CMP(method, "get") != 0) {
        return -1;
    }
    decodeMsg(path, path);

    char *file = NULL;
    if (strcmp(path, "/") == 0) {
        file = (char *) "./";
    } else {
        file = path + 1;
    }

    std::filesystem::path fsPath(file);
    std::error_code ec;
    if (!std::filesystem::exists(fsPath, ec)) {
        sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), -1);
        sendFile("404.html", cfd);
        return 0;
    }

    if (std::filesystem::is_directory(fsPath, ec)) {
        sendHeadMsg(cfd, 200, "OK", getFileType(".html"), -1);
        sendDir(file, cfd);
    } else {
        int fileSize = (int) std::filesystem::file_size(fsPath, ec);
        sendHeadMsg(cfd, 200, "OK", getFileType(file), fileSize);
        sendFile(file, cfd);
    }

    return 0;
}

const char *getFileType(const char *name) {
    const char *dot = strrchr(name, '.');
    if (dot == NULL)
        return "text/plain; charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp(dot, ".wav") == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}

int sendDir(const char *dirName, socket_t cfd) {
    char buf[4096] = {0};
    sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirName);
    sendAll(cfd, buf, (int) strlen(buf));

    std::error_code ec;
    for (const auto &entry : std::filesystem::directory_iterator(dirName, ec)) {
        std::string name = entry.path().filename().string();
        long long size = 0;
        bool isDir = entry.is_directory(ec);
        if (!isDir) {
            size = (long long) entry.file_size(ec);
        }

        if (isDir) {
            sprintf(buf,
                    "<tr><td><a href=\"%s/\">%s</a></td><td>%lld</td></tr>",
                    name.c_str(), name.c_str(), size);
        } else {
            sprintf(buf,
                    "<tr><td><a href=\"%s\">%s</a></td><td>%lld</td></tr>",
                    name.c_str(), name.c_str(), size);
        }
        sendAll(cfd, buf, (int) strlen(buf));
        memset(buf, 0, sizeof(buf));
    }

    sprintf(buf, "</table></body></html>");
    sendAll(cfd, buf, (int) strlen(buf));
    return 0;
}

int sendFile(const char *fileName, socket_t cfd) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        perror("open");
        return -1;
    }

    char buf[8192];
    while (file) {
        file.read(buf, sizeof buf);
        std::streamsize len = file.gcount();
        if (len > 0 && sendAll(cfd, buf, (int) len) == -1) {
            perror("send");
            return -1;
        }
    }
    return 0;
}

int sendHeadMsg(socket_t cfd, int status, const char *descr, const char *type, int length) {
    char buf[4096] = {0};
    sprintf(buf, "HTTP/1.1 %d %s\r\n", status, descr);
    sprintf(buf + strlen(buf), "Content-Type: %s\r\n", type);
    if (length >= 0) {
        sprintf(buf + strlen(buf), "Content-Length: %d\r\n", length);
    }
    sprintf(buf + strlen(buf), "Connection: close\r\n\r\n");

    sendAll(cfd, buf, (int) strlen(buf));
    return 0;
}

int hexToDec(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0;
}

void decodeMsg(char *to, char *from) {
    for (; *from != '\0'; ++to, ++from) {
        if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) {
            *to = hexToDec(from[1]) * 16 + hexToDec(from[2]);
            from += 2;
        } else {
            *to = *from;
        }
    }
    *to = '\0';
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return -1;
    }
#endif

    if (argc < 3) {
        printf("./a.out port path\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return -1;
    }

    unsigned short port = (unsigned short) atoi(argv[1]);
    if (CHDIR(argv[2]) != 0) {
        perror("chdir");
#ifdef _WIN32
        WSACleanup();
#endif
        return -1;
    }

    socket_t lfd = initListenFd(port);
    if (lfd == INVALID_SOCKET) {
#ifdef _WIN32
        WSACleanup();
#endif
        return -1;
    }

    epollRun(lfd);

    CLOSE_SOCKET(lfd);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
