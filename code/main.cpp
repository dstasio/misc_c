// main.cpp

#include <windows.h>
#define DST_FILE_STATIC
#define DST_FILE_IMPLEMENTATION
#include "dst/dst_file.h"

#define DST_STRING_STATIC
#define DST_STRING_IMPLEMENTATION
#include "dst/dst_1_string.h"

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
    //u8 *file_data;
    //u64 file_size;
    //dst_read_entire_file("test.txt", &file_data, &file_size);

    //dst_String str = dstr_as_string(file_data, file_size);        // <---------
    //dstr_String str = {};
    //dstr_make_string(&str, 

    //dstr_replace(&str, "rep", "sub");                             // <---------

    //dstr_as_bytes(&str, &file_data, &file_size);                  // <---------
    //dst_write_entire_file("test.txt", file_data, file_size);      // <---------
    
    //u8 *file_data;
    //u64 file_size;
    //dst_read_entire_file("in.txt", &file_data, &file_size);

    //dstr_String str = {};
    //dstr_make_string(&str, file_data, file_size, DSTR_ASCII);

    //dst_free_file(file_data);

    float p1 = 0;
    float p2 = 0;
    float p3 = 0;
    float p4 = 0;
    float p5 = 0;
    char *n1 = "12.34.";
    char *n2 = "-43.";
    char *n3 = "++-32.1";
    char *n4 = ".124";
    char *n5 = "12..2";
    p1 = dstr8_parse_float(n1);
    p2 = dstr8_parse_float(n2);
    p3 = dstr8_parse_float(n3);
    p4 = dstr8_parse_float(n4);
    p5 = dstr8_parse_float(n5);

    return 0;
}
