#ifndef SYSTEM_DIRECTORIES_H
#define SYSTEM_DIRECTORIES_H

#include <string>

class SystemDirectories {
public:
	// Retrieves the path of a local directory of the current user that
	// can be used to save&load user specific application data.
	// This method will create a directory named "userHomeDirectory/applicationName"
	// if it does not yet exist, where userHomeDirectory depends on the current
	// system.
	// Note: getLocalUserPath(...) might be identical to getLocalPath(...) on a system
	// without home directories. The calling application must be able to deal with
	// this special case.
	static std::string getLocalUserPath(std::string applicationName);

	// Retrieves the path of a local directory that
	// can be used to save&load system wide application data.
	// This method will create a directory named "sharedDirectory/applicationName"
	// if it does not yet exist, where sharedDirectory depends on the current
	// system.
	static std::string getLocalPath(std::string applicationName);
};

#endif
