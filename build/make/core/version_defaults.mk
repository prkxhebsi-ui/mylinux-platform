# Default Android platform version values.
# Override these values through the product/build configuration as appropriate.

ifndef PLATFORM_VERSION
PLATFORM_VERSION := 11
endif

ifndef PLATFORM_VERSION_CODENAME
PLATFORM_VERSION_CODENAME := REL
endif

ifndef PLATFORM_SDK_VERSION
PLATFORM_SDK_VERSION := 30
endif

ifndef PLATFORM_PREVIEW_SDK_VERSION
PLATFORM_PREVIEW_SDK_VERSION := 0
endif

ifndef PLATFORM_VERSION_ALL_CODENAMES
PLATFORM_VERSION_ALL_CODENAMES := $(PLATFORM_VERSION_CODENAME)
endif

ifndef PLATFORM_SECURITY_PATCH
PLATFORM_SECURITY_PATCH := 1970-01-01
endif

ifndef PLATFORM_BASE_OS
PLATFORM_BASE_OS :=
endif

ifndef PLATFORM_MIN_SUPPORTED_TARGET_SDK_VERSION
PLATFORM_MIN_SUPPORTED_TARGET_SDK_VERSION := 1
endif

ifndef DEFAULT_APP_TARGET_SDK
DEFAULT_APP_TARGET_SDK := $(PLATFORM_SDK_VERSION)
endif

ifndef BUILD_ID
BUILD_ID := RQ3A
endif

ifndef BUILD_NUMBER
BUILD_NUMBER := $(shell date +%Y%m%d%H%M%S)
endif

ifndef PLATFORM_BUILD_TYPE
PLATFORM_BUILD_TYPE := userdebug
endif

# Basic version sanity checks.
ifeq ($(strip $(PLATFORM_VERSION)),)
$(error PLATFORM_VERSION must not be empty)
endif

ifeq ($(strip $(PLATFORM_SDK_VERSION)),)
$(error PLATFORM_SDK_VERSION must not be empty)
endif

ifeq ($(strip $(BUILD_ID)),)
$(error BUILD_ID must not be empty)
endif
