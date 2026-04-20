#include <climits>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Solution {
public:
  string minWindow(string s, string t) {
    map<char, int> m;
    if (s.length() < t.length())
      return "";

    // count all occurence of char in target
    for (auto c : t) {
      m[c]++;
    }
    int len = s.length();
    int fulfilled = t.length();

    int l = 0, r = 0;       // pointers to string position
    int L = 0, R = INT_MAX; // current minimum window
    while (r != len) {
      auto it = m.find(s[r]);
      if (it != m.end()) {
        it->second--;
        if (it->second >= 0) {
          fulfilled--;
        }
      }

      while (fulfilled == 0) {
        if ((r + 1 - l) == t.length()) {
          return s.substr(l, r + 1 - l);
        }

        auto it2 = m.find(s[l]);
        if (it2 != m.end()) {
          it2->second++;
          if (it2->second > 0) {
            fulfilled++;

            if ((r - l) < (R - L)) {
              R = r;
              L = l;
            }
          }
        }

        l++;
      }
      r++;
    }

    if (R == INT_MAX) {
      return "";
    }
    return s.substr(L, R - L + 1);
  }
};

int main() {
  Solution sol;
  cout << sol.minWindow("ADOBECODEBANC", "ABC") << endl;
  cout << sol.minWindow("ABC", "AC") << endl;
  cout << sol.minWindow("A", "C") << endl;
}
