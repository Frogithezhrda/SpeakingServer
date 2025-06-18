#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <string>
#include "DatabaseException.hpp"
#include <sstream>

constexpr const char* DATABASE_NAME = "UserDB.sqlite";

class SQLDatabase : public IDatabase
{
public:
	SQLDatabase();

	virtual void createQuery(const Query& query) override;
	virtual void close() override;

	void addNewUser(const std::string& userName, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate);

	bool doesPasswordMatch(const std::string& userName, const std::string& password);


private:
	sqlite3* db;

	static int callbackCount(void* data, int argc, char** argv, char** colNames);
};