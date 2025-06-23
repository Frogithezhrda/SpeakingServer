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
//Menu Responses
typedef struct SearchRequest
{
	std::string username;
} SearchRequest;

typedef struct SearchResponse
{
	unsigned int status;
	std::string username;
	std::string profilePath;
	unsigned int userId;
} SearchResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
} CreateRoomRequest;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;

typedef struct getParticipantsResponse
{
	std::vector<std::string> users;
} getParticipantsResponse;

typedef struct getParticipantsRequest
{
	unsigned int roomId;
} getParticipantsRequest;

typedef struct getContactsResponse
{
	std::vector<std::string> users;
} getContactsResponse;

typedef struct StartChatRequest
{
	std::string usernameToChat;
} StartChatRequest;

typedef struct StartChatResponse
{
	unsigned int status;
} StartChatResponse;
//end of menu
//
//
