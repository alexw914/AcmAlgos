//
// Created by Krisw on 2026/1/13.
//

/*
给定长度为n的无序的数字数组，每个数字代表二叉树的叶子节点的权值，数字数组的值均大于等于1。请完成一个函数，根据输入的数字数组，生成哈夫曼树，并将哈夫曼树按照中序遍历输出
为了保证输出的二叉树中序遍历结果统一，增加以下限制: 二叉树节点中，左节点权值小于等于右节点权值，根节点权值为左右节点权值之和。当左右节点权值相同时，左子树高度高度小于等于右子树。
注意:所有用例保证有效，并能生成哈夫曼树。
提醒:哈夫曼树又称最优二叉树，是一种带权路径长度最短的二叉树。所谓树的带权路径长度，就是树中所有的叶结点的权值乘上其到根结点的路径长度。(若根结点为0层，叶结点到根结点的路径长度为叶结点的层数)。
例如:
由叶子节点5 15 40 30 10生成的最优二叉树如下图所示，该树的最短带权路径长度为401+30*2+15*3+5*4+10*4=205.



输入描述
第一行输入为数组长度，记为N，1<=N=1000，

第二行输入无序数值数组，以空格分割，数值均大于等于1，小于100000
输出描述:
输出一个哈夫曼树的中序遍历的数组，数值间以空格分割

示例1
输入:
5
5 15 40 30 10
输出:
40 100 30 60 15 30 5 15 10
说明:
根据输入，生成哈夫曼树，按照中序遍历返回。所有节点中，左节点权值小于等于右节点权值，根节点权值为左右节点权值之和。当左右节点权值相同时，左子树高度高度小于等于右子树。
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    long long w;      // weight
    int h;            // height (leaf = 1)
    int id;           // unique id for deterministic tie-break
    Node* l;
    Node* r;
    Node(long long _w, int _h, int _id) : w(_w), h(_h), id(_id), l(nullptr), r(nullptr) {}
};

// Priority: smaller (w), then smaller (h), then smaller (id)
struct Cmp {
    bool operator()(const Node* a, const Node* b) const {
        if (a->w != b->w) return a->w > b->w;   // min-heap by w
        if (a->h != b->h) return a->h > b->h;   // then by height
        return a->id > b->id;                   // then by id
    }
};

// Normalize left/right to satisfy problem constraint
static inline void normalize(Node*& a, Node*& b) {
    if (a->w > b->w) swap(a, b);
    else if (a->w == b->w) {
        if (a->h > b->h) swap(a, b);
        else if (a->h == b->h && a->id > b->id) swap(a, b);
    }
}

void inorder(Node* root, vector<long long>& out) {
    if (!root) return;
    inorder(root->l, out);
    out.push_back(root->w);
    inorder(root->r, out);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    priority_queue<Node*, vector<Node*>, Cmp> pq;

    int uid = 0;
    for (int i = 0; i < N; i++) {
        long long x;
        cin >> x;
        pq.push(new Node(x, 1, uid++)); // leaf height = 1
    }

    // N==1: Huffman tree is just that leaf; inorder is itself.
    while ((int)pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();

        normalize(a, b);

        Node* p = new Node(a->w + b->w, max(a->h, b->h) + 1, uid++);
        p->l = a;
        p->r = b;

        pq.push(p);
    }

    Node* root = pq.top();
    vector<long long> out;
    inorder(root, out);

    for (int i = 0; i < (int)out.size(); i++) {
        if (i) cout << " ";
        cout << out[i];
    }
    cout << "\n";
    return 0;
}
