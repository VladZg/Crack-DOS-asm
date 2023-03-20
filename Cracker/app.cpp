#include "./AppConfig.h"
#include <stdlib.h>
#include "./Include/CrackUtils.h"
#include "./Include/AppUtils.h"

int main()
{
    int file_hash = CheckFileHash(INP_FILEPATH "CRACK_1.COM");
    exit(StartApp(file_hash, INP_FILEPATH "CRACK_1.COM"));

    return 1;
}
