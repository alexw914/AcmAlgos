//
// Created by Krisw on 2025/12/28.
//

/*
小明是 核心网工程师，客户交给小明一个任务:给定一个网络配置列表，每个配置是一个字符串，仅由数字和"*"、"?"符号组成。输入用户的IMSI(国际移动用户识别码)，根据以下规则匹配配置列表:
"*"匹配0个或连续多个任意字符，
"?"匹配下标为奇数的单个字符，比如123?中的"?"可以匹配123456789012345下标为3的字符'4'，下标从0开始。


输入描述
输入第一行为 网络配置列表，列表中的每个配置是由数字和"*" "?"组成的字符串，每个字符串中"*"不会超过一个,"?"若干，网络配置列表长度小于200，每个字符串以英文逗号隔开。
输入第二行为用户的IMSI(国际移动用户识别码)，仅由数字组成，长度等于15.
备注
保证输入格式正确，无需考虑格式错误。


输出描述
输出为满足匹配规则的配置字符串列表，列表按字典序升序输出，每个字符以英文逗号隔开。若没有满足条件的配置，则返回字符串"null"

示例1

输入：

1234567,1234567*
123456789012345

输出：

1234567*

说明：

*可以匹配0或多个任意字符，故输出1234567*

示例2

输入：

123?????????345,123????*????345
123456789012345

输出：

null
说明：

"?"字符只能匹配IMSI中为奇数下标的字符，故都不符合要求，返回null
*/

#include <bits/stdc++.h>
using namespace std;

bool matchDP(const string &pattern, const string &imsi) {
    int n = pattern.size();
    int m = imsi.size();   // 固定为 15

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    // 初始化
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
        if (pattern[i - 1] == '*') {
            dp[i][0] = dp[i - 1][0];
        }
    }

    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char p = pattern[i - 1];

            if (p == '*') {
                // 匹配 0 个 或 匹配 >=1 个
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else if (p == '?') {
                // 只能匹配 IMSI 奇数下标字符
                if ((j - 1) % 2 == 1) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            } else {
                // 普通数字字符
                if (p == imsi[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
    }

    return dp[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读取配置列表
    string line;
    getline(cin, line);

    // 读取 IMSI
    string imsi;
    getline(cin, imsi);

    vector<string> patterns;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        patterns.push_back(token);
    }

    vector<string> result;
    for (const auto &p : patterns) {
        if (matchDP(p, imsi)) {
            result.push_back(p);
        }
    }

    if (result.empty()) {
        cout << "null\n";
    } else {
        sort(result.begin(), result.end());
        for (int i = 0; i < result.size(); i++) {
            if (i) cout << ",";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}
