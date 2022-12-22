#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int a, int b) {
	return a > b ? a : b; 
}
static void rotacao_dir(t_avl *avl) {

	TipoApontador j, B;

	// filho à esq da raiz
	j = (*avl)->esq;
	// filho à esq à dir da raiz
	B = j->dir;

	// a sub-arv muda de pai pela antiga raiz
	(*avl)->esq = B;
	// aux passa a ser a raiz
	j->dir = (*avl);

	(*avl)->altura = max(RetornaAltura(&(*avl)->esq), RetornaAltura(&(*avl)->dir)) + 1;

	j->altura = max(RetornaAltura(&j->esq),RetornaAltura(&j->dir)) + 1;

	// mudar o ponteiro "de cima"
	*avl = j;

}

static void rotacao_esq(t_avl *avl) {

	TipoApontador j, B;

	// filho à dir da raiz
	j = (*avl)->dir;
	// filho à dir à esq da raiz
	B = j->esq;

	// a sub-arv muda de pai pela antiga raiz
	(*avl)->dir = B;
	// aux passa a ser a raiz
	j->esq = (*avl);

	(*avl)->altura = max(RetornaAltura(&(*avl)->esq),
						RetornaAltura(&(*avl)->dir)) + 1;

	j->altura = max(RetornaAltura(&j->esq),
						RetornaAltura(&j->dir)) + 1;

	// mudar o ponteiro "de cima"
	*avl = j;

}

static void rotacao_dir_esq(t_avl *avl) {
	//rotacionar à direita
	rotacao_dir(&(*avl)->dir);
	//rotacionar à esquerda
	rotacao_esq(avl);

}

static void rotacao_esq_dir(t_avl *avl) {
	rotacao_esq(&(*avl)->esq);
	rotacao_dir(avl);
}
void CriaAgenda(t_avl *avl) {//criando agenda
	*avl = NULL;
}
int static criar_raiz(t_avl *avl, TipoContato contato){

	*avl = (t_avl) malloc(sizeof(TipoNo));
	if (*avl == NULL)
		return ERRO_CHEIA;
	
	(*avl)->esq = NULL;
	(*avl)->dir = NULL;
	(*avl)->contato = contato;
	(*avl)->altura = 0;

	return SUCESSO;

}

int RetornaAltura(t_avl *avl) {
    if ((*avl) == NULL)
        return -1;
    else
        return (*avl)->altura;
}

int ChecaFb(t_avl *avl) {
    if ((*avl) == NULL)
        return 0;
    else 
        return RetornaAltura(&(*avl)->esq) - 
    			RetornaAltura(&(*avl)->dir);
}

int InsereContato(t_avl *avl, TipoContato contato) {//inserindo contatos
	if ((*avl)==NULL) {
		return criar_raiz(avl, contato);
	}
	//considerar chaves primárias
	if (strcmp((*avl)->contato.nome, contato.nome) == 0) { //caso as strings sejam iguais
        printf("Contatinho ja inserido\n");
	} else {
		if (strcmp((*avl)->contato.nome, contato.nome) > 0) {//caso o valor da string1 seja maior que o da string2
			InsereContato(&(*avl)->esq, contato);
			(*avl)->altura = max((*avl)->altura,
						RetornaAltura(&(*avl)->esq) + 1);
		} 
    else if(strcmp((*avl)->contato.nome, contato.nome) < 0){//caso o valor da string2 seja menor que o da string2
			InsereContato(&(*avl)->dir, contato);
			(*avl)->altura = max((*avl)->altura,
						RetornaAltura(&(*avl)->dir) + 1);
		}

	}
	//logo depois de inserir, fazer rotações
	int fb = ChecaFb(avl);
	if (fb > 1) { // esq

		// 2 casos
		int fb_filho = ChecaFb(&(*avl)->esq);

		if (fb_filho >=0) {
			rotacao_dir(avl);
		} 
        else{
			rotacao_esq_dir(avl);
		}
	} 
    else if (fb < -1) { // dir
		int fb_filho = ChecaFb(&(*avl)->dir);

		if (fb_filho <= 0) {
			rotacao_esq(avl);
		} 
        else{
			rotacao_dir_esq(avl);
		}
	}
    return SUCESSO;

}
int Pesquisa(t_avl *avl, TipoNome chave) {
	if ((*avl) == NULL) {//caso o contatinho não tenha sido encontrado
		printf("Contatinho nao encontrado\n");
		return -1;
	}
	if (strcmp((*avl)->contato.nome, chave) == 0) {//encontrando, informar telefone
		printf("Contatinho encontrado: telefone %ld\n",(*avl)->contato.numero); 
	} 
  	else{
		if (strcmp(chave, (*avl)->contato.nome) < 0){//pesquisar até encontrar
			return Pesquisa(&(*avl)->esq, chave);
		} 
        else if(strcmp(chave, (*avl)->contato.nome) > 0){
			return Pesquisa(&(*avl)->dir, chave);
		}
	}
	return SUCESSO;
}

