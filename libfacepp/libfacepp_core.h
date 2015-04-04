#pragma once

#ifndef LIBFACEPP_CORE_H
#	define LIBFACEPP_CORE_H

#define __DEBUG__ 1

#include <string>
#include <cpprest\http_client.h>

const web::uri API_SERVER(U("http://api.faceplusplus.com/v2/"));
const std::string API_KEY = "d80b2d4e7c2fe1e584c06b62dea1c840";
const std::string API_SECRET = "oOx5V2xvdf6wkaKRYlVD5Jzs5WxEH55A";

#endif