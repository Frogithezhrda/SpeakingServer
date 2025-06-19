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
    LOGIN,
    SIGNUP,
    LOGOUT,

    //base user
    GET_CONTACTS_LIST,       
    SEARCH_USER,              
    START_CHAT_WITH_USER,     

    //direct chats
    SEND_DIRECT_MESSAGE,
    GET_DIRECT_MESSAGES,
    START_DIRECT_CALL,
    END_DIRECT_CALL,

    //group rooms
    CREATE_ROOM,
    INVITE_TO_ROOM,
    JOIN_ROOM,
    LEAVE_ROOM,
    CLOSE_ROOM,
    GET_ROOM_PARTICIPANTS,

    //groups
    SEND_ROOM_MESSAGE,
    GET_ROOM_MESSAGES,
    START_ROOM_CALL,
    END_ROOM_CALL,

    //errors
    ERROR_MSG,
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