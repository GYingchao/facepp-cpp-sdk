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

bool resize_cv2(Mat img) 
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

