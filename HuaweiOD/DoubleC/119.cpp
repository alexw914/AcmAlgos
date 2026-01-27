//
// Created by Krisw on 2026/1/18.
//

/*
某购物城有m个商铺，现决定举办一场活动选出人气最高店铺。活动共有n位市民参与，每位市民只能投一票，但1号店铺如果给该市民发放q元的购物补贴，该市民会改为投1号店铺。
请计算1号店铺需要最少发放多少元购物补贴才能成为人气最高店铺(即获得的票数要大于其他店铺)，如果1号店铺本身就是票数最高店铺，返回0。
输入描述:
第一行为小写逗号分割的两个整数n，m，其中第一个整数n表示参与的市民总数，第二个整数m代表店铺总数，1<= n, m <= 3000.
第2到n+1行，每行为小写逗号分割的两个整数p，q，表示市民的意向投票情况，其中每行的第一个整数p表示该市民意向投票给p号店铺，第二个整数q表示其改投1号店铺所需给予的q元购物补贴，1 <= p <= m,1<= q <= 10^9.不考虑输入的格式问题
输出描述
1号店铺需要最少发放购物补贴金额。

示例1
输入:
5,5
2,10
3,20
4,30
5,40
5,90
输出:
50
说明:
有5个人参与，共5个店铺。
如果选择发放 10元+20元+30元=60元 的补贴来抢2.3.4号店铺的票，总共发放了60元补贴

(5号店铺有2票，1号店铺要3票才能胜出)

如果选择发放 10元+40元=50元 的补贴来抢2.5号店铺的票，总共发放了50元补贴

(抢了5号店铺的票后，现在1号店铺只要2票就能胜出)

所以最少发放50元补贴

示例2
输入:
5,5
2,10
3,20
4,30
5,80
5,90
输出:
60
说明:
有5个人参与，共5个店铺.
如果选择发放 10元+20元+30元=60元 的补贴来抢2.3.4号店铺的票，总共发放了60元补贴(5号店铺有2票，1号店铺要3票才能胜出)

如果选择发放 10元+80元=90元 的补贴来抢2,5号店铺的票，总共发放了90元补贴(抢了5号店铺的票后，现在1号店铺只要2票就能胜出)所以最少发放60元补贴
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
using LL = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    char c;
    cin >> n >> c >> m;

    vector<vector<int>> cost(m + 1);
    vector<int> cnt(m + 1, 0);

    for (int i = 0; i < n; ++i) {
        int p; LL q;
        cin >> p >> c >> q;
        cnt[p]++;
        if (p != 1) cost[p].push_back(q);
    }

    int cnt1 = cnt[1];
    int mx = 0;
    for (int i = 2; i <= m; ++i)
        mx = max(mx, cnt[i]);

    if (cnt1 > mx) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 2; i <= m; ++i)
        sort(cost[i].begin(), cost[i].end());

    LL ans = LLONG_MAX;

    for (int T = 0; T < mx; ++T) {
        LL base_cost = 0;
        int base_taken = 0;

        vector<LL> rest;

        for (int i = 2; i <= m; ++i) {
            int need = max(0, cnt[i] - T);
            for (int j = 0; j < cost[i].size(); ++j) {
                if (j < need) {
                    base_cost += cost[i][j];
                    base_taken++;
                } else {
                    rest.push_back(cost[i][j]);
                }
            }
        }

        int cur1 = cnt1 + base_taken;
        if (cur1 > T) {
            ans = min(ans, base_cost);
            continue;
        }

        int extra = T - cur1 + 1;
        if (rest.size() < extra) continue;

        nth_element(rest.begin(), rest.begin() + extra, rest.end());
        sort(rest.begin(), rest.begin() + extra);

        LL extra_cost = 0;
        for (int i = 0; i < extra; ++i) extra_cost += rest[i];

        ans = min(ans, base_cost + extra_cost);
    }

    cout << ans << '\n';
    return 0;
}

/*
贪心策略
按店铺分组所有选民：

对每个店铺 i (i ≠ 1)，收集它的选民补贴成本列表 costs[i] 并排序。

枚举目标最大对手票数 T

让最终所有其他店铺票数 ≤ T

T 从 0 到 mx-1 枚举。

对于某个 T：

对于每个店铺 i：

如果 cnt[i] > T

必须强制收买 cnt[i] - T 个最便宜的选民

记：

base_cost = 所有强制收买的费用之和
base_taken = 总收买人数


剩余可选选民：所有未被强制收买的市民

我们还需要：

cnt1 + base_taken + extra > T


即：

extra ≥ T - (cnt1 + base_taken) + 1


从剩余选民中选择 extra 个最便宜的即可。
*/
