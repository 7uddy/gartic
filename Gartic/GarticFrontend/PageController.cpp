#include "PageController.h"

PageController::PageController(QWidget* parent):QStackedWidget(parent)
{
	/*empty*/
}

void PageController::AddPage(QWidget* page, const QString& name)
{
	pagesMap[name] = page;
	QStackedWidget::addWidget(page);
}

void PageController::ShowPage(const QString& name)
{
	if (pagesMap.contains(name))
	{
		QWidget* page = pagesMap[name];
		setCurrentWidget(page);
	}
}

void PageController::SetStartupPage(const QString& name)
{
	if (pagesMap.contains(name))
	{
		ShowPage(name);
	}
}

bool PageController::VerifyLogin(const QString& enteredUsername, const QString& enteredPassword)
{
	std::string username = enteredUsername.toUtf8().constData();
	std::string password = enteredPassword.toUtf8().constData();
	if (player.VerifyLogin(username, password))
	{
		auto responseVerify = cpr::Get(
			cpr::Url{ "http://localhost:18080/login" },
			cpr::Parameters{
					{ "username", username},
					{ "password", password},
			}
		);
		if (responseVerify.status_code == 202)
		{
			player.SetUsername(username);
			player.SetPassword(password);
			return true;
		}
	}
	return false;
}

bool PageController::VerifyRegister(const QString& enteredUsername, const QString& enteredEmail, const QString& enteredPassword)
{
	std::string username = enteredUsername.toUtf8().constData();
	std::string email = enteredEmail.toUtf8().constData();
	std::string password = enteredPassword.toUtf8().constData();
	if (player.VerifyRegister(username, email, password))
	{
		auto responseVerify = cpr::Put(
			cpr::Url{ "http://localhost:18080/register" },
			cpr::Parameters{
					{ "username", username},
					{ "password", password},
					{ "email", email },
			}
		);
		if (responseVerify.status_code == 201)
			return true;
	}
	return false;
}

bool PageController::CreateRoom()
{
	auto responseCreate = cpr::Get(
		cpr::Url{ "http://localhost:18080/createlobby" },
		cpr::Parameters{
				{ "username", player.GetUsername()},
		}
	);
	std::string responseText = responseCreate.text;
	auto json = nlohmann::json::parse(responseText);
    roomCode = json["text"];
	static const int responseLength = 5;
	if (roomCode.size() == responseLength)
		return true;
	roomCode.clear();
	return false;
}

bool PageController::VerifyCode(const QString& enteredCode)
{
	std::string lobbyCode = enteredCode.toUtf8().constData();
	auto responseJoin = cpr::Get(
		cpr::Url{ "http://localhost:18080/joinlobby" },
		cpr::Parameters{
				{ "lobbycode", lobbyCode },
				{ "username", player.GetUsername()},
		}
	);
	if (responseJoin.status_code == 200)
		return true;
	return false;
}

bool PageController::LeaveRoom()
{
	auto responseLeave = cpr::Get(
		cpr::Url{ "http://localhost:18080/disconnectfromlobby" },
		cpr::Parameters{
				{ "username", player.GetUsername()},
		}
	);
	if (responseLeave.status_code == 200)
		return true;
	return false;
}

std::string PageController::GetLobbyCode()
{
	return roomCode;
}

Player PageController::GetPlayer()
{
	return player;
}
