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
  inline int get_cost() const { return cost; }
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

vector<Weapon> weapons();

vector<Armor> armors();

vector<Ring> rings();

class Warrior {
private:
  Warrior() {};

protected:
  int hp;

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

  inline int equip_cost() const {
    int result = 0;
    if (weapon) {
      result += weapon.value().get_cost();
    }
    if (armor) {
      result += armor.value().get_cost();
    }
    if (left_ring) {
      result += left_ring.value().get_cost();
    }
    if (right_ring) {
      result += left_ring.value().get_cost();
    }
    return result;
  }
};

class Boss : public Warrior {
  int damage;
  int armor;

  Boss() = delete;

public:
  explicit Boss(const Boss &other)
      : Warrior(other.hp), damage(other.damage), armor(other.armor) {}

  explicit Boss(const int hp, const int damage, const int armor)
      : Warrior(hp), damage(damage), armor(armor) {}
  int get_damage() const override { return damage; }

  int get_armor() const override { return armor; }
};

bool fight(Player *player, Boss *boss);

int solve_day21_pt1();

} // namespace Day21

#endif
