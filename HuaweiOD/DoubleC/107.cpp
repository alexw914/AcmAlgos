//
// Created by Krisw on 2026/1/17.
//

/*
实现一个支持优先级的队列，高优先级先出队列，同优先级时先进先出。

如果两个输入数据和优先级都相同，则后一个数据不入队列被丢弃。

队列存储的数据内容是一个整数。

输入描述
一组待存入队列的数据（包含内容和优先级）。

输出描述
队列的数据内容（优先级信息输出时不再体现）。

补充说明
不用考虑数据不合法的情况，测试数据不超过100个。
示例1
输入:
(10,1),(20,1),(30,2),(40,3)
输出:
40,30,10,20
说明:
输入样例中，向队列写入了4个数据，每个数据由数据内容和优先级组成。输入和输出内容都不含空格。数据40的优先级最高，所以最先输出，其次是30:10和20优先级相同，所以按输入顺序输出
示例2
输入:
(10,1),(10,1),(30,2),(40,3)
输出:
40,30,10

说明:
输入样例中，向队列写入了4个数据，每个数据由数据内容和优先级组成输入和输出内容都不含空格。
数据40的优先级最高，所以最先输出，其次是30;两个10和10构成重复数据，被丢弃一个。
*/

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <unordered_set>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int,int>& p) const noexcept {
        return (static_cast<size_t>(p.first) << 32) ^ static_cast<unsigned int>(p.second);
    }
};

vector<pair<int,int>> parseArray(const string& line) {
    stringstream ss(line);
    string item;
    vector<pair<int,int>> array;

    // 输入形如: (10,1),(20,1),(30,2)
    // 按逗号分割会把 "(10" 和 "1)" 拆开，原实现会出错。
    // 这里用更稳健的解析：扫描括号对。
    for (int i = 0; i < line.size(); ) {
        if (line[i] != '(') { i++; continue; }
        int j = i;
        while (j < line.size() && line[j] != ')') j++;
        string inside = line.substr(i + 1, j - i - 1); // "10,1"
        auto comma = inside.find(',');
        int x = stoi(inside.substr(0, comma));
        int y = stoi(inside.substr(comma + 1));
        array.push_back({x, y});
        i = j + 1;
    }
    return array;
}

struct Node {
    int pri;
    int seq;   // 越小越早入队
    int val;
};

// 最大优先级先出；同优先级 seq 小的先出（FIFO）
struct Cmp {
    bool operator()(const Node& a, const Node& b) const {
        if (a.pri != b.pri) return a.pri < b.pri;     // pri 大的优先
        return a.seq > b.seq;                         // seq 小的优先
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    auto arr = parseArray(line);

    priority_queue<Node, vector<Node>, Cmp> pq;

    // 去重：如果(value, priority)完全相同且之前已入队，则丢弃
    unordered_set<pair<int,int>, PairHash> seen;

    int seq = 0;
    for (auto [val, pri] : arr) {
        pair<int,int> key{val, pri};
        if (seen.count(key)) continue;
        seen.insert(key);
        pq.push(Node{pri, seq++, val});
    }

    bool first = true;
    while (!pq.empty()) {
        auto cur = pq.top(); // priority_queue 取 top()
        pq.pop();
        if (!first) cout << ",";
        first = false;
        cout << cur.val;
    }
    cout << "\n";
    return 0;
}