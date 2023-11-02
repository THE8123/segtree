#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<typename REF>
struct Node {
    REF val;
    Node<REF> *left = nullptr;
    Node<REF> *right = nullptr;
};

template<typename REF>
void merge(Node<REF> *par, Node<REF> *a, Node<REF> *b) {
    par->val = a->val + b->val;
}

template<typename REF>
void merge(Node<REF> *par, Node<REF> *a) {
    par->val += a->val;
}

template<typename NODE, typename REF>
class segment_tree {
public:
    Node<NODE> *root = new Node<NODE>;
    size_t size = 0;

    segment_tree(const vector<REF> &a) {
        size = a.size();
        build(root, 0, size, a);
    }

    NODE get(int l, int r) {
        Node<NODE> *ans = new Node<NODE>;
        get(root, 0, size, l, r, ans);
        return ans->val;
    }

private:
    void
    build(Node<NODE> *v, int l, int r, const vector<REF> &a) {
        if (l + 1 == r) {
            v->val = a[l];
            return;
        }
        Node<NODE> *left = new Node<NODE>;
        Node<NODE> *right = new Node<NODE>;
        v->left = left;
        v->right = right;
        build(left, l, (l + r) / 2, a);
        build(right, (l + r) / 2, r, a);
        merge(v, left, right);
    }

    void get(Node<NODE> *v, int l, int r, int ql, int qr, Node<NODE> *ans) {
        if (l >= ql && r <= qr) {
            merge(ans, v);
            return;
        }
        if (l >= qr || r <= ql) {
            return;
        }
        get(v->left, l, (l + r) / 2, ql, qr, ans);
        get(v->right, (l + r) / 2, r, ql, qr, ans);
    }
};


signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    vector<int> a = {1, 2, 3, 4, 5};
    auto st = segment_tree<int, int>(a);
    cout << st.get(0, 5);
}