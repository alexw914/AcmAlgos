//
// Created by 巫妖王 on 2026/5/22.
//

/*
小明在一个充满人文关怀的公司上班，公司每个月都要为该月生日的同事送一份生日小礼物，该事项由小明负责，
请帮助小明统计某一月份应该准备多少礼物，重复录入的员工生日以最后一次录入结果为准，请不要重复统计，避免浪费。
输入描述
参数1，要发放礼物的月份，取值1到12。
参数2，员工列表。
参数3，员工生日日期列表，该列表和员工列表中的数据对应存在一一对应关系，长度一致。
输出描述
该月份要准备的礼品个数。
补充说明
1.小明公司的员工人数不超过100人。
2.员工姓名是字母和数字的组合，姓名长度大于0，小于16字节。
3.日期录入格式统一采用Year/Month/Day，Year
长度为4，Month和Day长度为1到2，系统保证录入 日期为合法日期。
4.不考虑同名多位员工的情况，名字一致即可认为是同一员工(在生产系统会通过工号区分，本系统简化处理)。

示例1

输入

5
Alice Bob Charlie David Eve Frank Grace Helen
1985/5/10 1990/10/11 1995/10/11 2000/11/10 2005/05/01 2010/10/13 2015/10/14
2020/5/2

输出

3

说明

在 5 月份出生的员工有 3 人 ，因此返回为 3 。

示例2

输入

10
Alice Bob Charlie David Eve Frank Grace Helen
1985/05/10 1990/10/11 1995/10/11 2000/11/10 2005/10/13 2010/10/13 2015/10/14
2020/10/15

输出

6

说明

10 月份出生的员工有 6 人，因此返回 6 。
*/

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct BirthDay {
  int year;
  int mouth;
  int day;
};

BirthDay parseString(const string &str) {
  stringstream ss(str);
  BirthDay ans;
  string item;
  getline(ss, item, '/');
  ans.year = stoi(item);
  getline(ss, item, '/');
  ans.mouth = stoi(item);
  getline(ss, item, '/');
  ans.day = stoi(item);
  return ans;
}

class Solution {
public:
  int countBirthdayGifts(int month, vector<string> &employees,
                         vector<string> &birthdays) {
    const int N = employees.size();
    map<string, string> mp;
    for (int i = 0; i < N; i++) {
      mp[employees[i]] = birthdays[i];
    }

    int cnt = 0;
    for (auto &[k, v] : mp) {
      auto birth = parseString(v);
      if (birth.mouth == month)
        cnt++;
    }

    return cnt;
  }
};

int main() {
  auto solution = Solution();
  vector<string> employees = {"Alice", "Bob",   "Charlie", "David",
                              "Eve",   "Frank", "Grace",   "Helen"};
  vector<string> birthdays = {"1985/05/10", "1990/10/11", "1995/10/11",
                              "2000/11/10", "2005/10/13", "2010/10/13",
                              "2015/10/14", "2020/10/15"};
  cout << solution.countBirthdayGifts(10, employees, birthdays) << endl;
}
