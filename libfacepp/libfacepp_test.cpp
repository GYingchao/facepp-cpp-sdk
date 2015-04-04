#include "libfacepp.h"

int main()
{
	facepp face("test.jpg");
	
	detection detections;
	detections.detect(true);

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
