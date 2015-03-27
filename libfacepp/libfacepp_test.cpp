#include "libfacepp_core.h"

using namespace std;
using namespace cv;

int main()
{
	facepp face("test.jpg");
	face.connect();
	
	return 0;
}
