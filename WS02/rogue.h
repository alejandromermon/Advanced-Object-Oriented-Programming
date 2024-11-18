#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include <iostream>
#include <string>
#include "characterTpl.h"

namespace seneca {
	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue : public CharacterTpl<T> {
		// The basic defense of this character.
		int m_baseDefense{ 0 };
		// The basic attack power of this character.
		int m_baseAttack{ 0 };
		// The first special ability of this character.
		FirstAbility_t m_firstAbility{};
		// The second special ability of this character.
		SecondAbility_t m_secondAbility{};
		// The two weapons the character can use in battle.
		seneca::Dagger m_weapon{};
	public:
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) :
			CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {}
		Rogue(const Rogue& src) : CharacterTpl<T>(src.getName().c_str(), src.getHealthMax()),
			m_baseDefense(src.m_baseDefense), m_baseAttack(src.m_baseAttack) {}
		// Returns the damage that character can do in an attack.
		int getAttackAmnt() const {
			return static_cast<int>(m_baseAttack + 2 * (static_cast<double>(m_weapon)));
		}
		// Return the base defense value.
		int getDefenseAmnt() const { return m_baseDefense; }
		// Creates a copy of the current instance and returns its address to the client.
		Character* clone() const { return new Rogue(*this); }
		// Attacks the enemy received as parameter and inflicts damage to it.
		void attack(Character* enemy) {
			int damage;

			std::cout << Character::getName() << " is attacking " << enemy->getName() << '.' << std::endl;

			m_firstAbility.useAbility(this);
			m_secondAbility.useAbility(this);
			
			damage = getAttackAmnt();

			m_firstAbility.transformDamageDealt(damage);
			m_secondAbility.transformDamageDealt(damage);

			std::cout << "   Rogue deals " << damage << " melee damage!" << std::endl;

			enemy->takeDamage(damage);
		}
		// Some other character inflicts damage to the current barbarian in the amount specified as parameter.
		void takeDamage(int dmg) {
			std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl
				<< "    Barbarian has a defense of " << m_baseDefense <<
				". Reducing damage received." << std::endl;

			dmg = dmg - m_baseDefense > -1 ? dmg - m_baseDefense : 0;

			m_firstAbility.transformDamageReceived(dmg);
			m_secondAbility.transformDamageReceived(dmg);

			this->CharacterTpl<T>::takeDamage(dmg);
		}
	};
}
#endif // !SENECA_ROGUE_H
