#include <iostream>
#include <string>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <cpprest\http_headers.h>
#include <cpprest\json.h>
#include <cpprest\http_listener.h>
#include <cpprest\uri.h>
#include <cpprest\asyncrt_utils.h>

using namespace std;
using namespace cv;
using namespace web;
using namespace utility;
using namespace http;
using namespace http::client;
