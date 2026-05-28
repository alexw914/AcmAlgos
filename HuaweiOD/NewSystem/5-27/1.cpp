#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  string electMonitor(vector<string> &students, vector<string> &votes) {
    if (votes.size() > students.size())
      return "Invalid election.";

    unordered_set<string> st;
    for (auto &student : students) {
      if (st.count(student)) {
        int idx = 1;
        auto name = student;
        while (st.count(name)) {
          name = student + to_string(idx);
          idx++;
        }
        st.insert(name);
      } else {
        st.insert(student);
      }
    }

    unordered_map<string, int> mp;

    int max = -1;
    string name;
    for (auto &vote : votes) {
      if (st.count(vote)) {
        mp[vote]++;
        if (mp[vote] > max) {
          max = mp[vote];
          name = vote;
        }
        if (mp[vote] == max && vote < name) {
          name = vote;
        }
      }
    }
    if (name.empty())
      return "Invalid election.";

    return name;
  }
};

int main() {
  auto solution = Solution();
  vector<string> students{"Zhangsan", "Lisi", "Wangwu"};
  vector<string> votes{"Zhangsan", "Lisi", "Zhangsan"};
  cout << solution.electMonitor(students, votes) << endl;

  return 0;
}
