MyLinux Android Framework Build

Framework source:
  core/java/

System-server source:
  services/core/java/

Expected output:
  prebuilts/java/jars/framework.jar
  prebuilts/java/jars/services.jar

Build dependencies:
  javac - Java compilation
  jar   - Java archive packaging
  d8    - DEX conversion

Important:
A complete Android framework requires generated AIDL sources,
framework resources, annotation processors, and many dependencies.

A simple javac invocation is not a replacement for the AOSP Soong
build. Do not package incomplete classes as production framework.jar
or services.jar.
