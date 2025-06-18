#pragma once
#include <memory>
#include "IDatabase.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(std::shared_ptr<IDatabase> database);
	virtual ~RequestHandlerFactory();

	//std::unique_ptr<LoginRequestHandler> createLoginRequestHandler(std::shared_ptr<SOCKET> userSocket) const;
	//std::unique_ptr<MenuRequestHandler> createMenuRequestHandler(std::shared_ptr<LoggedUser> user) const;
	//std::unique_ptr<RoomAdminRequestHandler> createAdminRequestHandler(std::shared_ptr<LoggedUser> user, std::shared_ptr<Room> room) const;
	//std::unique_ptr<RoomMemberRequestHandler> createRoomMemberHandler(std::shared_ptr<LoggedUser> user, std::shared_ptr<Room> room) const;
	//LoginManager* getLoginManager() const;
	//RoomManager* getRoomManager() const;
	//StatisticsManager* getStatisticsManager() const;
private:
	//RoomManager* m_roomManager;
	std::shared_ptr<IDatabase> m_database;
	//LoginManager* m_loginManager;
};