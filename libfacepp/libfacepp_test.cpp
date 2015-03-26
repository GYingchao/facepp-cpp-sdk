#include "libfacepp_core.h"

using namespace std;
using namespace cv;

int main()
{
	facepp face("test.jpg");
	face.connect();
	face.get_result();

	return 0;
}
