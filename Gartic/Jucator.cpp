#include "Jucator.h"

Jucator::Jucator()
{
}

Jucator::Jucator(const std::string& username, const std::string& password, const uint32_t& id) :
	m_username(username), m_password(password), m_uniqueId(id), m_artist(false), m_score(0)
{
}

void Jucator::setUsername(const std::string& username)
{
	m_username = username;
}

void Jucator::setScore(const uint16_t score)
{
	m_score = score;
}

