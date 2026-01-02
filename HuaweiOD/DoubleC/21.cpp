//
// Created by Krisw on 2025/12/14.
//

/*
设定一组四码的数字作为谜底，另一方猜每猜一个数，出数者就要根据这个数字给出提示，提示以XAYB形式呈现，直到猜中位置。

其中X表示位置正确的数的个数(数字正确且位置正确)，而Y表示数字正确而位置不对的数的个数例如，当谜底为8123，
而猜谜者猜1052时，出题者必须提示0A2B。例如，当谜底为5637，而猜谜者猜4931时，出题者必须提示1A0B。
当前已知N组猜谜者猜的数字与提示，如果答案确定，请输出答案，不确定则输出NA。
输入描述
第一行输入一个正整数，0< N < 100.
接下来N行，每一行包含一猜测的数字与提示结果
输出描述
输出最后的答案，答案不确定则输出NA。

示例1：
输入

6
4815 1A1B
5716 0A1B
7842 0A1B
4901 0A0B
8585 3A0B
8555 2A1B

输出
3585


 */
#include <bits/stdc++.h>
using namespace std;

static string score(const string& secret, const string& guess) {
    int A = 0, B = 0;
    int cs[10] = {0}, cg[10] = {0};

    for (int i = 0; i < 4; i++) {
        if (secret[i] == guess[i]) {
            A++;
        } else {
            cs[secret[i] - '0']++;
            cg[guess[i] - '0']++;
        }
    }
    for (int d = 0; d < 10; d++) B += min(cs[d], cg[d]);

    return to_string(A) + "A" + to_string(B) + "B";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    string line;
    vector<pair<string, string>> cons;
    for (int i = 0; i < N; ) {
        string line;
        getline(cin, line);
        if (line.empty()) continue; // 跳过空行，但不增加 i

        string g, hint;
        stringstream ss(line);
        ss >> g >> hint;
        cons.push_back({g, hint});
        i++;
    }

    string answer = "";
    int cnt = 0;

    for (int x = 0; x <= 9999; x++) {
        string s = to_string(x);
        s.insert(0, 4 - s.size(), '0');
        bool ok = true;
        for (auto &p : cons) {
            if (score(s, p.first) != p.second) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cnt++;
            answer = s;
            if (cnt > 1) break; // 已经不唯一了，提前结束
        }
    }

    if (cnt == 1) cout << answer << "\n";
    else cout << "NA\n";
    return 0;
}
