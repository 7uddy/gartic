#include "Player.h"

Player::Player(const std::string& username, const std::string& email, const std::string& password)
	:m_username(username), m_password(password), m_email(email)
{
	m_score = 0;
}

Player::Player(Player&& player) noexcept
{
	*this = std::move(player);
}

void Player::SetUsername(std::string_view  username)
{
	m_username = std::string(username);
}

void Player::SetPassword(std::string_view  password)
{
	m_password = std::string(password);
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

bool Player::VerifyLogin(std::string_view username, std::string_view password) const
{
	std::regex usernamePattern("^[a-zA-Z0-9_]+$");
	std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z]).+$");
	return std::regex_match(std::string(username), usernamePattern) && std::regex_match(std::string(password), passwordPattern);
}

bool Player::VerifyRegister(std::string_view username, std::string_view email, std::string_view password) const
{
	std::regex usernamePattern("^[a-zA-Z0-9_]+$");
	std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z]).+$");
	std::regex emailPattern(R"(\b[A-Za-z0-9.]+@[A-Za-z0-9]+\.[A-Z|a-z]{2,}\b)");
	return std::regex_match(std::string(username), usernamePattern) && std::regex_match(std::string(email), emailPattern)
		&& std::regex_match(std::string(password), passwordPattern);
}

Player::~Player()
{
	/*empty*/
}
