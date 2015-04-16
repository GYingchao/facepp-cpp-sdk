// Face++ SDK for C++
// The MIT License (MIT)
// Copyright (c) 2015 clarkzjw@gmail.com
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#ifndef LIBFACEPP_CORE_H
#	define LIBFACEPP_CORE_H

#define __DEBUG__ 0

#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
using namespace std;

#include <cpprest\http_client.h>
#include <cpprest\filestream.h>
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::json;
using namespace web::http::client;
using namespace pplx;
using namespace concurrency::streams;

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;

const uri API_SERVER(U("http://api.faceplusplus.com/v2/"));
const string API_KEY = "d80b2d4e7c2fe1e584c06b62dea1c840";
const string API_SECRET = "oOx5V2xvdf6wkaKRYlVD5Jzs5WxEH55A";

#endif