#include <iostream>
//#include <cstring>
//#include <cassert>

using namespace std;

typedef pair<uint64_t, uint64_t> hash_t;

constexpr size_t MAXN = 300000;
constexpr hash_t q = make_pair(24137, 24683);
hash_t p[MAXN];

void calculateP() {
    p[0] = make_pair(1, 1);
    for (size_t i = 1; i < MAXN; ++i) {
        p[i].first = (p[i - 1].first * 7499) % q.first;
        p[i].second = (p[i - 1].second * 7691) % q.second;
    }
}

string s;
int n, m;

hash_t pref[MAXN + 1];

hash_t get_hash(size_t b, size_t e) {
    hash_t ret;
    if (pref[e].first < pref[b].first)
        ret.first = (((pref[e].first + q.first) - pref[b].first) * p[q.first - 1 - (b % (q.first - 1))].first) % q.first;
    else
        ret.first = ((pref[e].first - pref[b].first) * p[q.first - 1 - (b % (q.first - 1))].first) % q.first;

    if (pref[e].second < pref[b].second)
        ret.second = (((pref[e].second + q.second) - pref[b].second) * p[q.second - 1 - (b % (q.second - 1))].second) % q.second;
    else
        ret.second = ((pref[e].second - pref[b].second) * p[q.second - 1 - (b % (q.second - 1))].second) % q.second;
    //cout << "hash of:\n" << s.substr(b, e - b) << "\n" << ret.first << ", " << ret.second << "\n";
    return ret;
}

int cmp(size_t a, size_t b, size_t c, size_t d) {
    size_t diff1 = b - a, diff2 = d - c;
    size_t begin = 0, end = diff2;
    if (diff1 < end)
        end = diff1;
    if (get_hash(a, a + end) == get_hash(c, c + end)) {
        //cout << "hashes for:\n" << s.substr(a, end) << "\n" << s.substr(c, end) << "\nare equal\n";
        if (diff1 > diff2) {
            //assert(strcmp(s.substr(a, b - a).c_str(), s.substr(c, d - c).c_str()) > 0);
            return 1;
        }
        if (diff1 < diff2) {
            //assert(strcmp(s.substr(a, b - a).c_str(), s.substr(c, d - c).c_str()) < 0);
            return -1;
        }
        //assert(strcmp(s.substr(a, b - a).c_str(), s.substr(c, d - c).c_str()) == 0);
        return 0;
    }
    while (end - 1 != begin) {
        //assert(get_hash(a, a + begin) == get_hash(c, c + begin));
        //assert(get_hash(a, a + end) != get_hash(c, c + end));
        size_t m = (end + begin) / 2;
        //cout << begin << ", " << end << "\n";
        //cout << "testing segment:\n" << s.substr(a, m) << "\n" << s.substr(c, m) << "\n";
        if (get_hash(a, a + m) == get_hash(c, c + m))
            begin = m;
        else
            end = m;
    }
    //cout << begin << ", " << end << "\n";
    //assert(get_hash(a, a + begin) == get_hash(c, c + begin));
    //assert(get_hash(a, a + end) != get_hash(c, c + end));
    char cmpval1 = s[a + begin], cmpval2 = s[c + begin];
    //assert(cmpval1 != cmpval2);
    if (cmpval1 > cmpval2) {
        //assert(strcmp(s.substr(a, b - a).c_str(), s.substr(c, d - c).c_str()) > 0);
        return 1;
    }
    if (cmpval1 < cmpval2) {
        //assert(strcmp(s.substr(a, b - a).c_str(), s.substr(c, d - c).c_str()) < 0);
        return -1;
    }
    //assert(strcmp(s.substr(a, b - a).c_str(), s.substr(c, d - c).c_str()) == 0);
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    calculateP();
    cin >> n >> m >> s;

    pref[0] = make_pair(0, 0);
    for (size_t i = 1; i <= n; ++i)
        pref[i] = make_pair((pref[i - 1].first + s[i - 1] * p[i - 1].first) % q.first,
                            (pref[i - 1].second + s[i - 1] * p[i - 1].second) % q.second);

    while (m--) {
        size_t a, b, c, d;
        cin >> a >> b >> c >> d;
        --a;
        --c;
        //cout << s.substr(a, b - a) << "\n" << s.substr(c, d - c) << endl;
        int cmpval = cmp(a, b, c, d);
        if (cmpval == 1)
            cout << ">\n";
        else if (cmpval == -1)
            cout << "<\n";
        else
            cout << "=\n";
    }
    return 0;
}
