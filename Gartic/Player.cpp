#include "Player.h"

uint8_t Player::m_playerCount = 1;

Player::Player()
{
}

Player::Player(const std::string& username, const std::string& password) :
	m_username(username), m_password(password), m_artist(false), m_score(0), 
	m_uniqueId(generateID())
{
	
	m_playerCount++;
}

void Player::setUsername(const std::string& username)
{
	m_username = username;
}

void Player::setScore(const uint16_t score)
{
	m_score = score;
}

uint32_t Player::generateID() const
{
	return m_playerCount;
}

uint32_t Player::getID() const
{
	return m_uniqueId;
}
