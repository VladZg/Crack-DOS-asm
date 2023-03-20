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

    PatchCode(code, mode);

    FILE* out_file = fopen(out_filename, "wb");
    assert(out_file != nullptr);
    fwrite(code, sizeof(char), file_len, out_file);
    fclose(out_file);
    free(code);

    fprintf(stdout, "%s CRACKED!\n New file \"%s\" with cracked code created\n", inp_filename, out_filename);

    return 1;
}

int CheckFileHash(const char* filename)
{
    assert(filename != nullptr);

    FILE* file = fopen(filename, "rb");
    assert(file != nullptr);
    char* code = (char*) calloc(MAX_FILE_LEN, sizeof(char));
    assert(code != nullptr);
    int file_len = ReadFile(file, &code);
    fclose(file);

    int file_hash = 0;

    for (int i = 0; i < file_len; i++)
        file_hash += int(code[i]);

    // printf("hash: %d\n", file_hash);

    return file_hash;
}

int PatchCode(char* code, int mode)
{
    assert(code != nullptr);

    switch (mode)
    {                                   // basic crack 1:
                                        // - найти пароль в коде программы: "ak47"
                                        // - ввести пароль с таким же хешом (137h|311d): "DEDj"

        case 0xA:
            code[0x0000095D] = 0x01;    // light crack 1: подмена адреса перехода на начало функции, печатающей "access granted" в условном джампе
            break;

        case 0xB:
            code[0x00000953] = 0xF3;    // hard crack 1: подмена адреса строки для функции, считающей хеш так, чтобы она дважды считала хэш одной и той же строки
            break;

        case 0xC:
        {
            code[0x00000897] = 0x68;    // crack 3: подмена адреса возврата из функции, проверяющей хэш введённого пароля (по адресу cs:0997)
            code[0x00000898] = 0x5F;    // push 0A5F <-- адрес начала функции, печатающей ACCESS GRANTED
            code[0x00000899] = 0x0A;
            break;
        }

        case 0xD:
        {                                                   // crack 4: переписывание пароля на "Vlad"
            ((int*)((code + 0x000008F3)))[0] = 0x64616C56;  // new password: Vlad
            break;
        }
                                        // basic crack 2:
                                        // - найти пароль в коде программы: "huysosi"
                                        // - найден баг: при введении 7 символов + Enter программа даёт доступ

        case 0xE:                       // light crack 2:
                                        // code[0x00000906] = 0x07;
            break;

        case 0xF:                       //
            break;
    }

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
