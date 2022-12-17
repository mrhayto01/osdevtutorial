#include <Windows.h>
#include <stdio.h>

// Follow me on youtube : mrhayto01

typedef struct _FLAG_STRUCT
{
    DWORD64 i;
    USHORT Test;
    union {
        USHORT Flags;
        struct {
            USHORT Flag1 : 1;
            USHORT Flag2 : 1;
            USHORT Flag3 : 1;
            USHORT Flag4 : 1;
            USHORT Flag5 : 1;
            USHORT Flag6 : 1;
            USHORT Flag7 : 1;
            USHORT Flag8 : 1;
            USHORT Flag9 : 1;
            USHORT UnUsed : 7;
        };
    };
} FLAG_STRUCT, * PFLAG_STRUCT;

#define FLAG1 1
#define FLAG2 2
#define FLAG3 4
#define FLAG4 8
#define FLAG5 16
#define FLAG6 32
#define FLAG7 64
#define FLAG8 128

int main()
{
    //UCHAR flags = 0;                              // 00000000
    //flags = (FLAG1 | FLAG2);                      // 00000011

    //if (flags & FLAG1)
    //    printf("flag1 is enable.\r\n");

    //if ((flags & (FLAG1 | FLAG2))== (FLAG1 | FLAG2))
    //    printf("flag1 and flag2 are enable.\r\n");

    //if((flags&7) == 7)
    //    printf("flag1, flag2 and flag3 are enable.\r\n");

    //-------------------------------------------------------------------------------

    FLAG_STRUCT flagStruct;
    int i = sizeof(FLAG_STRUCT);

    flagStruct.Flags = 0;
    flagStruct.Flag1 = TRUE;
    flagStruct.Flag2 = TRUE;
    flagStruct.Flag9 = TRUE;

    if (flagStruct.Flag1)
        printf("flag1 is enable.\r\n");

    if (flagStruct.Flag9)
        printf("flag3 is enable.\r\n");

    if (flagStruct.Flag1 & flagStruct.Flag2)
        printf("flag1 and flag2 are enable.\r\n");

    if((flagStruct .Flags&3) == 3)
        printf("flag1 and flag2 are enable.\r\n");

    return 0;
}
