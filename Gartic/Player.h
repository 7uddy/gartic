#pragma once
#include <string>

class Player
{
public:
	Player();
	Player(const std::string& username, const std::string& password);

	/*-------Player variables related functions.-------*/
	uint16_t GetID() const;
	void SetID(const uint16_t& id);

	void SetUsername(const std::string& username);
	std::string GetUsername() const;

	void SetPassword(const std::string& password);


	void UpdateScore(const int16_t score);
	void ResetScore();
	int16_t GetScore() const;

	bool IsArtist() const;
	void ChangeArtistState();
	/*-------Player variables related functions.-------*/

private:
	std::string m_username;
	std::string m_password;
	uint16_t m_uniqueId;
	bool m_artist;
	int16_t m_score;

private:
	static uint8_t m_playerCount;

private:
	uint16_t GenerateID() const;
};

