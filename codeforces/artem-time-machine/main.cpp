#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// operations:
// 1. add integer to multiset
// 2. remove one instance of integer in multiset
// 3. count instance of integer in multiset

/*
Idea:
- use a fenwick tree
  - what to use as index? time value or integer instance itself:
    - time value:
      - use map as value which has all the frequencies of integers <-- try this
first
*/
const int N = 100000;

struct Query {
  int op, time, val;
};

bool comp(const Query &a, const Query &b) {
  if (a.op == 3 || b.op == 3) {
    return false;
  }

  return a.time < b.time;
}

void add(vector<map<int, int>> &arr, int i, int val) {
  while (i < arr.size()) {
    arr[i][val]++;
    /*cout << i << " " << arr[i][val] << endl;*/
    i += i & -i;
  }
}

void remove(vector<map<int, int>> &arr, int i, int val) {
  while (i < arr.size()) {
    arr[i][val]--;
    i += i & -i;
  }
}

int get(vector<map<int, int>> &arr, int i, int val) {
  int sum = 0;
  while (i > 0) {
    sum += arr[i][val];
    /*cout << i << " " << sum << endl;*/
    i -= i & -i;
  }

  return sum;
}

int main() {
  int n;

  vector<Query> t(N + 1, {0, N + 1, 0}); // {op, val}
  vector<int> res;

  cin >> n;
  vector<map<int, int>> bit(N + 1);

  for (int i = 0; i < n; i++) {
    Query q;
    scanf("%d %d %d", &q.op, &q.time, &q.val);

    t[i] = q;
  }

  /*sort(t.begin(), t.end(), comp);*/

  for (auto &e : t) {
    if (e.op == 0) {
      continue;
    }
    /*cout << e.time << endl;*/
    switch (e.op) {
    case 1:
      /*cout << "add " << e.time << " " << e.val << endl;*/
      add(bit, e.time, e.val);
      break;
    case 2:
      /*cout << "del " << e.time << " " << e.val << endl;*/
      remove(bit, e.time, e.val);
      break;
    case 3:
      /*cout << "get " << e.time << " " << e.val << endl;*/
      int x = get(bit, e.time, e.val);
      res.push_back(x);
    }

    /*cout << "end" << endl;*/
  }

  for (auto &e : res) {
    cout << e << endl;
  }
}
