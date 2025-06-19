#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponseSerializer.h"
#include "JsonRequestDeserializer.h"
#include "LoginManager.h"


class MenuRequestHandler : public IRequestHandler
{
public:

	MenuRequestHandler(std::shared_ptr<RequestHandlerFactory> factory, std::shared_ptr<LoggedUser> user);
	virtual ~MenuRequestHandler() = default;

	virtual bool isRequestRelevant(const RequestInfo& request) const override;

	virtual RequestResult handleRequest(const RequestInfo& request) const override;
private:
	std::shared_ptr<RequestHandlerFactory> m_handlerFactory;
	std::shared_ptr<LoggedUser> m_user;

	RequestResult createRoom(const Buffer& buffer);
	RequestResult getContacts(const Buffer& buffer);
	RequestResult logout(const Buffer& buffer);
	RequestResult searchUsers(const Buffer& buffer);
	RequestResult joinRoom(const Buffer& buffer);
	RequestResult startChat(const Buffer& buffer);
	RequestResult getRoomParticipants(const Buffer& buffer);


};