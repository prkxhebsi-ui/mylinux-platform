#include "DexFormat.h"
#include "DexError.h"

const char *DexErrorString(DexError error) {
    switch (error) {
        case DEX_OK: return "Success";
        case DEX_ERROR_ARGUMENT: return "Invalid argument";
        case DEX_ERROR_OPEN: return "Cannot open DEX file";
        case DEX_ERROR_READ: return "Cannot read DEX file";
        case DEX_ERROR_MEMORY: return "Memory allocation failed";
        case DEX_ERROR_MAGIC: return "Invalid DEX magic";
        case DEX_ERROR_HEADER: return "Invalid DEX header";
        case DEX_ERROR_SIZE: return "Invalid DEX file size";
        case DEX_ERROR_ENDIAN: return "Unsupported endian format";
        case DEX_ERROR_TABLE: return "Invalid DEX table";
        case DEX_ERROR_INDEX: return "DEX index out of range";
        case DEX_ERROR_STRING: return "Invalid DEX string";
        default: return "Unknown DEX error";
    }
}
