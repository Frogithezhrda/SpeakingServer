#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase> database)
{
	m_database = database;
	m_loginManager = std::make_shared<LoginManager>(database);
}

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler(std::shared_ptr<SOCKET> userSocket) const
{
	return std::make_shared<LoginRequestHandler>(const_cast<RequestHandlerFactory*>(this), userSocket);
}

std::shared_ptr<LoginManager> RequestHandlerFactory::getLoginManager() const
{
	return m_loginManager;
}

