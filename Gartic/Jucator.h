#pragma once
#include <string>

class Jucator
{
public:
	Jucator();
	Jucator(const std::string& username, const std::string& password, const uint32_t& id);

	void setUsername(const std::string& username);
	void setScore(const uint16_t score);
private:
	std::string m_username;
	std::string m_password;
	uint32_t m_uniqueId;
	bool m_artist;
	uint16_t m_score;
};

