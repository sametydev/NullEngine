#include <PCH.h>
#include <Core/FileSystem.h>
#include <filesystem>
#include <sstream>
#include <streambuf>
#include <fstream>



std::string FileSystem::GetNameFromPath(std::string path)
{
	std::string name = std::filesystem::path(path).filename().u8string();
	return name;
}

bool FileSystem::IsExistsFile(const std::string& file)
{
	return std::filesystem::exists(file);
}

std::string FileSystem::ReadAllLinesFromFile(std::string path)
{
    if (!FileSystem::IsExistsFile(path)) LOG_ERROR("File is not exists \n%s", path);

    std::ifstream t(path);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    
    return str;
}

std::string FileSystem::GetExtension(std::string path)
{
    return (path.substr(path.find_last_of(".") + 1));
}
