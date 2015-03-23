#include "libfacepp_core.h"

using namespace std;
using namespace cv;

int main()
{
	Mat img  = imread("test.jpg");
	resize_cv2(img);

	connect();
	
	return 0;
}
