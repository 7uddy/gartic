module player;
using namespace gartic;

Player::Player(const std::string& username, const std::string& email, const std::string& password) :
	m_username{ username }, m_password{ password }, m_score{ 0 },
	m_email{ email }
{
	/*EMPTY*/
}

Player::Player(const std::string& username):
	m_username{ username }, m_email{ "" }, m_password{ "" }, m_score{ 0 }
{
	/*EMPTY*/
}

Player::Player(const Player& other)
{
	m_username = other.m_username;
	m_email = other.m_email;
	m_password = other.m_password;
	m_score = other.m_score;
}

Player::Player(Player&& otherPlayer)
{
	*this = std::move(otherPlayer);
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this != &other)
	{
		std::exchange(m_username, other.m_username);
		std::exchange(m_email, other.m_email);
		std::exchange(m_password, other.m_password);
		std::exchange(m_score, other.m_score);
	}
	return *this;
}

void Player::SetUsername(const std::string& username) noexcept
{
	m_username = username;
}

const std::string& Player::GetUsername() const noexcept
{
	return m_username;
}

void Player::SetPassword(const std::string& password) noexcept
{
	m_password = password;
}

void Player::SetEmail(const std::string& email) noexcept
{
	m_email = email;
}

const std::string& Player::GetPassword() const noexcept
{
	return m_password;
}

const std::string& Player::GetEmail() const noexcept
{
	return m_email;
}

void Player::SetScoreTo(const float& score) noexcept
{
	m_score = score;
}

//template <typename T, typename>
//void Player::AddToScore(const T& score) noexcept
//{
//	m_score += score;
//}

void Player::ResetScore() noexcept
{
	m_score = 0;
}

float Player::GetScore() const noexcept
{
	return m_score;
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
	if (m_score != player.m_score) return false;
	return true;
}

bool Player::operator!=(const Player& otherPlayer) const
{
	return !((*this) == otherPlayer);
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	os << player.GetUsername() << ' ' << player.GetEmail() << ' ' << player.GetPassword() << ' ' << player.GetScore();
	return os;
}