#include "libfacepp_core.h"

using namespace std;
using namespace cv;

int main()
{
	Mat img  = imread("test.jpg");
	resize_cv2(img);

	facepp face;
	face.connect();

	return 0;
}
