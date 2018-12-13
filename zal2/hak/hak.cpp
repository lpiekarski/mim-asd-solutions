#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

//constexpr int MAXN = 100000;

int n, imax, q;

vector<pair<int, int>> intervals;
unordered_map<int, list<int>> sorted;

struct Tree {

    int n, s;
    int (*tree_op)(int, int);
    vector<int> t;

    Tree(int n, int (*op)(int, int)): n(n), tree_op(op), s(1) {
        while(s < n)
            s *= 2;
        t.resize(2 * s + 1);
    }

    void clear(int x) {
        x += s;
        t[x] = 0;
        x /= 2;
        while(x) {
            t[x] = tree_op(t[x * 2], t[x * 2 + 1]);
            x /= 2;
        }
    }

    void add(int x, int y) {
        x += s;
        t[x] = y;
        x /= 2;
        while(x) {
            t[x] = tree_op(t[x * 2], t[x * 2 + 1]);
            x /= 2;
        }
    }

    int query(int l, int r) {
        int res = 0;
        l += s;
        r += s;
        while (l < r) {
            if (l & 1)
                res = tree_op(res, t[l++]);
            if (!(r & 1))
                res = tree_op(res, t[r--]);
            l /= 2;
            r /= 2;
        }
        if (l == r)
            res = tree_op(res, t[l]);
        return res;
    }

    void print() {
        for (int i = 0; i < t.size(); i++)
            cout << t[i] << " ";
        cout << endl;
    }

};
void remove_max(Tree &tmin, Tree &tmax, int res) {
    int iv_a = intervals[res].first;
    list<int> &l = sorted[iv_a];
    l.pop_back();
    tmax.clear(iv_a);
    if (l.empty())
        tmin.clear(iv_a);
    else
        tmax.add(iv_a, l.back());
}

void remove_min(Tree &tmin, Tree &tmax, int res) {
    int iv_a = intervals[res].first;
    list<int> &l = sorted[iv_a];
    l.pop_front();
    tmin.clear(iv_a);
    if (l.empty())
        tmax.clear(iv_a);
    else
        tmin.add(iv_a, l.front());
}

int main() {
    cin >> n;
    intervals.emplace_back(-1, -1); //id 0 pair
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        intervals.emplace_back(a, b);
        sorted[a].push_back(i + 1);
        if (imax < b)
            imax = b;
    }
    for (auto &kv : sorted) {
        vector<int> v(make_move_iterator(begin(kv.second)), make_move_iterator(end(kv.second)));
        sort(v.begin(), v.end(), [](int a, int b) { return intervals[a].second < intervals[b].second; });
        kv.second = list<int>(make_move_iterator(begin(v)), make_move_iterator(end(v)));
    }

    /*for (auto &kv : sorted) {
        cout << kv.first << ": ";
        for (const auto &l : kv.second)
            cout << l << " ";
        cout << endl;
    }*/

    Tree tmin(imax + 1, [](int a, int b) {
        if (a == 0)
            return b;
        if (b == 0)
            return a;
        if (intervals[a].second < intervals[b].second)
            return a;
        return b;
    });
    Tree tmax(imax + 1, [](int a, int b) {
        if (a == 0)
            return b;
        if (b == 0)
            return a;
        if (intervals[a].second < intervals[b].second)
            return b;
        return a;
    });
    for (const auto &kv : sorted) {
        tmin.add(kv.first, kv.second.front());
        tmax.add(kv.first, kv.second.back());
    }
    string s;
    int x, y;
    /*tmin.print();
    tmax.print();*/
    cin >> q;
    while (q--) {
        cin >> s >> x >> y;
        if (s == "in") {
            int res = tmin.query(x, y);
            if (res == 0 || intervals[res].second > y) {
                cout << "-1\n";
            } else {
                cout << res << "\n";
                remove_min(tmin, tmax, res);
            }
        } else if (s == "over") {
            int res = tmax.query(0, x);
            if (res == 0 || intervals[res].second < y) {
                cout << "-1\n";
            } else {
                cout << res << "\n";
                remove_max(tmin, tmax, res);
            }
        } else if (s == "none") {
            int pre_a = 0, pre_b = x - 1;
            int post_a = y + 1, post_b = imax + 1;
            int res = 0;
            if (pre_a <= pre_b)
                res = tmin.query(pre_a, pre_b);
            if ((res == 0 || intervals[res].second >= x) && post_a <= post_b)
                res = tmin.query(post_a, post_b);
            if (res == 0) {
                cout << "-1\n";
            } else {
                cout << res << "\n";
                remove_min(tmin, tmax, res);
            }
        } else if (s == "some") {
            int res = tmax.query(0, y);
            if (res == 0 || intervals[res].second < x) {
                cout << "-1\n";
            } else {
                cout << res << "\n";
                remove_max(tmin, tmax, res);
            }
        }
        /*for (auto &kv : sorted) {
            cout << kv.first << ": ";
            for (const auto &l : kv.second)
                cout << l << " ";
            cout << endl;
        }
        tmin.print();
        tmax.print();*/
    }
    return 0;
}

/*
6
1 10
6 9
2 7
6 7
3 5
2 2

 */