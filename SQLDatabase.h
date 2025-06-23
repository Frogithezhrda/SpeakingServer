#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <string>
#include "DatabaseException.hpp"
#include <sstream>

//cause this handles all the contacts and users we will use a struct here to repersent a user
typedef struct Contact
{
	std::string username;
	unsigned int id;
	std::string profilePath;

	Contact(const std::string& username, const unsigned int id, const std::string& profilePath)
		: username(username), id(id), profilePath(profilePath) {
	}
} Contact;
//

constexpr const char* DATABASE_NAME = "UserDB.sqlite";

class SQLDatabase : public IDatabase
{
public:
	SQLDatabase();

	virtual void createQuery(const Query& query) override;
	virtual void close() override;

	void addNewUser(const std::string& userName, const std::string& password, const std::string& email, const std::string& profilePath);

	bool doesPasswordMatch(const std::string& userName, const std::string& password);

	std::shared_ptr<Contact> getUser(const std::string& userToSearch);


private:
	sqlite3* db;

	static int callbackCount(void* data, int argc, char** argv, char** colNames);
	static int callbackUser(void* data, int argc, char** argv, char** colNames);
};