#pragma once
class Auth
{
public:
	static int is_authed(const std::string& username, const std::string& password);
};

extern int menu_version;
