#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

int getchar();
int putchar(char c);
void emptyBuffer() ;
int scanf(char * command, ...);
void getCommandWithArgs();
char * getCommandWithArgsBis();
int isBackground();
void printf(char * command, ...);
int strlen(char * string);
int strcmp(const char * str1, const char * str2);
void strcpy(char *str1, char *str2);
void cleanBuffer(char * buffer);
void putInBuff(char c);
void tokenize(char token, int *cant, char **dest, char *source, int limit);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
int atoi(char * str);
int isValidHexaAddress(char * buff);
int hexToInt(char* num);
char * intToHex(uint64_t num, char * str, int bytes);
void sleep(int secs);

#endif
