#include "libfacepp_core.h"

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img  = imread("test.jpg");
	facepp::resize_cv2(img);
	return 0;
}