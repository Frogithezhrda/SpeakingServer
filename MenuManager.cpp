#include "MenuManager.h"

MenuManager::MenuManager(const std::shared_ptr<IDatabase> database)
{
	m_database = std::dynamic_pointer_cast<SQLDatabase>(database);
}

std::vector<Contact> MenuManager::getContacts() const
{
	//std::string sqlStatement = "SELECT NAME, USER_ID, PROFILE_PATH FROM USERS JOIN CONTACTS ON USERS.USER_ID = CONTACTS.CONTACT_ID;";


	return std::vector<Contact>();
}

std::shared_ptr<Contact> MenuManager::searchUser(const std::string& searchUser) const
{
	return m_database->getUser(searchUser);
}

void MenuManager::startChat(const std::string& username) const
{

}
