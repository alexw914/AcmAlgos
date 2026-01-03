//
// Created by Krisw on 2025/12/22.
//

/*
一个设备由N种类型元器件组成(每种类型元器件只需要一个，类型type编号从0~N-1),每个元器件均有可靠性属性reliability，
可靠性越高的器件其价格price越贵。而设备的可靠性由组成设备的所有器件中可靠性最低的器件决定。
给定预算S，购买N种元器件(每种类型元器件都需要购买一个)，在不超过预算的情况下，请给出能够组成的设备的最大可靠性.
输入描述
S N // S总的预算，N元器件的种类
total // 元器件的总数，每种型号的元器件可以有多种:
此后有total行具体器件的数据
type reliability price / type 整数类型，代表元器件的类型编号从0 ~ N-1; reliabily 整数类型，代表元器件的可靠性: price 整数类型，代表元器件的价格
输出描述
符合预算的设备的最大可靠性，如果预算无法买产N种器件，则返回 -1

备注
0 <= S,price <= 10000000
0 <= N <= 100
0 <= type <= N-1
0 <= total <= 100000
0 < reliability <= 100000


示例1：

输入
500 3
6
0 80 100
0 90 200
1 50 50
1 70 210
2 50 100
2 60 150
输出
60
说明

预算500，设备需要3种元件组成，方案类型0的第一个(可靠性80),
类型1的第二个(可靠性70).
类型2的第二个(可靠性60).

可以使设备的可靠性最大 60

示例2：

输入

100 1

1
0 90 200
输出
-1
说明
组成设备需要1个元件，但是元件价格大于预算，因此无法组成设备，返回-1
*/

#include <bits/stdc++.h>
using namespace std;

#define inf 0x3f3f3f3f3f3f3f3fLL
#define infi 0x3f3f3f3f
using LL = long long;
using pii = pair<int, int>;
int s, n, t;

bool check(int x, vector<array<int, 3>> &a){
    vector<int> mi(n + 1, infi);//记录每一个元件的最小价值
    for (int i = 1; i <= t; i++) {
        if (a[i][1] >= x) {//如果这个元件的可靠性符合要求
            mi[a[i][0]] = min(mi[a[i][0]], a[i][2]);//那么我们肯定要钱最少的
        }
    }
    LL cost = 0;
    for (int i = 1; i <= n; i++) {
        cost += mi[i];//记录一下最少花了多少钱
    }
    return s >= cost;//如果花的钱太多，return false
}

int main() {
    cin >> s >> n;
    cin >> t;
    vector<array<int, 3>> a(t + 1);
    for (int i = 1; i <= t; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        a[i][0]++;//范围枚举从[0,n-1]变为[1,n]
    }//输入
    int left = 0;
    int right = infi;
    int ans = -1;//二分
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid, a)) {//如果钱足够满足mid可靠性
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}