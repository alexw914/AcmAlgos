//
// Created by Krisw on 2026/1/17.
//

/*
有 M(1<=M<=10) 个端口组
每个端口组是长度为 N(1<=N<=100)的整数数组，如果端口组间存在2个及以上不同端口相同，则认为这2个端口组 互相关联，可以合并
第一行输入端口组个数M，再输入M行，每行逗号分隔，代表端口组。输出合并后的端口组，用二维数组表示
输入描述
第一行输入一个数字M
第二行开始输入M行，每行是长度为N的整数数组，用逗号分割

输出描述
合并后的二维数组，用二维数组表示

1：组合内同端口仅保留一个，并从小到大排序。

2：组合外顺序保持输入顺序。

示例1：

输入：

4
4
2,3,2
1,2
5

输出：

[[4],[2,3],[1,2],[5]]

示例2：

输入：

3
2,3,1
4,3,2
5

输出：

[[1,2,3,4],[5]]

示例3：

输入：

6
10
4,2,1
9
3,6,9,2
6,3,4
8

输出：

[[10],[1,2,3,4,6,9],[9],[8]]
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> parseArray(const std::string &line, char delim) {
    stringstream ss(line);
    vector<int> array;
    string item;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}

/******** 并查集 ********/
struct DSU {
    vector<int> p;
    explicit DSU(const int n): p(n) { iota(p.begin(), p.end(), 0); }

    int find(const int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    void unite(const int x, const int y) {
        int px = find(x), py = find(y);
        if (px != py) p[py] = px;
    }
};

/******** 判断交集是否 >= 2 ********/
bool intersectAtLeast2(const vector<int>& a, const vector<int>& b) {
    int i = 0, j = 0, cnt = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            cnt++;
            if (cnt >= 2) return true;
            i++; j++;
        } else if (a[i] < b[j]) i++;
        else j++;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;
    cin.ignore();

    vector<vector<int>> port_group(M);

    // 读入并去重排序
    for (int i = 0; i < M; i++) {
        string line;
        getline(cin, line);
        auto v = parseArray(line, ',');
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        port_group[i] = v;
    }

    // 并查集
    DSU dsu(M);

    // 两两检查是否需要合并
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            if (intersectAtLeast2(port_group[i], port_group[j])) {
                dsu.unite(i, j);
            }
        }
    }

    // 按输入顺序收集连通分量
    unordered_map<int, vector<int>> merged;
    vector<int> order;

    for (int i = 0; i < M; i++) {
        int root = dsu.find(i);
        if (!merged.count(root)) order.push_back(root);
        merged[root].insert(
            merged[root].end(),
            port_group[i].begin(),
            port_group[i].end()
        );
    }

    // 输出
    cout << "[";
    bool firstGroup = true;
    for (int root : order) {
        auto &v = merged[root];
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        if (!firstGroup) cout << ",";
        firstGroup = false;

        cout << "[";
        for (int i = 0; i < v.size(); i++) {
            if (i) cout << ",";
            cout << v[i];
        }
        cout << "]";
    }
    cout << "]\n";

    return 0;
}