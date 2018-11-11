#include <iostream>
#include <vector>
#include <algorithm>
//#include <windows.h>

using namespace std;

constexpr int MAXN = 1001;
constexpr long long MOD = 1000000000;

int n, a[MAXN];

long long state[MAXN][MAXN][2];

long long state_result(int i, int j, int k) {
    if (state[i][j][k] != -1) {
        return state[i][j][k];
    }
    if (i + j == n) {
        return state[i][j][k] = 1;
    }
    long long res = 0;
    if (k == 0) {
        if (a[i] > a[i - 1])
            res += state_result(i + 1, j, 0);
        if (a[n - j - 1] > a[i - 1] && n - j - 1 != i)
            res += state_result(i, j + 1, 1);
    }
    else {
        if (a[i] < a[n - j])
            res += state_result(i + 1, j, 0);
        if (a[n - j - 1] < a[n - j] && n - j - 1 != i)
            res += state_result(i, j + 1, 1);
    }
    res = res % MOD;
    return state[i][j][k] = res;
}

int main() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            for (int k = 0; k < 2; k++)
                state[i][j][k] = -1;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (n > 1)
        cout << (state_result(1, 0, 0) + state_result(0, 1, 1)) % MOD << endl;
    else
        cout << "1" << endl;
    //system("pause");
    return 0;
}