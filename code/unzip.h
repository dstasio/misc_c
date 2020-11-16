#if !defined(UNZIP_H)

#include "datatypes.h"
#define end_of(x) byte_offset(((x)), sizeof(*x))

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
    // u8 filename_start; // size: 'filename_length' bytes
    // @note: extra field starts after filename
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ZIP_Central_File_Header
{
    u32 signature; // 0x02014b50
    u16 version_made_by;
    u16 version_needed;
    u16 flags;
    u16 compression_method;
    u16 last_mod_time;
    u16 last_mod_date;
    u32 crc_32;
    u32 compressed_size;
    u32 uncompressed_size;
    u16 filename_length;
    u16 extra_field_length;
    u16 file_comment_length;
    u16 disk_number_start;
    u16 internal_file_attributes;
    u32 external_file_attributes;
    u32 local_header_relative_offset;
    // file name (variable size);
    // extra field (variable size);
    // file comment (variable size);
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ZIP_End_Of_Central_Directory
{
    u32 signature; // 0x06054b50
    u16 current_disk_number;
    u16 central_dir_disk_number;
    u16 n_entries_central_dir_current_disk;
    u16 n_entries_central_dir;
    u32 central_dir_size;
    u32 central_dir_offset;
    u16 comment_length;
};
#pragma pack(pop)

static void read_zip(void *file, u32 file_size)
{
    ZIP_End_Of_Central_Directory *zip_end = (ZIP_End_Of_Central_Directory *)byte_offset(file, file_size - sizeof(ZIP_End_Of_Central_Directory));
    Assert(!zip_end->comment_length);
    Assert(zip_end->signature == 0x06054b50); // @todo: some encoders might add a comment at the end (7zip doesn't)

    ZIP_Central_File_Header *file_header = (ZIP_Central_File_Header *)byte_offset(file, zip_end->central_dir_offset);
    while (file_header->signature == 0x02014b50)
    {
        u8 *filename_start = (u8 *)end_of(file_header);
        u8 filename[100] = {};
        u8 *at = filename;
        u8 *c = filename_start;
        while ((c - filename_start) < file_header->filename_length)
        {
            *(at++) = *(c++);
        }
        printf("Filename: %s\n", filename);

        file_header = (ZIP_Central_File_Header *)byte_offset(file_header, file_header->filename_length + file_header->extra_field_length + file_header->file_comment_length);
        file_header += 1;
    }
}

#if 0
static void read_zip(void *file, u32 file_size)
{
    ZIP_Header *zip = (ZIP_Header *)file;
    u32 consumed_size = 0;

    ZIP_Header *prev_zip = 0;
    u32 last_consumed = 0;
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

        prev_zip = zip;
        last_consumed = consumed_size;
        do
        {
            zip = (ZIP_Header *)byte_offset(zip, 1);
            consumed_size += 1;
        } while ((consumed_size >= file_size) || (zip->signature != 0x04034b50));
    }
}
#endif

#define UNZIP_H
#endif
