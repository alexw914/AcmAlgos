//
// Created by Krisw on 2025/12/6.
//

/*
在一个采购系统中，采购申请(PR)需要经过审批后才能生成采购订单(PO)。每个PR包含商品的单价(假设相同商品的单价一定是一样的)及数量信息。
系统要求对商品进行分类处理:单价高于100元的商品需要单独处理，单价低于或等于100元的相同商品可以合并到同一采购订单PO中。
针对单价低于100的小额订单，如果量大可以打折购买。
具体规则如下:
如果PR状态为"审批通过"，则将其商品加入到PO中。如果PR的状态为"审批拒绝"或"待审批"，则忽略改PR,对于单价高于100元的商品、
每个商品单独生成一条PO记录。对于单价低于100元的商品，将相同商品的数量合并到一条PO记录中。如果商品单价<100且商品数量>=100，则单价打9折。
输入描述
第一行包含整数N，表示PR的数量。
接下来N行，每行包含四个用空格分割的整数，按顺序表示:商品ID,数量，单价，PR状态(0表示审批通过，1表示审批拒绝，2表示待审批)
输出描述
输出若干行，每行表示一条PO记录，按以下格式输出:
对于单价高于100元的商品:商品ID 数量 单价
对于单价低于或等于100元的商品:商品ID 总数量 打折后的单价(向上取整)输出的PO记录按商品ID升序升序排列，相同商品按照数量降序排列
补充
2<=n<= 1000
1<= 商品价格 <= 200
1 <= 商品数量 <= 1000
2<= 商品编号 <= 1000

示例1：

输入

2
1 200 90 0
2 30 101 0


输出

1 200 81
2 30 101


说明：

商品1的原始单价为90，审批通过，生成一条PO，满足打折条件，打折后单价为81。商品2的单价为101，审批通过，生成一条PO

示例2：

输入

3
1 10 90 0
1 5 90 0
2 8 120 0


输出

1 15 90
2 8 120


说明：

PR1和PR2均为商品1，单价90，审批通过，单价低于100元，合并数量为150.PR3为商品2，单价120元，审批通过，单价高于100元，单独生成一条PO记录

示例3：

输入

4
1 5 80 0
2 3 120 0
3 2 90 1
4 10 150 2


输出

1 5 80
2 3 120


说明：

PR1:商品1，单价80元，审批通过，单价低于100元，合并到PO中。

PR2:商品2，单价120元，审批通过，单价高于100元，单独生成一条PO记录。PR3:审批拒绝，忽略。PR4待审批忽略。
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    unordered_map<int, pair<int, int>> lowPoMap;
    vector<vector<int>> highPo;
    while (n--) {
        int id, num, price, state;
        cin >> id >> num >> price >> state;
        if (state == 1 || state == 2) { continue; }
        if (price >= 100) { highPo.push_back({id, num, price}); }
        else {
            if (lowPoMap.count(id)) {
                lowPoMap[id].first += num;
            } else {
                lowPoMap[id] = {num, price};
            }
        }
    }

    // 处理低价商品，打折后生成 PO
    vector<vector<int> > finalPo;
    for (auto [id, value]: lowPoMap) {
        int num = value.first;
        int price = value.second;
        if (num >= 100) {
            price = (price * 9 + 9) / 10;
        }
        finalPo.push_back({id, num, price});
    }

    finalPo.insert(finalPo.end(), highPo.begin(), highPo.end());
    sort(finalPo.begin(), finalPo.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });

    for (auto &l: finalPo) {
        cout << l[0] << " " << l[1] << " " << l[2] << endl;
    }

    return 0;
}
