#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(std::shared_ptr<RequestHandlerFactory> factory, std::shared_ptr<LoggedUser> user)
{
	m_user = user;
	m_handlerFactory = factory;
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return request.id == RequestId::GET_CONTACTS_LIST || request.id == RequestId::SEARCH_USER
		|| request.id == RequestId::LOGOUT || request.id == RequestId::START_CHAT_WITH_USER
		|| request.id == RequestId::JOIN_ROOM || request.id == RequestId::CREATE_ROOM
		|| request.id == RequestId::GET_ROOM_PARTICIPANTS;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request) const
{
	ErrorResponse errorResponse;
	RequestResult result;

	if (isRequestRelevant(request))
	{
		std::map<RequestId, RequestResult(MenuRequestHandler::*)(const Buffer&)> handlers = {
			{RequestId::CREATE_ROOM,&MenuRequestHandler::createRoom},
			{RequestId::GET_CONTACTS_LIST,&MenuRequestHandler::getContacts},
			{RequestId::LOGOUT,&MenuRequestHandler::logout},
			{RequestId::SEARCH_USER,&MenuRequestHandler::searchUsers},
			{RequestId::JOIN_ROOM,&MenuRequestHandler::joinRoom},
			{RequestId::START_CHAT_WITH_USER,&MenuRequestHandler::startChat},
			{RequestId::GET_ROOM_PARTICIPANTS,&MenuRequestHandler::getRoomParticipants},
		};
		auto it = handlers.find(request.id);
		if (it != handlers.end())
		{
			// Call the appropriate handler function.
			auto func = it->second;
			result = (const_cast<MenuRequestHandler*>(this)->*func)(request.buffer);
		}
		return result;
	}
	errorResponse.message = "Error: Try Again Later!";
	result.response = JsonResponseSerializer::serializeResponse(errorResponse);
	return result;
}

RequestResult MenuRequestHandler::createRoom(const Buffer& buffer)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getContacts(const Buffer& buffer)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::logout(const Buffer& buffer)
{
	RequestResult result;
	LogoutResponse logout;

	m_handlerFactory->getLoginManager()->logout(m_user->getUsername()) ? logout.status = Ok : logout.status = Bad;

	result.response = JsonResponseSerializer::serializeResponse(logout);

	result.newHandler = m_handlerFactory->createLoginRequestHandler(m_handlerFactory, m_user->getSocket());
	return result;
}

RequestResult MenuRequestHandler::searchUsers(const Buffer& buffer)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(const Buffer& buffer)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::startChat(const Buffer& buffer)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getRoomParticipants(const Buffer& buffer)
{
	return RequestResult();
}
