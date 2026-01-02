//
// Created by Krisw on 2025/11/30.
//

/*
请设计一个文件缓存系统，该文件缓存系统可以指定缓存的 最大值 (单位为字节)
文件缓存系统有两种操作: 存储文件(put)和读取文件(get)
操作命令为put fileName fileSize或者get fileName
存储文件是把文件放入文件缓存系统中;读取文件是从文件缓存系统中访问已存在的文件，如果文件不存在，则不作任何操作。
当缓存空间不足以存放新的文件时，根据规则删除文件，直到剩余空间满足新的文件大小为止，再存放新文件。具体的删除规则为:
文件访问过后，会更新文件的最近访问时间和总的访问次数，当缓存不够时，按照第一优先顺序为访问次数从少到多，第二顺序为时间从老到新的方式来删除文件。


输入描述:
第一行为缓存最大值m(整数，取值范围为0 < m <= 52428800);

第二行为 文件操作序列个数n(0 <= n <= 300000)

从第三行起为文件操作序列，每个序列单独一行文件操作定义为"op file name file size"
file name是 文件名，file size是文件大小
输出描述
输出当前文件缓存中的文件名列表，文件名用英文逗号分隔，按字典顺序排序如:
a,c
如果文件缓存中没有文件，则输出NONE


补充说明:
1.如果新文件的文件名和文件缓存中已有的文件名相同，则不会放在缓存中
2.新的文件第一次存入到文件缓存中时，文件的总访问次数不会变化，文件的最近访问时间会更新到最新时间
3.每次文件访问后，总访问次数加1，最近访问时间更新到最新时间
4.任何两个文件的最近访问时间不会重复
5.文件名不会为空，均为小写字母，最大长度为10。
6.缓存空间不足时，不能存放新文件
7.每个文件大小都是大于0的整数


示例1
输入:
50

6
put a 10

put b 20
get a
get a
get b
put c 30
输出:
a,c
示例2
输入:
50

1
get file
输出:
NONE
 */

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct FileInfo {
    LL size, cnt, time;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int allCapacity;
    cin >> allCapacity;
    int N;
    cin >> N;

    unordered_map<string, FileInfo> mp;
    set<tuple<LL, LL, string>> order;

    LL usedSize = 0;
    LL curTime = 0;

    while (N--) {
        string op, fileName;
        cin >> op;
        if (op == "put") {
            LL fileSize;
            cin >> fileName >> fileSize;

            if (mp.count(fileName) != 0 || fileSize > allCapacity) {
                continue;
            }  // Already in Filesystem or file size too large

            while (usedSize + fileSize > allCapacity && !order.empty()) {
                auto it = order.begin();
                auto [ccnt, ctime, cname] = *it;
                order.erase(it);

                auto itMap = mp.find(cname);
                if (itMap != mp.end()) {
                    usedSize -= itMap->second.size;
                    mp.erase(itMap);
                }
            }

            // 淘汰之后仍然放不下，则放弃这个文件
            if (usedSize + fileSize > allCapacity) { continue; }

            // 插入新文件：cnt 初始为 0，time 更新为最新
            FileInfo fi{fileSize, 0, ++curTime};

            mp[fileName] = fi;
            order.insert({fi.cnt, fi.time, fileName});
            usedSize += fileSize;
        }

        if (op == "get") {
            cin >> fileName;

            auto itMap = mp.find(fileName);
            if (itMap == mp.end()) {
                // 文件不存在，不做任何事
                continue;
            }
            // 更新访问次数与时间
            FileInfo& fi = itMap->second;
            // 先从 set 中删除旧的排序键
            order.erase({fi.cnt, fi.time, fileName});
            // 更新
            fi.cnt += 1;
            fi.time = ++curTime;
            // 重新插入
            order.insert({fi.cnt, fi.time, fileName});
        }
    }

    if (mp.empty()) {
        cout << "NONE\n";
    } else {
        vector<string> names;
        names.reserve(mp.size());
        for (auto& p : mp) { names.push_back(p.first); }
        sort(names.begin(), names.end());
        for (size_t i = 0; i < names.size(); ++i) {
            if (i) cout << ",";
            cout << names[i];
        }
        cout << "\n";
    }
    return 0;
}