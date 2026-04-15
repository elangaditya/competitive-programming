#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

vector<int> global_A;
vector<int> global_B;

int get_cost(int index, bool lp, bool rp) {
  if (!lp && !rp) {
    return 0;
  } else if (lp && rp) {
    return global_B[index];
  }
}
