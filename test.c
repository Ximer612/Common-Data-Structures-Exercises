#include <stdio.h>
#include <stdlib.h>

#define RED_PRINT(x) printf("\033[0;31m %s \033[0;00m",x)

int main(int argc, char const *argv[])
{
        RED_PRINT("ciao");
        RED_PRINT("%d",20);
        RED_PRINT("%d %s",20,"ciao");

    return 0;
}