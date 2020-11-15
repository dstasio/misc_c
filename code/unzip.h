#if !defined(UNZIP_H)

#include "datatypes.h"

#pragma pack(push, 1)
struct ZIP_Header
{
    u32 signature; // must be 0x04034b50
    u16 version;
    u16 flags;
    u16 compression_method;
    u16 last_mod_time;
    u16 last_mod_date;
    u32 crc_32;
    u32 compressed_size;
    u32 uncompressed_size;
    u16 filename_length;
    u16 extra_field_length;

    u8 filename_start; // size: 'filename_length' bytes
    // @note: extra field starts after filename
};
#pragma pack(pop)

static void read_zip(void *file, u32 file_size)
{
    ZIP_Header *zip = (ZIP_Header *)file;
    u32 consumed_size = 0;
    while (consumed_size < file_size)
    {
        Assert(zip->signature == 0x04034b50);
        Assert(!(zip->flags & 4));

        u8 filename[100] = {};
        u8 *at = filename;
        u8 *c = &zip->filename_start;
        while ((c - &zip->filename_start) < zip->filename_length)
        {
            *(at++) = *(c++);
        }
        printf("Filename: %s\n", filename);

        do
        {
            zip = (ZIP_Header *)byte_offset(zip, 1);
            consumed_size += 1;
        } while ((consumed_size >= file_size) || (zip->signature != 0x04034b50));
    }
}

#define UNZIP_H
#endif
