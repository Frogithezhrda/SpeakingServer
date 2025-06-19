#include "PostgreDatabase.h"

PostgreDatabase::PostgreDatabase()
{

	m_conn = pqxx::connection("dbname=postgres user=saban password=saban hostaddr=127.0.0.1 port=17422");
	if (!m_conn.is_open())
	{
		throw DataBaseException("Could Not Open Database");
	}

}

void PostgreDatabase::createQuery(const Query& query)
{

}

void PostgreDatabase::close()
{
	m_conn.close();
}
