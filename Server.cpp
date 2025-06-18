#include "Server.h"

Server::Server()
{
	m_database = std::make_shared<SQLDatabase>();
	m_handlerFactory = std::make_shared<RequestHandlerFactory>(m_database);
	m_communicator = std::make_unique<Communicator>(m_handlerFactory);

}

Server::~Server()
{
}

void Server::run()
{
	std::string command = "";
	std::thread clientsThread(&Communicator::startHandleRequests, m_communicator.get());
	clientsThread.detach();
	while (true);
}
