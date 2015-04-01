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

#ifndef LIB_FACEPP_CORE_H
#	define LIB_FACEPP_CORE_H

#include <iostream>
#include <string>
#include <map>
#include <set>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <cpprest\http_client.h>
#include <cpprest\filestream.h>

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

const web::uri API_SERVER(U("http://api.faceplusplus.com/v2/"));

class facepp
{
#ifndef API_NUM
#	define API_NUM 35
#endif

private:
	map<string, value> map_result;
	set<string> APIs;
	task<value> result;
	
	Mat img;
	wstring face_id;

	const string API_KEY = "d80b2d4e7c2fe1e584c06b62dea1c840";
	const string API_SECRET = "oOx5V2xvdf6wkaKRYlVD5Jzs5WxEH55A";
	
	void initAPIs();

public:

	facepp();
	facepp(string path);

	bool cv2Resize();
	void connect(bool init = true);
	void parseResult();

	class person
	{
	public:
		void create();
	};

	class group
	{
	public:
		void create();
	};

	class train
	{
	public:
		void identify();
	};
	
	class recognition
	{
	public:
		void identify();
	};
};

#endif
