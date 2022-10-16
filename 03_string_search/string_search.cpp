#include <bits/stdc++.h>
using namespace std;
#include <atcoder/string>
using namespace atcoder;

#define SZ(v) (int)v.size()

// s : 文字列
// q : クエリの個数
// p : 各クエリの文字列

// 各クエリの文字列 p が s の部分文字列かどうかを判定

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