#include "LoginManager.h"

LoginManager::LoginManager(std::shared_ptr<IDatabase> database)
{
	//casting to sql database cause not all functions are in IDatabase
	m_database = std::dynamic_pointer_cast<SQLDatabase>(database);
}

bool LoginManager::logout(const std::string& userName)
{
	return false;
}

bool LoginManager::signup(const std::string& userName, const std::string& password, const std::string& email, std::shared_ptr<LoggedUser> user)
{
	return false;
}

bool LoginManager::signin(const std::string& userName, const std::string& password, std::shared_ptr<LoggedUser> user)
{
	if (!m_database->doesPasswordMatch(userName, password))
	{
		return false;
	}
	if (m_loggedUsers.find(userName) != m_loggedUsers.end())
	{
		return false;
	}
	m_loggedUsers[userName] = user;
	return true;



}
	
std::string LoginManager::getUsernameBySocket(const SOCKET socket)
{
	return std::string();
}
