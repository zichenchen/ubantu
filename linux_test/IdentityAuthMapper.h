#pragma once
#include <iostream>
#include"rttr/type.h"
#include "Dao.h"
using namespace std;
class IdentityAuthMapper {
public:
	IdentityAuthMapper();
	~IdentityAuthMapper();
	rttr::variant finduserinfoByNameAndPassword(string username, string password);
private:
	Dao* dao;
};