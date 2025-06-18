#pragma once
#include <WinSock2.h>
#include <windows.h>
#include <map>
#include <iostream>
#include <thread>
#include <vector>
//#include "LoginRequestHandler.h"
#include "IRequestHandler.h"
#include "CommunicatorException.hpp"
#include <mutex>
//#include "JsonRequestPacketDeserializer.h"
//#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

//message size
#define MESSAGE_SIZE 1024
#define START_PROTOCOL 5

constexpr const int PORT = 17423;

class Communicator
{
public:
	Communicator(std::shared_ptr<RequestHandlerFactory> handlerFactory);
	virtual ~Communicator();

	void startHandleRequests();

	static void sendMessage(const SOCKET& clientSocket, Buffer message);
	static void setClientHandler(const SOCKET& sock, std::unique_ptr<IRequestHandler> handler);

private:
	SOCKET acceptClient() const;
	void bindAndListen();
	void handleNewClient(const SOCKET& clientSocket);

	static std::map<SOCKET, std::unique_ptr<IRequestHandler>> m_clients;
	SOCKET m_serverSocket;
	std::shared_ptr<RequestHandlerFactory> m_handlerFactory;
	static std::recursive_mutex _clientsMutex;
};