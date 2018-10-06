#include <iostream>
#include <string>

using namespace std;

string s;
char lastChar;
int lastCharPos = -1;
int minDist = -1;

int main() {
    cin >> s;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == '*')
            continue;
        if (lastCharPos == -1) {
            lastCharPos = i;
            lastChar = s[i];
            continue;
        }
        if (lastChar != s[i] && (minDist == -1 || minDist > i - lastCharPos))
            minDist = i - lastCharPos;
        lastCharPos = i;
        lastChar = s[i];
    }
    if (minDist == -1)
        cout << "1\n";
    else
        cout << n - minDist + 1 << "\n";
    return 0;
}