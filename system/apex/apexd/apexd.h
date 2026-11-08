#ifndef MYLINUX_APEXD_H
#define MYLINUX_APEXD_H

#include <string>

class Apexd {
public:
    Apexd();

    int Run();
    int ScanPackages();

private:
    int ScanDirectory(const std::string& path);

    bool IsApexFile(const std::string& name) const;

    int package_count_;
};

#endif
