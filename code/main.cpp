// main.cpp

#include <windows.h>
#define DST_FILE_STATIC
#define DST_FILE_IMPLEMENTATION
#include "dst/dst_file.h"

#include <stdint.h>
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

int main()
{
    u8 *file_data;
    u64 file_size;
    dst_read_entire_file("test.txt", &file_data, &file_size);

    dst_String str = dstr_as_string(file_data, file_size);        // <---------

    dstr_replace(&str, "rep", "sub");                             // <---------

    dstr_as_bytes(&str, &file_data, &file_size);                  // <---------
    dst_write_entire_file("test.txt", file_data, file_size);      // <---------

    return 0;
}
