#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
 /* T?o hàm ğ?o ngı?c chu?i trong C*/
void strrev(char str[]) {
  int lo = 0;
  int length;
  for (length = 0; str[length] != '\0' ; length++) {} 
  while ( lo < length ) {
    --length;
    char tmp = str[lo];
    str[lo] = str[length];
    str[length] = tmp;
    ++lo;
  }
}
void Char2Bin( char str[],int number)
{
    while(number>0)
    {
        if(number%2==0)
        strcat(str, "0");
        else strcat(str, "1");
        number /=2;
    }
    strrev(str);
    //chuan hoa 8 bit
    int lstr = strlen(str);
    char temp[448]="";
    for(int i=lstr;i<8;i++)
        strcat(temp,"0");
    strcat(temp,str);
    strcpy(str,temp);
}
//ham A mu B
int AmuB(int a, int b)
{
    int sum=1;
    while(b>0)
    {
        sum=sum*a;
        b--;
    }
    return sum;
}
//ham cat 32 ki tu chuyen doi thanh kieu int
int dec32char(char str[], int start, int end)
 {
    int num =0;
    int dem =32;
    for(int k = start; k<end ; k++)
    {
        dem--;
        num = num + (str[k]-48)*AmuB(2,dem);
    }
    return num;
}
int main()
{
    char input[]="hello world";
    char *strText=(char *)malloc(448* sizeof(char));
    char *strNum=(char *)malloc(64* sizeof(char));
    char *strHash=(char *)malloc(512* sizeof(char));
    int lWord = strlen(input);
    int n;
    
    for(int i=0; i < lWord;i++)
    {
        char str[448]="";
        Char2Bin(str,input[i]);
        strcat(strText,str);
    }
    //Them 1 vao sau
    strcat(strText,"1");
    //Them 0 vao cho full 448 bit
    n = 448-strlen(strText);
    for(int i = 0; i<n;i++)
    {
        strcat(strText,"0");
    }
    // Ham tao str64
    Char2Bin(strNum,lWord*8);
    char temp[64]="";
    for(int i = 0; i<56;i++)
    {
        strcat(temp,"0");
    }
    strcat(temp,strNum);
    strcpy(strNum,temp);

    //noi strText va strNum thanh chuoi 512 bit la strHash
    strcat(strHash, strText);
    strcat(strHash, strNum);

    //check
    // printf("%sva len= %ld",strText,strlen(strText));
    // printf("%sva len= %ld",strNum,strlen(strNum));
    // printf("%sva len= %ld",strNum,strlen(strHash));

    //ham chia 512 thanh mang a gom 16 phan tu chu tung doan 32 bit;
    int a[16];
    int dem =0;
    for(int i =0;i<=512;i+=32)
    {
        if( i%32==0 )
        {
            a[dem]= dec32char(strHash,i,i+32);
            dem++;
        }
    }
    for(int i =0;i<16;i++)
    {
        printf("a[%d] = %d\n",i,a[i]);
    }
    
    return 0;
}