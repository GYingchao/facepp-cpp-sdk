#include "libfacepp.h"

#include <iostream>
using namespace std;

int main()
{
	facepp face("test.jpg");

	person persons;
	persons.query.append_path(U("/person/create"));
	persons.create();

	group groups;
	groups.create();

	train trains;
	trains.identify();

	recognition recognitions;
	recognitions.identify();

	return 0;
}
