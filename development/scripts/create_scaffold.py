from pathlib import Path

ROOT = Path.home() / "roms/mylinux-platform"

directories = """
bootable/boot/src
bootable/recovery/src
bootable/ramdisk/config
bootable/kernel-source
dalvik/vm/src
dalvik/vm/include
dalvik/lib
art/runtime/gc
art/runtime/jni
art/compiler/optimizing
art/libartbase/base
external/src
external/include
external/licenses
libcore/luni/src/main/java
libcore/ojluni/src/main/java
libcore/dalvik/src/main/java
libnativehelper/include/nativehelper
libnativehelper/src
sdk/api/current
sdk/platforms
sdk/tools
frameworks/base/core/java
frameworks/base/core/jni
frameworks/base/services/core
frameworks/base/native
frameworks/base/include
device/samsung/gto/kernel
device/samsung/gto/config
vendor/interfaces/include
vendor/interfaces/src
vendor/samsung/gto/config
tools/src
tools/scripts
tools/config
build/core
build/config
build/scripts
build/targets
packages/apps
packages/services
packages/modules
prebuilts/host
prebuilts/target
prebuilts/kernel
toolchain/clang
toolchain/gcc
toolchain/binutils
toolchain/config
android/init
android/bionic
android/permissions
android/security
android/include
""".split()

files = {
"bootable/README.md": "# Bootable\nBoot images, recovery, ramdisk and kernel integration.\n",
"bootable/boot/README.md": "# Boot image components\n",
"bootable/recovery/README.md": "# Recovery environment\n",
"bootable/ramdisk/README.md": "# Ramdisk sources and configuration\n",

"dalvik/README.md": "# Dalvik Runtime\nLegacy runtime research and compatibility.\n",
"dalvik/vm/README.md": "# Dalvik VM\n",
"dalvik/config/runtime.conf": "DALVIK_RUNTIME_ENABLED=false\n",

"art/README.md": "# Android Runtime\nRuntime, compiler and garbage collection.\n",
"art/runtime/README.md": "# ART runtime\n",
"art/compiler/README.md": "# ART compiler\n",
"art/config/runtime.conf": "ART_RUNTIME_ENABLED=false\n",

"external/README.md": "# External dependencies\nThird-party source and license tracking.\n",
"external/manifest.txt": "# name | version | license | source\n",

"libcore/README.md": "# Java Core Libraries\n",
"libcore/config/library.conf": "LIBCORE_ENABLED=false\n",

"libnativehelper/README.md": "# Native Helper\nJNI and native runtime helpers.\n",
"libnativehelper/JNIHelp.cpp": """/*
 * MyLinux JNI helper prototype.
 * JNI functionality is not implemented.
 */
namespace mylinux {
void native_helper_placeholder(void) {}
}
""",
"libnativehelper/config/nativehelper.conf": "NATIVEHELPER_ENABLED=false\n",

"sdk/README.md": "# MyLinux SDK\nAPI definitions and development tools.\n",
"sdk/config/sdk.conf": "SDK_API_LEVEL=1\nSDK_STATUS=prototype\n",

"frameworks/README.md": "# Android Frameworks\nFramework APIs, services and native interfaces.\n",
"frameworks/base/README.md": "# Framework base\n",
"frameworks/base/core/README.md": "# Framework core APIs\n",
"frameworks/base/services/README.md": "# Framework services\n",
"frameworks/base/native/README.md": "# Native framework interfaces\n",
"frameworks/config/framework.conf": "FRAMEWORK_STATUS=prototype\n",

"device/README.md": "# Device Configuration\nPer-device board and product configuration.\n",
"device/samsung/gto/README.md": """# Samsung GTO
Model: SM-T295
Codename: gto
SoC: Qualcomm MSM8937
Architecture: arm64
""",
"device/samsung/gto/BoardConfig.mk": """# MyLinux GTO prototype
TARGET_ARCH := arm64
TARGET_DEVICE := gto
TARGET_SOC := msm8937
""",
"device/samsung/gto/device.conf": """DEVICE_MODEL=SM-T295
DEVICE_CODENAME=gto
DEVICE_ARCH=arm64
DEVICE_SOC=MSM8937
""",
"device/config/device-list.conf": "samsung/gto\n",

"vendor/README.md": "# Vendor Components\nVendor hardware integration and configuration.\n",
"vendor/samsung/gto/vendor.conf": "VENDOR_DEVICE=gto\nVENDOR_SOC=msm8937\n",

"tools/README.md": "# MyLinux Development Tools\nHost-side utilities and source generators.\n",
"tools/src/platform-info.c": """#include <stdio.h>

int main(void)
{
    puts("MyLinux platform development environment");
    puts("Status: source scaffold");
    return 0;
}
""",
"tools/config/tools.conf": "TOOLS_VERSION=0.1.0\n",

"out/README.md": "# Build Output\nGenerated artifacts only. Not authoritative source.\n",
"out/.gitignore": "*\n!.gitignore\n!README.md\n",

"build/README.md": "# Build System\nBuild orchestration and component definitions.\n",
"build/config/platform.conf": """PLATFORM_NAME=MyLinux
PLATFORM_VERSION=0.1.0
PLATFORM_STATUS=scaffold
DEFAULT_ARCH=arm64
""",
"build/targets/targets.conf": """# Planned targets
# host-tools
# platform-components
# device-gto
""",

"packages/README.md": "# Packages\nApplications, services and platform modules.\n",
"packages/config/packages.conf": "PACKAGE_SYSTEM_STATUS=prototype\n",

"prebuilts/README.md": "# Prebuilt Artifacts\nOnly verified host tools and target binaries belong here.\n",
"prebuilts/manifest.txt": "# name | version | architecture | checksum\n",

"toolchain/README.md": "# Toolchain\nCompiler, linker and assembler configuration.\n",
"toolchain/config/toolchain.conf": """TARGET_ARCH=arm64
COMPILER=clang
TOOLCHAIN_STATUS=prototype
""",

"android/README.md": "# Android Compatibility Layer\nAndroid-specific compatibility interfaces.\n",
"android/config/android.conf": """ANDROID_COMPATIBILITY=true
ANDROID_API_BASE=30
IMPLEMENTATION_STATUS=prototype
""",
}

created_dirs = 0
created_files = 0
preserved_files = 0

for name in directories:
    path = ROOT / name
    if not path.exists():
        path.mkdir(parents=True, exist_ok=True)
        created_dirs += 1

for name, content in files.items():
    path = ROOT / name
    path.parent.mkdir(parents=True, exist_ok=True)

    if path.exists() or path.is_symlink():
        preserved_files += 1
        print("KEEP   ", name)
        continue

    path.write_text(content, encoding="utf-8")
    created_files += 1
    print("CREATED", name)

print("\n===== SCAFFOLD COMPLETE =====")
print("New directories:", created_dirs)
print("New files:", created_files)
print("Existing files preserved:", preserved_files)
print("Project:", ROOT)
print("No kernel build or boot attempted.")
