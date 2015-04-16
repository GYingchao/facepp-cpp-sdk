// Face++ SDK for C++
// The MIT License (MIT)
// Copyright (c) 2015 clarkzjw@gmail.com
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#ifndef LIB_FACEPP_H
#	define LIB_FACEPP_H

#include "libfacepp_core.h"

#include "detection\detection.h"
#include "faceset\faceset.h"
#include "group\group.h"
#include "info\info.h"
#include "person\person.h"
#include "recognition\recognition.h"
#include "train\train.h"

class facepp
{
private:
	set<string> APIs;
	Mat img;

	void initAPIs();
public:
	double __version__ = 1.0;

	facepp();
	facepp(string path);

	bool cv2Resize();

	void connect();
};

#endif
