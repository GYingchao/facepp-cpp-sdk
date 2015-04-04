#include "person.h"
#include "libfacepp_core.h"

#include <iostream>

#include <cpprest\http_client.h>
#include <cpprest\filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

person::person()
{
}


person::~person()
{
}

void person::create()
{
	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("persons.json")).then([=](concurrency::streams::ostream outFile)
	{
		http_client client(API_SERVER);

		query.append_query(U("api_key"), API_KEY.c_str());
		query.append_query(U("api_secret"), API_SECRET.c_str());

#if __DEBUG__
		std::wcout << query.to_string() << std::endl;
#endif
		return client.request(methods::POST, query.to_string());
	})

		.then([=](http_response response)
	{
		std::cout << "Received response status code " << response.status_code() << std::endl;

		pplx::task<web::json::value> jsonResult = response.extract_json();

		result = jsonResult.get();

		std::wofstream res_json("persons.json");
		res_json << jsonResult.get() << std::endl;
	});

	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		std::cout << "Error exception " << e.what() << std::endl;
	}
}