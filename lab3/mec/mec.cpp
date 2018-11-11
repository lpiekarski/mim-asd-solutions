#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAXN = 40000;

int n, m;
long long num[MAXN];

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            a--;
            if (j < n / 2)
                num[a] *= 2;
            else
                num[a] = num[a] * 2 + 1;
        }
    }
    sort(num, num + n);
    for (int i = 1; i < n; i++)
        if (num[i] == num[i - 1]) {
            cout << "NIE\n";
            return 0;
        }
    cout << "TAK\n";
    return 0;
}