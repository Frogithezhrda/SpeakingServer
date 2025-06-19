#pragma once
#include <string>

//login and logout Requests/Responses
typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
	std::string profilePath;
} SignupRequest;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;
// end of login
//