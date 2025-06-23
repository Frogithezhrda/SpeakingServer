#include "JsonResponseSerializer.h"

Buffer JsonResponseSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	Buffer buffer;
	return serialize("status", loginResponse.status, buffer, RequestId::LOGIN);
}

Buffer JsonResponseSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	Buffer buffer;
	return serialize("status", signupResponse.status, buffer, RequestId::SIGNUP);
}

Buffer JsonResponseSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	Buffer buffer;
	return serialize("message", errorResponse.message, buffer, RequestId::ERROR_MSG);
}

Buffer JsonResponseSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
	Buffer buffer;
	return serialize("status", logoutResponse.status, buffer, RequestId::LOGOUT);
}

Buffer JsonResponseSerializer::serializeResponse(const SearchResponse& searchResponse)
{
	Buffer buffer;
	json searchResult = {
	{ "status", searchResponse.status },
	{ "userId", searchResponse.userId },
	{ "username", searchResponse.username },
	{ "profilePath", searchResponse.profilePath }
	};


	return serialize("Search", searchResult, buffer, RequestId::SEARCH_USER);
}

Buffer JsonResponseSerializer::serializeResponse(const CreateRoomResponse& createResponse)
{
	Buffer buffer;
	return serialize("status", createResponse.status, buffer, RequestId::CREATE_ROOM);
}

Buffer JsonResponseSerializer::serializeResponse(const JoinRoomResponse& joinResponse)
{
	Buffer buffer;
	return serialize("status", joinResponse.status, buffer, RequestId::JOIN_ROOM);
}
