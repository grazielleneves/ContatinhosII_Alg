#ifndef AGENDA_H
#define AGENDA_H

#define ERRO_CHEIA 0
#define SUCESSO 1

typedef char TipoNome[50];
typedef long int TipoNumero;

typedef struct {
    TipoNome nome;
    TipoNumero numero;
}TipoContato;

typedef struct TipoNo *TipoApontador;
typedef struct TipoNo {
    TipoContato contato;
    TipoApontador esq, dir;
    int altura;
} TipoNo;

typedef TipoApontador t_avl;

void CriaAgenda(t_avl *avl);
int RetornaAltura(t_avl *avl);
int ChecaFb(t_avl *avl);
int InsereContato(t_avl *avl, TipoContato contato);
int Pesquisa(t_avl *avl, TipoNome nome);
int Remove(t_avl *avl, TipoNome nome);
int AlteraAgenda(t_avl *avl, TipoContato novo);
void ApagaArvore(t_avl *avl);

#endif