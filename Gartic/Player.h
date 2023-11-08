#pragma once
#include <string>

class Player
{
public:
	/*-------Enums-------*/
	enum class Role : uint8_t
	{
		Guesser,
		Artist
	};


	/*-------Constructors-------*/
	Player() = default;
	Player(const std::string& username, const std::string& password);


	/*-------Player variables related functions-------*/
	const uint16_t& GetID() const noexcept;
	void SetID(const uint16_t& id) noexcept;

	void SetUsername(const std::string& username) noexcept;
	const std::string& GetUsername() const noexcept;

	void SetPassword(const std::string& password) noexcept;

	void UpdateScore(const int16_t score) noexcept;
	void ResetScore() noexcept;
	const int16_t& GetScore() const noexcept;

	bool IsArtist() const noexcept;
	void ChangeRole() noexcept;


	/*-------Operator overloading-------*/

	bool operator<(const Player&) noexcept;
	bool operator==(const Player&) noexcept;

private:
	uint16_t GenerateID() const noexcept;

private:
	uint16_t m_uniqueId;
	std::string m_username;
	std::string m_password;
	Role m_role : 1;
	float m_score;

private:
	static uint8_t m_playerCount;
};

