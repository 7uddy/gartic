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
