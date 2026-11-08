#ifndef ART_RUNTIME_CLASS_LINKER_H_
#define ART_RUNTIME_CLASS_LINKER_H_

#include <string>

namespace art {

class ClassLinker {
 public:
  ClassLinker() = default;
  ClassLinker(const ClassLinker&) = delete;
  ClassLinker& operator=(const ClassLinker&) = delete;
  ~ClassLinker() = default;

  bool Initialize();
  bool IsInitialized() const;
  const std::string& GetInitializationError() const;

 private:
  bool initialized_ = false;
  std::string initialization_error_;
};

}  // namespace art

#endif  // ART_RUNTIME_CLASS_LINKER_H_
