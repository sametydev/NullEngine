#include <PCH.h>
#include <Core/FileSystem.h>
#include <filesystem>
#include <sstream>


std::string FileSystem::GetNameFromPath(std::string path)
{
	std::string name = std::filesystem::path(path).filename().u8string();
	return name;
}

bool FileSystem::IsExistsFile(const std::string& file)
{
	return std::filesystem::exists(file);
}

const char* FileSystem::ReadAllLinesFromFile(const char* path)
{
    if (!FileSystem::IsExistsFile(path)) LOG_ERROR("File is not exists \n%s", path);

    FILE* f;
    struct stat fs;
    char* buf;

    stat(path, &fs);
    buf = (char*)malloc(fs.st_size);

    fopen_s(&f,path, "rb");
    fread(buf, fs.st_size, 1, f);
    fclose(f);
    
    return buf;
}
