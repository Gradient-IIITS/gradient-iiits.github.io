#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define INF 1000000002;

using namespace std;

static int n, sqrt_n, block_count;

void prepare_blocks(vector<int>& values, vector<int>& blocks) {
  for (int i = 0; i < block_count; i++) {
    int mx = -INF;
    for (int j = 0; j < sqrt_n && (i * sqrt_n + j) < n; j++) {
      mx = max(mx, values[i * sqrt_n + j]);
    }
    blocks[i] = mx;
  }
}

void update_value(vector<int>& values, vector<int>& blocks, int i, int A) {
  values[i] = A;
  int s_idx = (i / sqrt_n) * sqrt_n;
  int mx = -INF;
  for (int j = 0; j < sqrt_n && (s_idx + j) < n; j++) {
    mx = max(mx, values[s_idx + j]);
  }
  blocks[s_idx / sqrt_n] = mx;
}

int range_query(vector<int>& values, vector<int>& blocks, int L, int R) {
  int s_idx = L / sqrt_n;
  int e_idx = R / sqrt_n;
  if (s_idx == e_idx) {
    int mx = -INF;
    for (int i = L; i <= R; i++) {
      mx = max(mx, values[i]);
    }
    return mx;
  }
  s_idx++;
  int mx = -INF;
  for (int j = L; j < n && j < (s_idx * sqrt_n); j++) {
    mx = max(mx, values[j]);
  }
  for (int j = (e_idx * sqrt_n); j <= R; j++) {
    mx = max(mx, values[j]);
  }
  for (int j = s_idx; j < e_idx; j++) {
    mx = max(mx, blocks[j]);
  }
  return mx;
}

int main() {
  n = 13;
  vector<int> a({1, -4, 6, 8, 9, 3, 5, 6, 12, 14, 11, 5, 8});
  sqrt_n = sqrt(n);
  block_count = (n + sqrt_n - 1) / sqrt_n;
  vector<int> blocks(block_count);
  prepare_blocks(a, blocks);
  cout << range_query(a, blocks, 3, 9) << " ";
  update_value(a, blocks, 4, 20);
  cout << range_query(a, blocks, 3, 9) << " ";
  update_value(a, blocks, 7, 30);
  cout << range_query(a, blocks, 3, 9) << "\n";
  return 0;
}