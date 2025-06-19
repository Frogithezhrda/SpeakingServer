#pragma once
#include "RequestException.hpp"
#include <time.h>
#include <vector>
#include <memory>

class IRequestHandler;

typedef std::vector<unsigned char> Buffer;

enum Status
{
	Bad = 0, Ok = 1
};
enum class RequestId
{
	NONE = 0x0, ERROR_MSG, LOGIN, SIGNUP, LOGOUT, CREATE_ROOM, JOIN_ROOM, GET_PLAYERS_IN_ROOM, GET_ROOMS_CHAT, CLOSE_ROOM, START_ROOM,
	LEAVE_ROOM, JOIN_CHAT, CREATE_CHAT, LEAVE_CHAT, GET_MESSAGES, EXIT
};

typedef struct RequestInfo
{
	RequestId id;
	time_t receivalTime;
	Buffer buffer;
} RequestInfo;

typedef struct RequestResult
{
	Buffer response;
	std::shared_ptr<IRequestHandler> newHandler;
} RequestResult;


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& request) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& request) const = 0;

private:

};