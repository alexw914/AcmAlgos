//
// Created by 巫妖王 on 2026/1/19.
//

/*
题目描述
给定一些短词字符串作为分割词，去分割一段长字符串。从前往后遍历分割词，查找并分割长字符串为对应的token。分词规则如下:
1.优先匹配最长分割词:若多个分割词可匹配同一位置，选择长度最长的;长度相同时，按字典序较大的优先。
2.未匹配部分保留原样:无法匹配分割词的部分直接作为独立token输出。
3.输出格式:每个token用括号包裹，按原字符串顺序输出。


输入描述:
短词字符串列表，每行一个，空行后输入待分割的长字符串。

输出描述:
括号包裹的分词结果，如(token1)(token2)


示例1:
输入:

zhong guo
zhong
guo
wo
mei guo

wo ai zhong guo mei guo ye xing

输出：

(wo)(ai)(zhong guo)(mei guo)(ye)(xing)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

static vector<string> split_by_space(const string& s) {
    vector<string> out;
    istringstream iss(s);
    string w;
    while (iss >> w) out.push_back(w); // 自动跳过连续空格
    return out;
}

static string join_with_space(const vector<string>& v) {
    string res;
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) res.push_back(' ');
        res += v[i];
    }
    return res;
}

struct Pattern {
    vector<string> w;  // 词元序列
    string raw;        // 原始串（规范化为单空格连接）
    int raw_len;       // raw.size()
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Pattern> patterns;
    string line;

    // 读分割词（每行一个），空行结束
    while (getline(cin, line)) {
        if (line.empty()) break;
        auto parts = split_by_space(line);
        Pattern p;
        p.w = parts;
        p.raw = join_with_space(parts);  // 规范化：多空格变单空格
        p.raw_len = (int)p.raw.size();
        patterns.push_back(std::move(p));
    }

    // 读长字符串
    string text;
    getline(cin, text);
    vector<string> words = split_by_space(text);

    // 排序：优先 raw_len 大；再 raw 字典序大
    sort(patterns.begin(), patterns.end(), [](const Pattern& a, const Pattern& b) {
        if (a.raw_len != b.raw_len) return a.raw_len > b.raw_len;
        return a.raw > b.raw;
    });

    vector<string> tokens;
    int n = (int)words.size();

    for (int i = 0; i < n; ) {
        int bestIdx = -1;

        for (int pi = 0; pi < (int)patterns.size(); pi++) {
            const auto& pw = patterns[pi].w;
            int k = (int)pw.size();
            if (i + k > n) continue;

            bool ok = true;
            for (int t = 0; t < k; t++) {
                if (words[i + t] != pw[t]) { ok = false; break; }
            }
            if (ok) { bestIdx = pi; break; } // 已按规则排序，首个即最优
        }

        if (bestIdx != -1) {
            tokens.push_back(patterns[bestIdx].raw);
            i += (int)patterns[bestIdx].w.size();
        } else {
            tokens.push_back(words[i]);
            i++;
        }
    }

    for (auto& t : tokens) cout << "(" << t << ")";
    cout << "\n";
    return 0;
}