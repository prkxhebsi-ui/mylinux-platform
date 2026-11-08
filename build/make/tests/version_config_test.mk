include build/make/core/version_defaults.mk

.PHONY: version-config-test

version-config-test:
@test -n "$(PLATFORM_VERSION)"
@test -n "$(PLATFORM_SDK_VERSION)"
@test -n "$(BUILD_ID)"
@echo "PLATFORM_VERSION=$(PLATFORM_VERSION)"
@echo "PLATFORM_VERSION_CODENAME=$(PLATFORM_VERSION_CODENAME)"
@echo "PLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)"
@echo "BUILD_ID=$(BUILD_ID)"
@echo "Version configuration: PASS"
