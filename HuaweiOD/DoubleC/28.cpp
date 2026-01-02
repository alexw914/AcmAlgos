//
// Created by Krisw on 2025/12/18.
//

/*
实现一个模拟目录管理功能的软件，输入一个命令序列，输出最后一条命令运行结果。 支持命令:
1)创建目录命令: mkdir 目录名称，如mkdir abc为在当前目录创建abc目录，如果已存在同名目录则不执行任何操作。此命令无输出。
2)进入目录命令: cd 目录名称,如cd abc为进入abc目录，特别地，cd ..为返回上级目录，如果目录不存在则不执行任何操作。此命令无输出。
3)查看当前所在路径命令: pwd，输出当前路径字符串

约束: 1)目录名称仅支持小写字母;mkdir和cd命令的参数仅支持单个目录，如: mkdir bc和cd abc;
不支持嵌套路径和绝对路径，如mkdir abc/efg,cd abc/efg,mkdir /abc/efg, cd /abc/efg是不支持的。

2)目录符号为/，根目录/作为初始目录。

输入描述
输入N行字符串，每一行字符串是一条命令。

输出描述
输出最后一条命令运行结果字符串

示例1
输入:
mkdir abc
cd abc
pwd

输出:
/abc/

说明:
在根目录创建一个abc的目录并进入abc目录中查看当前目录路径，输出当前路径/abc/。
AI写代码

备注

命令行数限制100行以内，目录名称限制10个字符以内。
*/

#include <bits/stdc++.h>
using namespace std;

static bool validDirName(const string &s) {
    if (s.empty() || s.size() > 10) return false;
    for (char c : s) {
        if (c < 'a' || c > 'z') return false; // 只允许小写字母
    }
    return true;
}

static string curPathStr(const vector<string> &cur) {
    string path = "/";
    for (auto &x : cur) path += x + "/";
    return path;
}

int main() {
    string line;
    unordered_map<string, unordered_set<string>> dir; // 路径 -> 子目录集合
    vector<string> cur; // 当前路径（不含根）
    string lastPwd;     // 最后一次 pwd 输出（题目只输出最后一条命令的结果）

    while (getline(cin, line)) {
        if (line.empty()) continue;

        // 用 stringstream 更稳妥解析，避免多空格
        string cmd, arg;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "mkdir") {
            ss >> arg;
            // 非法：没有参数 / 多余参数 / 参数不合法（含'/'、非小写等）
            string extra;
            if (arg.empty() || (ss >> extra)) continue;
            if (arg.find('/') != string::npos) continue; // 不支持 abc/efg 或 /abc
            if (!validDirName(arg)) continue;

            string path = curPathStr(cur);
            dir[path].insert(arg); // 已存在同名目录则不变（set天然忽略重复）
        }
        else if (cmd == "cd") {
            ss >> arg;
            string extra;
            if (arg.empty() || (ss >> extra)) continue;

            if (arg == "..") {
                if (!cur.empty()) cur.pop_back(); // 根目录不能再退
            } else {
                if (arg.find('/') != string::npos) continue;
                if (!validDirName(arg)) continue;

                string path = curPathStr(cur);
                if (dir[path].count(arg)) {
                    cur.push_back(arg); // 存在才进入
                }
            }
        }
        else if (cmd == "pwd") {
            // pwd 不应带参数（带了就当非法命令，直接忽略）
            string extra;
            if (ss >> extra) continue;

            lastPwd = curPathStr(cur);
        }
        // 其他未知命令：忽略
    }

    if (!lastPwd.empty()) cout << lastPwd << "\n";
    return 0;
}
