// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <stdarg.h>
#include "stdlib.h"
#include "userlib.h"
#include "clock.h"
#include "sysCalls.h"

#define limit_BUFFER 100
#define STDIN 0
#define STDOUT 1
char buffer[limit_BUFFER];
int buffSize = 0;
int background = 0;

int getchar(){
    char temp[2] = {0};
    int read = scan(0, temp, 2);
    if (read <= 0)
        return -1;
    return *temp;
    
}

int putchar(char c){
    char temp[2] = {0};
    *temp = c;
    return print(STDOUT, temp, 2);
}

void emptyBuffer() {
    buffSize = 0;
    int c = 0;
    while(c != -1)
        c = getchar();
    
}




void strcpy(char *str1, char *str2)
{ //copies str1 into str2
      int i;
      for (i = 0; str1[i] != 0; i++)
            str2[i] = str1[i];
      str2[i] = 0;
}

int isBackground() {
    return background;
}

char * getCommandWithArgsBis(){
    emptyBuffer();
    int c = 0;
    int back = 0;
    while ((c = getchar()) != '\n'){
        if (c == '\b'){
            back = 0;
            if (buffSize != 0)
                buffSize--;
        }
        else if (c == '&') { 
            back = 1;
            putchar(c);
        }
        else if (c != -1){
            back = 0;
            putInBuff(c);
            putchar(c);
        }
    }
    background = back; 
    putchar('\n');
    putInBuff('\0');
    char retString[buffSize];
    strcpy(buffer, retString);
    return retString;
}

void printf(char * command, ...){
    char auxBuff[limit_BUFFER];
    va_list args;
    va_start(args, command);
    while(*command != 0){
        if(*command == '%'){
            command++;
            char * string;
            switch(*command){
                case 'd':
                    string = itoa(va_arg(args, int), auxBuff, 10);
                break;
                case 'x':
                    string = itoa(va_arg(args, int), auxBuff, 16);
                break;
                case 's':
                    string = va_arg(args,char*);
                break;
                default:
                    printf("Error en formato");
                    va_end(args);
                    return;
                break;  
            }
            print(1, string, strlen(string));
        }
        else{
            print(1, command, 1);
        }
    command++;                   
    }
    va_end(args);
}

int strlen(char * string){
    int i = 0;
    while (string[i] != 0)
        i++;
    return i;
}

int strcmp(const char * str1, const char * str2){
    if(*str1 == 0 || *str2 == 0){
        return 1;
    }
    while(*str1 != 0 && *str2 != 0){
        if(*str1 != *str2){
            return 1;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void cleanBuffer(char * buffer){
    int len = strlen(buffer);
    for(int i = 0; i < len; i++)
        buffer[i] = 0;
}

void tokenize(char token, int *cant, char **dest, char *source, int limit){
      int index = 0;

      if (*source != token && *source != '\0')
            dest[index++] = source;

      while (*source != '\0'){
            if (*source == token){
                  *source = 0;
                  if (*(source + 1) != token && (*(source + 1) != '\0')){
                        if (index >= limit)
                              return index;
                        dest[index++] = source + 1;
                  }
            }
            source++;
      }
    

      *cant = index;
}

void putInBuff(char c) {
    if(buffSize < limit_BUFFER - 1)
        buffer[buffSize++] = c;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end){
        char aux = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = aux;
        start++;
        end--;
    }
}

  
// Implementation of itoa() - https://www.geeksforgeeks.org/implement-itoa/
char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
  
    //Handle 0 explicitely, otherwise empty string is printed for 0 
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
  
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
  
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }
  
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
  
    str[i] = '\0'; // Append string terminator
  
    // Reverse the string
    reverse(str, i);
  
    return str;
}

int atoi(char * str){
    int number = 0;
    int mult = 1;
    int n = strlen(str);
    //n = (int)n < 0 ? -n : n; /* quick absolute value check  */
    /* for each character in array */
    while (n--)
    {
        /* if not digit or '-', check if number > 0, break or continue */
        if ((str[n] < '0' || str[n] > '9') && str[n] != '-')
        {
                if (number)
                    break;
                else
                    continue;
        }

        if (str[n] == '-')
        { /* if '-' if number, negate, break */
                if (number)
                {
                    number = -number;
                    break;
                }
        }
        else
        { /* convert digit to numeric value   */
                number += (str[n] - '0') * mult;
                mult *= 10;
        }
    }

    return number;
}
 
//https://stackoverflow.com/questions/10156409/convert-hex-string-char-to-int
int hexToInt(char * num){
    if (num[0] == '0' && (num[1] == 'x' || num[1] == 'X')){
        int val = 0;
        while (*num) {
            // get current character then increment
            char byte = *num++; 
            // transform hex character to the 4bit equivalent number, using the ascii table indexes
            if (byte >= '0' && byte <= '9') byte = byte - '0';
            else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
            else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
            // shift 4 to make space for new digit, and add the 4 bits of the new digit 
            val = (val << 4) | (byte & 0xF);
        }
        return val;
    }
    return -1;
}

//Inspirada en itoa. La adaptamos para que str tenga la cantidad de bytes que queremos
char * intToHex(uint64_t num, char * str, int bytes) 
{ 
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i++] = 'x';

        while (i < bytes*2 + 2) {
            str[i++] = '0';
        }

        str[i] = '\0'; 
        return str; 
    } 

    while (i < bytes*2 && num != 0) { 
        int rem = num % 16; 
        str[i++] = (rem >= 10)? (rem - 10) + 65 : rem + 48; 
        num = num/16; 
    } 

    while (i < bytes*2) {
        str[i++] = '0';
    }

    str[i++] = 'x';
    str[i++] = '0';
    str[i] = '\0';
    reverse(str, i);
    return str; 
}

void sleep(int secs){
    char auxBuff[3] = {0};
    seconds(auxBuff);
    int initialSecs = (auxBuff[0] - '0') * 10 + (auxBuff[1] - '0');
    while(1){
        seconds(auxBuff);
        int auxSeconds = (auxBuff[0] - '0') * 10 + (auxBuff[1] - '0');
        if (auxSeconds - initialSecs >= secs)
            return;
    }
}
