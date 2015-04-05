# facepp-cpp-sdk

![Face++ Inside](http://www.faceplusplus.com.cn/static/resources/facepp_inside.png)

## Introduction
facepp-cpp-sdk is [Face++](http://www.faceplusplus.com.cn/) SDK written in C++.

## Dependencies
**Recommended**
+ [Visual Studio 2013 Community](https://www.visualstudio.com/products/visual-studio-community-vs)
+ [C++ REST SDK](http://casablanca.codeplex.com/)
+ [OpenCV](http://opencv.org)

**Note**
+ C++ REST SDK and OpenCV will be automatically installed by NuGet package manager if you are using MS Visual Studio 2013 and above.
+ Only tested on MS Windows yet, but this SDK itself is designed to be cross-platform. So You can build [C++ REST SDK](http://casablanca.codeplex.com/) and [OpenCV](http://opencv.org/downloads.html) by yourself on other platfroms and integrate our SDK in your own projects.

## Roadmap

### APIs
- [x] detection
- [x] train
- [ ] recognition
- [ ] grouping
- [ ] person
- [ ] faceset
- [ ] group
- [ ] info

### Toolchain
- [ ] **cmake** support
- [ ] Accepted by official repos