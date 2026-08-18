#include "util.hpp"
#include <string>
#include <vector>

namespace Day23 {

using namespace std;

struct Computer {
  size_t a = 1;
  size_t b = 0;
  size_t rip = 0;
};

void exec_command(Computer &computer, const string &line) {
  const vector<string> tokens = util::split(line, " ");

  const string command = tokens[0];

  if (command == "hlf") {
    const string reg = tokens[1];
    if (reg == "a") {
      computer.a /= 2;
    } else {
      computer.b /= 2;
    }
    computer.rip++;
  } else if (command == "tpl") {
    const string reg = tokens[1];
    if (reg == "a") {
      computer.a *= 3;
    } else {
      computer.b *= 2;
    }
    computer.rip++;
  } else if (command == "inc") {
    const string reg = tokens[1];
    if (reg == "a") {
      computer.a++;
    } else {
      computer.b++;
    }
    computer.rip++;
  } else if (command == "jmp") {
    const string offset_raw = tokens[1];
    const long offset = stol(offset_raw);
    computer.rip += offset;
  } else if (command == "jie") {
    const string offset_raw = tokens[2];
    const long offset = stol(offset_raw);

    string reg = tokens[1];
    reg.pop_back();

    size_t value = reg == "a" ? computer.a : computer.b;
    if (value % 2 == 0) {
      computer.rip += offset;
    } else {
      computer.rip++;
    }
  } else if (command == "jio") {
    const string offset_raw = tokens[2];
    const long offset = stol(offset_raw);

    string reg = tokens[1];
    reg.pop_back();

    size_t value = reg == "a" ? computer.a : computer.b;
    if (value == 1) {
      computer.rip += offset;
    } else {
      computer.rip++;
    }
  }
}

size_t solve_day23_pt1(const vector<string> &input) {
  Computer computer;
  while (computer.rip < input.size()) {
    cout << computer.a << " " << computer.b << " " << computer.rip << endl;
    const string instruction = input[computer.rip];
    exec_command(computer, instruction);
  }
  return computer.b;
}

} // namespace Day23
