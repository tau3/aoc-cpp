#include <cassert>
#include <deque>
#include <unordered_map>

namespace Day22 {

using namespace std;

enum class Spell { MAGIC_MISSLE, DRAIN, SHIELD, POISON, RECHARGE };

struct Player {
  int hp;
  int armor;
  int mana;
};

struct Boss {
  int hp;
  int damage;
};

struct State {
  Player player;
  Boss boss;
  bool is_player;
  int mana_spent;
  unordered_map<Spell, int> dots;
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
                     const int price, const Spell spell, const int ticks) {
  assert(state.is_player);

  if (state.player.mana < price || state.dots.at(spell) > 0) {
    return;
  }

  unordered_map<Spell, int> new_dots = state.dots;
  new_dots.emplace(spell, ticks);
  State new_state = {state.player, state.boss, false, state.mana_spent + price,
                     new_dots};

  states.push_back(new_state);
}

void apply_effects(State &state) {
  if (state.dots[Spell::SHIELD] > 0) {
    state.dots[Spell::SHIELD]--;
  }

  if (state.dots[Spell::POISON] > 0) {
    state.dots[Spell::POISON]--;
  }
  if (state.dots[Spell::POISON] > 0) {
    state.boss.hp -= 3;
  }

  if (state.dots[Spell::RECHARGE] > 0) {
    state.dots[Spell::RECHARGE]--;
  }
  if (state.dots[Spell::RECHARGE] > 0) {
    state.player.mana += 101;
  }
}

void enque_boss_turn(const State &state, std::deque<State> &states) {
  int damage = state.boss.damage;
  if (state.dots.at(Spell::SHIELD) > 0) {
    damage -= 7;
  }
  if (damage <= 0) {
    damage = 1;
  }

  State new_state = {state.player, state.boss, true, state.mana_spent,
                     state.dots};
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
    enque_boss_turn(state, states);
  } else {
    // TODO 1 function?
    maybe_enque_magic_missle(state, states);
    maybe_enque_drain(state, states);

    maybe_enque_dot(state, states, 113, Spell::SHIELD, 6);
    maybe_enque_dot(state, states, 173, Spell::POISON, 7);
    maybe_enque_dot(state, states, 229, Spell::RECHARGE, 5);
  }

  return solve(states);
}

} // namespace Day22
