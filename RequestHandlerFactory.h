#pragma once
#include <memory>
#include "IDatabase.h"
#include "LoginManager.h"
#include "MenuManager.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(std::shared_ptr<IDatabase> database);

	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler(std::shared_ptr<RequestHandlerFactory> selfPointer, std::shared_ptr<SOCKET> userSocket) const;
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(std::shared_ptr<RequestHandlerFactory> selfPointer, std::shared_ptr<LoggedUser> user) const;
	//std::unique_ptr<RoomAdminRequestHandler> createAdminRequestHandler(std::shared_ptr<LoggedUser> user, std::shared_ptr<Room> room) const;
	//std::unique_ptr<RoomMemberRequestHandler> createRoomMemberHandler(std::shared_ptr<LoggedUser> user, std::shared_ptr<Room> room) const;
	std::shared_ptr<LoginManager> getLoginManager() const;
	std::shared_ptr<MenuManager> getMenuManager() const;
	std::shared_ptr<RoomManager> getRoomManager() const;
private:
	std::shared_ptr<IDatabase> m_database;
	std::shared_ptr<LoginManager> m_loginManager;
	std::shared_ptr<MenuManager> m_menuManager;
	std::shared_ptr<RoomManager> m_roomManager;
};