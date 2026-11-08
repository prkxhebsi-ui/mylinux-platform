# Reusable directory checks for MyLinux Make targets.

MYLINUX_REQUIRED_BUILD_DIRS := \
    build/make/core \
    build/make/target \
    build/make/tools \
    build/make/mylinux

.PHONY: mylinux-check-directories

mylinux-check-directories:
@set -e; \
for directory in $(MYLINUX_REQUIRED_BUILD_DIRS); do \
    test -d "$(MYLINUX_PLATFORM_ROOT)/$$directory" || { \
        echo "Missing directory: $$directory"; \
        exit 1; \
    }; \
done
@echo 'Required MyLinux build directories exist.'
