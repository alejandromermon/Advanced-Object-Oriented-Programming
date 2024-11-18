#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include "character.h"

constexpr int G_HEALTH_INCREASE = 300;

namespace seneca {
	class Guild {
		std::string m_name{};
		Character** m_character{ nullptr };
		unsigned int m_noOfChars{ 0 };
	public:
		Guild() = default;
		Guild(const char* name) : m_name(name) {};

		//Rule of 5
		Guild(const Guild&);
		Guild(Guild&&) noexcept;
		Guild& operator=(const Guild&);
		Guild& operator=(Guild&&) noexcept;
		~Guild();

		// Adds the character if the team doesn't have a character with the same name.
		void addMember(Character* c);
		// Searches the team for a character with the provided name and removes it from the team.
		void removeMember(const std::string& c);
		// Returns the character at the index specified as parameter, or null if the index is out of bounds.
		Character* operator[](size_t idx) const;
		// Prints to screen the content of current object.
		void showMembers() const;
		// Returns the index of a character in the guild that matches the name in the parameter, -1 if not found.
		int findChar(const std::string& name) const;
		// Returns true if the Guild is not in an empty state
		operator bool() const;
	};
}
#endif // !SENECA_GUILD_H