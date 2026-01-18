//
// Created by Krisw on 2026/1/15.
//

/*
为了达到新冠疫情精准防控的需要，为了避免全员核酸检测带来的浪费，需要精准圈定可能被感染的人群。现在根据传染病流调以及大数据分析，
得到了每个人之间在时间、空间上是否存在轨迹的交叉现在给定一组确诊人员编号(X1,X2,X3...Xn)在所有人当中，找出哪些人需要进行核酸检测，输出需要进行核酸检测的人数。
注意:确诊病例自身不需要再做核酸检测)需要进行核酸检测的人，是病毒传播链条上的所有人员，即有可能通过确诊病例所能传播到的所有人。
例如:A是确诊病例，A和B有接触、B和C有接触 C和D有接触，D和E有接触。那么B、C、D、E都是需要进行核酸检测的


输入描述
第一行为总人数N
第二行为确证病例人员编号 (确证病例人员数量<N) ，用逗号隔开接下来N行，每一行有N个数字，用逗号隔开，其中第i行的第个j数字表名编号i是否与编号j接触过。0表示没有接触，1表示有接触
备注
人员编号从0开始
0 < N < 100
输出描述
输出需要做核酸检测的人数


示例1：
输入：
5
1,2
1,1,0,1,0
1,1,0,0,0
0,0,1,0,1
1,0,0,1,0
0,0,1,0,1
输出
3

说明：

编号为1、2号的人员为确诊病例1号与0号有接触，0号与3号有接触，2号4号有接触。所以，需要做核酸检测的人是0号、3号、4号,总计3人要进行核酸检测。

 */

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> parseArray(const string &line, char delim) {
    vector<int> array;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cin.ignore();
    string line;
    getline(cin, line);
    auto persons = parseArray(line, ',');

    vector<vector<int> > m(N);
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        m[i] = parseArray(line, ',');
    }
    
    queue<int> q;
    unordered_set<int> st;
    for (auto p: persons) {
        q.push(p);
        st.insert(p);
    }
    while (!q.empty()) {
        auto sz = q.size();
        for (int i = 0; i < sz; i++) {
            auto id = q.front();
            q.pop();
            for (int j = 0; j < N; j++) {
                if (j != id && !st.count(j) && m[id][j] == 1) {
                    st.insert(j);
                    q.push(j);
                }
            }
        }
    }

    for (auto p: persons) { st.erase(p); }
    cout << st.size() << endl;
    return 0;
}
