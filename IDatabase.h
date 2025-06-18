#pragma once
typedef struct Query
{
	const char* sqlStatement;
	void* param;
	int (*callback)(void*, int, char**, char**);
	Query(const char* sqlStatement, void* param, int (*callback)(void*, int, char**, char**))
		: sqlStatement(sqlStatement), param(param), callback(callback) {
	}

} Query;

class IDatabase
{
public:
	virtual void createQuery(const Query& query) = 0;
	virtual void close() = 0;


};