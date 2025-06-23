#include "JsonRequestDeserializer.h"

json JsonRequestDeserializer::bufferToString(const Buffer& buffer)
{
    std::string jsonStr(buffer.begin(), buffer.end());
    return json::parse(jsonStr);;
}

LoginRequest JsonRequestDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
    json jsonContainer = bufferToString(buffer);

    return LoginRequest{ jsonContainer["username"].get<std::string>(),
                          jsonContainer["password"].get<std::string>() };
}

SignupRequest JsonRequestDeserializer::deserializeSignupRequest(const Buffer& buffer)
{
    json jsonContainer = bufferToString(buffer);
    return SignupRequest{ jsonContainer["username"].get<std::string>(),
                          jsonContainer["password"].get<std::string>(),
                          jsonContainer["email"].get<std::string>(),
                          jsonContainer["profilePath"].get<std::string>() };
}


SearchRequest JsonRequestDeserializer::deserializeSearchRequest(const Buffer& buffer)
{
    json jsonContainer = bufferToString(buffer);
    return SearchRequest{ jsonContainer["username"].get<std::string>() };
}

JoinRoomRequest JsonRequestDeserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
    json jsonContainer = bufferToString(buffer);
    return JoinRoomRequest{ jsonContainer["roomId"].get<unsigned int>() };
}

CreateRoomRequest JsonRequestDeserializer::deserializeCreateRoomRequest(const Buffer& buffer)
{
    json jsonContainer = bufferToString(buffer);
    return CreateRoomRequest{ jsonContainer["roomName"].get<std::string>(),
                              (unsigned)std::stoi(jsonContainer["maxUsers"].get<std::string>()) };

}

StartChatRequest JsonRequestDeserializer::deserializeStartChatRequest(const Buffer& buffer)
{
    json jsonContainer = bufferToString(buffer);
    return StartChatRequest{ jsonContainer["username"].get<std::string>() };
}
