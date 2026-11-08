# MyLinux Make build entry point.
# This is a standalone starter, not the upstream AOSP Makefile.

.DEFAULT_GOAL := help

.PHONY: help check-tree

help:
@printf '%s\n' \
  'MyLinux Make build infrastructure' \
  'Targets:' \
  '  help       Show this help' \
  '  check-tree Check required build directories'

check-tree:
@test -d core
@test -d target
@test -d tools
@test -d mylinux
@printf '%s\n' 'MyLinux Make directory checks passed.'
