#include "day22.hpp"
#include <cassert>
#include <deque>
#include <stdexcept>

namespace Day22 {

using namespace std;

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

  State new_state = {new_player, new_boss, false, state.mana_spent + price,
                     state.dots};

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

  State new_state = {new_player, new_boss, false, state.mana_spent + price,
                     state.dots};

  states.push_back(new_state);
}

void maybe_enque_dot(const State &state, std::deque<State> &states,
                     const int price, const Effect spell, const int ticks) {
  assert(state.is_player);

  if ((state.player.mana < price) || (state.dots.at(spell) > 0)) {
    return;
  }

  unordered_map<Effect, int> new_dots = state.dots;
  new_dots[spell] = ticks;

  assert(new_dots.at(spell) == ticks);

  State new_state = {state.player, state.boss, false, state.mana_spent + price,
                     new_dots};

  states.push_back(new_state);
}

void apply_effects(State &state) {
  if (state.dots.at(Effect::SHIELD) > 0) {
    state.dots[Effect::SHIELD]--;
  }

  if (state.dots.at(Effect::POISON) > 0) {
    state.dots[Effect::POISON]--;
  }
  if (state.dots.at(Effect::POISON) > 0) {
    state.boss.hp -= 3;
  }

  if (state.dots.at(Effect::RECHARGE) > 0) {
    state.dots[Effect::RECHARGE]--;
  }
  if (state.dots.at(Effect::RECHARGE) > 0) {
    state.player.mana += 101;
  }
}

void enque_boss_turn(const State &state, std::deque<State> &states) {
  assert(!state.is_player);

  int damage = state.boss.damage;
  if (state.dots.at(Effect::SHIELD) > 0) {
    damage -= 7;
  }
  if (damage <= 0) {
    damage = 1;
  }

  Player new_player = state.player;
  new_player.hp -= damage;

  State new_state = {new_player, state.boss, true, state.mana_spent,
                     state.dots};
  states.push_back(new_state);
}

int solve(const State &initial) {
  std::deque<State> states;
  states.push_back(initial);

  while (!states.empty()) {
    State state = states.front();
    states.pop_front();

    apply_effects(state);

    if ((state.player.hp <= 0) || (state.player.mana <= 0)) {
      continue;
    }
    if (state.boss.hp <= 0) {
      return state.mana_spent;
    }

    if (!state.is_player) {
      enque_boss_turn(state, states);
    } else {
      maybe_enque_magic_missle(state, states);
      maybe_enque_drain(state, states);

      maybe_enque_dot(state, states, 113, Effect::SHIELD, 6);
      maybe_enque_dot(state, states, 173, Effect::POISON, 6);
      maybe_enque_dot(state, states, 229, Effect::RECHARGE, 5);
    }
  }
  throw std::runtime_error("unreachable!");
}

} // namespace Day22
