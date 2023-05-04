#include <PCH.h>
#include <Core/FileSystem.h>

std::string FileSystem::GetNameFromPath(std::string path)
{
	std::string name = std::filesystem::path(path).filename().u8string();
	return name;
}
