#pragma once
#include <string>
#include <thread>
#include <iostream>
#include "Communicator.h"
#include "SQLDatabase.h"

constexpr const char* EXIT = "EXIT";

class Server
{
public:
	Server();
	virtual ~Server();
	void run();


private:
	std::shared_ptr<IDatabase> m_database;
	std::shared_ptr<RequestHandlerFactory> m_handlerFactory;
	std::unique_ptr<Communicator> m_communicator;


};