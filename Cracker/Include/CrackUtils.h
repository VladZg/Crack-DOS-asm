#ifndef CRACK_UTILS_H
#define CRACK_UTILS_H

#include "../AppConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ReadFile(FILE* file, char** buf);
int CrackProgramm(const char* inp_filename, const char* out_filename);

#endif
