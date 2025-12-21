#include "gauss.hpp"
#include <cassert>
#include <cstddef>
#include <vector>

namespace Gauss {
using namespace std;

void check_size(const vector<vector<num_t>> &matrix) {
  const size_t n = matrix.size();
  assert(n > 0);
  for (const vector<num_t> &line : matrix) {
    assert(line.size() == (n + 1));
  }
}

#ifdef DEBUG
void print(const vector<vector<num_t>> &matrix) {
  for (const vector<num_t> &line : matrix) {
    for (const num_t i : line) {
      cout << i << " ";
    }
    cout << endl;
  }
}
#endif

vector<num_t> gauss(vector<vector<num_t>> &matrix) {
  check_size(matrix);

  const size_t n = matrix.size();
  for (size_t i = 0; i < n; i++) {
    const num_t div = matrix[i][i];
    for (size_t j = i; j < n + 1; j++) {
      matrix[i][j] = matrix[i][j] / div;
    }

    for (size_t j = i + 1; j < n; j++) {
      const auto factor = matrix[j][i] / matrix[i][i] * -1;
      for (size_t k = i; k < n + 1; k++) {
        matrix[j][k] += (matrix[i][k] * factor);
      }
    }
  }

  for (size_t i = n - 1; i > 0; i--) {
    for (size_t j = i; j-- > 0;) {
      const auto factor = matrix[j][i] / matrix[i][i] * -1;
      for (size_t k = j; k < n + 1; k++) {
        matrix[j][k] += (matrix[i][k] * factor);
      }
    }
  }

  vector<num_t> result;
  for (size_t i = 0; i < n; i++) {
    result.push_back(matrix[i][n]);
  }
  return result;
}

} // namespace Gauss
