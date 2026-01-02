//
// Created by Krisw on 2025/12/30.
//

/*
题目描述:
任务编排服务负责对任务进行组合调度。参与编排的任务有两种类型，其中一种执行时长为taskA，另一种执行时长为taskB。
任务一旦开始执行不能被打断，且任务可连续执行。服务每次可以编排num个任务。请编写一个方法，生成每次编排后的任务所有可能的总执行时长。
输入描述:
第1行输入分别为第1种任务执行时长taskA，第2种任务执行时长taskB，这次要编排的任务个数num，以逗号分隔。

输出描述:
数组形式返回所有总执行时时长，需要按从小到大排列
补充说明:
每种任务的数量都大于本次可以编排的任务数量
0 < taskA
0 < taskB
0 <= num <= 100000

示例1
输入:
1,2,3
输出:
[3, 4, 5, 6]
说明:
可以执行 3 次 taskA，得到结果 3: 执行 2次 taskA和1次 taskB，得到结果 4。以此类推，得到最终结果.
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> parseArray(const std::string& line) {
    stringstream ss(line);
    string item;
    vector<int> array;
    while (getline(ss, item, ',')) {
        array.push_back(stoi(item));
    }
    return array;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);

    auto array = parseArray(line);

    int taskA = array[0], taskB = array[1], num = array[2];

    unordered_set<int> st;
    for (int i = 0; i <= num; i++ ) {
        st.insert(i * taskA + (num-i) * taskB);
    }

    vector<int> ans(st.begin(), st.end());
    sort(ans.begin(), ans.end());

    const int N = ans.size();
    cout << "[";
    for (int i = 0; i < N; i++) {
        cout << ans[i];
        if (i != N-1) cout << ",";
    }
    cout << "]" << endl;


    return 0;
}

