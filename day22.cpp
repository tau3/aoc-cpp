#include <algorithm>
#include <cassert>
#include <deque>
#include <stdexcept>
#include <vector>

namespace Day22 {

using namespace std;

enum class Spell { MAGIC_MISSLE, DRAIN, SHIELD, POISON, RECHARGE };

struct Player {
  int hp;
  int armor;
  int mana;
  vector<pair<Spell, int>> effects;
};

struct Boss {
  int hp;
  int damage;
};

void turn(Player &attacker, Boss &defender) {
  for (pair<Spell, int> &effect : attacker.effects) {
    const Spell spell = effect.first;

    switch (spell) {

    case Spell::MAGIC_MISSLE:
      throw runtime_error("magic missle is not a dot");
    case Spell::DRAIN:
      throw runtime_error("drain is not a dot");
    case Spell::SHIELD:
      break;
    case Spell::POISON:
      defender.hp -= 3;
      break;
    case Spell::RECHARGE:
      attacker.mana += 101;
      break;
    }

    effect.second -= 1;
  }

  // TODO attack somehow
  // ...

  attacker.effects.erase(std::remove_if(
      attacker.effects.begin(), attacker.effects.end(),
      [](const pair<Spell, int> &effect) { return effect.second == 0; }));
}

struct State {
  Player player;
  Boss boss;
  bool is_player;
  int mana_spent;
};

void maybe_enque_magic_missle(const State &state, std::deque<State> &states) {
  assert(state.is_player);

  const int price = 53;
  if (state.player.mana < price) {
    return;
  }

  Player new_player = state.player;
  new_player.mana -= price;

  Boss new_boss = state.boss;
  new_boss.hp -= 4;
  State new_state = {new_player, new_boss, false, state.mana_spent + price};

  states.push_back(new_state);
}

void maybe_enque_drain(const State &state, std::deque<State> &states) {
  assert(state.is_player);

  const int price = 73;
  if (state.player.mana < price) {
    return;
  }

  Player new_player = state.player;
  new_player.mana -= price;
  new_player.hp += 2;

  Boss new_boss = state.boss;
  new_boss.hp -= 2;
  State new_state = {new_player, new_boss, false, state.mana_spent + price};

  states.push_back(new_state);
}

void maybe_enque_shield(const State &state, std::deque<State> &states) {
  assert(state.is_player);

  const int price = 113;
  if (state.player.mana < price || state.player.has_effect(Spell::SHIELD)) {
    return;
  }

  Player new_player = state.player;
  new_player.add_effect(Spell::SHIELD, 6);
  State new_state = {new_player, state.boss, false, state.mana_spent + price};

  states.push_back(new_state);
}

void maybe_enque_poison(const State &state, std::deque<State> &states) {
  assert(state.is_player);

  const int price = 173;
  if (state.player.mana < price || state.player.has_effect(Spell::POISON)) {
    return;
  }

  Player new_player = state.player;
  new_player.add_effect(Spell::POISON, 6);
  State new_state = {new_player, state.boss, false, state.mana_spent + price};

  states.push_back(new_state);
}

void maybe_enque_recharge(const State &state, std::deque<State> &states) {
  assert(state.is_player);

  const int price = 229;
  if (state.player.mana < price || state.player.has_effect(Spell::RECHARGE)) {
    return;
  }

  Player new_player = state.player;
  new_player.add_effect(Spell::RECHARGE, 5);
  State new_state = {new_player, state.boss, false, state.mana_spent + price};

  states.push_back(new_state);
}

int solve(std::deque<State> &states) {
  State state = states.front();
  states.pop_front();

  apply_effects(state);
  if (state.player.hp <= 0 || state.player.mana <= 0) {
    return MAX_INT;
  }
  if (state.boss.hp <= 0) {
    return state.mana_spent;
  }

  if (!state.is_player) {
    int damage = state.boss.damage - state.player.shield();
    if (damage <= 0) {
      damage = 1;
    }

    State new_state = {state.player, state.boss, true, state.mana_spent};
    states.push_back(new_state);
  } else {
    // TODO 1 function?
    maybe_enque_magic_missle(state, states);
    maybe_enque_drain(state, states);

    // TODO one function
    maybe_enque_shield(state, states);
    maybe_enque_poison(state, states);
    maybe_enque_recharge(state, states);
  }

  return solve(states);
}

} // namespace Day22
