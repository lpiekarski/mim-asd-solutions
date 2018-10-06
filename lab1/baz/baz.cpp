#include <iostream>

using namespace std;

constexpr int MAXN = 1000000;
constexpr int MAXM = MAXN;

int n, m;
int a[MAXN];
int oddLeft[MAXN], oddRight[MAXN], evenLeft[MAXN], evenRight[MAXN];
long long sum[MAXN + 1];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int even = -1, odd = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] & 1)
            odd = a[i];
        else
            even = a[i];
        oddLeft[i] = odd;
        evenLeft[i] = even;
        sum[i + 1] = sum[i] + a[i];
    }
    even = odd = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] & 1)
            odd = a[i];
        else
            even = a[i];
        oddRight[i] = odd;
        evenRight[i] = even;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        long long s = sum[n] - sum[n - k];
        if (s & 1) {
            cout << s << endl;
            continue;
        }
        long long maxS = -1;
    }
    return 0;
}