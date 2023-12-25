#include <vector>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

class BaseSubsystem {
public:
    virtual ~BaseSubsystem() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
};

class SubsystemManager {
private:
    static std::vector<std::unique_ptr<BaseSubsystem>> subsystems;

    static std::unordered_map<const char*,BaseSubsystem*> subsystemMap;

    SubsystemManager() = default;

public:
    SubsystemManager(const SubsystemManager&) = delete;
    SubsystemManager& operator=(const SubsystemManager&) = delete;

    template <typename T, typename... Args>
    //args for class initialization
    static T* Create(Args... args) {
        T* subsystem = new T(std::forward<Args>(args)...);

        subsystems.emplace_back(subsystem);
        subsystemMap[typeid(T).name()] = subsystem;

        subsystem->Initialize();

        return subsystem;
    }

    template <typename T>
    static T* Get() {
        auto it = subsystemMap.find(typeid(T).name());
        if (it != subsystemMap.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    static void Update() {
        for (auto& subsystem : subsystems) {
            subsystem->Update();
        }
    }

    static void Shutdown() {
        for (auto& subsystem : subsystems) {
            subsystem->Shutdown();
        }
        subsystems.clear();
        subsystemMap.clear();
    }
};
