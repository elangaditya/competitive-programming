#include <bits/stdc++.h>
#include <functional>
#include <queue>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'shortestPath' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY a
 *  2. 2D_INTEGER_ARRAY queries
 */

struct Node {
  int row, col, weight;

  bool operator>(const Node &n) const { return this->weight > n.weight; }
};

vector<int> shortestPath(vector<vector<int>> a, vector<vector<int>> queries) {
  for (auto &q : queries) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    int s_row = q[0];
    int s_col = q[1];
    int t_row = q[2];
    int t_col = q[3];

    pq.push({s_row, s_col, 0});

    while (!pq.empty()) {
      Node n = pq.top();
      pq.pop();

      // edge detection
    }

    // path not found should be impossible
  }
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string first_multiple_input_temp;
  getline(cin, first_multiple_input_temp);

  vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

  int n = stoi(first_multiple_input[0]);

  int m = stoi(first_multiple_input[1]);

  vector<vector<int>> a(n);

  for (int i = 0; i < n; i++) {
    a[i].resize(m);

    string a_row_temp_temp;
    getline(cin, a_row_temp_temp);

    vector<string> a_row_temp = split(rtrim(a_row_temp_temp));

    for (int j = 0; j < m; j++) {
      int a_row_item = stoi(a_row_temp[j]);

      a[i][j] = a_row_item;
    }
  }

  string q_temp;
  getline(cin, q_temp);

  int q = stoi(ltrim(rtrim(q_temp)));

  vector<vector<int>> queries(q);

  for (int i = 0; i < q; i++) {
    queries[i].resize(4);

    string queries_row_temp_temp;
    getline(cin, queries_row_temp_temp);

    vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

    for (int j = 0; j < 4; j++) {
      int queries_row_item = stoi(queries_row_temp[j]);

      queries[i][j] = queries_row_item;
    }
  }

  vector<int> result = shortestPath(a, queries);

  for (size_t i = 0; i < result.size(); i++) {
    fout << result[i];

    if (i != result.size() - 1) {
      fout << "\n";
    }
  }

  fout << "\n";

  fout.close();

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(),
          find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
