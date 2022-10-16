#include <bits/stdc++.h>
using namespace std;
#include <atcoder/string>
using namespace atcoder;

#define SZ(v) (int)v.size()

// s : 入力文字列
// t : BWT 後の s

// suffix array にはACL(SA-IS)を利用

int main() {
  string s;
  getline(cin, s);

  s.push_back('$');

  vector<int> sa = suffix_array(s);

#ifdef LOCAL
  for (int i = 0; i < SZ(s); i++) {
    cout << sa[i] << " \n"[i == SZ(s) - 1];
  }
#endif

  string t = "";
  for (int i = 0; i < SZ(s); i++) {
    t.push_back(s[(SZ(s) + sa[i] - 1) % SZ(s)]);
  }

  cout << t << '\n';

  return 0;
};