#include "libfacepp.h"

int main()
{
	detection detections;
	detections.Detect("http://cn.faceplusplus.com/static/resources/python_demo/1.jpg");
	wstring face_id = detections.result.at(U("face"))[0].at(U("face_id")).as_string();

	person persons;
	persons.query.append_query(U("face_id"), face_id.c_str());
	persons.query.append_query(U("person_name"), "TestName2");
	wcout << persons.query.to_string() << endl;
	persons.Create();
	wstring person_id = persons.result.at(U("person_id")).as_string();
	wcout << person_id << endl;

	group groups;
	groups.query.append_query(U("group_name"), "TestGroup2");
	groups.Create();
	wstring group_name = groups.result.at(U("group_name")).as_string();

	train trains;
	trains.query.append_query(U("group_name"), group_name.c_str());
	trains.Identify();

	recognition recognitions;
	recognitions.Identify();

	return 0;
}
