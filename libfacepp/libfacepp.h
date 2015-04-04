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

#ifndef LIB_FACEPP_H
#	define LIB_FACEPP_H

#include <iostream>
#include <string>
#include <map>
#include <set>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <cpprest\http_client.h>
#include <cpprest\filestream.h>

#include "libfacepp_core.h"
#include "group.h"
#include "person.h"
#include "recognition.h"
#include "train.h"

using std::map;
using std::set;
using std::string;
using std::wstring;
using web::json::value;
using pplx::task;
using cv::Mat;

#ifdef MAX
#undef MAX
#	define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

class facepp
{
#ifndef API_NUM
#	define API_NUM 35
#endif

private:
	set<string> APIs;
	Mat img;

	Concurrency::task<web::json::value> jsonResult;
	void initAPIs();

public:
	double __version__ = 1.0;

	web::json::value result;
	web::uri_builder query;

	facepp();
	facepp(string path);

	bool cv2Resize();
	void connect(bool init = true);
};

#endif
