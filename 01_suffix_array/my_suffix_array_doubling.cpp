#include <bits/stdc++.h>
using namespace std;

#define SZ(v) (int)v.size()

// suffix_array
// O(N * log^2(N))

vector<int> suffix_array(const string &s) {
  int n = SZ(s);
  vector<int> sa(n + 1);
  vector<int> rank(n + 1);
  vector<int> tmp(n + 1);
  int k = -1;

  auto compare_sa = [&n, &rank, &k](const int &i, const int &j) -> bool {
    if (rank[i] != rank[j]) {
      return rank[i] < rank[j];
    } else {
      int ri = (i + k <= n ? rank[i + k] : -1);
      int rj = (j + k <= n ? rank[j + k] : -1);
      return ri < rj;
    }
  };

  for (int i = 0; i <= n; i++) {
    sa[i] = i;
    rank[i] = i < n ? s[i] : -1;
  }

  for (k = 1; k <= n; k *= 2) {
    sort(sa.begin(), sa.end(), compare_sa);

    tmp[sa[0]] = 0;
    for (int i = 1; i <= n; i++) {
      tmp[sa[i]] = tmp[sa[i - 1]] + !(rank[sa[i - 1]] == rank[sa[i]] &&
                                      rank[sa[i - 1] + k] == rank[sa[i] + k]);
    }
    for (int i = 0; i <= n; i++) {
      rank[i] = tmp[i];
    }
  }

  vector<int> ret(sa.begin() + 1, sa.end());
  return ret;
};

int main() {
  string s;
  cin >> s;

  vector<int> sa = suffix_array(s);

  int q;
  cin >> q;
  while (q--) {
    string p;
    cin >> p;

    int l = -1, r = SZ(s) - 1;
    int mid = -1;
    while (l + 1 < r) {
      mid = (l + r) / 2;
      string tmp = s.substr(sa[mid], min(SZ(p), SZ(s) - sa[mid]));
      if (tmp < p) {
        l = mid;
      } else {
        r = mid;
      }
    }

    if (p == s.substr(sa[r], min(SZ(p), SZ(s) - sa[r])))
      cout << "1\n";
    else
      cout << "0\n";
  }
}

// 検証用: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D
