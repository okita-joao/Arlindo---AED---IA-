#include <stdio.h>
#include <stdlib.h>

int main(void){
  FILE *arquivo;
  char palavra[20];

  arquivo = fopen("arquivo_palavra.txt", "w");

  if(arquivo == NULL){
    printf("Erro na abertura do arquivo");
    return 1;
  }

  printf("Escreva uma palavra, para ser registrada no arquivo: ");
  fgets(palavra, 20, stdin);

  fprintf(arquivo, "%s", palavra);

  fclose(arquivo);
  printf("Dados gravados com sucesso!");
  return 0;
}