#include "../libfacepp_core.h"
#include "person.h"

#include <iostream>
using namespace std;

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

void person::Create()
{
	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("persons.json")).then([=](concurrency::streams::ostream outFile)
	{
		http_client client(API_SERVER);

		query.append_path(U("/person/create"));
		query.append_query(U("api_key"), API_KEY.c_str());
		query.append_query(U("api_secret"), API_SECRET.c_str());

#if __DEBUG__
		wcout << query.to_string() << endl;
#endif
		return client.request(methods::POST, query.to_string());
	})

		.then([=](http_response response)
	{
		cout << "Received response status code " << response.status_code() << endl;

		if (response.status_code() != 200)
		{
			wcerr << response.to_string() << endl;
			exit(-1);
		}
		pplx::task<web::json::value> jsonResult = response.extract_json();

		result = jsonResult.get();
#if __DEBUG__
		wcout << result << endl << endl;
#endif
		wofstream res_json("persons.json");
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