// Face++ SDK for C++
// The MIT License (MIT)
// Copyright (c) 2015 clarkzjw
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
#define LIB_FACEPP_CORE_H

#include <iostream>
#include <string>
#include <map>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <cpprest\http_client.h>
#include <cpprest\filestream.h>

const int API_NUM = 35;
const int API_MAX_LENGTH = 100;

class facepp
{
public:
	std::map<std::string, web::json::value> map_result;

	facepp(std::string path);

	bool resize_cv2(cv::Mat img);
	void connect();
	void get_result(pplx::task<web::json::value> result);

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

const char APIS[API_NUM][API_MAX_LENGTH] = 
{
	"/detection/detect",
	"/detection/landmark",

	"/train/verify",
	"/train/search",
	"/train/identify",
	
	"/recognition/compare",
	"/recognition/verify",
	"/recognition/identify",
	"/recognition/search",

	"/grouping/grouping",

	"/person/create",
	"/person/delete",
	"/person/add_face",
	"/person/remove_face",
	"/person/set_info",
	"/person/get_info",

	"/faceset/create",
	"/faceset/delete",
	"/faceset/add_face",
	"/faceset/remove_face",
	"/faceset/set_info",
	"/faceset/get_info",

	"/group/create",
	"/group/delete",
	"/group/add_person",
	"/group/remove_person",
	"/group/set_info",
	"/group/get_info",

	"/info/get_image",
	"/info/get_face",
	"/info/get_faceset_list",
	"/info/get_person_list",
	"/info/get_group_list",
	"/info/get_session",
	"/info/get_app"	
};

#endif