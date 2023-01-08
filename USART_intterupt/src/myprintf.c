#include <stdint.h>
#include <stdarg.h>

#include "myprintf.h"

int tsprintf(char* buff, char* , ...){
  va_list arg;
  int len;

  va_start(arg, fmt);

  len = vtsprint(buff, fmt, arg);

  va_end(arg);

  return len;
}

int vtsprintf(char *buff, char *fmt, va_list arg){
  int len;
  int size;
  uint8_t zero_flag, width;

  size = 0;
  len = 0;

  while(*fmt){
    if(*fmt == '%'){
      zero_flag = 0;
      width = 0;
      fmt++;

      if(*fmt == '0'){
        fmt++;
        zero_flag = 1;
      }

