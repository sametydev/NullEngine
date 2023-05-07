#pragma once
#include <string>
#include <iostream>

class FileSystem
{
public:
	static std::string GetNameFromPath(std::string path);
	static bool		   IsExistsFile(const std::string& file);
};

