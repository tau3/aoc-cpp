#ifndef INCLUDE_DAY_21_H
#define INCLUDE_DAY_21_H

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace Day21 {

using namespace std;

class Item {
protected:
  string name;
  int cost;
  int damage;
  int armor;

private:
  Item() {};

public:
  explicit Item(const string &name, const int cost, const int damage,
                const int armor)
      : name(name), cost(cost), damage(damage), armor(armor) {};

public:
  inline int get_damage() const { return damage; }
  inline int get_armor() const { return armor; }
};

class Weapon : public Item {
public:
  explicit Weapon(const string &name, const int cost, const int damage,
                  const int armor)
      : Item(name, cost, damage, armor) {};
};

class Armor : public Item {
public:
  explicit Armor(const string &name, const int cost, const int damage,
                 const int armor)
      : Item(name, cost, damage, armor) {};
};

class Ring : public Item {
public:
  explicit Ring(const string &name, const int cost, const int damage,
                const int armor)
      : Item(name, cost, damage, armor) {};

  // TODO move from class
  inline bool operator==(const Ring &other) const {
    return name == other.name && cost == other.cost && damage == other.damage &&
           armor == other.armor;
  }
};

vector<Weapon> weapons() {
  static vector<Weapon> weapons = {
      Weapon("Dagger", 8, 4, 0),
      Weapon("Shortsword", 10, 5, 0),
      Weapon("Warhammer", 25, 6, 0),
      Weapon("Longsword", 40, 7, 0),
  };
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

class Warrior {
private:
  int hp;
  Warrior() {};

public:
  virtual int get_damage() const = 0;
  virtual int get_armor() const = 0;

  inline void reduce_hp(const int attack) { hp -= attack; }

  inline bool is_alive() const { return hp >= 0; }

  explicit Warrior(int hp) : hp(hp) {};
  Warrior(const Warrior &) = delete;
  Warrior &operator=(const Warrior &) = delete;
  virtual ~Warrior() = default;
};

class Player : public Warrior {
  optional<Weapon> weapon;
  optional<Armor> armor;
  optional<Ring> left_ring;
  optional<Ring> right_ring;

  Player() = delete;

public:
  explicit Player(const int hp, const optional<Weapon> &weapon,
                  const optional<Armor> &armor, const optional<Ring> &left_ring,
                  const optional<Ring> &right_ring)
      : Warrior(hp), weapon(weapon), armor(armor), left_ring(left_ring),
        right_ring(right_ring) {
    if (left_ring.has_value() && right_ring.has_value()) {
      if (left_ring.value() == right_ring.value()) {
        throw runtime_error("repeated ring");
      }
    }
  };

  inline int get_damage() const override {
    int result = 0;
    if (weapon) {
      result += weapon.value().get_damage();
    }
    if (armor) {
      result += armor.value().get_damage();
    }
    if (left_ring) {
      result += left_ring.value().get_damage();
    }
    if (right_ring) {
      result += left_ring.value().get_damage();
    }
    return result;
  }

  inline int get_armor() const override {
    int result = 0;
    if (weapon) {
      result += weapon.value().get_armor();
    }
    if (armor) {
      result += armor.value().get_armor();
    }
    if (left_ring) {
      result += left_ring.value().get_armor();
    }
    if (right_ring) {
      result += left_ring.value().get_armor();
    }
    return result;
  }
};

class Boss : public Warrior {
  int damage;
  int armor;

  Boss() = delete;

public:
  explicit Boss(const int hp, const int damage, const int armor)
      : Warrior(hp), damage(damage), armor(armor) {}
  int get_damage() const override { return damage; }

  int get_armor() const override { return armor; }
};

bool fight(Player *player, Boss *boss);

} // namespace Day21

#endif
