#pragma once

#ifndef RECOGNITION_H
#	define RECOGNITION_H

#include "../libfacepp_core.h"

class recognition
{
private:
	Concurrency::task<web::json::value> jsonResult;

public:
	recognition();
	~recognition();

	web::json::value result;
	void identify();
};
#endif
