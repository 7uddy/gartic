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
	Player(const std::string& username, const std::string& password);
	Player(const Player& player) = default;
	Player(Player&& player) noexcept;
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	void SetScore(float score);
	std::string& GetUsername();
	std::string& GetPassword();
	float GetScore();
	Player& operator=(const Player& player) = default;
	Player& operator=(Player&& player) noexcept;

	static bool HasLowerCase(const std::string& word);
	static bool HasUpperCase(const std::string& word);
	static bool HasMinimumLength(const std::string& word);
	static bool IsValidUsername(const std::string& username);
	static bool IsValidPassword(const std::string& password);
	static bool IsValidEmail(const std::string& email);
	static bool VerifyLogin(const std::string& username, const std::string& password);
	static bool VerifyRegister(const std::string& username, const std::string& email, const std::string& password);
	~Player();
private:
	std::string m_username;
	std::string m_password;
	float m_score;
};

