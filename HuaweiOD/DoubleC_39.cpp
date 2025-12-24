//
// Created by Krisw on 2025/12/22.
//

/*
普通的伞在二维平面世界中，左右两侧均有一条边，而两侧伞边最下面各有一个伞坠子，雨滴落到伞面，逐步流到伞坠处，
会将伞坠的信息携带并落到地面，随着日积月累，地面会呈现伞坠的信息。

1、为了模拟伞状雨滴效应，用二叉树来模拟二维平面伞，现在输入一串正整数数组序列(不含0，数组成员至少是1个) ，若此数组序列是二叉搜索树的前序遍历的结果，那么请输出一个返回值1，否则输出0.

2、同时请将此序列构成的伞状效应携带到地面的数字信息输出来(左边伞坠信息，右边伞坠信息，详细参考示例图地面上数字)，
若此树不存在左或右扇坠，则对应位置返回0。同时若非 二叉排序树那么左右伞坠信息也返回0。



输入描述:
1个通过空格分割的整数序列字符串，数组不含0，数组成员至少1个，输入的数组的任意两个数字都互不相同，最多1000个正整数，正整数值范围1~655350
输出描述:
输出如下三个值，以空格分隔: 是否二叉排序树，左侧地面呈现的伞坠数字值，右侧地面呈现的伞坠数字值.
若是二叉排序树，则输出1，否则输出0 (其左右伞坠值也直接赋值0) 。
若不存存在左侧或者右侧伞坠值，那么对应伞坠值直接赋值0。
示例1
输入:
8 3 1 6 4 7 10 14 13
输出:
1 1 13
说明:
1表示是二叉搜索树前序遍历结果，1表示左侧地面呈现的伞坠数字值，13表示右侧地面呈现的伞坠数字值
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left = nullptr;
    Node *right = nullptr;
    explicit Node(int v): val(v) {}
};

// O(n) 判断是否为 BST 前序（互不相同）
bool isBSTPreorder(const vector<int>& pre) {
    long long lower = LLONG_MIN;
    vector<int> st;
    st.reserve(pre.size());

    for (int x : pre) {
        if ((long long)x <= lower) return false;
        while (!st.empty() && x > st.back()) {
            lower = st.back();
            st.pop_back();
        }
        st.push_back(x);
    }
    return true;
}

// 线性重建 BST：前序 + (min,max) 边界
Node* buildBST(const vector<int>& pre, int &idx, long long lo, long long hi) {
    if (idx >= (int)pre.size()) return nullptr;
    int x = pre[idx];
    if ((long long)x <= lo || (long long)x >= hi) return nullptr;

    Node* root = new Node(x);
    idx++;
    root->left  = buildBST(pre, idx, lo, x);
    root->right = buildBST(pre, idx, x, hi);
    return root;
}

int leftUmbrella(Node* root) {
    if (!root || !root->left) return 0;
    Node* cur = root->left;
    while (cur->left || cur->right) {
        if (cur->left) cur = cur->left;
        else cur = cur->right;
    }
    return cur->val;
}

int rightUmbrella(Node* root) {
    if (!root || !root->right) return 0;
    Node* cur = root->right;
    while (cur->left || cur->right) {
        if (cur->right) cur = cur->right;
        else cur = cur->left;
    }
    return cur->val;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if (!getline(cin, line)) return 0;

    stringstream ss(line);
    vector<int> pre;
    int x;
    while (ss >> x) pre.push_back(x);

    // 输入至少 1 个数，且均为正整数（题目保证），这里不额外校验
    if (pre.empty() || !isBSTPreorder(pre)) {
        cout << "0 0 0\n";
        return 0;
    }

    int idx = 0;
    Node* root = buildBST(pre, idx, LLONG_MIN, LLONG_MAX);

    int L = leftUmbrella(root);
    int R = rightUmbrella(root);

    cout << "1 " << L << " " << R << "\n";

    freeTree(root);
    return 0;
}

