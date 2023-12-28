#pragma once
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#include <iostream>
#include <string>
#include <string_view>
#include <regex>

class DLL_API Player
{
public:
	Player() = default;
	Player(const std::string& username, const std::string& email, const std::string& password);
	Player(const Player& player) = default;
	Player(Player&& player) noexcept;
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	void SetEmail(const std::string& email);
	void SetScore(float score);
	std::string& GetUsername();
	std::string& GetPassword();
	std::string& GetEmail();
	float GetScore();
	Player& operator=(const Player& player) = default;
	Player& operator=(Player&& player) noexcept;
	bool VerifyLogin(const std::string& username, const std::string& password) const;
	bool VerifyRegister(const std::string& username, const std::string& email, const std::string& password) const;
	~Player();
private:
	std::string m_username;
	std::string m_password;
	std::string m_email;
	float m_score;
};

