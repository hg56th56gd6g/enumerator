#include "enumerator.h"
#include <windows.h>
#define CHAR_SET "0123456789"
#define BUF_SIZE (5)
CreateEnumeratorFunction(
    EnumChar,
    char,
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),buf,BUF_SIZE+1,0,0)
);
void Main(void){
    char arr[]=CHAR_SET;
    char buf[BUF_SIZE+1];//最后放一个换行符
    buf[BUF_SIZE]='\n';
    EnumChar(
        arr,
        arr+(sizeof(CHAR_SET)-1),
        buf,
        buf+BUF_SIZE//换行符不包括在Enum函数的buf里
    );
}