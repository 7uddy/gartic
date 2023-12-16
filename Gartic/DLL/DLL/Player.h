#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <regex>

class __declspec(dllexport) Player
{
public:
	Player() = default;
	Player(const std::string& username, const std::string& email, const std::string& password);
	Player(const Player& player) = default;
	Player(Player&& player) noexcept;
	void SetUsername(std::string_view username);
	void SetPassword(std::string_view  password);
	void SetEmail(const std::string& email);
	void SetScore(float score);
	std::string& GetUsername();
	std::string& GetPassword();
	std::string& GetEmail();
	float GetScore();
	Player& operator=(const Player& player) = default;
	Player& operator=(Player&& player) noexcept;
	bool VerifyLogin(std::string_view username, std::string_view password) const;
	bool VerifyRegister(std::string_view username, std::string_view email, std::string_view password) const;
	~Player();
private:
	std::string m_username;
	std::string m_password;
	std::string m_email;
	float m_score;
};

