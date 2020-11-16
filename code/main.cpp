// main.cpp
#include <windows.h>

#define output_string(s, ...)        {char Buffer[100];sprintf_s(Buffer, s, __VA_ARGS__);OutputDebugStringA(Buffer);}
#define throw_error_and_exit(e, ...) {output_string(" ------------------------------[ERROR] " ## e, __VA_ARGS__); getchar(); global_error = true;}
#define throw_error(e, ...)           output_string(" ------------------------------[ERROR] " ## e, __VA_ARGS__)
#define inform(i, ...)                output_string(" ------------------------------[INFO] " ## i, __VA_ARGS__)
#define warn(w, ...)                  output_string(" ------------------------------[WARNING] " ## w, __VA_ARGS__)

#define Assert(expr) if(!(expr)) {*(int *)0 = 0;}
#define byte_offset(base, offset) ((u8*)(base) + (offset))

#include "stdio.h"
#include "unzip.h"

struct Input_File
{
    char *path;
    u8   *data;
    u64   size;
    u64   write_time;  // @todo: this should be useless in release build
};

internal Input_File win32_read_file(char *Path)
{
    Input_File Result = {};
    HANDLE FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, 0,
                                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (FileHandle != INVALID_HANDLE_VALUE)
    {
        // TODO(dave): Currently only supports up to 4GB files
        u32 FileSize = GetFileSize(FileHandle, 0);
        DWORD BytesRead;

        // TODO(dave): Remove this allocation
        u8 *Buffer = (u8 *)VirtualAlloc(0, FileSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
        if(ReadFile(FileHandle, Buffer, FileSize, &BytesRead, 0))
        {
            Result.data = Buffer;
            Result.size = (u32)BytesRead;
            Result.path = Path;
//            Result.write_time = win32_get_last_write_time(Path);
        }
        else
        {
            throw_error("Unable to read file: %s\n", Path);
        }

        CloseHandle(FileHandle);
    }
    else
    {
        throw_error("Unable to open file: %s\n", Path);
        DWORD error = GetLastError();
        error = 0;
    }

    return(Result);
}

int main(int argc, char **args)
{
    Input_File zip_file = win32_read_file("test.zip");

    read_zip(zip_file.data, (u32) zip_file.size);

//    scanf_s("%n");
    system("pause");
    return 0;
}
