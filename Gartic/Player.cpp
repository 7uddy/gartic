#include "Player.h"

uint8_t Player::m_playerCount = 1;

Player::Player(const std::string& username, const std::string& password) :
	m_username{ username }, m_password{ password }, m_role{ Role::Guesser }, m_score{ 0 },
	m_uniqueId{ GenerateID() }
{
	
	m_playerCount++;
}

void Player::SetUsername(const std::string& username) noexcept
{
	m_username = username;
}

const std::string& Player::GetUsername() const noexcept
{
	return m_username;
}

void Player::SetPassword(const std::string& password) noexcept
{
	m_password = password;
}

void Player::UpdateScore(const int16_t score) noexcept
{
	m_score = score;
}

void Player::ResetScore() noexcept
{
	m_score = 0;
}

const int16_t& Player::GetScore() const noexcept
{
	return m_score;
}

uint16_t Player::GenerateID() const noexcept
{
	return m_playerCount;
}

const uint16_t& Player::GetID() const noexcept
{
	return m_uniqueId;
}

void Player::SetID(const uint16_t& id) noexcept
{
	m_uniqueId = id;
}

bool Player::IsArtist() const noexcept
{
	return m_role==Role::Artist;
}

void Player::ChangeRole() noexcept
{
	switch (m_role)
	{
		case Role::Artist:
			m_role = Role::Guesser;
			return;
		case Role::Guesser:
			m_role = Role::Artist;
			return;
	}
}

bool Player::operator<(const Player& player)
{
	if (this->m_score < player.m_score) 
		return true;
	return false;
}
