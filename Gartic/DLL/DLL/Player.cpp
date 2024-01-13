#include "Player.h"

Player::Player(const std::string& username,const std::string& password)
	:m_username(username), m_password(password)
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
		std::exchange(m_score, player.m_score);
	}
	return *this;
}

bool Player::HasLowerCase(const std::string& word)
{
	std::regex lowercasePattern("[a-z]");
	return std::regex_search(word, lowercasePattern);
}

bool Player::HasUpperCase(const std::string& word)
{
	std::regex uppercasePattern("[A-Z]");
	return std::regex_search(word, uppercasePattern);
}

bool Player::HasMinimumLength(const std::string& word)
{
	const int minimumlength = 4;
	if (word.size() < minimumlength)
		return false;
	return true;
}

bool Player::IsValidUsername(const std::string& username)
{
	std::regex usernamePattern("^[a-zA-Z0-9_]+$");
	return std::regex_match(username, usernamePattern);
}

bool Player::IsValidPassword(const std::string& password)
{
	std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z]).+$");
	return std::regex_match(password, passwordPattern);
}

bool Player::IsValidEmail(const std::string& email)
{
	std::regex emailPattern(R"(\b[A-Za-z0-9.]+@[A-Za-z0-9]+\.[A-Z|a-z]{2,}\b)");
	return std::regex_match(email, emailPattern);
}

bool Player::VerifyLogin(const std::string& username, const std::string& password)
{
	return Player::HasLowerCase(username) && Player::HasUpperCase(username) && Player::HasMinimumLength(username) && Player::IsValidUsername(username);
		Player::HasLowerCase(password) && Player::HasUpperCase(password)&&Player::HasMinimumLength(password),Player::IsValidPassword(password);
}

bool Player::VerifyRegister(const std::string& username, const std::string& email, const std::string& password)
{
	return Player::HasLowerCase(username) && Player::HasUpperCase(username) && Player::HasMinimumLength(username) && Player::IsValidUsername(username);
	    Player::HasLowerCase(password) && Player::HasUpperCase(password) && Player::HasMinimumLength(password), Player::IsValidPassword(password) &&
		Player::IsValidEmail(email);
}

Player::~Player()
{
	/*empty*/
}
