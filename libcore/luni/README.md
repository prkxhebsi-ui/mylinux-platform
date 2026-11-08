MyLinux libcore/luni
====================

Purpose:
Android-specific Java core-library implementations.

Source:
  src/main/java/

Resources:
  src/main/resources/

Tests:
  src/test/java/
  src/test/resources/

Build output:
  out/java/luni/
  out/dex/luni/

Final artifacts:
  prebuilts/java/jars/
  prebuilts/java/dex/

This module is intended to contain genuine Android-compatible
implementations, not invented replacements for java.* APIs.

A complete Luni library requires compatible OpenJDK-derived
classes, Android dependencies, generated sources, and build rules.
