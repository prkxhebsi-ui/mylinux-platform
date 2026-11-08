#define _FILE_OFFSET_BITS 64

#include "vold_fs.h"

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

static int read_exact_at(int fd, void *buffer, size_t size, off_t offset)
{
    unsigned char *out = buffer;
    size_t done = 0;

    while (done < size) {
        ssize_t n = pread(fd, out + done, size - done,
                          offset + (off_t)done);

        if (n < 0)
            return -1;

        if (n == 0)
            return -1;

        done += (size_t)n;
    }

    return 0;
}

static uint16_t read_le16(const unsigned char *p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static uint32_t read_le32(const unsigned char *p)
{
    return (uint32_t)p[0]
        | ((uint32_t)p[1] << 8)
        | ((uint32_t)p[2] << 16)
        | ((uint32_t)p[3] << 24);
}

static int has_fat_signature(int fd)
{
    unsigned char boot[512];

    if (read_exact_at(fd, boot, sizeof(boot), 0) != 0)
        return 0;

    if (boot[510] != 0x55 || boot[511] != 0xAA)
        return 0;

    uint16_t sector_size = read_le16(&boot[11]);

    if (sector_size != 512 && sector_size != 1024
        && sector_size != 2048 && sector_size != 4096)
        return 0;

    /*
     * This is a conservative FAT boot-sector heuristic.
     * A signature alone does not prove a volume is FAT.
     */
    if (boot[54] == 'F' && boot[55] == 'A'
        && boot[56] == 'T')
        return 1;

    return 0;
}

enum vold_fs_type vold_fs_detect_fd(int fd)
{
    unsigned char magic[4];

    /*
     * Ext4 superblock magic is 0xEF53 at byte offset 0x438.
     */
    if (read_exact_at(fd, magic, 2, 0x438) == 0) {
        if (read_le16(magic) == 0xEF53)
            return VOLD_FS_EXT4;
    }

    /*
     * F2FS magic is 0xF2F52010 at the beginning of
     * its superblock, normally located at byte offset 1024.
     */
    if (read_exact_at(fd, magic, sizeof(magic), 1024) == 0) {
        if (read_le32(magic) == 0xF2F52010)
            return VOLD_FS_F2FS;
    }

    if (has_fat_signature(fd))
        return VOLD_FS_VFAT;

    return VOLD_FS_UNKNOWN;
}

const char *vold_fs_name(enum vold_fs_type type)
{
    switch (type) {
    case VOLD_FS_EXT4:
        return "ext4";
    case VOLD_FS_F2FS:
        return "f2fs";
    case VOLD_FS_VFAT:
        return "vfat";
    case VOLD_FS_UNKNOWN:
    default:
        return "unknown";
    }
}
