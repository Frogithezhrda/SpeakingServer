#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"
#include "JsonRequestDeserializer.h"
#include "JsonResponseSerializer.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	// Constructor that builds the exception message.
	LoginRequestHandler(std::shared_ptr<RequestHandlerFactory> factory, std::shared_ptr<SOCKET> currentSocket);
	virtual ~LoginRequestHandler() = default;
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) const override;

private:
	std::shared_ptr<RequestHandlerFactory> m_handlerFactory;
	std::shared_ptr<SOCKET> m_currentUserSock;
};
