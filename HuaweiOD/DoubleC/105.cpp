//
// Created by 巫妖王 on 2026/1/19.
//

/*
题目描述
给定一些短词字符串作为分割词，去分割一段长字符串。从前往后遍历分割词，查找并分割长字符串为对应的token。分词规则如下:
1.优先匹配最长分割词:若多个分割词可匹配同一位置，选择长度最长的;长度相同时，按字典序较大的优先。
2.未匹配部分保留原样:无法匹配分割词的部分直接作为独立token输出。
3.输出格式:每个token用括号包裹，按原字符串顺序输出。


输入描述:
短词字符串列表，每行一个，空行后输入待分割的长字符串。

输出描述:
括号包裹的分词结果，如(token1)(token2)


示例1:
输入:

zhong guo
zhong
guo
wo
mei guo

wo ai zhong guo mei guo ye xing

输出：

(wo)(ai)(zhong guo)(mei guo)(ye)(xing)
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {


  return 0;
}