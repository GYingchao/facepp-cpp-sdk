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

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

namespace facepp {
	const string SERVER = "http://api.cn.faceplusplus.com/";
	const string API_KEY = "";
	const string API_SECRET = "";
	const int TIMEOUT = 300;

	bool resize_cv2(Mat img) {
		if (!(img.data && img.size))  { cerr << "Invalid image" << endl; return false; }
		int bigdim = MAX(img.cols, img.rows);
		double downscale = MAX(1.0, bigdim / 600.0);
		cv::resize(img, img, cvSize(
			(int)img.cols / downscale, (int)img.rows / downscale
			));
		imwrite("ftmp.bmp", img);
		return true;
	}

	string APIS[] = {
		"/detection/detect",
		"/detection/landmark",
		"/faceset/add_face",
		"/faceset/create",
		"/faceset/delete",
		"/faceset/get_info",
		"/faceset/remove_face",
		"/faceset/set_info",
		"/group/add_person",
		"/group/create",
		"/group/delete",
		"/group/get_info",
		"/group/remove_person",
		"/group/set_info",
		"/grouping/grouping",
		"/info/get_app",
		"/info/get_face",
		"/info/get_faceset_list",
		"/info/get_group_list",
		"/info/get_image",
		"/info/get_person_list",
		"/info/get_quota",
		"/info/get_session",
		"/person/add_face",
		"/person/create",
		"/person/delete",
		"/person/get_info",
		"/person/remove_face",
		"/person/set_info",
		"/recognition/compare",
		"/recognition/group_search",
		"/recognition/identify",
		"/recognition/recognize",
		"/recognition/search",
		"/recognition/test_train",
		"/recognition/train",
		"/recognition/verify",
		"/train/group_search",
		"/train/identify",
		"/train/recognize",
		"/train/search",
		"/train/verify"
	};
}
