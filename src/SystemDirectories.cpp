#include "SystemDirectories.h"

#include <windows.h>
#include <shlobj.h>

// TODO: factorize common parts of both functions into single function

std::string SystemDirectories::getLocalUserPath(std::string applicationName) {
	LPITEMIDLIST itemList;

	// Get a pointer to an item ID list that represents the path of a special folder
	HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &itemList);

	// Convert the item ID list's binary representation into a file system path
	wchar_t path[_MAX_PATH];
	BOOL f = SHGetPathFromIDList(itemList, (char*)path);

	// Free the Item ID list
	LPMALLOC shMalloc;
	hr = SHGetMalloc(&shMalloc);
	shMalloc->Free(itemList);
	shMalloc->Release();

	// TODO: convert LPWSTR path into std::string
	// TODO: create MMT subfolder if not existing
	// TODO: create applicationName subfolder if not existing

	// FIXME: dummy implementation
	return ".";
}

std::string SystemDirectories::getLocalPath(std::string applicationName) {
	LPITEMIDLIST itemList;

	// Get a pointer to an item ID list that represents the path of a special folder
	HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_COMMON_APPDATA, &itemList);

	// Convert the item ID list's binary representation into a file system path
	wchar_t path[_MAX_PATH];
	BOOL f = SHGetPathFromIDList(itemList, (char*)path);

	// Free the Item ID list
	LPMALLOC shMalloc;
	hr = SHGetMalloc(&shMalloc);
	shMalloc->Free(itemList);
	shMalloc->Release();

	// TODO: convert LPWSTR path into std::string
	// TODO: create MMT subfolder if not existing
	// TODO: create applicationName subfolder if not existing

	// FIXME: dummy implementation
	return ".";
}

