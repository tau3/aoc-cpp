#include "util.hpp"
#include <cassert>
#include <format>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace Day10 {

using namespace std;

class Node {
private:
  Node() = delete;

public:
  Node(const Node &node) = delete;
  Node &operator=(const Node &node) = delete;
  virtual ~Node() = default;

  Node(const int id) : id(id) {}

  virtual void accept_chip(const int chip) = 0;

  virtual string display() const = 0;

  int get_id() const { return id; }

protected:
  int id;
};

class Bot : public Node {
private:
  optional<int> value;
  shared_ptr<Node> low;
  shared_ptr<Node> high;

public:
  Bot(const int id) : Node(id) {}

  void accept_chip(const int chip) override {
    assert(low && high);

    if (!value.has_value()) {
      value = chip;
      return;
    }

    const int lower = min(value.value(), chip);
    const int higher = max(value.value(), chip);
    if (lower == 17 && higher == 61) {
      cout << "pt1: " << get_id() << endl;
    }

    value.reset();

    low->accept_chip(lower);
    high->accept_chip(higher);
  }

  void setup(shared_ptr<Node> lower, shared_ptr<Node> higher) {
    low = lower;
    high = higher;
  }

  virtual string display() const override {
    assert(low && high);
    return "bot " + to_string(get_id()) + ", low=" + to_string(low->get_id()) +
           " high=" + to_string(high->get_id()) +
           " val=" + (value ? to_string(value.value()) : "null");
  }
};

class Output : public Node {
private:
  optional<int> value;

public:
  Output(const int id) : Node(id) {}

  void accept_chip(const int chip) override {
    if (value.has_value()) {
      throw runtime_error(std::format("output {} contains {}, received {}", id,
                                      value.value(), chip));
    }

    value = chip;
  }

  int get_value() const {
    if (!value) {
      throw runtime_error(std::format("no value in {}", get_id()));
    }
    return value.value();
  }

  virtual string display() const override {
    return "output " + to_string(get_id()) +
           ", val=" + (value ? to_string(value.value()) : "null");
  }
};

shared_ptr<Node> get(unordered_map<string, shared_ptr<Node>> &nodes,
                     const bool is_bot, const int id) {
  string key = is_bot ? "b" : "o";
  key += to_string(id);

  if (nodes.find(key) == nodes.end()) {
    shared_ptr<Node> node;
    if (is_bot) {
      node = make_shared<Bot>(id);
    } else {
      node = make_shared<Output>(id);
    }
    nodes.emplace(key, node);
  }

  return nodes[key];
}

int solve_day10(const vector<string> &input) {
  unordered_map<string, shared_ptr<Node>> nodes;

  vector<string> commands;
  for (const string &line : input) {
    if (line.starts_with("value")) {
      commands.push_back(line);
      continue;
    }

    const vector<string> tokens = util::split(line, " ");
    const int id = stoi(tokens[1]);
    const int id_lower = stoi(tokens[6]);
    const int id_higher = stoi(tokens[11]);
    const bool is_bot_lower = tokens[5] == "bot";
    const bool is_bot_higher = tokens[10] == "bot";

    const shared_ptr<Node> lower = get(nodes, is_bot_lower, id_lower);
    const shared_ptr<Node> higher = get(nodes, is_bot_higher, id_higher);
    shared_ptr<Bot> bot = static_pointer_cast<Bot>(get(nodes, true, id));

    bot->setup(lower, higher);
  }

  for (const string &command : commands) {
    const vector<string> tokens = util::split(command, " ");
    const int value = stoi(tokens[1]);
    const string key = "b" + tokens[5];
    shared_ptr<Node> bot = nodes[key];
    bot->accept_chip(value);
  }

  const int result = static_pointer_cast<Output>(nodes["o0"])->get_value() *
                     static_pointer_cast<Output>(nodes["o1"])->get_value() *
                     static_pointer_cast<Output>(nodes["o2"])->get_value();
  cout << "pt2: " << result << endl;

  return 0;
}

} // namespace Day10
