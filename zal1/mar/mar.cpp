#include <iostream>
//#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

constexpr int MAXN = 100000;
constexpr int MAXNLOG = 16;

priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<tuple<int, int, int> > > q;

int a[MAXN];
int n, k, u;

int state_result[MAXN][MAXNLOG];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k >> u;
    for (int i = 0; i < n; ++i) {
        char c;
        //scanf("%c", &c);
        cin >> c;
        switch (c) {
        case '.':
            a[i] = 0;
            break;
        case '*':
            a[i] = 1;
            break;
        case '<':
            a[i] = 2;
            break;
        case '>':
            a[i] = 3;
            break;
        case 'U':
            a[i] = 4;
            break;
        default:
            a[i] = 5;
        }
    }
    q.push(make_tuple(0, 0, 0));
    int t, pos, s;
    while (!q.empty()) {
        tuple<int, int, int> tpl = q.top();
        tie(t, pos, s) = tpl;
        q.pop();
        //if (state_result[pos][s] != 0)
        //    continue;
        bool lost = false;
        if (pos + 1 < n) {
            switch (a[pos + 1]) {
            case 0:
                ++pos;
                ++t;
                break;
            case 1:
                ++pos;
                if (s < MAXNLOG - 1)
                    ++s;
                ++t;
                break;
            case 2:
                pos += 1 - k;
                ++t;
                break;
            case 3:
                pos += 1 + k;
                ++t;
                break;
            case 4:
                ++pos;
                t += 1 + u;
                break;
            default:
                lost = true;
                break;
            }
        }
        if (!lost && state_result[pos][s] == 0) {
            state_result[pos][s] = t + 1;
            q.push(make_tuple(t, pos, s));
        }
        lost = false;
        tie(t, pos, s) = tpl;
        int true_s = 1 << (s + 1);
        if (pos + true_s < n) {
            switch (a[pos + true_s]) {
            case 0:
                pos += true_s;
                ++t;
                break;
            case 1:
                pos += true_s;
                if (s < MAXNLOG - 1)
                    ++s;
                ++t;
                break;
            case 2:
                pos += true_s - k;
                ++t;
                break;
            case 3:
                pos += true_s + k;
                ++t;
                break;
            case 4:
                pos += true_s;
                t += 1 + u;
                break;
            default:
                lost = true;
                break;
            }
        }
        if (!lost && state_result[pos][s] == 0) {
            state_result[pos][s] = t + 1;
            q.push(make_tuple(t, pos, s));
        }
    }
    int res = -1;
    bool inited = false;
    for (int i = 0; i < MAXNLOG; ++i) {
        if (state_result[n - 1][i] == 0)
            continue;
        if (!inited) {
            inited = true;
            res = state_result[n - 1][i] - 1;
        }
        else {
            if (res > state_result[n - 1][i] - 1)
                res = state_result[n - 1][i] - 1;
        }
    }
    //printf("%d\n", res);
    cout << res << "\n";
    return 0;
}