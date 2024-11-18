#include <iostream>
#include <iomanip>
#include <string>
#include "guild.h"
#include "character.h"

using namespace std;

namespace seneca {
	Guild::Guild(const Guild& src) {
		m_character = nullptr;
		*this = src;
	}
	Guild::Guild(Guild&& src) noexcept {
		m_character = nullptr;
		*this = move(src);
	}
	Guild& Guild::operator=(const Guild& src) {
		if (this != &src) {
			delete[] m_character;

			m_name = src.m_name;
			m_noOfChars = src.m_noOfChars;

			m_character = new Character * [m_noOfChars];

			for (auto i = 0u; i < src.m_noOfChars; i++) {
				m_character[i] = src.m_character[i];
			}
		}
		return *this;
	}
	Guild& Guild::operator=(Guild&& src) noexcept {
		if (this != &src) {
			delete[] m_character;

			m_name = src.m_name;
			m_noOfChars = src.m_noOfChars;
			m_character = src.m_character;

			src.m_name.clear();
			src.m_noOfChars = 0;
			src.m_character = nullptr;
		}
		return *this;
	}
	Guild::~Guild() {
		delete[] m_character;
	}
	void Guild::addMember(Character* c) {
		if (c != nullptr && findChar(c->getName()) == -1) {
			Character** tmp{};
			tmp = new Character * [m_noOfChars + 1] {};

			for (auto i = 0u; i < m_noOfChars; i++) {
				tmp[i] = m_character[i];
			}
			delete[] m_character;
			m_character = tmp;
			c->setHealthMax(c->getHealthMax() + G_HEALTH_INCREASE);
			m_character[m_noOfChars++] = c;
		}
	}
	void Guild::removeMember(const string& c) {
		int idx = findChar(c);
		if (idx != -1) {
			m_character[idx]->setHealthMax(m_character[idx]->getHealthMax() - G_HEALTH_INCREASE);
			m_character[idx] = nullptr;
			for (unsigned i = idx + 1; i < m_noOfChars; i++) {
				m_character[i - 1] = m_character[i];
			}
			m_noOfChars--;
		}
	}
	Character* Guild::operator[](size_t idx) const {
		if (idx >= 0 && idx <= m_noOfChars) {
			return m_character[idx];
		}
		return nullptr;
	}
	void Guild::showMembers() const {
		if (*this) {
			cout << "[Guild] " << m_name << endl;
			for (auto i = 0u; i < m_noOfChars; i++) {
				cout << setw(5) << setiosflags(ios::right) << i + 1 << resetiosflags(ios::right)
					<< ": " << *m_character[i] << endl;
			}
		}
		else {
			cout << "No guild." << endl;
		}
	}
	int Guild::findChar(const std::string& name) const {
		string nm;

		if (!name.empty() && m_character != nullptr) {
			for (auto i = 0u; i < m_noOfChars; i++) {
				if (m_character[i] != nullptr) {
					nm = m_character[i]->getName();
					if (!nm.empty() && nm == name) return i;
				}
			}
		}
		return -1;
	}
	Guild::operator bool() const { return !m_name.empty() && m_character != nullptr; };
}