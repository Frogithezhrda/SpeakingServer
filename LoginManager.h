#pragma once
#include <unordered_map>
#include "DatabaseException.hpp"
#include "LoggedUser.hpp"
#include "SQLDatabase.h"
#include <regex>

class LoginManager
{
public:
	LoginManager(const std::shared_ptr<IDatabase> database);
	bool logout(const std::string& userName);
	bool signup(const std::string& password, const std::string& email, const std::string& profilePath, std::shared_ptr<LoggedUser> user);
	bool signin(const std::string& password, std::shared_ptr<LoggedUser> user);
	std::string getUsernameBySocket(const std::shared_ptr<SOCKET> socket) const;



private:
	std::shared_ptr<SQLDatabase> m_database;
	std::unordered_map<std::string, std::shared_ptr<LoggedUser>> m_loggedUsers;

	bool isPasswordValid(const std::string& password) const;
	bool isMailValid(const std::string& mail) const;
	bool isNameValid(const std::string& name) const;

};