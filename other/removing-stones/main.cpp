#include <vector>

using namespace std;

int calculate_removal_cost(int index, vector<int> removed, const vector<int> &A,
                           const vector<int> &B) {
  int n = A.size();
  int cost = 0;

  bool left_neighbor = false;
  bool right_neighbor = false;

  if (index > 0 && removed[index - 1] == 0) {
    left_neighbor = true;
  }
  if (index < n - 1 && removed[index + 1] == 0) {
    right_neighbor = true;
  }

  if (left_neighbor && right_neighbor) {
    cost = B[index];
  } else if (left_neighbor || right_neighbor) {
    cost = A[index];
  }

  return cost;
}

int solve(int index, vector<int> removed, const vector<int> &A,
          const vector<int> &B) {
  // decision is whether to take or not take current stone.

  // Decision 1: take stone
  int cost = calculate_removal_cost(index, removed, A, B);
  removed[index] = 1;

  return 0
}

int min_stone_removal_cost(const vector<int> &A, const vector<int> &B) {
  int n = A.size();

  vector<int> removed(n, 0);

  return solve(0, removed, A, B);
}
