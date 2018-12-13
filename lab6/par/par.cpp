#include <iostream>

using namespace std;

constexpr int MAXN = 500000, MAXNLOG = 20;

int n, m, pos, diamA, diamB, left_v[MAXN], right_v[MAXN], ancestors[MAXN][MAXNLOG], depth[MAXN], subtreeSize[MAXN],
order[MAXN], furthest[MAXN], order_rev[MAXN];

bool isAncestor(int a, int v) {
    return (a >= 0 && v >= 0 && order[v] >= order[a] && order[v] < order[a] + subtreeSize[a]);
}

void createOrderArr(int v, int d, int a) {
    int newPos = pos++;
    order[v] = newPos;
    order_rev[newPos] = v;
    subtreeSize[v] = 1;
    depth[v] = d;
    ancestors[v][0] = a;

    if (left_v[v] >= 0) {
        createOrderArr(left_v[v], d + 1, v);
        subtreeSize[v] += subtreeSize[left_v[v]];
    }

    if (right_v[v] >= 0) {
        createOrderArr(right_v[v], d + 1, v);
        subtreeSize[v] += subtreeSize[right_v[v]];
    }
}

void fillAncestors() {
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < MAXNLOG; ++i) {
            if (ancestors[j][i - 1] < 0)
                ancestors[j][i] = -1;
            else
                ancestors[j][i] = ancestors[ancestors[j][i - 1]][i - 1];
        }
    }
}

void fillFurthest(int v, int d, int from) {
    furthest[v] = d;
    if (left_v[v] >= 0 && left_v[v] != from)
        fillFurthest(left_v[v], d + 1, v);
    if (right_v[v] >= 0 && right_v[v] != from)
        fillFurthest(right_v[v], d + 1, v);
    if (ancestors[v][0] >= 0 && ancestors[v][0] != from)
        fillFurthest(ancestors[v][0], d + 1, v);
}

void findDiam() {
    int maxDepth = 0;
    int maxDepthId = 0;
    for (int i = 1; i < n; ++i)
        if (depth[i] > maxDepth) {
            maxDepth = depth[i];
            maxDepthId = i;
        }
    diamA = maxDepthId;
    fillFurthest(diamA, 0, diamA);

    maxDepth = 0;
    maxDepthId = diamA;
    for (int i = 0; i < n; ++i) {
        if (furthest[i] > maxDepth) {
            maxDepth = furthest[i];
            maxDepthId = i;
        }
    }
    diamB = maxDepthId;
}

int lca(int u, int v) {
    if(isAncestor(u, v))
        return u;
    if(isAncestor(v, u))
        return v;

    int i = u, j = MAXNLOG - 1;

    while (j >= 0) {
        while (ancestors[i][j] < 0)
            j--;
        if (isAncestor(ancestors[i][j], v))
            j--;
        else
            i = ancestors[i][j];
    }

    return ancestors[i][0];
}

int jumpUp(int v, int n) {
    if (v == -1)
        return -1;
    if (n == 0)
        return v;
    int lg = 0;//CLZ1 - __builtin_clz(n);
    int pw = 1;
    while (pw <= n) {
        pw = pw << 1;
        lg++;
    }
    pw = pw >> 1;
    lg--;
    return jumpUp(ancestors[v][lg], n - pw);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> left_v[i] >> right_v[i];
        left_v[i]--;
        right_v[i]--;
    }
    createOrderArr(0, 0, -1);
    fillAncestors();
    findDiam();
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int v, d;
        cin >> v >> d;
        v--;
        int a = lca(v, diamA);
        int diam = diamA;
        int dV = depth[v] - depth[a], dD = depth[diam] - depth[a];
        if (dV + dD < d) {
            a = lca(v, diamB);
            diam = diamB;
            dV = depth[v] - depth[a];
            dD = depth[diam] - depth[a];
        }
        if (dV + dD < d)
            cout << "-1" << endl;
        else if (d <= dV)
            cout << jumpUp(v, d) + 1 << endl;
        else
            cout << jumpUp(diam, dD - (d - dV)) + 1 << endl;
    }
    return 0;
}