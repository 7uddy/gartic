module player;
using namespace gartic;

Player::Player(const std::string& username, const std::string& password) :
	m_username{ username }, m_password{ password }, m_score{ 0 },
	m_uniqueId{ 0 }
{
	/*EMPTY*/
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
	}
	return *this;
}

void Player::setUsername(const std::string& username) noexcept
{
	m_username = username;
}

const std::string& Player::getUsername() const noexcept
{
	return m_username;
}

void Player::setPassword(const std::string& password) noexcept
{
	m_password = password;
}

const std::string& gartic::Player::getPassword() const noexcept
{
	return m_password;
}

void Player::setScoreTo(const float& score) noexcept
{
	m_score = score;
}

void Player::addToScore(const float& score) noexcept
{
	m_score += score;
}

void Player::resetScore() noexcept
{
	m_score = 0;
}

const float& Player::getScore() const noexcept
{
	return m_score;
}


const uint16_t& Player::getID() const noexcept
{
	return m_uniqueId;
}

void Player::setID(const uint16_t& id) noexcept
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
	return true;
}

bool gartic::Player::operator!=(const Player& otherPlayer) const
{
	return !((*this) == otherPlayer);
}
