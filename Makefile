.DEFAULT_GOAL := help

.PHONY: help envcheck products mk-list check-cuttlefish

help:
@echo "MyLinux platform build targets"
@echo "------------------------------"
@echo "make envcheck        Check build environment"
@echo "make products        List product definitions"
@echo "make mk-list         List all .mk files"
@echo "make check-cuttlefish Check Python syntax"

envcheck:
@echo "MyLinux environment"
@echo "Platform: $(CURDIR)"
@command -v python
@command -v go || true
@command -v make

products:
@grep -RhnE '^[[:space:]]*PRODUCT_NAME[[:space:]]*[:?+]?=' device --include='*.mk' || true

mk-list:
@find device -type f -name '*.mk' | sort

check-cuttlefish:
@python -m compileall -q device/google/cuttlefish
@echo "Cuttlefish Python syntax checks passed."
