//
// Created by Krisw on 2025/12/21.
//

/*
在一个网络文件存储系统中，有众多的文件按照不同的文件夹进行分类存储。现在要对这些文件进行整理排序，以便便于快速地查找特定文件。
每个文件都有一个创建的时间戳(用整数标识，代表从特定时刻到文件创建时所经历的秒数)，并且文件夹之间存在层级关系。
现要求实现一个函数，对给定地某个文件夹下的所有文件(包含子文件夹中的文件)按照创建时间戳进行排序，可采用你熟悉的排序算法。

输入描述
首先输入一个整数n，表示接下来要输入的文件及文件夹信息的行数。
然后输入一指定文件夹的名称，用于说明获取哪个文件夹下的全部文件，并进行排序;
最后逐行输入文件或文件夹信息，行数为第一句输入的整数n。
对于文件，每行格式为:文件名 创建时间戳;对于文件夹，每行格式为:文件夹名 -1(-1表示这是一个文件夹)。
如果文件夹包含子文件或子文件夹，则在后序行中继续输入其内。
通过缩进(四个短横线)表示层级关系(例如，子文件或子文件的信息相比其父文件夹缩进4个短线)。
示例
5
Documents
Documents -1
----file1.txt 1600000000
----file2.txt 1600000100
----SubFolder1 -1
--------file3.txt 1600002000
输出描述
输出排序后的文件列表，每行格式为:文件名 创建时间戳口，按照时间截从小到大进行排序
补充说明:文件和文件夹名称只会出现 A-Z  a-z 0-9和字符. 。不会出现特殊字符。不会出现相同时间戳的文件，不会出现重名的文件或文件夹。
如果文件系统中不存在该文件，则返回字符串"No file"

示例1

输入：

5
Documents
Documents -1
----file1.txt 1600000000
----file2.txt 1600000100
----SubFolder1 -1
--------file3.txt 1600002000

输出：

fiel1.txt 1600000000
fiel2.txt 1600000100
fiel3.txt 1600002000

示例2

输入：

5
Video
Video -1
----SubFolder0 -1
----SubFolder1 -1
----SubFolder3 -1
--------SubFolder4 -1

输出：

No file
*/

#include <bits/stdc++.h>
using namespace std;

struct Item {
    string name;
    long long ts;
};

static int getLevel(const string& line) {
    int i = 0;
    while (i < (int)line.size() && line[i] == '-') i++;
    return i / 4; // 4个短横线一个层级
}

static string getContent(const string& line) {
    int i = 0;
    while (i < (int)line.size() && line[i] == '-') i++;
    // 去掉前导短横线后 trim
    int l = i, r = (int)line.size() - 1;
    while (l <= r && isspace((unsigned char)line[l])) l++;
    while (r >= l && isspace((unsigned char)line[r])) r--;
    if (l > r) return "";
    return line.substr(l, r - l + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string target;
    cin >> target;
    string dummy;
    getline(cin, dummy); // 吃掉行尾换行

    vector<string> lines;
    lines.reserve(n);
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        lines.push_back(line);
    }

    // 先判断 target 文件夹是否存在（作为文件夹出现过）
    bool exists = false;
    vector<string> st; // 当前路径文件夹栈
    st.reserve(64);

    for (const auto& line : lines) {
        int level = getLevel(line);
        string content = getContent(line);
        if (content.empty()) continue;

        // content 格式：name value
        // 名称不会含空格，所以用 stringstream 安全
        string name, val;
        {
            stringstream ss(content);
            ss >> name >> val;
            if (name.empty() || val.empty()) continue;
        }

        while ((int)st.size() > level) st.pop_back();

        if (val == "-1") {
            st.push_back(name);
            if (name == target) exists = true;
        }
    }

    // 收集 target 子树下文件
    vector<Item> files;
    st.clear();

    for (const auto& line : lines) {
        int level = getLevel(line);
        string content = getContent(line);
        if (content.empty()) continue;

        string name, val;
        {
            stringstream ss(content);
            ss >> name >> val;
            if (name.empty() || val.empty()) continue;
        }

        while ((int)st.size() > level) st.pop_back();

        if (val == "-1") {
            st.push_back(name);
        } else {
            // 当前文件属于 st 路径下；只要路径中出现 target，就算在其子树
            bool inTarget = false;
            for (const auto& folder : st) {
                if (folder == target) { inTarget = true; break; }
            }
            if (inTarget) {
                long long ts = stoll(val);
                files.push_back({name, ts});
            }
        }
    }

    if (!exists || files.empty()) {
        cout << "No file";
        return 0;
    }

    sort(files.begin(), files.end(), [](const Item& a, const Item& b) {
        return a.ts < b.ts;
    });

    for (const auto& f : files) {
        cout << f.name << " " << f.ts << "\n";
    }
    return 0;
}
