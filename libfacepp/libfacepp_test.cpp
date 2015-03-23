#include "libfacepp_core.h"

using namespace std;
using namespace cv;

int main()
{
	Mat img  = imread("test.jpg");
	resize_cv2(img);

	for (int i = 0; i < 40; i++)
		cout << APIS[i] << endl;
	return 0;
}
