//
// Created by Krisw on 2026/4/6.
//

#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int k = 0, v = 0;
    Node *prev = nullptr, *next = nullptr;
    Node() {}
    Node(int key, int val) : k(key), v(val) {}
};

class LRUCache {
public:
    LRUCache(size_t capcity) : cap(capcity) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    // 命中返回value，同时将数据移动到表头
    int get(int key) {
        if (!cache.count(key)) return -1;
        Node *node = cache[key];
        moveToHead(node);
        return node->v;
    }

    // 存在更新到表头，不存在加到表头，并且可能淘汰尾部节点
    void put(int key, int value) {
        if (cache.count(key)) {
            Node *node = cache[key];
            node->v = value;
            moveToHead(node);
        } else {
            Node *node = new Node(key, value);
            cache[key] = node;
            addToHead(node);
            ++size;
            if (size > cap) {
                node = removeTail();
                cache.erase(node->k);
                --size;
            }
        }
    }

private:
    unordered_map<int, Node *> cache;
    Node *head;
    Node *tail;
    int cap;
    int size = 0;

    void moveToHead(Node *node) {
        removeNode(node);
        addToHead(node);
    }

    void removeNode(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToHead(Node *node) {
        node->next = head->next;
        node->prev = head;
        head->next = node;
        node->next->prev = node;
    }

    // 返回尾部节点
    Node *removeTail() {
        Node *node = tail->prev;
        removeNode(node);
        return node;
    }
};
