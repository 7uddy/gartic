module player;
using namespace gartic;

Player::Player(std::string_view username, std::string_view password,std::string_view email,const int& uniqueId) :
	m_username{ username }, m_password{ password }, m_score{ 0 },
	m_email {email}
{
	m_uniqueId = uniqueId;
}

Player::Player(Player&& otherPlayer)
{
	*this = std::move(otherPlayer);
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this != &other)
	{
		m_uniqueId = std::exchange(other.m_uniqueId, 0);
		m_username = std::exchange(other.m_username, std::string());
		m_password = std::exchange(other.m_password, std::string());
		m_score = std::exchange(other.m_score, 0);
		m_email = std::exchange(other.m_email, std::string());
	}
	return *this;
}

void Player::SetUsername(std::string_view username) noexcept
{
	m_username = username;
}

std::string_view gartic::Player::GetUsername() const noexcept
{
	return m_username;
}

void gartic::Player::SetEmail(std::string_view email) noexcept
{
	m_email = email;
}

std::string_view Player::GetEmail() const noexcept
{
	return m_username;
}

void Player::SetPassword(std::string_view password) noexcept
{
	m_password = password;
}

std::string_view gartic::Player::GetPassword() const noexcept
{
	return m_password;
}

void Player::SetScoreTo(const float& score) noexcept
{
	m_score = score;
}

void Player::AddToScore(const float& score) noexcept
{
	m_score += score;
}

void Player::ResetScore() noexcept
{
	m_score = 0;
}

const float& Player::GetScore() const noexcept
{
	return m_score;
}


const int Player::GetID() const noexcept
{
	return m_uniqueId;
}

void Player::SetID(const int id) noexcept
{
	m_uniqueId = id;
}

bool Player::operator<(const Player& player) noexcept
{
	if (m_score < player.m_score)
		return true;
	return false;
}

bool Player::operator==(const Player& player) const 
{
	if (this == &player) return true;
	if (m_password != player.m_password) return false;
	if (m_username != player.m_username) return false;
	if (m_uniqueId != player.m_uniqueId) return false;
	if (m_score != player.m_score) return false;
	if (m_email != player.m_email) return false;
	return true;
}

bool gartic::Player::operator!=(const Player& otherPlayer) const
{
	return !((*this) == otherPlayer);
}
