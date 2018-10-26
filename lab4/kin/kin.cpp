#include <iostream>
#include <vector>

using namespace std;

constexpr int MAXN = 20000;
constexpr int MAXK = 10;
constexpr long long MOD = 1000000000LL;

int n, k, a[MAXN];

struct Tree {
    int s = 1;
    vector<long long> t;

    Tree() {}

    Tree(int n) {
        while (s < n)
            s *= 2;
        t.resize(2 * s + 1);
    }

    void update(int x, long long y) {
        x += s;
        while (x) {
            t[x] += y;
            x /= 2;
        }
    }

    int sum(int l, int r) {
        long long res = 0LL;
        l += s;
        r += s;
        while (l < r) {
            if (l & 1)
                res = (res + t[l++]) % MOD;
            if (!(r & 1))
                res = (res + t[r--]) % MOD;
            l /= 2;
            r /= 2;
        }
        if (l == r)
            res = (res + t[l]) % MOD;
        return res;
    }
};

Tree t[MAXK];

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < k; i++)
        t[i] = Tree(n);
    for (int i = 0; i < n; i++) {
        t[0].update(a[i], 1);
        for (int j = 1; j < k; j++)
            t[j].update(a[i], t[j - 1].sum(a[i] + 1, n - 1));
    }
    cout << t[k - 1].sum(0, n - 1) << endl;
    return 0;
}