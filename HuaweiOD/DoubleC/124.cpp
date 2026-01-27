//
// Created by Krisw on 2026/1/24.
//

/*

题目描述
有N个快递站点用字符串标识，某些站点之间有道路连接。
每个站点有一些包裹要运输，每个站点间的包裹不重复，路上有检查站会导致部分货物无法通行，计算哪些货物无法正常投递?
输入描述
1、第一行输入M N，M个包裹N个道路信息
2、0<=M.N<=100
3、检查站禁止通行的包裹如果有多个以空格分开
输出描述
输出不能送达的包裹，如: package2 package4
如果所有包惠都可以送达则输出: none,
输出结果按照升序排列

示例1：
4 2
package1 A C
package2 A C
package3 B C

package4 A C

A B package1

A C package2
输出
package2

说明

4个包裹，2个禁止通行信息。

接下来的4行是每个包裹的名称, 起点, 终点。

最后2行是两个站点之间无法通行的包裹名称。

 */

#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Package {
    string name;
    string from;
    string to;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<Package> packages(M);

    for (int i = 0; i < M; ++i) {
        cin >> packages[i].name >> packages[i].from >> packages[i].to;
    }

    set<string> blocked;

    for (int i = 0; i < N; ++i) {
        string a, b, pkg;
        cin >> a >> b >> pkg;

        for (auto &p : packages) {
            if (p.name == pkg && p.from == a && p.to == b) {
                blocked.insert(pkg);
            }
        }
    }

    if (blocked.empty()) {
        cout << "none";
        return 0;
    }

    bool first = true;
    for (auto &name : blocked) {
        if (!first) cout << " ";
        cout << name;
        first = false;
    }

    return 0;
}
