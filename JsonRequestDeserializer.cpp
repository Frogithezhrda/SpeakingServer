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
