#include <iostream>
#include <vector>
#include <z3++.h>

std::vector<double>
solveSystem(const std::vector<std::vector<double>> &coefficients,
            const std::vector<double> &constants) {
  z3::context c;
  // Declare variables
  std::vector<z3::expr> vars;
  for (size_t i = 0; i < coefficients[0].size(); ++i) {
    vars.push_back(c.real_const("x" + std::to_string(i))); // x0, x1, ...
  }

  // Create optimizer
  z3::optimize optimizer(c);

  // Minimize the last variable (assumed y)
  optimizer.minimize(vars.back());

  // Add the equations to the optimizer
  for (size_t i = 0; i < coefficients.size(); ++i) {
    z3::expr equation = c.int_val(0);
    for (size_t j = 0; j < coefficients[i].size(); ++j) {
      equation = equation + coefficients[i][j] * vars[j];
    }
    optimizer.add(equation == constants[i]);
  }

  // Check satisfiability
  if (optimizer.check() == z3::sat) {
    // Get the model
    z3::model m = optimizer.get_model();
    std::vector<double> results;
    for (size_t i = 0; i < vars.size(); ++i) {
      results.push_back(m.eval(vars[i]).get_numeral_double());
    }
    return results; // Return results as vector
  } else {
    throw std::runtime_error("Unsatisfiable");
  }
}

int foo() {
  std::vector<std::vector<double>> coefficients = {
      {2, 4}, // Coefficients for the first equation
      {1, 2}, // Coefficients for the second equation
  };
  std::vector<double> constants = {10, 5}; // Constants on the right-hand side

  try {
    // Call the function to solve the system and get results
    std::vector<double> results = solveSystem(coefficients, constants);

    // Output the results
    std::cout << "Satisfiable (Infinite Solutions):" << std::endl;
    for (size_t i = 0; i < results.size(); ++i) {
      std::cout << "Variable x" << i << " = " << results[i] << std::endl;
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
