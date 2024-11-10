#include <stdio.h>
#include <string.h>

int main() {
  int T, respostas2[5], cont = 0;
  char respostas[10];
  scanf("%i", &T);
  getchar();
  fgets(respostas, 10, stdin);
  respostas[9] = '\0';
  for(int i = 0; i < 9; i++){
    if(respostas[i] != ' '){
      if(respostas[i] == '1'){
        respostas2[cont] = 1;
        cont++;
      }
      else if(respostas[i] == '2'){
        respostas2[cont] = 2;
        cont++;
      }
      else if(respostas[i] == '3'){
        respostas2[cont] = 3;
        cont++;
      }
      else if(respostas[i] == '4'){
        respostas2[cont] = 4;
        cont++;
      }
    }
  } cont = 0;
  for(int i = 0; i < 5; i++)
    if(respostas2[i] == T) cont++; 
  printf("%i\n", cont);
  return 0;
}
