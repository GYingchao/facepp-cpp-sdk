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
#if __DEBUG__
		cout << "Resize Done" << endl;
#endif
		imwrite("ftmp.bmp", img);
		img = imread("ftmp.bmp");
		return true;
	}
	else
	{
#if __DEBUG__
		cout << "No need to resize" << endl;
#endif
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

		query.append_path(U("/detection/detect"));
		query.append_query(U("api_key"), API_KEY.c_str());
		query.append_query(U("api_secret"), API_SECRET.c_str());
		query.append_query(U("url"), "http://www.faceplusplus.com/static/img/demo/1.jpg");

#if __DEBUG__
		wcout << query.to_string() << endl;
#endif
		return client.request(methods::POST, query.to_string());
	})

		.then([=](http_response response)
	{
		cout << "Received response status code " << response.status_code() << endl;

		jsonResult = response.extract_json();
		result = jsonResult.get();
		
		wofstream res_json("results.json");
		res_json << jsonResult.get() << endl;
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
