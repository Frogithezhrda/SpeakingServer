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
	RequestResult result;
	CreateRoomResponse response;
	CreateRoomRequest request = JsonRequestDeserializer::deserializeCreateRoomRequest(buffer);

	RoomData data;
	data.maxPlayers = request.maxUsers;
	data.name = request.roomName;
	try
	{
		auto room = m_handlerFactory->getRoomManager()->createRoom(m_user, data);
		//result.newHandler = std::move(m_handlerFactory->createAdminRequestHandler(m_user, room));
		response.status = Ok;
	}
	catch (const std::exception&)
	{
		response.status = Bad;
	}

	result.response = JsonResponseSerializer::serializeResponse(response);
	return result;
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
	RequestResult result;
	auto contact = m_handlerFactory->getMenuManager()->searchUser(JsonRequestDeserializer::deserializeSearchRequest(buffer).username).get();
	if (contact)
	{
		result.response = JsonResponseSerializer::serializeResponse({ Ok, contact->username, contact->profilePath, contact->id });
	}
	else
	{
		result.response = JsonResponseSerializer::serializeResponse({ Bad, "", "", Bad });
	}
	result.newHandler = m_handlerFactory->createMenuRequestHandler(m_handlerFactory, m_user);
	return result;
}

RequestResult MenuRequestHandler::joinRoom(const Buffer& buffer)
{
	JoinRoomResponse join;
	RequestResult result;
	try
	{
		auto room = m_handlerFactory->getRoomManager()->joinRoom(JsonRequestDeserializer::deserializeJoinRoomRequest(buffer).roomId, m_user);

		room.first ? join.status = Ok : join.status = Bad;
		result.response = JsonResponseSerializer::serializeResponse(join);
		return result;
	}
	catch (const std::exception&)
	{
		join.status = Bad;
	}

	result.response = JsonResponseSerializer::serializeResponse(join);
	return result;
}

RequestResult MenuRequestHandler::startChat(const Buffer& buffer)
{
	JsonRequestDeserializer::deserializeStartChatRequest(buffer).usernameToChat;
	m_handlerFactory->getMenuManager()->startChat();
	return RequestResult();
}

RequestResult MenuRequestHandler::getRoomParticipants(const Buffer& buffer)
{
	return RequestResult();
}
