#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n = 10;
  vector<int> a = {1, 2, -5, 9, -3, 0, -2, 9, 1, 2};
  int k = 0;
  while (n >> k) k++;

  vector<vector<int>> queries(n, vector<int>(k));

  for (int i = 0; i < n; i++) {
    queries[i][0] = a[i];
  }

  for (int i = 1; i < k; i++) {
    for (int j = 0; (j + (1 << i)) <= n; j++) {
      queries[j][i] = queries[j][i - 1] + queries[j + (1 << (i - 1))][i - 1];
    }
  }

  int vals[][2] = {{0, 5}, {0, 6}, {3, 7}, {4, 9}, {2, 8}};

  for (auto x : vals) {
    int sum = 0;
    int size = x[1] - x[0] + 1;
    int pos = x[0];
    for (int i = k - 1; i >= 0; i--) {
      if (size - (1 << i) >= 0) {
        sum += queries[pos][i];
        size -= 1 << i;
        pos += 1 << i;
      }
    }
    cout << sum << "\n";
  }
}