#pragma once
#include <unordered_map>
#include "DatabaseException.hpp"
#include "LoggedUser.hpp"
#include "SQLDatabase.h"

class LoginManager
{
public:
	LoginManager(std::shared_ptr<IDatabase> database);
	bool logout(const std::string& userName);
	bool signup(const std::string& userName, const std::string& password, const std::string& email, std::shared_ptr<LoggedUser> user);
	bool signin(const std::string& userName, const std::string& password, std::shared_ptr<LoggedUser> user);
	std::string getUsernameBySocket(const SOCKET socket);



private:
	std::shared_ptr<SQLDatabase> m_database;
	std::unordered_map<std::string, std::shared_ptr<LoggedUser>> m_loggedUsers;


};