#include "day21.hpp"

namespace Day21 {

bool turn(Warrior &attacker, Warrior &defender) {
  const int damage = attacker.get_damage();
  const int armor = defender.get_armor();

  int attack = damage - armor;
  if (attack <= 0) {
    attack = 1;
  }
  defender.reduce_hp(attack);
  return !defender.is_alive();
}

bool fight(Player *player, Boss *boss) {
  Warrior *attacker = player;
  Warrior *defender = boss;

  while (!turn(*attacker, *defender)) {
    swap(attacker, defender);
  }

  return attacker == player;
}

} // namespace Day21
