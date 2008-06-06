#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "06";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2008";
	static const double UBUNTU_VERSION_STYLE = 8.06;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 23;
	static const long REVISION = 125;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 183;
	#define RC_FILEVERSION 1,0,23,125
	#define RC_FILEVERSION_STRING "1, 0, 23, 125\0"
	static const char FULLVERSION_STRING[] = "1.0.23.125";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //VERSION_h
