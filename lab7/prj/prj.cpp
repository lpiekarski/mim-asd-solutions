#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int MAXN = 100000;

int n, m, k;

vector<int> v[MAXN];
int degree[MAXN];
int weight[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
        cin >> weight[i];

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        v[b].push_back(a);
        ++degree[a];
    }

    for (int i = 0; i < n; ++i)
        if (degree[i] == 0)
            q.push(make_pair(weight[i], i));

    int ret = 0;
    while (k--) {
        pair<int, int> wi = q.top();
        q.pop();
        if (ret < wi.first)
            ret = wi.first;
        for (auto& vert : v[wi.second])
            if (degree[vert]-- == 1)
                q.push(make_pair(weight[vert], vert));
    }
    cout << ret << endl;
    return 0;
}