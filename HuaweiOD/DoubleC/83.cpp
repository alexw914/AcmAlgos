//
// Created by Krisw on 2026/1/12.
//

/*
给定一个字符串的摘要算法，请输出给定字符串的摘要值
1、去除字符串中非字母的符号
2、如果出现连续字符 (不区分大小写) ，则输出: 该字符 (小) + 连续出现的次数
3、如果是非连续的字符(不区分大小写) ，则输出: 该字符(小写) 该字母之后字符串中出现的该字符的次数
4、对按照以上方式表示后的字符串进行排序: 字母和紧随的数字作为一组进行排序，数字大的在前，数字相同的则按字母进行排序，字母小的在前。
输入描述:
行字符串，长度为[1,200]

输出描述:
摘要字符串
示例1
输入:
aabbcc
输出:
a2b2c2
示例2
输入:
bAaAcBb
输出:
a3b2b2c0
说明:
第一个b非连续字母，该字母之后字符串中还出现了2次 (最后的两个Bb) ，所以输出b2a连续出现3次，输出a3，
c非连续，该字母之后字符串再没有出现过c，输出c0Bb连续2次，输出b2
对b2a3c0b2进行排序，最终输出a3b2b2c0
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

struct Info {
    char c;
    int n;
};

string run(string &line) {
    vector<Info> infos;
    string ans;
    const int N = line.size();
    int i = 0, j = 0;
    unordered_map<char, int> mp;
    while (j < N && i < N) {
        auto c = line[i];
        int num = 0;
        while (j < N && line[j] == c ) {
            j++;
            num++;
        }
        if (num == 1) {
            if (mp.count(c) == 0) {
                mp[c] = 0;
            }
            else {
                mp[c]++;
            }
        } else {
            infos.push_back({c, num});
            if (mp.count(c)) {
                mp[c] += num;
            }
        }
        i = j;
    }
    for (auto &[k,v]: mp) {
        infos.push_back({k, v});
    }
    sort(infos.begin(), infos.end(), [](Info& a, Info&b) {
        if (a.n != b.n) { return a.n > b.n; }
        else { return a.c < b.c; }
    });
    for (auto& info: infos) {
        ans.push_back(info.c);
        ans += to_string(info.n);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    string s;
    for (const auto ch : line) {
        if (isalpha(ch)) s.push_back(tolower(ch));
    }
    cout << run(s) << endl;
    return 0;
}
