//
// Created by Krisw on 2026/1/12.
//

/*
题目描述

给定一个非空字符串 S，其被 N 个’-‘分隔成 N+1 的子串，给定正整数 K，要求除第一个子串外，其余的串每 K 个用’-‘分隔，并将小写字母转换为大写。

输入描述

正整数 K 和‘-’分割的字符串，如：

2
25G3C-abc-d

输出描述

转换后的字符串

示例 1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

S = "5F3Z-2e-9-w"
K = 4
4
5F3Z-2e-9-w
输出

"5F3Z-2E9W"

解释

字符串 S 被分成了两个部分，每部分 4 个字符；

注意，两个额外的破折号需要删掉。

示例 2 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

S = "2-5g-3-J"
K = 2

2
2-5g-3-J
输出

"2-5G-3J"

解释

字符串 S 被分成了 3 个部分，按照前面的规则描述，第一部分的字符可以少于给定的数量，其余部分皆为 2 个字符。
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

vector<string> parseArray(const string &line) {
    vector<string> array;
    stringstream ss(line);
    string item;
    while (getline(ss, item, '-')) {
        array.push_back(item);
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    cin.ignore();
    string line;
    getline(cin, line);
    const auto array = parseArray(line);

    string tail;
    for (int i = 1; i < array.size(); ++i) {
        for (auto c : array[i]) {
            if (isalpha(c)) tail.push_back(toupper(c));
            else tail.push_back(c);
        }
    }

    string ans = array[0];
    if (!tail.empty()) {
        ans.push_back('-');
        for (int i = 0; i < tail.size(); ++i) {
            if (i > 0 && i % K == 0) ans.push_back('-');
            ans.push_back(tail[i]);
        }
    }

    cout << ans << endl;
    return 0;
}
