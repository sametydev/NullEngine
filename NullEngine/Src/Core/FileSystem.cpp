#include <PCH.h>
#include <Core/FileSystem.h>
#include <filesystem>

std::string FileSystem::GetNameFromPath(std::string path)
{
	std::string name = std::filesystem::path(path).filename().u8string();
	return name;
}

bool FileSystem::IsExistsFile(const std::string& file)
{
	return std::filesystem::exists(file);
}
