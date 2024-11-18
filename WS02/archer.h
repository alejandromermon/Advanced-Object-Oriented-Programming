#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include <iostream>
#include <string>
#include "characterTpl.h"
#include "health.h"

namespace seneca {
	template <typename Weapon_t>
	class Archer : public CharacterTpl<seneca::SuperHealth> {
		// The basic defense of this character.
		int m_baseDefense{ 0 };
		// The basic attack power of this character.
		int m_baseAttack{ 0 };
		// The weapon the character can use in battle.
		Weapon_t m_weapon{};
	public:
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon) :
			CharacterTpl(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack),
			m_weapon(weapon) {}
		Archer(const Archer& src) :
			CharacterTpl(src.getName().c_str(), src.getHealthMax()), m_baseDefense(src.m_baseDefense),
			m_baseAttack(src.m_baseAttack), m_weapon(src.m_weapon) {}
		// Returns the damage that character can do in an attack.
		int getAttackAmnt() const { return static_cast<int>(m_baseAttack * 1.3); }
		// Rreturn the defense of this archer.
		int getDefenseAmnt() const { return static_cast<int>(m_baseDefense * 1.2); }
		// Creates a copy of the current instance and returns its address to the client.
		Character* clone() const { return new Archer(*this); }
		// Attacks the enemy received as parameter and inflicts damage to it.
		void attack(Character* enemy) {
			int damage;

			std::cout << getName() << " is attacking " << enemy->getName() << '.' << std::endl;

			damage = getAttackAmnt();

			std::cout << "   Archer deals " << damage << " ranged damage!" << std::endl;

			enemy->takeDamage(damage);
		}
		// Some other character inflicts damage to the current barbarian in the amount specified as parameter.
		void takeDamage(int dmg) {
			std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl
				<< "    Archer has a defense of " << m_baseDefense <<
				". Reducing damage received." << std::endl;

			dmg = dmg - m_baseDefense > -1 ? dmg - m_baseDefense : 0;

			this->CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
		}
	};
}
#endif // !SENECA_ARCHER_H
