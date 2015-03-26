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
using namespace web::json;

const string API_KEY = "d80b2d4e7c2fe1e584c06b62dea1c840";
const string API_SECRET = "oOx5V2xvdf6wkaKRYlVD5Jzs5WxEH55A";
const uri API_SERVER(U("http://api.faceplusplus.com/v2/detection/detect"));

bool facepp::resize_cv2(Mat img) 
{
	if (!(img.data && img.size))  { cerr << "Invalid image" << endl; return false; }
	int bigdim = MAX(img.cols, img.rows);
	double downscale = MAX(1.0, bigdim / 600.0);
	cv::resize(img, img, cvSize(
		static_cast<int>(img.cols / downscale), static_cast<int>(img.rows / downscale)
		));
	imwrite("ftmp.bmp", img);
	cout << "Resize Done" << endl;
	return true;
}

void facepp::connect()
{
	auto fileStream = std::make_shared<concurrency::streams::ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("results.json")).then([=](concurrency::streams::ostream outFile)
	{
		*fileStream = outFile;

		// Create http_client to send the request.
		http_client client(API_SERVER);

		// Build request URI and start the request.
		uri_builder builder(U("/"));
		builder.append_query(U("api_key"), API_KEY.c_str());
		builder.append_query(U("api_secret"), API_SECRET.c_str());
		builder.append_query(U("url"), "http://www.faceplusplus.com/static/img/demo/1.jpg");

		wcout << builder.to_string().c_str() << endl;
		return client.request(methods::POST, builder.to_string());
	})

		// Handle response headers arriving.
		.then([=](http_response response)
	{
		cout << "Received response status code " << response.status_code() << endl;

		pplx::task<json::value> result = response.extract_json();

		wofstream res_json("res.json");

		wcout << result.get().serialize().c_str() << endl;
		res_json << result.get().serialize().c_str() << endl;

		// Write response body into the file.
		return response.body().read_to_end(fileStream->streambuf());
	})

		// Close the file stream.
		.then([=](size_t)
	{
		return fileStream->close();
	});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		cout << "Error exception " << e.what() << endl;
	}
}

facepp::facepp(String path)
{
	Mat img = imread(path);
	resize_cv2(img);
	img = imread("ftmp.bmp");
}

void facepp::get_result()
{
	wifstream res_json("res.json");
	wstring res;
	res_json >> res;

	web::json::value result(res);

}