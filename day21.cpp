#include "day21.hpp"
#include <climits>

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

vector<Weapon> weapons() {
  // clang-format off
  static vector<Weapon> weapons = {
      Weapon("Dagger", 8, 4, 0),
      Weapon("Shortsword", 10, 5, 0),
      Weapon("Warhammer", 25, 6, 0),
      Weapon("Longsword", 40, 7, 0),
  };
  // clang-format on
  return weapons;
}

vector<Armor> armors() {
  // clang-format off
  static vector<Armor> armors = {
      Armor("Leather", 13, 0, 1),
      Armor("Chainmail", 31, 0, 2),
      Armor("Splintmail", 53, 0, 3),
      Armor("Bandedmail", 75, 0, 4),
      Armor("Platemail", 102, 0, 5),
  };
  // clang-format on
  return armors;
}

vector<Ring> rings() {
  // clang-format off
  static vector<Ring> rings = {
      Ring("Damage +1", 25, 1, 0),
      Ring("Damage +2", 50, 2, 0),
      Ring("Damage +3", 100, 3, 0),
      Ring("Defense +1", 20, 0, 1),
      Ring("Defense +2", 40, 0, 2),
      Ring("Defense +3", 80, 0, 3),
  };
  // clang-format on
  return rings;
}

void solve_day21_pt1() {
  const Boss boss = Boss(1, 2, 3);
  int result = INT_MAX;
  for (const Weapon &weapon : weapons()) {
    for (const Armor &armor : armors()) {
      for (const Ring &left_ring : rings()) {
        for (const Ring &right_ring : rings()) {
          if (left_ring == right_ring) {
            continue;
          }

          Player player(100, weapon, armor, left_ring, right_ring);
          bool is_player_won = fight(player, boss);
          const int equip_price = player.equip_price();
          if (is_player_won && equip_price < result) {
            result = equip_price;
          }
        }
      }
    }
  }
}

} // namespace Day21
