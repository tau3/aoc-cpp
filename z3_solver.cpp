#include "z3_solver.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <z3++.h>

namespace Z3 {

using num_t = double;

std::vector<num_t>
solve_system(const std::vector<std::vector<num_t>> &coefficients,
            const std::vector<num_t> &constants) {
  z3::context context;

  std::vector<z3::expr> vars;
  for (size_t i = 0; i < coefficients[0].size(); ++i) {
    std::string name = "x" + std::to_string(i);
    vars.push_back(context.real_const(name.c_str()));
  }

  z3::optimize optimizer(context);
  optimizer.minimize(vars.back());

  for (size_t i = 0; i < coefficients.size(); ++i) {
    z3::expr equation = context.int_val(0);
    for (size_t j = 0; j < coefficients[i].size(); ++j) {
      equation = equation + context.fpa_val(coefficients[i][j]) * vars[j];
    }
    optimizer.add(equation == constants[i]);
  }

  if (optimizer.check() == z3::sat) {
    z3::model model = optimizer.get_model();
    std::vector<num_t> results;
    for (size_t i = 0; i < vars.size(); ++i) {
      results.push_back(model.eval(vars[i]).as_double());
    }
    return results;
  } else {
    throw std::runtime_error("Unsatisfiable");
  }
}

int foo() {
  std::vector<std::vector<num_t>> coefficients = {
      {2, 4},
      {1, 2},
  };
  std::vector<num_t> constants = {10, 5};

  try {
    std::vector<num_t> results = solve_system(coefficients, constants);

    std::cout << "Satisfiable (Infinite Solutions):" << std::endl;
    for (size_t i = 0; i < results.size(); ++i) {
      std::cout << "Variable x" << i << " = " << results[i] << std::endl;
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}

} // namespace Z3
