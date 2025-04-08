#pragma once
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)>HttpHandle;
class LogicSystem :public Singleton<LogicSystem> {
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem(){}
	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
	void RegGet(std::string, HttpHandle handle);
	void RegPost(std::string url, HttpHandle handle);
	bool HandlePos(std::string url, std::shared_ptr<HttpConnection>);
private:
	LogicSystem();
	std::map<std::string, HttpHandle> _post_handlers;
	std::map<std::string, HttpHandle> _get_handlers;
};