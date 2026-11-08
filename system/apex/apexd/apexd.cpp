#include "apexd.h"
#include "apex_constants.h"

#include <dirent.h>
#include <sys/stat.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>

Apexd::Apexd()
    : package_count_(0) {
}

bool Apexd::IsApexFile(const std::string& name) const {
    const std::string apex = APEX_FILE_EXTENSION;
    const std::string compressed = APEX_COMPRESSED_EXTENSION;

    if (name.size() >= apex.size() &&
        name.compare(name.size() - apex.size(),
                      apex.size(), apex) == 0) {
        return true;
    }

    if (name.size() >= compressed.size() &&
        name.compare(name.size() - compressed.size(),
                      compressed.size(), compressed) == 0) {
        return true;
    }

    return false;
}

int Apexd::ScanDirectory(const std::string& path) {
    DIR* directory = opendir(path.c_str());

    if (directory == NULL) {
        std::fprintf(stderr,
                     "apexd: cannot open %s: %s\n",
                     path.c_str(), std::strerror(errno));
        return -1;
    }

    std::printf("apexd: scanning %s\n", path.c_str());

    struct dirent* entry;

    while ((entry = readdir(directory)) != NULL) {
        const std::string name(entry->d_name);

        if (name == "." || name == "..") {
            continue;
        }

        if (!IsApexFile(name)) {
            continue;
        }

        const std::string full_path = path + "/" + name;

        struct stat file_info;

        if (lstat(full_path.c_str(), &file_info) != 0) {
            std::fprintf(stderr,
                         "apexd: cannot inspect %s\n",
                         full_path.c_str());
            continue;
        }

        if (!S_ISREG(file_info.st_mode)) {
            continue;
        }

        std::printf("  package: %s\n", full_path.c_str());
        package_count_++;
    }

    closedir(directory);
    return 0;
}

int Apexd::ScanPackages() {
    package_count_ = 0;

    std::printf("===== MYLINUX APEX SCANNER =====\n");

    ScanDirectory(APEX_SYSTEM_DIR);
    ScanDirectory(APEX_DATA_DIR);

    std::printf("\n");
    std::printf("Packages discovered: %d\n", package_count_);

    return 0;
}

int Apexd::Run() {
    std::printf("MyLinux APEX daemon %s\n", APEX_VERSION);
    std::printf("Daemon initialization started.\n");

    return ScanPackages();
}
