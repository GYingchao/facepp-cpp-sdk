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
