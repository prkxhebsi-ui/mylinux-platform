#include "runtime/dex_file_loader.h"

#include <cstring>
#include <limits>

namespace art {
namespace {

uint32_t ReadU32LE(const uint8_t* p) {
  return static_cast<uint32_t>(p[0]) |
         (static_cast<uint32_t>(p[1]) << 8) |
         (static_cast<uint32_t>(p[2]) << 16) |
         (static_cast<uint32_t>(p[3]) << 24);
}

}  // namespace

bool DexFileLoader::InspectHeader(
    const uint8_t* data, size_t size, DexFileInfo* info) {
  error_.clear();

  if (data == nullptr || info == nullptr) {
    error_ = "null input";
    return false;
  }

  constexpr size_t kDexHeaderSize = 112;
  if (size < kDexHeaderSize) {
    error_ = "truncated DEX header";
    return false;
  }

  if (std::memcmp(data, "dex\n", 4) != 0 || data[7] != '\0') {
    error_ = "invalid DEX magic";
    return false;
  }

  const uint32_t file_size = ReadU32LE(data + 32);
  const uint32_t header_size = ReadU32LE(data + 36);
  const uint32_t endian_tag = ReadU32LE(data + 40);

  if (file_size < kDexHeaderSize || file_size > size) {
    error_ = "invalid DEX file size";
    return false;
  }

  if (header_size != kDexHeaderSize) {
    error_ = "unsupported DEX header size";
    return false;
  }

  if (endian_tag != 0x12345678U) {
    error_ = "unsupported DEX byte order";
    return false;
  }

  info->checksum = ReadU32LE(data + 8);
  info->file_size = file_size;
  info->header_size = header_size;
  info->endian_tag = endian_tag;
  return true;
}

const std::string& DexFileLoader::GetError() const {
  return error_;
}

}  // namespace art
