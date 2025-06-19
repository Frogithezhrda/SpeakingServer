#include "Communicator.h"

std::recursive_mutex Communicator::_clientsMutex;
std::map<SOCKET, std::shared_ptr<IRequestHandler>> Communicator::m_clients;

Communicator::Communicator(std::shared_ptr<RequestHandlerFactory> handlerFactory) : m_handlerFactory(handlerFactory)
{
	//starting server socket
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
	{
		//getting function name and socket error
		throw CommunicatorException(__FUNCTION__ " - socket");
	}

}

Communicator::~Communicator()
{
	//trying to close the socket
	try
	{
		closesocket(this->m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	std::vector<std::thread> connections;
	try
	{
		bindAndListen();
		while (true)
		{
			// and add then to the list of handlers
			std::cout << "Waiting for client connection request" << std::endl;
			//getting the sockets
			SOCKET clientSocket = acceptClient();
			//putting the threads
			connections.emplace_back(std::thread(&Communicator::handleNewClient, this, clientSocket));
		}
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what();
	}
}

SOCKET Communicator::acceptClient() const
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		throw CommunicatorException(__FUNCTION__);
	}

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	return client_socket;
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	//connecting between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw CommunicatorException(__FUNCTION__ " - bind");
	}

	//listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw CommunicatorException(__FUNCTION__ " - listen");
	}
	std::cout << "Listening on port " << PORT << std::endl;
}

void Communicator::handleNewClient(const SOCKET& clientSocket)
{
	RequestResult result;
	unsigned char data[MESSAGE_SIZE] = { 0 };
	RequestInfo requestInfo;
	int bytesReceived = 0;
	unsigned int size = 0;
	//we must lock the using the lockguard
	{
		std::lock_guard<std::recursive_mutex> lock(_clientsMutex);
		m_clients[clientSocket] = m_handlerFactory->createLoginRequestHandler(std::make_shared<SOCKET>(clientSocket));
	}

	try
	{
		while (true)
		{
			//receving the request if not valid throw exception
			bytesReceived = recv(clientSocket, reinterpret_cast<char*>(data), MESSAGE_SIZE, 0);
			if (0 >= bytesReceived)
			{
				throw CommunicatorException("Could Not Receive Data.");
			}
			//creating requestInfo
			for (int i = 1; i < START_PROTOCOL; i++)
			{
				if (data[i] != '\0')
				{
					size += int(data[i]);
				}
			}
			for (int i = START_PROTOCOL; i < size + START_PROTOCOL; i++)
			{
				requestInfo.buffer.push_back(static_cast<unsigned char>(data[i]));
			}
			requestInfo.id = RequestId(data[0]);
			requestInfo.receivalTime = time(nullptr);
			std::string dataStr(reinterpret_cast<char*>(data), bytesReceived);
			//getting message and sending request
			std::cout << "Message: " << dataStr << std::endl;
			{
				std::lock_guard<std::recursive_mutex> lock(_clientsMutex);
				result = m_clients[clientSocket]->handleRequest(requestInfo);
				m_clients[clientSocket] = result.newHandler;
			}
			sendMessage(clientSocket, result.response);
			memset(data, 0, MESSAGE_SIZE);
			result.response.resize(0);
			requestInfo.buffer.resize(0);
			size = 0;
		}
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what();
	}
}

void Communicator::sendMessage(const SOCKET& clientSocket, Buffer message)
{
	std::string resultString = std::string(message.begin(), message.end());
	if (send(clientSocket, resultString.c_str(), resultString.size(), 0) == SOCKET_ERROR)
	{
		throw CommunicatorException("Could Not Send Data." + std::to_string(WSAGetLastError()));
	}
	std::cout << "Sended Message." << std::endl;
}

void Communicator::setClientHandler(const SOCKET& sock, std::unique_ptr<IRequestHandler> handler)
{
	std::lock_guard<std::recursive_mutex> lock(_clientsMutex);
	m_clients[sock] = std::move(handler);
}