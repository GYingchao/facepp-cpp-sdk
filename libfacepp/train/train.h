#pragma once

#ifndef TRAIN_H
#	define TRAIN_H

#include "../libfacepp_core.h"

class train
{
private:
	Concurrency::task<web::json::value> jsonResult;

public:
	train();
	~train();

	web::json::value result;
	void identify();
};
#endif
