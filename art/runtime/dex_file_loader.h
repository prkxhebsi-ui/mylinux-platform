#ifndef ART_RUNTIME_DEX_FILE_LOADER_H_
#define ART_RUNTIME_DEX_FILE_LOADER_H_

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace art {

struct DexFileInfo {
  uint32_t checksum = 0;
  uint32_t file_size = 0;
  uint32_t header_size = 0;
  uint32_t endian_tag = 0;
};

class DexFileLoader {
 public:
  bool InspectHeader(const uint8_t* data, size_t size, DexFileInfo* info);
  const std::string& GetError() const;

 private:
  std::string error_;
};

}  // namespace art

#endif  // ART_RUNTIME_DEX_FILE_LOADER_H_
