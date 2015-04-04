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

		uri_builder builder(U("/"));

		const std::string API_KEY = "d80b2d4e7c2fe1e584c06b62dea1c840";
		const std::string API_SECRET = "oOx5V2xvdf6wkaKRYlVD5Jzs5WxEH55A";

		builder.append_path(U("person/create"));
		builder.append_query(U("api_key"), API_KEY.c_str());
		builder.append_query(U("api_secret"), API_SECRET.c_str());

		std::wcout << builder.to_string() << std::endl;
		return client.request(methods::POST, builder.to_string());
	})

		.then([=](http_response response)
	{
		std::cout << "Received response status code " << response.status_code() << std::endl;

		pplx::task<web::json::value> result_tmp = response.extract_json();

		std::wofstream res_json("persons.json");
		res_json << result_tmp.get() << std::endl;
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