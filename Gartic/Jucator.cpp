#include "Jucator.h"

uint8_t Jucator::m_playerCount = 1;

Jucator::Jucator()
{
}

Jucator::Jucator(const std::string& username, const std::string& password) :
	m_username(username), m_password(password), m_artist(false), m_score(0), 
	m_uniqueId(generateID())
{
	
	m_playerCount++;
}

void Jucator::setUsername(const std::string& username)
{
	m_username = username;
}

void Jucator::setScore(const uint16_t score)
{
	m_score = score;
}

uint32_t Jucator::generateID() const
{
	return m_playerCount;
}

uint32_t Jucator::getID() const
{
	return m_uniqueId;
}
