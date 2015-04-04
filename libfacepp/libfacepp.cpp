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

#include "libfacepp.h"

using namespace cv;
using namespace std;

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

void facepp::initAPIs()
{
	string apis[35] = {
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

	for (auto api : apis)
		APIs.insert(api);
}

facepp::facepp()
{
	initAPIs();
	connect();
}

facepp::facepp(String path)
{
	initAPIs();
	img = imread(path);
	cv2Resize();
	connect(false);
}

bool facepp::cv2Resize() 
{
	if (!(img.data && img.size))  
	{ 
		cerr << "Invalid Image" << endl; 
		return false; 
	}
	int bigdim = MAX(img.cols, img.rows);
	double downscale = MAX(1.0, bigdim / 600.0);

	if (downscale != 1.0)
	{
		resize(img, img, cvSize(static_cast<int>(img.cols / downscale), static_cast<int>(img.rows / downscale)));
		cout << "Resize Done" << endl;
		imwrite("ftmp.bmp", img);
		img = imread("ftmp.bmp");
		return true;
	}
	else
	{
		cout << "No need to resize" << endl;
		return false;
	}
}

void facepp::connect(bool init)
{
	//if (init == false)
	//	return;

	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("results.json")).then([=](concurrency::streams::ostream outFile)
	{
		http_client client(API_SERVER);

		uri_builder builder(U("/"));
		
		builder.append_path(U("detection/detect"));
		builder.append_query(U("api_key"), API_KEY.c_str());
		builder.append_query(U("api_secret"), API_SECRET.c_str());
		builder.append_query(U("url"), "http://www.faceplusplus.com/static/img/demo/1.jpg");

		wcout << builder.to_string() << endl;
		return client.request(methods::POST, builder.to_string());
	})

		.then([=](http_response response)
	{
		cout << "Received response status code " << response.status_code() << endl;

		result = response.extract_json();
		parseResult();

		wofstream res_json("results.json");
		res_json << result.get() << endl;
	});

	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		cout << "Error exception " << e.what() << endl;
	}
}

void facepp::parseResult()
{
	json::value root = result.get();
	json::value face = root.at(U("face"))[0];
	json::value position = face.at(U("position"));

	face_id = face.at(U("face_id")).as_string();

	map_result.insert(pair<string, json::value>("img_height", root.at(U("img_height"))  ));
	map_result.insert(pair<string, json::value>("img_width",  root.at(U("img_width"))   ));
	map_result.insert(pair<string, json::value>("session_id", root.at(U("session_id"))  ));
	map_result.insert(pair<string, json::value>("url",		  root.at(U("url"))         ));
	map_result.insert(pair<string, json::value>("img_id",     root.at(U("img_id"))      ));

	map_result.insert(pair<string, json::value>("face",       face                      ));
	map_result.insert(pair<string, json::value>("position",   position                  ));

	map <string, json::value>::iterator Iter;
	for (Iter = map_result.begin(); Iter != map_result.end(); Iter++)
	{
		cout << Iter->first << " ";
		wcout << Iter->second << endl;
	}
}
