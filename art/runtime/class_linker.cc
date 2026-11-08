#include "runtime/class_linker.h"

namespace art {

bool ClassLinker::Initialize() {
  if (initialized_) {
    return true;
  }

  initialization_error_ =
      "ClassLinker requires the ART runtime and managed class metadata";
  return false;
}

bool ClassLinker::IsInitialized() const {
  return initialized_;
}

const std::string& ClassLinker::GetInitializationError() const {
  return initialization_error_;
}

}  // namespace art
