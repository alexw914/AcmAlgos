#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <list>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <numeric>
#include <functional>

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    getline(cin, line);
    cout << "This is template..." << endl;
    return 0;
}
