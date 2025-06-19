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

