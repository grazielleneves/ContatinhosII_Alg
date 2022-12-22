//Amália Melo - 13692417
//Grazielle Tomaz Neves - 13861176
//Gabriel Henrique dos Santos - 13783972
//Pedro Guilherme Tolvo - 10492012

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "agenda.h"

int main() {    
    //Declarando variaveis
    
  t_avl A;
  TipoContato contato;
  TipoApontador p;

  CriaAgenda(&A);
	
  char op = '1';
  int x=0;
    
  while(x<100000000) { //limitando o numero de operacoes
        
    scanf(" %c", &op);//lendo operação
    if (op == '0'){ 
        ApagaArvore(&A);
        break;//parando caso operação seja 0
    }
    switch(op){
        case 'I'://Operação de Inserir
            scanf("%s", contato.nome);
            scanf("%ld", &contato.numero);
            InsereContato(&A, contato);
            break;  
        case 'P'://Operação de Pesquisar
            scanf("%s", contato.nome);
            Pesquisa(&A, contato.nome);
            break;
        case 'A'://Operação de Alterar
            scanf("%s", contato.nome);
            scanf("%ld", &contato.numero);  
            AlteraAgenda(&A, contato);
            break;  
        case 'R'://Operação de Remover
            scanf("%s", contato.nome);
            Remove(&A, contato.nome);
            break;
        default:
            printf("Operação invalida\n");
      }
    }
	return 0;
}