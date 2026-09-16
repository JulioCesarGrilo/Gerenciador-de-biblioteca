

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void consulta_livros();
void cadastrousuarios();
void cadastroeditora();
void cadastroautor();
void cadastrolivro();
void selecionaropcao(char destinoopcao[50]);
void selecaomenu();
void mensagemretorno();
void imprimecabecario();
void altera_livro();
void apaga_livro();
void incializa_codigo_livro();


struct cadastro_livro {
    int codigo;
    char titulo[50];
    char autor[50];
    char editora[50];
    int ano;
    int quantidade;
    
};

int totalivros = 0;
struct cadastro_livro livro[100];


struct cadastro_autor {
    int codigo;
    char nome[50];
    char nacionalidade[50];
};

int totalautor = 0;
struct cadastro_autor autores[100];

struct cadastro_editora {
    int codigo;
    char nome[50];
    char cidade[50];
};

int totaleditora = 0;
struct cadastro_editora editora[100];

struct cadastro_usuario {
    int codigo;
    char nome[50];
    int CPF;
    int telefone;
};

int totalusuario = 0;
struct cadastro_usuario usuario[100];

