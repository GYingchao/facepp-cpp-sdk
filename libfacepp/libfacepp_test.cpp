#include "libfacepp.h"

int main()
{
	facepp face("test.jpg");
	
	person persons;
	persons.create();

	group groups;
	groups.create();

	train trains;
	trains.identify();

	recognition recognitions;
	recognitions.identify();

	return 0;
}
