#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(std::shared_ptr<RequestHandlerFactory> factory, std::shared_ptr<SOCKET> currentSocket)
{
	m_handlerFactory = factory;
	m_currentUserSock = currentSocket;
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return request.id == RequestId::SIGNUP || request.id == RequestId::LOGIN;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request) const
{
	RequestResult result;
    LoginResponse loginResponse;
    std::shared_ptr<LoggedUser> user;
    ErrorResponse errorResponse;
	if (isRequestRelevant(request))
	{
        if (request.id == RequestId::SIGNUP)
        {
            SignupRequest login = JsonRequestDeserializer::deserializeSignupRequest(request.buffer);
            user = std::make_shared<LoggedUser>(login.username, m_currentUserSock);
            //currently not profile picture!
            loginResponse.status = m_handlerFactory->getLoginManager()->signup(login.password, login.email, login.profilePath, user) ? Ok : Bad;
        }
        else
        {
            LoginRequest login = JsonRequestDeserializer::deserializeLoginRequest(request.buffer);
            user = std::make_shared<LoggedUser>(login.username, m_currentUserSock);
            loginResponse.status = m_handlerFactory->getLoginManager()->signin(login.password, user) ? Ok : Bad;
        }
        //loginResponse.status == Ok ? result.newHandler = m_handlerFactory->createMenuRequestHandler(user) : result.newHandler = m_handlerFactory->createLoginRequestHandler(m_currentUserSock);
        result.response = JsonResponseSerializer::serializeResponse(loginResponse);
        return result;
	}
    result.newHandler = m_handlerFactory->createLoginRequestHandler(m_handlerFactory, m_currentUserSock);
    errorResponse.message = "Error: Not A Login/Signup Request!";
    result.response = JsonResponseSerializer::serializeResponse(errorResponse);
    return result;
}