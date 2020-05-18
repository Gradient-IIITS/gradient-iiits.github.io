#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n = 10;
  vector<int> a = {1, 2, -5, 9, -3, 0, -2, 9, 1, 2};

  vector<int> lg(n + 1);

  lg[0] = -1;

  for (int i = 1; i <= n; i++) {
    lg[i] = lg[i / 2] + 1;
  }

  int k = lg[n];

  vector<vector<int>> queries(n, vector<int>(k));

  for (int i = 0; i < n; i++) {
    queries[i][0] = a[i];
  }

  for (int i = 1; i < k; i++) {
    for (int j = 0; (j + (1 << i)) <= n; j++) {
      queries[j][i] =
          min(queries[j][i - 1], queries[j + (1 << (i - 1))][i - 1]);
    }
  }

  int vals[][2] = {{0, 5}, {0, 6}, {3, 7}, {4, 9}, {2, 8}};

  for (auto x : vals) {
    int size = x[1] - x[0] + 1;
    cout << min(queries[x[0]][lg[size]],
                queries[x[1] - (1 << lg[size]) + 1][lg[size]])
         << "\n";
  }
}