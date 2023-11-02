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

template<typename REF>
void merge2(Node<REF> *par, Node<REF> *a, Node<REF> *b) {
    par->val = a->val * b->val;
}

template<typename REF>
void merge2(Node<REF> *par, Node<REF> *a) {
    par->val *= a->val;
}

template<typename REF>
void merge3(Node<REF> *par, Node<REF> *a, Node<REF> *b) {
    par->val = max(a->val, b->val);
}

template<typename REF>
void merge3(Node<REF> *par, Node<REF> *a) {
    par->val = max(par->val, a->val);
}


template<typename NODE, typename REF>
class segment_tree {
public:
    Node<NODE> *root = new Node<NODE>;
    size_t size = 0;

    segment_tree(const vector<REF> &a, void merge(Node<NODE> *, Node<NODE> *, Node<NODE> *)) {
        //референсный массив, функция слияния вершин
        size = a.size();
        build(root, 0, size, a, merge);
    }

    NODE get(int l, int r, const NODE &val, void merge(Node<NODE> *, Node<NODE> *)) {
        //левая граница, правая граница, инициализатор ответа, функция слияния вершин
        auto *ans = new Node<NODE>(val);
        get(root, 0, size, l, r, ans, merge);
        return ans->val;
    }

private:
    void
    build(Node<NODE> *v, int l, int r, const vector<REF> &a, void merge(Node<NODE> *, Node<NODE> *, Node<NODE> *)) {
        if (l + 1 == r) {
            v->val = a[l];
            return;
        }
        auto *left = new Node<NODE>;
        auto *right = new Node<NODE>;
        v->left = left;
        v->right = right;
        build(left, l, (l + r) / 2, a, merge);
        build(right, (l + r) / 2, r, a, merge);
        merge(v, left, right);
    }

    void get(Node<NODE> *v, int l, int r, int ql, int qr, Node<NODE> *ans, void merge(Node<NODE> *, Node<NODE> *)) {
        if (l >= ql && r <= qr) {
            merge(ans, v);
            return;
        }
        if (l >= qr || r <= ql) {
            return;
        }
        get(v->left, l, (l + r) / 2, ql, qr, ans, merge);
        get(v->right, (l + r) / 2, r, ql, qr, ans, merge);
    }
};


signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    vector<int> a = {1, 2, 3, 4, 5};
    auto st = segment_tree<int, int>(a, merge3<int>);
    cout << st.get(0, 5, 0, merge3<int>);
}