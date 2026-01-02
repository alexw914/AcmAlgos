//
// Created by Krisw on 2026/1/1.
//

/*
企业路由器的统计页面，有一个功能需要动态统计公司访问最多的网页URL top N。请设计一个算法，可以高效动态统计Top N的页面。

输入描述

每一行都是一个URL或一个数字，如果是URL，代表一段时间内的网页访问；
如果是一个数字N，代表本次需要输出的Top N个URL。

输入约束

1、总访问网页数量小于5000个，单网页访问次数小于65535次；
2、网页URL仅由字母，数字和点分隔符组成，且长度小于等于127字节；
3、数字是正整数，小于等于10且小于当前总访问网页数；

输出描述

每行输入要对应一行输出，输出按访问次数排序的前N个URL，用逗号分隔。

输出要求

1、每次输出要统计之前所有输入，不仅是本次输入；
2、如果有访问次数相等的URL，按URL的字符串字典序升序排列，输出排序靠前的URL；

示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

news.qq.com
news.sina.com.cn
news.qq.com
news.qq.com
game.163.com
game.163.com
www.huawei.com
www.cctv.com
3
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
3

输出

news.qq.com,game.163.com,news.sina.com.cn
www.huawei.com,www.cctv.com,news.qq.com

示例2   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

news.qq.com
www.cctv.com
1
www.huawei.com
www.huawei.com
2
3

输出

news.qq.com
www.huawei.com,news.qq.com
www.huawei.com,news.qq.com,www.cctv.com
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Info {
    string line;
    int cnt;
};

bool isNumber(const string &s) {
    if (s.empty()) return false;
    for (const char c: s) { if (!isdigit(static_cast<unsigned char>(c))) return false; }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    map<string, int> mp;

    while (getline(cin, line)) {
        if (line.empty()) { continue; }

        if (isNumber(line)) {
            int x = stoi(line);

            vector<Info> infos;
            infos.reserve(mp.size());
            for (auto &[k, v]: mp) { infos.push_back({k, v}); }

            sort(infos.begin(), infos.end(), [](const Info &a, const Info &b) {
                if (a.cnt != b.cnt) { return a.cnt > b.cnt; }
                return a.line < b.line; // 字典序升序
            });

            int limit = min(x, static_cast<int>(infos.size()));
            for (int i = 0; i < limit; ++i) {
                cout << infos[i].line;
                if (i != limit - 1) cout << ",";
            }
            cout << '\n';
        } else {
            mp[line]++;
        }
    }

    return 0;
}
