#include <algorithm>
#include <map>
#include <string>

using namespace std;

class Solution {
public:
  string minWindow(string s, string t) {
    map<char, int> m;

    // count all occurence of char in target
    for (auto c : t) {
      m[c]++;
    }
    int len = s.length();
    int fulfilled = t.length();

    int l, r = 0; // pointers to string position
    int L, R = 0; // current minimum window
    while (l != len && r != len) {
      if (fulfilled == 0) {
        if ((r - l) == t.length()) {
          return s.substr(l, r);
        }

        if ((r - l) < (R - L)) {
          R = r;
          L = l;
        }

        auto lit = m.find(s[l]);
        lit->second++;
        if (lit->second == 1) {
          fulfilled = t.length();
          l = r;
          continue;
        }

        l++;
        continue;
      }

      auto rit = m.find(s[r]);
      if (rit != m.end()) { // found
        rit->second--;
        if (rit->second >= 0) {
          fulfilled--;
        }
      }
      r++;
    }
    return s.substr(L, R);
  }
};
