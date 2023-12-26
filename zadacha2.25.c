 int main() {
   char symb;
   scanf("%c", &symb);
   getchar();
   unsigned int number = 0;
   number = symb;
   number = number << 8;
   scanf("%c", &symb);
   getchar();
   number = number | (int)(symb);
   number = number << 8;
   scanf("%c", &symb);
   getchar();
   number = number | (int)(symb);
   number = number << 8;
   scanf("%c", &symb);
   getchar();
   number = number | (int)(symb);
   printf("%u", number);
 }
