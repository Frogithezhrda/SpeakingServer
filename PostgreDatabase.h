#pragma once
#include "IDatabase.h"
#include "DatabaseException.hpp"
#include <pqxx/pqxx>

class PostgreDatabase : public IDatabase
{
public:
	PostgreDatabase();

	virtual void createQuery(const Query& query) override;
	virtual void close() override;

private:
	pqxx::connection m_conn;
};