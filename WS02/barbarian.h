#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include <string>
#include "characterTpl.h"

namespace seneca {
	template <typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T> {
		// The basic defense of this character.
		int m_baseDefense{ 0 };
		// The basic attack power of this character.
		int m_baseAttack{ 0 };
		// The special ability of this character.
		Ability_t m_ability{};
		// The two weapons the character can use in battle.
		Weapon_t m_weapon[2]{};
	public:
		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
			Weapon_t primaryWeapon, Weapon_t secondaryWeapon) : CharacterTpl<T>(name, healthMax),
			m_baseDefense(baseDefense), m_baseAttack(baseAttack),
			m_weapon{ primaryWeapon, secondaryWeapon } {}
		Barbarian(const Barbarian& src) : CharacterTpl<T>(src.getName().c_str(), src.getHealthMax()),
			m_baseDefense(src.m_baseDefense), m_baseAttack(src.m_baseAttack),
			m_weapon{ src.m_weapon[0], src.m_weapon[1]} {}
		// Returns the damage that character can do in an attack.
		int getAttackAmnt() const {
			return static_cast<int>(m_baseAttack + (static_cast<double>(m_weapon[0]) / 2) +
				(static_cast<double>(m_weapon[1]) / 2));
		}
		// Return the base defense value.
		int getDefenseAmnt() const { return m_baseDefense; }
		// Creates a copy of the current instance and returns its address to the client.
		Character* clone() const { return new Barbarian(*this); }
		// Attacks the enemy received as parameter and inflicts damage to it.
		void attack(Character* enemy) {
			int damage;

			std::cout << Character::getName() << " is attacking " << enemy->getName() << '.' << std::endl;

			m_ability.useAbility(this);

			damage = getAttackAmnt();

			m_ability.transformDamageDealt(damage);

			std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;

			enemy->takeDamage(damage);
		}
		// Some other character inflicts damage to the current barbarian in the amount specified as parameter.
		void takeDamage(int dmg) {
			std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl
				<< "    Barbarian has a defense of " << m_baseDefense <<
				". Reducing damage received." << std::endl;

			dmg = dmg - m_baseDefense > -1 ? dmg - m_baseDefense : 0;

			m_ability.transformDamageReceived(dmg);

			this->CharacterTpl<T>::takeDamage(dmg);
		}
	};
}
#endif // !SENECA_BARBARIAN_H
