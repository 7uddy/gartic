#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

import utils;
struct LoginCredential
{
	int userID;
	std::string username;
	std::string password;
	std::string email;
};
inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"LoginCredentials",
			sql::make_column("userID", &LoginCredential::userID, sql::primary_key().autoincrement()),
			sql::make_column("username", &LoginCredential::username),
			sql::make_column("password", &LoginCredential::password),
			sql::make_column("email", &LoginCredential::email)
			)
	);
}
using Storage = decltype(createStorage(""));
void populateStorage(Storage& storage);


class AddUserHandler {
public:
	AddUserHandler(Storage& storage);

	crow::response operator() (const crow::request& req) const;
private:
	Storage& m_db;
};
