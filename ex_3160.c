#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // cria a célula tipo "amigo"
    typedef struct amigos {
        char nome[500];
        struct amigos *prox;
    } amigo;

    // cria a lista de amigos, e lê ela:
    char lista_atual_amigos[500];
    fgets(lista_atual_amigos, 500, stdin); // pega a lista atual de amigos
    lista_atual_amigos[strlen(lista_atual_amigos) - 1] = '\0'; // remove o caractére \n da string

    // vê quantos amigos possui a lista:
    int cont = 0, num_amigos_atuais = 0;
    for (int i = 0; i < strlen(lista_atual_amigos); i++)
        if (lista_atual_amigos[i] == ' ')
            cont++;
    num_amigos_atuais += cont + 1;

    // divide a string em uma lista de amigos separados(cada amigo é uma célula)
    int *pCont = &cont;
    char aux[20];
    cont = 0; // zera o contador

    amigo *inicio = NULL, *temp = NULL, *ultimo = NULL; // cria um ponteiro inicio, temporário, último
    for (int i = 0; i < num_amigos_atuais; i++) {
        temp = (amigo *)malloc(sizeof(amigo)); // com ajuda do ponteiro ele aloca memória para uma nova cell (amigo)
        for (int c = 0; c < 20; c++) {
            if (lista_atual_amigos[cont] == ' ')
                c = 20;
            aux[c] = lista_atual_amigos[cont];
            *pCont += 1;
        }
        strcpy(temp->nome, aux);
        for (int b = 0; b < 20; b++)
            aux[b] = '\0';   // esvazia a string auxiliar
        temp->prox = NULL; // a próxima cell é NULL por enquanto;
        if (inicio == NULL)
            inicio = temp; // caso seja a primeira célula
        else
            ultimo->prox = temp; // conecta a última cell criada com a temporária
        ultimo = temp; // atualiza, agora a cell temporária vira a última criada
    }
    amigo cabeca;
    strcpy(cabeca.nome, "\0");
    cabeca.prox = inicio; // cria uma cabeça pra lista

    // leitura dos amigos novos:
    char lista_novos_amigos[500];
    fgets(lista_novos_amigos, 500, stdin);
    lista_novos_amigos[strlen(lista_novos_amigos) - 1] = '\0'; // elimina o último caractére \n da string

    // cria uma cell com os novos amigos:
    amigo amigos_novos;
    amigos_novos.prox = NULL;
    strcpy(amigos_novos.nome, lista_novos_amigos); // atribui o conteudo da nova cell

    // leitura da indicação:
    char indicacao[20];
    fgets(indicacao, 20, stdin);
    indicacao[strlen(indicacao) - 1] = '\0';

    // indicação não (nao):
    amigo *not = &cabeca;
    int nao = strcmp(indicacao, "nao");
    if (nao == 0) {
        while (not ->prox != NULL)
            not = not ->prox;
        not ->prox = &amigos_novos; // not é o ponteiro que aponta para a última celula imprimindo a lista indicada e atualizada
        amigo *comeco = cabeca.prox;
        while (comeco != NULL) {
            printf("%s", comeco->nome);
            if(comeco->prox != NULL) printf(" ");
            comeco = comeco->prox;
        }
        printf("\n");
        return 0;
    }
    // indicação sim (algum nome):
  else {
      // busca do nome indicado
      amigo *referente = cabeca.prox, *anterior = &cabeca;
      while (referente != NULL) {
          int num = strcmp(referente->nome, indicacao);
          if (num == 0) { // foi encontrado a cell com o amigo indicado
              anterior->prox = &amigos_novos;
              amigos_novos.prox = referente;
          }
          referente = referente->prox;
          anterior = anterior->prox;
      }
      amigo *comeco = cabeca.prox;
      while (comeco != NULL) {
          printf("%s", comeco->nome);
          if(comeco->prox != NULL) printf(" ");
          comeco = comeco->prox;
      }
      printf("\n");
      return 0;
    }
}
