#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <string>
#include "character.h"

namespace seneca {
	class Team {
		std::string m_name{};
		Character** m_character{ nullptr };
		unsigned int m_noOfChars{ 0 };
	public:
		Team() = default;
		Team(const char* name) : m_name(name) {};

		//Rule of 5
		Team(const Team&);
		Team(Team&&) noexcept;
		Team& operator=(const Team&);
		Team& operator=(Team&&) noexcept;
		~Team();

		// Adds the character if the team doesn't have a character with the same name.
		void addMember(const Character* c);
		// Searches the team for a character with the provided name and removes it from the team.
		void removeMember(const std::string& c);
		// Returns the character at the index specified as parameter, or null if the index is out of bounds.
		Character* operator[](size_t idx) const;
		// Prints to screen the content of current object.
		void showMembers() const;
		// Returns the index of a character in the team that matches the name in the parameter, -1 if not found.
		int findChar(const std::string& name) const;
		// Returns true if the Team is not in an empty state
		operator bool() const;
	};
}
#endif // !SENECA_TEAM_H
