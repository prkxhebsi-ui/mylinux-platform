#ifndef MYLINUX_INIT_H
#define MYLINUX_INIT_H

#include <string>
#include <vector>
#include <map>
#include <set>

namespace mylinux {
namespace init {

constexpr const char* kVersion = "MyLinux init 2.0";
constexpr const char* kDefaultConfig =
    "/system/etc/init/hw/init.rc";

struct InitOptions {
    bool check_config = false;
    bool show_version = false;
    const char* config_path = kDefaultConfig;
};

struct Command {
    std::vector<std::string> args;
};

struct Action {
    std::string trigger;
    std::vector<Command> commands;
};

struct Service {
    std::string name;
    std::string executable;
    std::vector<std::string> arguments;
    bool disabled = false;
    bool oneshot = false;
    bool started = false;
};

struct InitConfig {
    std::vector<Action> actions;
    std::vector<Service> services;
    std::set<std::string> imported_files;
};

class PropertyService {
public:
    static bool set(const std::string& name,
                    const std::string& value);
    static std::string get(const std::string& name);
    static bool contains(const std::string& name);
};

class ServiceManager {
public:
    bool add(const Service& service);
    Service* find(const std::string& name);
    const std::vector<Service>& all() const;

private:
    std::vector<Service> services_;
};

class Parser {
public:
    explicit Parser(InitConfig& config);
    bool parseFile(const std::string& path);

private:
    InitConfig& config_;
    std::vector<std::string> parseArguments(const std::string& line);
    bool importPath(const std::string& path);
};

class ActionRunner {
public:
    explicit ActionRunner(InitConfig& config);
    bool run(const std::string& trigger);

private:
    InitConfig& config_;
};

bool parse_arguments(int argc, char** argv, InitOptions& options);
bool initialize(const InitOptions& options);

void print_version();
void print_usage(const char* program);

std::string expandProperties(const std::string& input);
bool executeBuiltin(const Command& command, InitConfig& config);
bool executeImport(const std::string& path, InitConfig& config);

bool initializeUeventd();
void logMessage(const char* level, const std::string& message);

} // namespace init
} // namespace mylinux

#endif
