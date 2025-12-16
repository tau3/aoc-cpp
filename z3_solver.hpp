#ifndef INCLUDE_Z3
#define INCLUDE_Z3

#include <vector>

namespace Z3 {

std::vector<double>
solve_system(const std::vector<std::vector<double>> &coefficients,
            const std::vector<double> &constants);
} // namespace Z3

#endif
