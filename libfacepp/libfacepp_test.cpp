#include "libfacepp.h"

int main()
{
	detection detections;
	detections.Detect("http://cn.faceplusplus.com/static/resources/python_demo/1.jpg");

	person persons;
	persons.Create();

	group groups;
	groups.Create();

	train trains;
	trains.Identify();

	recognition recognitions;
	recognitions.Identify();

	return 0;
}
