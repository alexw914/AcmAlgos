//
// Created by Krisw on 2026/1/19.
//

/*
实现一个简易的重复内容识别系统，通过给定的两个内容名称，和相似内容符号，判断两个内容是否相似；如果相似，返回相似内容；如果不相似，返回不相似的内容。

初始化：给出两个字符串，一些相似字符对，如顿号和逗号相似，的和de相似，猪和潴，给出两个字符串的相似判断结果

输入：两条语句，给出是否相似，对于相似的语句，返回True和相似的字符对；对于不相似的内容，则返回第一个内容的不相似信息，方便后续补充

注意：

相似关系是 具有 传递性的。例如，如果"顿号"和"逗号"是相似的，"逗号"和"分号"是相似的，则"顿号"和"逗号"是相似的。
为了过滤一些无意义的信息，这里***可以匹配任意长度的内容，例如：
给出相似对"(****)",""时，"异世邪君（人气玄幻作家）" 和 "异世邪君" 认为是相似，此时相似符号返回 *** 即可

不相似的内容，需要给出不相似的字符串，多处不相似的字符串用空格分隔
输入描述
第一行表示第一张专辑的专辑名
第二行表示第二张专辑的专辑名
第三行开始每行为相似的字符串，每行一组，每组字符串不超过10个
总共相似字符串行不超过10行
输出描述
第一行返回相似判断的结果，即True或者False
第二行开始返回相似/不相似的字符串，每行一组
用例
输入
林汉达上下五千年
林汉达上下5千年
五 5 ⑤ 伍 wu

输出
True
五 5

说明	无
输入
幸福de猪的个人专辑
幸福的猪的个人专辑
得 的
得 de

输出
True
de 的

说明	无
输入
异世邪君(人气玄幻作家)
异世邪君
(***)

输出
True
(***)

说明	无
输入
浩然爸爸讲成语
浩然爸爸讲论语
论语 三字经

输出	False
成语 论语

说明	无
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/******** 并查集 ********/
struct DSU {
    unordered_map<string,string> p;

    string find(const string& x){
        if(!p.count(x)) p[x]=x;
        if(p[x]==x) return x;
        return p[x]=find(p[x]);
    }

    void unite(const string&a,const string&b){
        string pa=find(a), pb=find(b);
        if(pa!=pb) p[pb]=pa;
    }
};

/******** 工具 ********/
bool startsWith(const string& s,int i,const string& pat){
    if(i+pat.size()>s.size()) return false;
    return s.compare(i,pat.size(),pat)==0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A,B;
    getline(cin,A);
    getline(cin,B);

    vector<vector<string>> groups;
    string line;

    bool hasWildcard=false;

    while(getline(cin,line)){
        getline(cin,line);
        if(line.empty()) continue;
        if(line=="(***)"){
            hasWildcard=true;
            continue;
        }
        stringstream ss(line);
        vector<string> g;
        string t;
        while(ss>>t) g.push_back(t);
        if(!g.empty()) groups.push_back(g);
    }

    DSU dsu;
    for(auto &g:groups){
        for(int i=1;i<g.size();i++)
            dsu.unite(g[0],g[i]);
    }

    unordered_map<string,vector<string>> mp;
    for(auto &g:groups)
        for(auto &s:g)
            mp[dsu.find(s)].push_back(s);

    vector<vector<string>> classes;
    for(auto &kv:mp){
        auto v=kv.second;
        sort(v.begin(),v.end(),[](auto&a,auto&b){
            if(a.size()!=b.size()) return a.size()>b.size();
            return a>b;
        });
        classes.push_back(v);
    }

    int i=0,j=0;
    vector<pair<string,string>> similar;
    vector<pair<string,string>> diff;

    while(i<A.size() && j<B.size()){
        if(A[i]==B[j]){
            i++; j++; continue;
        }

        bool matched=false;

        for(auto &cls:classes){
            for(auto &x:cls){
                for(auto &y:cls){
                    if(startsWith(A,i,x) && startsWith(B,j,y)){
                        similar.push_back({x,y});
                        i+=x.size();
                        j+=y.size();
                        matched=true;
                        break;
                    }
                }
                if(matched) break;
            }
            if(matched) break;
        }

        if(matched) continue;

        if(hasWildcard){
            cout<<"True\n(***)\n";
            return 0;
        }

        string da,db;
        da.push_back(A[i]);
        db.push_back(B[j]);
        diff.push_back({da,db});
        i++; j++;
    }

    if(i<A.size() || j<B.size()){
        if(hasWildcard){
            cout<<"True\n(***)\n";
            return 0;
        }
        diff.push_back({A.substr(i),B.substr(j)});
    }

    if(diff.empty()){
        cout<<"True\n";
        for(auto&p:similar)
            cout<<p.first<<" "<<p.second<<"\n";
    }else{
        cout<<"False\n";
        for(auto&p:diff)
            cout<<p.first<<" "<<p.second<<"\n";
    }
    return 0;
}
