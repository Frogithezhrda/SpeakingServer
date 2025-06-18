#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase> database)
{
	m_database = database;
}

