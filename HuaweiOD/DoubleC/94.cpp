//
// Created by Krisw on 2026/1/16.
//

/*
题目描述

某公司研发了一款高性能AI处理器。每台物理设备具备8颗AI处理器，编号分别为0、1、2、3、4、5、6、7。

编号0-3的处理器处于同一个链路中，编号4-7的处理器处于另外一个链路中，不同链路中的处理器不能通信。

现给定服务器可用的处理器编号数组array，以及任务申请的处理器数量num，找出符合下列亲和性调度原则的芯片组合。

如果不存在符合要求的组合，则返回空列表。

亲和性调度原则：

-如果申请处理器个数为1，则选择同一链路，剩余可用的处理器数量为1个的最佳，其次是剩余3个的为次佳，然后是剩余2个，最后是剩余4个。

-如果申请处理器个数为2，则选择同一链路剩余可用的处理器数量2个的为最佳，其次是剩余4个，最后是剩余3个。

-如果申请处理器个数为4，则必须选择同一链路剩余可用的处理器数量为4个。

-如果申请处理器个数为8，则申请节点所有8个处理器。

提示：

任务申请的处理器数量只能是1、2、4、8。
编号0-3的处理器处于一个链路，编号4-7的处理器处于另外一个链路。
处理器编号唯一，且不存在相同编号处理器。
输入描述

输入包含可用的处理器编号数组array，以及任务申请的处理器数量num两个部分。

第一行为array，第二行为num。例如：

[0, 1, 4, 5, 6, 7]

表示当前编号为0、1、4、5、6、7的处理器可用。任务申请1个处理器。

0 <= array.length <= 8

0 <= array[i] <= 7

num in [1, 2, 4, 8]

输出描述

输出为组合列表，当array=[0，1，4，5，6，7]，num=1 时，输出为[[0], [1]]。

示例1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

[0, 1, 4, 5, 6, 7]

1

输出

[[0], [1]]

说明

根据第一条亲和性调度原则，在剩余两个处理器的链路（0, 1, 2, 3）中选择处理器。

由于只有0和1可用，则返回任意一颗处理器即可。
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
using namespace std;

vector<int> parseArray(const string &line) {
    vector<int> res;
    string s = line.substr(1, line.size() - 2);
    stringstream ss(s);
    string item;
    while (getline(ss, item, ',')) {
        res.push_back(stoi(item));
    }
    return res;
}

vector<vector<int>> combinations(vector<int>& nums, int k) {
    vector<vector<int>> res;
    vector<int> path;

    function<void(int)> dfs = [&](int idx) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }
        for (int i = idx; i < nums.size(); i++) {
            path.push_back(nums[i]);
            dfs(i + 1);
            path.pop_back();
        }
    };

    dfs(0);
    return res;
}

int priority_score(int remain, int num) {
    if (num == 1) {
        if (remain == 1) return 4;
        if (remain == 3) return 3;
        if (remain == 2) return 2;
        if (remain == 4) return 1;
    }
    if (num == 2) {
        if (remain == 2) return 3;
        if (remain == 4) return 2;
        if (remain == 3) return 1;
    }
    if (num == 4) {
        if (remain == 4) return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    vector<int> array = parseArray(line);

    int num;
    cin >> num;

    vector<int> linkA, linkB;
    for (int x : array) {
        if (x <= 3) linkA.push_back(x);
        else linkB.push_back(x);
    }

    // num = 8 特殊处理
    if (num == 8) {
        if (array.size() == 8) {
            cout << "[[";
            for (int i = 0; i < 8; i++) {
                if (i) cout << ",";
                cout << i;
            }
            cout << "]]\n";
        } else {
            cout << "[]\n";
        }
        return 0;
    }

    struct Link {
        vector<int>* v;
        int remain;
        int score;
    };

    vector<Link> links;

    if (linkA.size() >= num) {
        links.push_back({&linkA, 4 - (int)linkA.size(), priority_score(4 - linkA.size(), num)});
    }
    if (linkB.size() >= num) {
        links.push_back({&linkB, 4 - (int)linkB.size(), priority_score(4 - linkB.size(), num)});
    }

    int bestScore = 0;
    for (auto& l : links) bestScore = max(bestScore, l.score);

    if (bestScore == 0) {
        cout << "[]\n";
        return 0;
    }

    vector<vector<int>> result;

    for (auto& l : links) {
        if (l.score == bestScore) {
            auto comb = combinations(*l.v, num);
            result.insert(result.end(), comb.begin(), comb.end());
        }
    }

    // 输出
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        if (i) cout << ",";
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            if (j) cout << ",";
            cout << result[i][j];
        }
        cout << "]";
    }
    cout << "]\n";

    return 0;
}