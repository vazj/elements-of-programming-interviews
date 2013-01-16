#include <iostream>
#include <array>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

void print_matrix(vector<vector<bool> > &A) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A.size(); ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
}

// @include
void flip_color(vector<vector<bool> > &A, const int &x, const int &y) {
  vector<vector<bool> > processed(A.size(), vector<bool>(A.size(), false));
  const array<array<int, 2>, 4> dir = {-1, 0, 1, 0, 0, -1, 0, 1};

  queue<pair<int, int> > q;
  q.emplace(x, y);
  processed[x][y] = true;
  while (!q.empty()) {
    pair<int, int> curr(q.front());
    for (auto &d : dir) {
      pair<int, int> next(curr.first + d[0], curr.second + d[1]);
      if (next.first >= 0 && next.first < A.size() &&
          next.second >= 0 && next.second < A[next.first].size() &&
          !processed[next.first][next.second] &&
          A[next.first][next.second] == A[curr.first][curr.second]) {
        processed[next.first][next.second] = true;
        q.emplace(next);
      }
    }
    A[curr.first][curr.second] = !A[curr.first][curr.second];  // flip color
    q.pop();
  }
}
// @exclude

int main(int argc, char *argv[]) {
  int n;
  srand(time(nullptr));
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100;
  }
  vector<vector<bool> > A(n, vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      A[i][j] = rand() & 1;
    }
  }
  int i = rand() % n, j = rand() % n;
  cout << i << ' ' << j << ' ' << A[i][j] << endl;
  print_matrix(A);
  flip_color(A, i, j);
  cout << endl;
  print_matrix(A);
  return 0;
}