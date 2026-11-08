# MyLinux Go target configuration

GOOS ?= android
GOARCH ?= arm64

GOHOSTOS ?= linux
GOHOSTARCH ?= amd64

CGO_ENABLED ?= 0

GO_TARGET := $(GOOS)/$(GOARCH)
GO_HOST := $(GOHOSTOS)/$(GOHOSTARCH)
