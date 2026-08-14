#ifndef INCLUDE_DAY_21_H
#define INCLUDE_DAY_21_H

#include <optional>
#include <string>

namespace Day21 {

using namespace std;

class Item {
  string name;
  int cost;
  int damage;
  int armor;

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
};

class Warrior {
private:
  int hp;
  Warrior() {};

public:
  virtual int get_damage() const = 0;
  virtual int get_armor() const = 0;

  inline void reduce_hp(const int attack) { hp -= attack; }

  inline bool is_alive() const { return hp >= 0; }

  Warrior(int hp) : hp(hp) {};
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
  int get_damage() const override { return damage; }

  int get_armor() const override { return armor; }
};

bool fight(Player *player, Boss *boss);

} // namespace Day21

#endif
