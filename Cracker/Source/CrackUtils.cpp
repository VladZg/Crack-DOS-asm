#ifndef CRACK_UTILS_CPP
#define CRACK_UTILS_CPP

#include "../AppConfig.h"
#include <stdlib.h>
#include "../Include/CrackUtils.h"

int CrackProgramm(const char* inp_filename, const char* out_filename, int mode)
{
    assert(inp_filename != nullptr);
    assert(out_filename != nullptr);

    FILE* inp_file = fopen(inp_filename, "rb");
    assert(inp_file != nullptr);
    char* code = (char*) calloc(MAX_FILE_LEN, sizeof(char));
    assert(code != nullptr);
    int file_len = ReadFile(inp_file, &code);
    fclose(inp_file);

    switch (mode)
    {
                                        // basic crack 1:
                                        // - найти пароль в коде программы: "ak47"
                                        // - ввести пароль с таким же хешом (311): "DEDj"

        case 0xA:                         
            code[0x0000095D] = 0x01;    // light crack 1: подмена адреса перехода на начало функции, печатающей "access granted" в условном джампе
            break;

        case 0xB:
            code[0x00000953] = 0xF3;    // hard crack 1: подмена адреса строки для функции, считающей хеш так, чтобы она дважды считала хэш одной и той же строки
            break;

                                        // basic crack 2:
                                        // - найти пароль в коде программы: "huysosi"
                                        // - найден баг: при введении 7 символов + Enter программа даёт доступ

        case 0xC:                       // light crack 2: 
            // code[0x00000906] = 0x07;
            break;

        case 0xD:                       //
            break;
    }

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
