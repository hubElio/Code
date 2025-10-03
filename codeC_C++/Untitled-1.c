
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  char word[10] = "azertyuoip";
  int word_lenght = 0;
  while(word != NULL)
  {
      word_lenght++;
      word++;
  }
  word_lenght--;
  printf("\n %d",word_lenght);

  printf("\n %d",word_lenght + (word_lenght%8)*2 + (word_lenght%16)*3);
  return 0;
}
