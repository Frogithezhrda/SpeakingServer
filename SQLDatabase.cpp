#include "SQLDatabase.h"

SQLDatabase::SQLDatabase()
{
	//opening the database
	if (sqlite3_open(DATABASE_NAME, &this->db) != SQLITE_OK)
	{
		std::string msg = std::string("Failed to open DB: ") + sqlite3_errmsg(this->db);
		this->db = nullptr;
		throw DataBaseException(msg);
	}

	const char* sqlStatement = R"(
			CREATE TABLE IF NOT EXISTS USERS (
				USER_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
				NAME TEXT NOT NULL UNIQUE,
				PASSWORD TEXT NOT NULL,
				EMAIL TEXT NOT NULL,
				PROFILE_PATH NOT NULL
			);
			)";
	Query query = Query(sqlStatement, nullptr, nullptr);
	createQuery(query);
}

void SQLDatabase::createQuery(const Query& query)
{
	char* errMessage = nullptr;

	if (sqlite3_exec(this->db, query.sqlStatement, query.callback, query.param, &errMessage) != SQLITE_OK)
	{
		std::string msg = std::string("Failed to execute Query: ") + std::string(errMessage);
		sqlite3_free(errMessage);
		throw DataBaseException(msg);
	}
}

void SQLDatabase::close()
{
	if (this->db)
	{
		//closing the database
		sqlite3_close(this->db);
		this->db = nullptr;
	}
}

void SQLDatabase::addNewUser(const std::string& userName, const std::string& password, const std::string& email, const std::string& profilePath)
{
	// Creating SQL message that adds user.

	std::stringstream ss;
	ss << "INSERT INTO USERS(NAME, PASSWORDD, EMAIL, PROFILE_PATH) "
		<< "VALUES('" << userName << "', '" << password << "', '" << email << "', '"
		<< profilePath << "');";

	std::string query = ss.str();
	Query queryRequest = Query(query.c_str(), nullptr, nullptr);

	createQuery(queryRequest);
}

bool SQLDatabase::doesPasswordMatch(const std::string& userName, const std::string& password) 
{
	// Creating SQL message that returns 1 if the password is matching and 0 if not 

	std::stringstream ss;
	ss << "SELECT COUNT(*) FROM USERS "
		<< "WHERE USERS.NAME = '" << userName << "' AND USERS.PASSWORDD = '" << password << "';";

	std::string query = ss.str();
	const char* sqlStatement = query.c_str();
	int count = 0;
	Query queryRequest = Query(query.c_str(), &count, callbackCount);

	createQuery(queryRequest);

	return count > 0;
}



int SQLDatabase::callbackCount(void* data, int argc, char** argv, char** colNames)
{
	// Returning the number in data
	if (argc > 0 && argv[0]) 
	{
		*static_cast<int*>(data) = std::stoi(argv[0]);
	}
	return 0;
}
