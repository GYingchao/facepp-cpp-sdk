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

	for (int i = 0; i < 40; i++)
		cout << facepp::APIS[i] << endl;
	return 0;
}
