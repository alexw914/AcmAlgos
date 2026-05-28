//
// Created by 巫妖王 on 2026/5/22.
//

/*
模拟一个系统的命令行配置，包含添加、修改、删除三项操作，详情如下:
添加操作命令:add_rule rule_id=1 rule_index=18
修改操作命令: mod_rule rule_id=1 rule_index=100
删除操作命令:del_rule rule_id=1
其中:add_rule、mod_rule、 del_rule 是操作关键字，rule_id、 rule_index
是属性关键字且属性取值范围为数字1-9999之间，操作、属性之间都用空格进行分割。
1.在进行所有操作时，如果缺少关键字，或者相应的rule_id、rule_index的取值不符合要求，则操作失败。
2.在进行添加操作时，参数必须包含rule_id和rule_index，如果添加的rule_id当前不存在，则添加成功，如果添加已经存在的rule_id，则操作失败。
3.在进行修改操作时，参数必须包含rule_id和rule_index，如果当前rule_id不存在，或前后rule_index没有变化，则操作失败。
4.在进行删除操作时，参数必须包含rule_id，如果当前rule_id不存在，则操作失败。在进行批量操作时，

一个命令失败后可以继续下一条命令的操作。现给有一组批量操作的字符串，包括不超过1000条连续的操作指令，格式为[cmd][cmd][cmd]，请将字符串解析后按照顺序进入你实现的系统，统计出配置失败的次数。

输入描述：

一个字符串，格式为[cmd][cmd][cmd]，表示批量操作。最多不超过1000条连续的操作指令。

输出描述：

输出一个整数，表示统计出配置失败的次数。
示例1
输入
[add_rule rule_id=1 rule_index=9999][mod_rule rule_id=1 rule_index=10][del_rule rule_id=1]

输出：

1

说明：

[add_rule rule_id=1 rule_index=9999] 成功，[mod_rule rule_id=1 rule_index=10]
成功，[del_rule rule_id=1] 操作关键字是 del 不合法 → 失败1次，输出 1。
*/

#include <iostream>
#include <map>
#include <sstream>
using namespace std;

class Solution {
vector<string> split(const string &s) {
  vector<string> ops;
  int i = 0;

  while (i < s.size()) {
    if (s[i] == '[') {
      int j = i + 1;
      while (j < s.size() && s[j] != ']') { j++; }
      if (j == s.size()) { break; }
      ops.push_back(s.substr(i + 1, j - i - 1));
      i = j + 1;
    } else {
      i++;
    }
  }
  return ops;
}

int getInt(const string &s) {
  size_t pos = s.find('=');
  if(pos == string::npos) return -1;
  try { return stoi(s.substr(pos + 1)); }
  catch(...) { return -1; }
}


public:
    int getErrorCount(string rules) {
        auto ops = split(rules);
        map<int, int> mp;
        int ans = 0;
        for (auto& op : ops) {
            string rule, rule_id, rule_index;
            stringstream ss(op);
            getline(ss, rule, ' ');
            getline(ss, rule_id, ' ');
            getline(ss, rule_index);
            cout << rule << "," << rule_id << "," << rule_index << endl;
            if (rule.empty()) { ans++;}
            else if (rule == "add_rule") {
            if (!rule_id.empty() && !rule_index.empty() && getInt(rule_id) >= 1 && getInt(rule_id) <= 9999 &&  getInt(rule_index) >= 1 && getInt(rule_index) <= 9999) {
                if (mp.count(getInt(rule_id))) {
                ans++;
                }
                else {
                mp[getInt(rule_id)] = getInt(rule_index);
                }
            } else { ans++;}
            }
            else if (rule == "mod_rule") {
            if (!rule_id.empty() && ! rule_index.empty() && getInt(rule_id) >= 1 && getInt(rule_id) <= 9999 &&  getInt(rule_index) >= 1 && getInt(rule_index) <= 9999) {
                if (mp.count(getInt(rule_id)) && mp[getInt(rule_id)] != getInt(rule_index)) {
                mp[getInt(rule_id)] = getInt(rule_index);
                } else {
                ans++;
                }
            } else { ans++;}
            }
            else if (rule == "del_rule") {
            if (!rule_id.empty() && getInt(rule_id) >= 1 && getInt(rule_id) <= 9999) {
                if (mp.count(getInt(rule_id))) {
                mp.erase(getInt(rule_id));
                }
                else { ans++; }
            } else {ans++;}
            }
        }
        return ans;
    }
};

int main() {
  auto solution = Solution();
  cout << solution.getErrorCount("[add_rule rule_id=1 rule_index=9999][mod_rule rule_id=1 rule_index=10][del_rule rule_id=1]") << endl;
  return 0;
}