static void buscaMaiorEsqETroca(t_avl *raiz, t_avl *subarv) {

	if ((*subarv)->dir == NULL) {
		TipoApontador p;
		(*raiz)->contato = (*subarv)->contato;
		p = *subarv;
		*subarv = (*subarv)->esq;
		free(p);

	} 
  	else {
		buscaMaiorEsqETroca(raiz, &(*subarv)->dir);		
	}

}

int Remove(t_avl *avl, TipoNome chave) {

	// nao achou
	if ((*avl) == NULL){
		printf("Operacao invalida: contatinho nao encontrado\n");
        return -1;
    }
	// busca: direita ou esquerda
	if (strcmp((*avl)->contato.nome, chave) < 0) {
		return Remove(&(*avl)->dir, chave);
	} 
  	else if (strcmp((*avl)->contato.nome, chave) > 0) {
		return Remove(&(*avl)->esq, chave);
	}
	TipoApontador p;
	//se passou, é porque achou a chave
	if ((*avl)->esq==NULL && (*avl)->dir==NULL) { //caso 1 (folha)
		p = *avl;
		*avl = NULL;
		free(p);
	} 
    else if ((*avl)->esq==NULL) { // caso 2 (dir)
		p = *avl;
		*avl = (*avl)->dir;
		free(p);
	} 
    else if ((*avl)->dir==NULL) { //caso 3 (esq)
		p = *avl;
		*avl = (*avl)->esq;
		free(p);
	} 
    else { //caso 4
		buscaMaiorEsqETroca(avl, &(*avl)->esq);
	}
    int fb = ChecaFb(avl);
    if (fb > 1) { // esq
		// 2 casos
		int fb_filho = ChecaFb(&(*avl)->esq);
		if (fb_filho >=0) {
			rotacao_dir(avl);
		} 
        else{
			rotacao_esq_dir(avl);
		}
	} 
    else if (fb < -1) { // dir
		int fb_filho = ChecaFb(&(*avl)->dir);
		if (fb_filho <= 0) {
			rotacao_esq(avl);
		} 
        else{
			rotacao_dir_esq(avl);
		}
	}
	return SUCESSO;
}
int AlteraAgenda(t_avl *avl, TipoContato novo){
  	if ((*avl)== NULL) {//não encontrou
		printf("Operacao invalida: contatinho nao encontrado\n");
		return SUCESSO;
	}
  	if(strcmp((*avl)->contato.nome, novo.nome) == 0){//encontrou e altera
		(*avl)->contato.numero = novo.numero;
	} 
  	else {//percorrendo até encontrar
		if(strcmp((*avl)->contato.nome, novo.nome) > 0) {
			return AlteraAgenda(&((*avl)->esq), novo);
		} 
    	else{
			return AlteraAgenda(&((*avl)->dir), novo);
		}
	}
	return SUCESSO;
}
void ApagaArvore(t_avl *avl) {//liberando árvore
	if((*avl) != NULL) {
		ApagaArvore(&(*avl)->esq);
		ApagaArvore(&(*avl)->dir);
		free(*avl);
	}
}
