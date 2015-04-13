#include "libfacepp.h"

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
}

facepp::facepp(String path)
{
	initAPIs();
	img = imread(path);
	cv2Resize();
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

//void facepp::connect()
//{
//	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("groups.json")).then([=](concurrency::streams::ostream outFile)
//	{
//		http_client client(API_SERVER);
//		uri_builder query;
//
//#if __DEBUG__
//		wcout << query.to_string() << endl;
//#endif
//		return client.request(methods::POST, query.to_string());
//	})
//
//		.then([=](http_response response)
//	{
//		cout << "Received response status code " << response.status_code() << endl;
//		if (response.status_code() != 200)
//		{
//			wcerr << response.to_string() << endl;
//			exit(-1);
//		}
//
//		pplx::task<web::json::value> jsonResult = response.extract_json();
//
//		result = jsonResult.get();
//#if __DEBUG__
//		wcout << result << endl << endl;
//#endif
//		wofstream res_json("groups.json");
//		res_json << jsonResult.get() << endl;
//	});
//
//	try
//	{
//		requestTask.wait();
//	}
//	catch (const std::exception &e)
//	{
//		cout << "Error exception " << e.what() << endl;
//	}
//}