#include "libfacepp_core.h"

int main()
{
	facepp face("test.jpg");
	
	facepp::person persons;
	persons.create();

	facepp::group groups;
	groups.create();

	facepp::train trains;
	trains.identify();

	facepp::recognition recognitions;
	recognitions.identify();

	return 0;
}
