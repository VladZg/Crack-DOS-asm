#ifndef CRACK_UTILS_CPP
#define CRACK_UTILS_CPP

#include "../AppConfig.h"
#include <stdlib.h>
#include "../Include/CrackUtils.h"

int CrackProgramm(const char* inp_filename, const char* out_filename)
{
    assert(inp_filename != nullptr);
    assert(out_filename != nullptr);

    FILE* inp_file = fopen(inp_filename, "rb");
    assert(inp_file != nullptr);
    char* code = (char*) calloc(MAX_FILE_LEN, sizeof(char));
    assert(code != nullptr);
    int file_len = ReadFile(inp_file, &code);
    fclose(inp_file);

    code[0x0000095D] = 0x13;    // подмена адреса перехода

    FILE* out_file = fopen(out_filename, "wb");
    assert(out_file != nullptr);
    fwrite(code, sizeof(char), file_len, out_file);
    fclose(out_file);
    free(code);

    fprintf(stdout, "%s CRACKED!\n New file \"%s\" with cracked code created\n", inp_filename, out_filename);

    return 1;
}

int ReadFile(FILE* file, char** buf)
{
    assert(buf != nullptr);
    assert(*buf != nullptr);
    assert(file != nullptr);

    fseek(file, 0L, SEEK_END);
    int file_len = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return fread(*buf, sizeof(char), file_len, file);
}

#endif
