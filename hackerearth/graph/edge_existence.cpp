#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N, M;

  cin >> N >> M;
  // cout << N << M << endl;
  vector<vector<bool>> adj(N, vector<bool>(N, 0));

  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    adj[x][y] = adj[y][x] = true; 
  }

  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    int x, y;
    cin >> x >> y;
    if (adj[x][y]) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
