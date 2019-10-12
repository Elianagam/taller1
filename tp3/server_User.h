#ifndef _USER_H
#define _USER_H

class User {
private:
	bool logged;
	bool comand_user;

public:
	User();
	
	void loggin();

	void comand_not_user();

	void comand_is_user();

	bool is_logged();

	bool last_comand_was_user();
};

#endif