#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <string>
#include "DatabaseException.hpp"

constexpr const char* DATABASE_NAME = "UserDB.sqlite";

class SQLDatabase : public IDatabase
{
public:
	SQLDatabase();

	virtual void createQuery(const Query& query) override;
	virtual void close() override;

private:
	sqlite3* db;
};