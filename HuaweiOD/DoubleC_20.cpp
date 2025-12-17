//
// Created by Krisw on 2025/12/14.
//

/*
给定一组朋友关系，统计一下该朋友关系网中的朋友圈个数。

朋友圈的定义:一个朋友圈至少由3个朋友组成，且要求同一个朋友圈中的任意两个人都具有直接的朋友关系。
输入描述
输入一个朋友关系列表，如 Fiends =[A.B],[A.C],[B,D]，其中的每一个元素 Friendsi表示 Friends[i][0]和 Friends [i][1] 是朋友关系 先输入一个数字 N 代表关系的总数，后面每条关系一行，两个成员以逗号分隔
输出描述
输出一个整数，表示整个关系网中朋友圈的个数
补充
1：Friends.length>=1，Friends.length<= 10^3
2：输入的总朋友个数<= 100
3：输入保证 Friend[i][0]和 Friend[i][1]一定不一样，且同一关系不会反向输入，即不会同时输入[A,B] 和 [B,A]。

4：不考虑子朋友圈，即当发现 [A,B,C,D]组成一个朋友圈时，[A,B,C]、[A,B,D]等子朋友圈不单独计数

示例1：

输入：

3
A,B
A,C
B,D

输出：

0

示例2：

输入：

7
A,B
A,C
B,C
A,D
D,E
B,D
A,E


输出：

3

示例3：

输入：

6
A,B
A,C
B,C
A,D
B,D
D,C

输出：

1
*/

#include <bits/stdc++.h>
using namespace std;

static const int MAXV = 105;

int V = 0;
vector<bitset<MAXV>> adj;
long long ans = 0;

int choosePivot(const bitset<MAXV>& P, const bitset<MAXV>& X) {
    bitset<MAXV> U = P | X;
    int best = -1;
    size_t bestCnt = 0;
    for (int u = 0; u < V; u++) {
        if (!U.test(u)) continue;
        size_t cnt = (P & adj[u]).count();
        if (best == -1 || cnt > bestCnt) {
            best = u;
            bestCnt = cnt;
        }
    }
    return best; // if best==-1, caller will handle
}

void bronKerbosch(bitset<MAXV> R, bitset<MAXV> P, bitset<MAXV> X) {
    if (P.none() && X.none()) {
        if (R.count() >= 3) ans++;
        return;
    }

    int u = choosePivot(P, X);
    bitset<MAXV> candidates;
    if (u == -1) {
        candidates = P;
    } else {
        candidates = P & (~adj[u]); // P \ N(u)
    }

    for (int v = 0; v < V; v++) {
        if (!candidates.test(v)) continue;

        bitset<MAXV> R2 = R; R2.set(v);
        bitset<MAXV> P2 = P & adj[v];
        bitset<MAXV> X2 = X & adj[v];

        bronKerbosch(R2, P2, X2);

        P.reset(v);
        X.set(v);
    }
}

static inline string trim(string s) {
    size_t l = 0, r = s.size();
    while (l < r && isspace((unsigned char)s[l])) l++;
    while (r > l && isspace((unsigned char)s[r - 1])) r--;
    return s.substr(l, r - l);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    string line;
    getline(cin, line); // consume endline

    unordered_map<string, int> id;
    vector<pair<int,int>> edges;
    edges.reserve(N);

    auto getId = [&](const string& name) -> int {
        auto it = id.find(name);
        if (it != id.end()) return it->second;
        int idx = (int)id.size();
        id[name] = idx;
        return idx;
    };

    for (int i = 0; i < N; i++) {
        getline(cin, line);
        line = trim(line);
        if (line.empty()) { i--; continue; }

        auto pos = line.find(',');
        if (pos == string::npos) continue; // defensive
        string a = trim(line.substr(0, pos));
        string b = trim(line.substr(pos + 1));

        int u = getId(a);
        int v = getId(b);
        edges.push_back({u, v});
    }

    V = (int)id.size();
    adj.assign(V, bitset<MAXV>());

    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (u == v) continue;
        adj[u].set(v);
        adj[v].set(u);
    }

    bitset<MAXV> R, P, X;
    for (int i = 0; i < V; i++) P.set(i);

    bronKerbosch(R, P, X);

    cout << ans << "\n";
    return 0;
}
