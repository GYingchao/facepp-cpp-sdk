#pragma once

#ifndef PERSON_H
#	define PERSON_H

#include "../libfacepp_core.h"

class person
{
private:
	Concurrency::task<web::json::value> jsonResult;

public:
	person();
	~person();

	web::uri_builder query;
	web::json::value result;
	void create();
};
#endif
