#include <stdio.h>
int main() {  
  unsigned int number;
  scanf("%u", &number);
  unsigned int symbol = number & 255;
  printf("%c", symbol);
  symbol = number & 65280;
  symbol = symbol >> 8;
  printf("%c", symbol);
  symbol = number & 16711680;
  symbol = symbol >> 16;
  printf("%c", symbol);
  symbol = number & 4278190080;
  symbol = symbol >> 24;
  printf("%c", symbol);
}
