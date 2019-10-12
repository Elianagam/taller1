#include "server_User.h"

User::User() :
	logged(false),
	comand_user(false) {}

void User::loggin() {
	logged = true;
}

void User::comand_not_user() {
	comand_user = false;
}

void User::comand_is_user() {
	comand_user = true;
}
bool User::last_comand_was_user() {
	return comand_user;
}

bool User::is_logged() {
	return logged;
}

