//
// Created by Krisw on 2026/1/18.
//

/*
给定一个输入字符串，字符串只可能由英文字母 (a ~z、A~ Z ) 和左右小括号 (、) 组成当字符里存在小括号时，小括号是成对的，可以有一个或多个小括号对，
小括号对不会嵌套，小括号对内可以包含1个或多个英文字母也可以不包含英文字母。当小括号对内包含多个英文字母时，
这些字母之间是相互等效的关系，而且等效关系可以在不同的小括号对之间传递，即当存在a和b等效和存在b和c等效时，
a和c 也等效，另外，同一个英文字母的大写字和小写字母也相互等效(即使它们分布在不同的括号对里)
要对这个输入字符串做简化，输出一个新的字符串，输出字符串里只需保留输入字符串里的没有被小括号对包含的字符(按照输入字符串里的字符顺序)，
并将每个字符替换为在小括号对里包含的目字典序最小的等效字符。如果简化后的字符串为空，请输出为”0”
示例:输入字符串为"never(dont)live(run)up(f)()"，初始等效字符集合为(d,o,n,t)、r,u,n)，
由于等效关系可以传递，因此最终等效字符集合为(d,o,n,t,r,u)，将输入字符串里的剩余部分按字典序最小的等效字符替换后得到"devedgivedp
输入描述
input string
输入为1行，代表输入字符串

输出描述
output string
输出为1行，代表输出字符串
备注
输入字符串的长度在1~100000之间

示例1：

输入：

()abd
输出：

abd
说明：
输入字符串里没有被小括号包含的了字符串为"abd"，其中每个字符没有等效字符，输出为"abd"

示例2：

输入：

(abd)demand(fb)()for

输出：

aemanaaor

说明：
等效字符集为(a，b，d，f)，输入字符串里没有被小括号包含的了字符串集合为'demandfor”，将其中字符替换为字典序最小的等效字符后输出为:"aemanaaor

示例3：

输入：

()happy(xyz)new(wxy)year(t)

输出：
happwnewwear

说明：
等效字符集为(x，y,z，w)，输入字符串里没有被小括号包含的了字符串集合为"happynewyear”，将其中字符替换为字典序最小的等效字等后输出为:"happwnewwear

示例4：

输入
()abcdefgAC(a)(Ab)(C)
输出
AAcdefgAC
说明
等效字符集为('a','A','b'),输入字符里没有被小括号包含的子字符串集合为"abcdefgAC",
将其中字符替换为字典序最小的等效字符后输出为："AAcdefgAC"
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> p;
    explicit DSU(const int n): p(n) { iota(p.begin(), p.end(), 0); }

    int find(const int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    void unite(const int x, const int y) {
        int px = find(x), py = find(y);
        if (px != py) p[py] = px;
    }
};

int toId(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

char toChar(int x) {
    if (x < 26) return char('a' + x);
    return char('A' + x - 26);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    DSU dsu(52);

    // 大小写等效
    for (int i = 0; i < 26; ++i) {
        dsu.unite(i, i + 26);
    }

    bool inParen = false;
    vector<int> group;
    vector<int> outside;

    for (char c : s) {
        if (c == '(') {
            inParen = true;
            group.clear();
        }
        else if (c == ')') {
            for (int i = 1; i < (int)group.size(); ++i) {
                dsu.unite(group[0], group[i]);
            }
            inParen = false;
        }
        else if (isalpha(static_cast<unsigned char>(c))) {
            int cid = toId(c);
            if (inParen) group.push_back(cid);
            else outside.push_back(cid);
        }
    }

    // 每个集合的最小字符
    vector<int> minChar(52, -1);
    for (int i = 0; i < 52; ++i) {
        int r = dsu.find(i);
        if (minChar[r] == -1 || toChar(i) < toChar(minChar[r])) {
            minChar[r] = i;
        }
    }

    string result;
    for (int x : outside) {
        int r = dsu.find(x);
        result.push_back(toChar(minChar[r]));
    }

    if (result.empty()) cout << "0\n";
    else cout << result << "\n";

    return 0;
}
