#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include <iostream>
#include "character.h"

namespace seneca {
	template <typename T>
	class CharacterTpl : public Character {
		// The maximum health this character can have
		int m_healthMax{ 0 };
		// Current health of the character. When this value gets to 0, the character died.
		T m_health{};
	public:
		CharacterTpl(const char* name, int maxHealth) : Character{ name }, m_healthMax(maxHealth) {
			setHealth(maxHealth);
		}
		// Reduces the current health by the value of the parameter
		void takeDamage(int dmg) override {
			m_health = dmg > m_health ? 0 : m_health - dmg;

			if (Character::isAlive()) {
				std::cout << "    " << getName() << " took " << dmg << " damage, "
					<< getHealth() << " health remaining." << std::endl;
			}
			else
			{
				std::cout << "    " << getName() << " has been defeated!" << std::endl;
			}
		}
		// Returns current health.
		int getHealth() const override { return static_cast<int>(m_health); }
		// Returns current maximum health.
		int getHealthMax() const override { return m_healthMax; }
		// Sets the current health to the value received as parameter.
		void setHealth(int health) override { m_health = health; }
		// Sets the maximum health and current health to the value of the parameter.
		void setHealthMax(int health) override {
			m_healthMax = health;
			setHealth(health);
		}
	};
}
#endif // !SENECA_CHARACTERTPL_H
