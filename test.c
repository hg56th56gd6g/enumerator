#include "enumerator.h"
#include <windows.h>
#define CHAR_SET "0123456789"
HANDLE stdo;
COORD x0y0={0,0};
DWORD temp;
CreateEnumeratorFunction(EnumChar,char,WriteConsoleOutputCharacterA(stdo,buf,10,x0y0,&temp););
void Main(void){
    stdo=CreateFileA("CONOUT$",GENERIC_WRITE,FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
    if(stdo!=INVALID_HANDLE_VALUE){
        char arr[]=CHAR_SET;
        char *eoa=arr+(sizeof(CHAR_SET)-1);
        char buf[11];
        buf[10]='\n';
        char *eob=buf+10;
        EnumChar(arr,eoa,buf,eob);
    }
}