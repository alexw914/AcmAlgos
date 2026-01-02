//
// Created by Krisw on 2025/12/23.
//

/*
题目描述
大众对垃圾短信深恶痛绝，希望能对垃圾短信发送者进行识别，为此，很多软件增加了垃圾短信的识别机制。
经分析，发现正常用户的短信通常具备交互性，而垃圾短信往往都是大量单向的短信，按照如下规则进行垃圾短信识别:
本题中，发送者A符合以下条件之一的，则认为A是垃圾短信发送者:
1：A发送短信的接收者中，没有发过短信给A的人数L> 5;
2：A发送的短信数 - A接收的短信数M > 10;
3：如果存在X，A发送给X的短信数 - A接收到X的短信数N >5.
输入描述
第一行是条目数，接下来几行是具体的条目，每个条目，是一对D，第一人数字是发送者ID，后面的数字是接收者ID，中间空格隔开，所有的ID都为 无符号整型Q，ID最大值为100:
同一个条目中，两个ID不会相同 (即不会自己给自己发消息)
最后一行为指定的ID

输出描述
输出该ID是否为垃圾短信发送者，并且按序列输出 L M 的值(由于 N 值不唯一，不需要输出)输出均为字符串。

示例1：

输入
15

1 2

1 3

1 4

1 5

1 6

1 7

1 8

1 9
1 10
1 11
1 12
1 13
1 14
14 1
1 15

1
输出
true 13 13

说明
true 表示1是垃圾短信发送者，两个数字，代表发送者1对应的L和M值。true 13 13中间以一个空格分割。注意true是字符电输出

示例2：

输入

15

1 2

1 3

1 4

1 5

1 6

1 7

1 8

1 9
1 10
1 11
1 12
1 13
1 14
14 1
1 15

2
输出
false 0 -1
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int> > matrix(100, vector<int>(100, 0));
    int maxId = -1;
    while (N--) {
        int idFrom, idTo;
        cin >> idFrom >> idTo;
        maxId = max(max(idFrom, idTo), maxId);
        matrix[idFrom][idTo]++;
    }

    int Id;
    cin >> Id;

    int L = 0;
    int sendCnt = 0, receiveCnt = 0;
    bool existX = false;
    for (int i = 0; i <= maxId; i++) {

        sendCnt += matrix[Id][i];
        receiveCnt += matrix[i][Id];

        if (matrix[Id][i] > 0 && matrix[i][Id] == 0) {
            L++;
        }

        if (!existX && matrix[Id][i] - matrix[i][Id] > 5) {
            existX = true;
        }
    }
    int M = sendCnt - receiveCnt;

    bool ans = (L > 5) || (M > 10) || existX;

    cout << (ans ? "true" : "false") << " " << L << " " << M << "\n";
    return 0;
}
