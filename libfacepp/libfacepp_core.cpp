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

#include "libfacepp_core.h"

using namespace cv;
using namespace std;

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

const string API_KEY = "d80b2d4e7c2fe1e584c06b62dea1c840";
const string API_SECRET = "oOx5V2xvdf6wkaKRYlVD5Jzs5WxEH55A";
const uri API_SERVER(U("http://api.faceplusplus.com/v2/detection/detect"));

facepp::facepp(String path)
{
	Mat img = imread(path);
	resize_cv2(img);
	img = imread("ftmp.bmp");
}

bool facepp::resize_cv2(Mat img) 
{
	if (!(img.data && img.size))  
	{ 
		cerr << "Invalid image" << endl; 
		return false; 
	}
	int bigdim = MAX(img.cols, img.rows);
	double downscale = MAX(1.0, bigdim / 600.0);
	resize(img, img, cvSize(static_cast<int>(img.cols / downscale), static_cast<int>(img.rows / downscale)));
	imwrite("ftmp.bmp", img);
	cout << "Resize Done" << endl;
	return true;
}

void facepp::connect()
{
	auto fileStream = std::make_shared<concurrency::streams::ostream>();

	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("results.json")).then([=](concurrency::streams::ostream outFile)
	{
		*fileStream = outFile;

		http_client client(API_SERVER);

		uri_builder builder(U("/"));
		
		builder.append_query(U("api_key"), API_KEY.c_str());
		builder.append_query(U("api_secret"), API_SECRET.c_str());
		builder.append_query(U("url"), "http://www.faceplusplus.com/static/img/demo/1.jpg");

		wcout << builder.to_string() << endl;
		return client.request(methods::POST, builder.to_string());
	})

		.then([=](http_response response)
	{
		cout << "Received response status code " << response.status_code() << endl;

		pplx::task<json::value> result = response.extract_json();
		get_result(result);

		wofstream res_json("res.json");
		res_json << result.get() << endl;

		return response.body().read_to_end(fileStream->streambuf());
	})

		.then([=](size_t)
	{
		return fileStream->close();
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

void facepp::get_result(pplx::task<json::value> result)
{
	json::value root = result.get();
	json::value face = root.at(U("face"))[0];
	json::value position = face.at(U("position"));

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