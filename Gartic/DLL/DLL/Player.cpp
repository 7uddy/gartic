#include "Player.h"

Player::Player(const std::string& username, const std::string& password, const std::string& email) 
	:m_username(username), m_password(password), m_email(email)
{
	m_score = 0;
}

Player::Player(Player&& player) noexcept
{
	*this = std::move(player);
}

void Player::SetUsername(const std::string& username)
{
	m_username = username;
}

void Player::SetPassword(const std::string& password)
{
	m_password = password;
}

void Player::SetEmail(const std::string& email)
{
	m_email = email;
}

void Player::SetScore(float score)
{
	m_score = score;
}

std::string& Player::GetUsername()
{
	return m_username;
}

std::string& Player::GetPassword()
{
	return m_password;
}

std::string& Player::GetEmail()
{
	return m_email;
}

float Player::GetScore()
{
	return m_score;
}

Player& Player::operator=(Player&& player) noexcept
{
	if (this != &player)
	{
		std::exchange(m_username, player.m_username);
		std::exchange(m_password, player.m_password);
		std::exchange(m_email, player.m_email);
		std::exchange(m_score, player.m_score);
	}
	return *this;
}

Player::~Player()
{
	/*empty*/
}
