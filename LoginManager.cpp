#include "LoginManager.h"

LoginManager::LoginManager(const std::shared_ptr<IDatabase> database)
{
	//casting to sql database cause not all functions are in IDatabase
	m_database = std::dynamic_pointer_cast<SQLDatabase>(database);
}

bool LoginManager::logout(const std::string& userName)
{
	if (m_loggedUsers.find(userName) != m_loggedUsers.end())
	{
		m_loggedUsers.erase(userName);
		return true;
	}

	return false;
}

bool LoginManager::signup(const std::string& password, const std::string& email, const std::string& profilePath, std::shared_ptr<LoggedUser> user)
{
	if (isPasswordValid(password) && isMailValid(email) && isNameValid(user->getUsername()))
	{
		try
		{
			m_database->addNewUser(user->getUsername(), password, email, profilePath);
		}
		catch (const DataBaseException&)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool LoginManager::signin(const std::string& password, std::shared_ptr<LoggedUser> user)
{
	if (!m_database->doesPasswordMatch(user.get()->getUsername(), password))
	{
		return false;
	}
	//using the map to find the user
	if (m_loggedUsers.find(user.get()->getUsername()) != m_loggedUsers.end())
	{
		return false;
	}
	m_loggedUsers[user.get()->getUsername()] = user;
	return true;
}
	
std::string LoginManager::getUsernameBySocket(const std::shared_ptr<SOCKET> socket) const
{

	//we must go through each user and fine the socket
	for (const auto& loggedUser : m_loggedUsers)
	{
		if (loggedUser.second->getSocket() == socket)
		{
			return loggedUser.first;
		}
	}
	return "";
}

bool LoginManager::isPasswordValid(const std::string& password) const
{
	//at least one lowercase uppercase digit and special character and at least 8 chars(no spaces using whitespace)
	const std::regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?!.*\\s).{8,}$");
	return std::regex_match(password, pattern);
}

bool LoginManager::isMailValid(const std::string& mail) const
{
	//word + @ + word + dot + domain2-6 chars no spaces
	const std::regex pattern("^(?!.*\\s)\w+@\w+\.\w{2,6}$");
	return std::regex_match(mail, pattern);
}

bool LoginManager::isNameValid(const std::string& name) const
{
	//no spaces no symbols and at least 5 chars
	const std::regex pattern("^(?!.*\\s)(?!.*[!@#$%^&*]).{5,}$");
	return std::regex_match(name, pattern);
}
