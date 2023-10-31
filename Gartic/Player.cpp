#include "Player.h"

uint8_t Player::m_playerCount = 1;

Player::Player()
{
	/* EMPTY */
}

Player::Player(const std::string& username, const std::string& password) :
	m_username{ username }, m_password{ password }, m_artist{ false }, m_score{ 0 },
	m_uniqueId{ GenerateID() }
{
	
	m_playerCount++;
}

void Player::SetUsername(const std::string& username)
{
	m_username = username;
}

std::string Player::GetUsername() const
{
	return m_username;
}

void Player::UpdateScore(const uint16_t score)
{
	m_score = score;
}

void Player::ResetScore()
{
	m_score = 0;
}

uint16_t Player::GenerateID() const
{
	return m_playerCount;
}

uint16_t Player::GetID() const
{
	return m_uniqueId;
}

void Player::SetID(const uint16_t& id)
{
	m_uniqueId = id;
}

bool Player::IsArtist() const
{
	return m_artist;
}

void Player::ChangeArtistState()
{
	m_artist = !m_artist;
}
