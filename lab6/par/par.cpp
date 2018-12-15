#include <iostream>
#include <vector>
#include <algorithm>

#define if_has_child(pref, v) if (pref##_child[v] != -1)
#define ref_up(a, b) ((up[a].size() > b) ? (up[a][b]) : (0))

using namespace std;

constexpr int MAXN = 500000;

int left_child[MAXN], right_child[MAXN], subtree_size[MAXN], preorder[MAXN], depth[MAXN], n, m;
vector<int> up[MAXN];

void calculate_depth(int *d, int dpth, int v) {
    d[v] = dpth;
    if_has_child(left, v)
        calculate_depth(d, dpth + 1, left_child[v]);
    if_has_child(right, v)
        calculate_depth(d, dpth + 1, right_child[v]);
}

void calculate_subtree_size(int *ss, int v) {
    ss[v] = 1;
    if_has_child(left, v) {
        calculate_subtree_size(ss, left_child[v]);
        ss[v] += ss[left_child[v]];
    }
    if_has_child(right, v) {
        calculate_subtree_size(ss, right_child[v]);
        ss[v] += ss[right_child[v]];
    }
}

void calculate_preorder(int *po, int v) {
    static int pre_counter = 0;
    po[v] = pre_counter++;
    if_has_child(left, v)
        calculate_preorder(po, left_child[v]);
    if_has_child(right, v)
        calculate_preorder(po, right_child[v]);
}

int furthest[MAXN];

void fillFurthest(int v, int d, int from) {
    furthest[v] = d;
    if (left_child[v] != -1 && left_child[v] != from)
        fillFurthest(left_child[v], d + 1, v);
    if (right_child[v] != -1 && right_child[v] != from)
        fillFurthest(right_child[v], d + 1, v);
    if (v != 0 && up[v][0] != from)
        fillFurthest(up[v][0], d + 1, v);
}

void calculate_diameter(int &diam1, int &diam2) {
    int maxDepth = 0;
    int maxDepthId = 0;
    for (int i = 0; i < n; ++i)
        if (depth[i] > maxDepth) {
            maxDepth = depth[i];
            maxDepthId = i;
        }
    diam1 = maxDepthId;

    fillFurthest(diam1, 0, diam1);

    maxDepth = 0;
    maxDepthId = diam1;
    for (int i = 0; i < n; ++i) {
        if (furthest[i] > maxDepth) {
            maxDepth = furthest[i];
            maxDepthId = i;
        }
    }
    diam2 = maxDepthId;
}

bool ancestor(int a, int b) {
    return a >= 0 && a < n && b >= 0 && b < n && preorder[b] >= preorder[a] && preorder[b] < preorder[a] + subtree_size[a];
}

int jump_up(int v, int steps) {
    if (steps <= 0 || up[v].empty())
        return v;
    int pow = 1, id = 0;
    while (pow <= steps) {
        pow *= 2;
        id++;
    }
    pow /= 2;
    id--;
    if (id >= up[v].size())
        id = up[v].size() - 1;
    return jump_up(up[v][id], steps - pow);
}

int lca(int a, int b) {
    if (a < 0 || a >= n || b < 0 || b >= n) {
        return -1;
    }
    if (ancestor(a, b)) {
        return a;
    }
    if (ancestor(b, a)) {
        return b;
    }
    int i = a, j = up[a].size() - 1;
    while (j >= 0) {
        if(ancestor(ref_up(i, j), b))
            j--;
        else
            i = ref_up(i, j);
    }
    return ref_up(i, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> left_child[i] >> right_child[i];
        if (left_child[i] > 0) {
            --left_child[i];
            up[left_child[i]].push_back(i);
        }
        if (right_child[i] > 0) {
            --right_child[i];
            up[right_child[i]].push_back(i);
        }
    }
    int updated = 0, level = 0;
    do {
        updated = 0;
        level++;
        for (int i = 0; i < n; ++i) {
            if (up[i].size() < level || up[up[i][level - 1]].size() < level)
                continue;
            up[i].push_back(up[up[i][level - 1]][level - 1]);
            ++updated;
        }
    } while(updated);
    calculate_subtree_size(subtree_size, 0);
    calculate_preorder(preorder, 0);
    calculate_depth(depth, 0, 0);
    int diam1, diam2;
    calculate_diameter(diam1, diam2);
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, d;
        cin >> a >> d;
        a--;
        int diam = diam1;
        int l = lca(a, diam);
        if (depth[a] + depth[diam] - 2 * depth[l] < d) {
            diam = diam2;
            l = lca(a, diam);
            if (depth[a] + depth[diam] - 2 * depth[l] < d) {
                cout << "-1" << endl;
                continue;
            }
        }
        if (depth[a] - depth[l] >= d)
            cout << jump_up(a, d) + 1 << endl;
        else
            cout << jump_up(diam, depth[diam] + depth[a] - 2 * depth[l] - d) + 1 << endl;
    }
    return 0;
}
/*
6
-1 2
3 -1
-1 4
5 6
-1 -1
-1 -1
1
5 4

 8
3 4
-1 6
2 5
-1 -1
7 -1
-1 -1
8 -1
-1 -1
*/
