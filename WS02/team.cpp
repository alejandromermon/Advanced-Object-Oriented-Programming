#include <iostream>
#include <iomanip>
#include <string>
#include "team.h"
#include "character.h"

using namespace std;

namespace seneca {
	Team::Team(const Team& src) {
		m_character = nullptr;
		*this = src;
	}
	Team::Team(Team&& src) noexcept {
		m_character = nullptr;
		*this = move(src);
	}
	Team& Team::operator=(const Team& src) {
		if (this != &src) {
			for (auto i = 0u; i < m_noOfChars; i++) {
				delete m_character[i];
			}
			delete[] m_character;

			m_name = src.m_name;
			m_noOfChars = src.m_noOfChars;

			m_character = new Character * [m_noOfChars];

			for (auto i = 0u; i < src.m_noOfChars; i++) {
				m_character[i] = src.m_character[i] != nullptr ? src.m_character[i]->clone() : nullptr;
			}
		}
		return *this;
	}
	Team& Team::operator=(Team&& src) noexcept {
		if (this != &src) {
			for (auto i = 0u; i < m_noOfChars; i++) {
				delete m_character[i];
			}
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
	Team::~Team() {
		for (auto i = 0u; i < m_noOfChars; i++) {
			delete m_character[i];
		}
		delete[] m_character;
	}
	void Team::addMember(const Character* c) {
		if (c != nullptr && findChar(c->getName()) == -1) {
			Character** tmp = new Character * [m_noOfChars + 1];

			for (auto i = 0u; i < m_noOfChars; i++) {
				tmp[i] = m_character[i] != nullptr ? m_character[i]->clone() : nullptr;
				delete m_character[i];
			}
			delete[] m_character;
			m_character = tmp;
			m_character[m_noOfChars++] = c->clone();
		}
	}
	void Team::removeMember(const string& c) {
		int idx = findChar(c);
		if (idx != -1) {
			delete m_character[idx];
			m_character[idx] = nullptr;
			for (unsigned i = idx + 1; i < m_noOfChars; i++) {
				m_character[i - 1] = m_character[i];
			}
			m_noOfChars--;
		}
	}
	Character* Team::operator[](size_t idx) const {
		if (idx <= m_noOfChars) {
			return m_character[idx];
		}
		return nullptr;
	}
	void Team::showMembers() const {
		if (*this) {
			cout << "[Team] " << m_name << endl;
			for (auto i = 0u; i < m_noOfChars; i++) {
				cout << setw(5) << setiosflags(ios::right) << i + 1  << resetiosflags(ios::right) 
					<< ": " << *m_character[i] << endl;
			}
		}
		else {
			cout << "No team." << endl;
		}
	}
	int Team::findChar(const std::string& name) const {
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
	//Team::operator bool() const { return m_name.empty() && m_character != nullptr; };
	Team::operator bool() const { return !m_name.empty() && m_character != nullptr; };
}