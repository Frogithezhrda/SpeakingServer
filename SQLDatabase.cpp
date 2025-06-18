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
				NAME TEXT NOT NULL,
				PASSWORD TEXT NOT NULL,
				EMAIL TEXT NOT NULL UNIQUE
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
