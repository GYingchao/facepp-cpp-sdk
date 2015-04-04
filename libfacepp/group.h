#pragma once

#ifndef GROUP_H
#	define GROUP_H

#include "libfacepp_core.h"

class group
{
private:
	Concurrency::task<web::json::value> jsonResult;

public:
	group();
	~group();

	web::json::value result;
	void create();
};
#endif
