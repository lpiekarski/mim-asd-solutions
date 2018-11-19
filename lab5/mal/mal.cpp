#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
//#include <iomanip>

using namespace std;

constexpr int MAXN = 1000000;

struct Tree {
    int s = 1;
    vector<int> ins;
    vector<int> sum;

    Tree(int n) {
        while (s < n)
            s *= 2;
        ins.resize(2 * s + 1);
        sum.resize(2 * s + 1);
        for (int i = 0; i < 2 * s + 1; i++) {
            ins[i] = -1;
        }
    }

    /*void print_tree() {
        cout << "ins tree:\n";
        int p2 = 1, cnt = 0;
        for (int i = 1; i < 2 * s; i++) {
            int spaces = (2 * s + 1) / p2;
            cout << setw((cnt == 0) ? (spaces) : (spaces * 2)) << ins[i];
            cnt++;
            if (cnt == p2) {
                p2 *= 2;
                cnt = 0;
                cout << "\n";
            }
        }
        cout << "sum tree:\n";
        p2 = 1;
        cnt = 0;
        for (int i = 1; i < 2 * s; i++) {
            int spaces = (2 * s + 1) / p2;
            cout << setw((cnt == 0) ? (spaces) : (spaces * 2)) << sum[i];
            cnt++;
            if (cnt == p2) {
                p2 *= 2;
                cnt = 0;
                cout << "\n";
            }
        }
    }*/

    void update_rec(int a, int b, int val, int lo, int hi, int id) {
        if (a >= hi || b <= lo || lo == hi)
            return;
        if (ins[id] != -1 && id < s) {
            ins[id * 2] = ins[id];
            ins[id * 2 + 1] = ins[id];
            sum[id * 2 + 1] = ins[id] * (hi - lo) / 2;
            sum[id * 2 ] = ins[id] * (hi - lo) / 2;

            ins[id] = -1;
        }
        if (lo >= a && hi <= b) {
            ins[id] = val;
            sum[id] = (hi - lo) * val;
            return;
        }
        update_rec(a, b, val, lo, (lo + hi) / 2, id * 2);
        update_rec(a, b, val, (lo + hi) / 2, hi, id * 2 + 1);
       // if (ins[id] == -1)
            sum[id] = sum[id * 2] + sum[id * 2 + 1];
        //else
        //    sum[id] = ins[id] * (hi - lo);
    }

    void update(int a, int b, int val) {
        update_rec(a, b, val, 0, s, 1);
    }

    int query_rec(int a, int b, int lo, int hi, int id) {
        if (a >= hi || b <= lo || lo == hi)
            return 0;
        int res = 0;
        if (lo >= a && hi <= b) {
            return sum[id];
        }
        if (ins[id] != -1)
            return min(b - lo, hi - a) * ins[id];
        int l = query_rec(a, b, lo, (lo + hi) / 2, id * 2);
        int r = query_rec(a, b, (lo + hi) / 2, hi, id * 2 + 1);
        return l + r;
    }

    int query(int a, int b) {
        return query_rec(a, b, 0, s, 1);
    }

    int root() {
        return sum[1];
    }
};

int n, m;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    cin >> m;
    Tree t(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        if (c == 'C')
            t.update(a - 1, b, 0);
        else
            t.update(a - 1, b, 1);
        //cout << t.query(0, n) << "\n";
        cout << t.root() << "\n";
        //t.print_tree();
    }
    //system("pause");
    return 0;
}
