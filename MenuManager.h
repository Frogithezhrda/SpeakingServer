#pragma once
#include "DatabaseException.hpp"
#include "SQLDatabase.h"
#include <vector>

class MenuManager
{
public:
	MenuManager(const std::shared_ptr<IDatabase> database);

	std::vector<Contact> getContacts() const;
	std::shared_ptr<Contact> searchUser(const std::string& searchUser) const;
	void startChat(const std::string& username) const;

private:
	std::shared_ptr<SQLDatabase> m_database;
};