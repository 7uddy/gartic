#include "Database.h"

void populateStorage(Storage& storage)
{
	std::vector<LoginCredential> credentials{
	LoginCredential { -1, "Tudor", "123","tudorcalin11@yahoo.com"},
	LoginCredential { -1, "Nicu",   "321","andreinicugeani@yahoo.com"}
	};
	storage.insert_range(credentials.begin(), credentials.end());
}
AddUserHandler::AddUserHandler(Storage& storage)
	: m_db{ storage }
{

}

crow::response AddUserHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();

	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	auto emailIter = bodyArgs.find("email");

	if (usernameIter != end && passwordIter != end && emailIter != end)
	{
		LoginCredential userCredential;
		userCredential.userID = -1;
		userCredential.username = usernameIter->second;
		userCredential.password = passwordIter->second;
		userCredential.email = emailIter->second;
		m_db.insert(userCredential);
	}
	return crow::response(200);
}
