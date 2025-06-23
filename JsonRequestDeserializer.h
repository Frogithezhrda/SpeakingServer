#pragma once
#include "IRequestHandler.h"
#include "json.hpp"
#include "LoggedUser.hpp"
#include "Requests.h"                               

using json = nlohmann::json;

class JsonRequestDeserializer
{
public:

	static LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static SignupRequest deserializeSignupRequest(const Buffer& buffer);
	static SearchRequest deserializeSearchRequest(const Buffer& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const Buffer& buffer);
	static StartChatRequest deserializeStartChatRequest(const Buffer& buffer);

private:
	static json bufferToString(const Buffer& buffer);
};