#include <bits/stdc++.h>
using namespace std;

#define SZ(v) (int)v.size()

// suffix_array (induced sorting)
// O(N)

bool is_lms(const vector<bool> &t, int i) { return i > 0 && !t[i - 1] && t[i]; }

vector<int> induced_sort(const vector<int> &s, const int &k,
                         const vector<bool> &t, const vector<int> &lmss) {
  vector<int> sa(SZ(s));
  vector<int> bin(k + 1);
  for (auto &c : s)
    bin[c + 1]++;

  for (int i = 1; i <= k; i++) {
    bin[i] += bin[i - 1];
  }

  // step 1
  vector<int> count(k);
  for_each(lmss.rbegin(), lmss.rend(), [&](const int &i) {
    sa[bin[s[i] + 1] - 1 - count[s[i]]] = i;
    count[s[i]]++;
  });

  // step 2
  fill(count.begin(), count.end(), 0);
  for_each(sa.begin(), sa.end(), [&](const int &i) {
    if (i == 0)
      return;
    if (t[i - 1])
      return;
    sa[bin[s[i - 1]] + count[s[i - 1]]] = i - 1;
    count[s[i - 1]]++;
  });

  // step 3
  fill(count.begin(), count.end(), 0);
  for_each(sa.rbegin(), sa.rend(), [&](const int &i) {
    if (i == 0)
      return;
    if (!t[i - 1])
      return;
    sa[bin[s[i - 1] + 1] - 1 - count[s[i - 1]]] = i - 1;
    count[s[i - 1]]++;
  });

  return sa;
}

vector<int> sa_is(vector<int> s, const int k = 256) {
  vector<bool> t(SZ(s)); // true -> type S, false -> type L
  t[SZ(s) - 1] = true;
  for (int i = SZ(s) - 2; i >= 0; i--) {
    if (s[i] < s[i + 1])
      t[i] = true;
    else if (s[i] > s[i + 1])
      t[i] = false;
    else
      t[i] = t[i + 1];
  }

  vector<int> lmss;
  for (int i = 0; i < SZ(s); i++) {
    if (is_lms(t, i)) {
      lmss.push_back(i);
    }
  }
  auto seed = lmss;

  // 1回目のinduced_sort
  vector<int> sa = induced_sort(s, k, t, seed);

  // lmsのindexだけを取り出す
  vector<int> _sa;
  for (auto &i : sa) {
    if (is_lms(t, i))
      _sa.push_back(i);
  }

  vector<int> nums(SZ(sa), -1);
  int num = 0;
  nums[_sa[0]] = 0;
  for (int idx = 0; idx < SZ(_sa) - 1; idx++) {
    int i = _sa[idx], j = _sa[idx + 1];
    bool diff = false;
    for (int d = 0; d < SZ(s); d++) {
      if (s[i + d] != s[j + d] || is_lms(t, i + d) != is_lms(t, j + d)) {
        diff = true;
        break;
      } else if (d > 0 && (is_lms(t, i + d) || is_lms(t, j + d))) {
        break;
      }
    }
    num += diff;
    nums[j] = num;
  }

  vector<int> _nums;
  for (auto &i : nums) {
    if (i != -1) {
      _nums.push_back(i);
    }
  }

  if (num + 1 < SZ(_nums)) {
    sa = sa_is(_nums, num + 1);
  } else {
    sa.resize(SZ(_nums));
    for (int i = 0; i < SZ(_nums); i++) {
      sa[_nums[i]] = i;
    }
  }

  for (int i = 0; i < SZ(lmss); i++) {
    seed[i] = lmss[sa[i]];
  }

  // 2回目のinduced_sort
  sa = induced_sort(s, k, t, seed);

  return sa;
};

vector<int> suffix_array(string s) {
  vector<int> cs(SZ(s) + 1);
  for (int i = 0; i < SZ(s); i++)
    cs[i] = s[i];
  auto ret = sa_is(cs);
  for (int i = 0; i < SZ(ret) - 1; i++)
    ret[i] = ret[i + 1];
  ret.pop_back();
  return ret;
}

int main() {
  string s;
  cin >> s;

  vector<int> sa = suffix_array(s);

  // print sa
  // for (int i = 0; i < SZ(sa); i++)
  //   cout << sa[i] << " \n"[i == SZ(sa) - 1];

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
