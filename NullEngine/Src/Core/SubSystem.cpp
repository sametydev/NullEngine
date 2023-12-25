#include "PCH.h"
#include "SubSystem.h"

// Initialize static members
std::vector<std::unique_ptr<BaseSubsystem>> SubsystemManager::subsystems;
std::unordered_map<const char*, BaseSubsystem*> SubsystemManager::subsystemMap;