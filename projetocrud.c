#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"

char LIVRO[30], AUTOR[30], EDITORA[30], USUARIOS[30], EMPRE_DEV[30];




void imprimecabecario(){
    puts("*******************************");
    puts("||  GERENCIAMENTO DE LIVROS  ||");
    puts("*******************************");
}

void mensagemretorno(){
    puts("Processo finalizado! Vamos retornar para o menu inicial.");
}

void selecaomenu(){
    int opcaomenu = 0;
    puts("Insira um menu para explorar: ");
    printf("1 - %s | 2 - %s | 3 - %s | 4 - %s | 5 - %s\n",LIVRO, AUTOR, EDITORA, USUARIOS, EMPRE_DEV );
    scanf(" %d", &opcaomenu);

    switch (opcaomenu)
    {
    case 1:
        printf(" opcao %s selecionada!", LIVRO);
        selecionaropcao(LIVRO);
        break;
    case 2:
        printf(" opcao %s selecionada!", AUTOR);
        selecionaropcao(AUTOR);      
        break;
    case 3:
        printf(" opcao %s selecionada!", EDITORA);
        selecionaropcao(EDITORA);
        break;
    case 4:
        printf(" opcao %s selecionada!", USUARIOS);
        selecionaropcao(USUARIOS);
        break;
    case 5:
        printf(" opcao %s selecionada!", EMPRE_DEV);
        // puts("5");
        break;
    default:
        system("cls");
        puts("Opcao Invalida. Escolha a opcao a partir do menu de 1 a 5.");
        selecaomenu();
    } 
}

void selecionaropcao(char destinoopcao[50]){
    int opcao = 0;
    puts("Insira a opcao desejada: \n");
    puts("1 - Cadastros | 2 - Consulta | 3 - Alteracao | 4 - Exclusao \n");
    scanf(" %d", &opcao);


    switch (opcao)
    {
    case 1:
        if(destinoopcao == LIVRO) cadastrolivro();
        if(destinoopcao == AUTOR) cadastroautor();
        if(destinoopcao == EDITORA) cadastroeditora();
        if(destinoopcao == USUARIOS) cadastrousuarios();
        break;
    case 2:
        if(destinoopcao == LIVRO) consulta_livros();    
        break;
    case 3:
        if(destinoopcao == LIVRO) altera_livro();
        break;
    case 4:
        if(destinoopcao ==LIVRO) apaga_livro();
        break;
    default:
        system("cls");
        puts("Opcao Invalida. Escolha a opcao a partir do menu de 1 a 4.");
        selecionaropcao(destinoopcao);
        
    }
    
}

void cadastrolivro(){

    if(livro[totalivros].codigo == 0){
            printf("Digite o codigo de livro: "); 
            scanf(" %d", &livro[totalivros].codigo);
            printf("\nDigite o titulo do livro: ");
            getchar();
            fgets(livro[totalivros].titulo, sizeof(livro[totalivros].titulo), stdin );
            printf("\nDigite o nome do autor: ");
            fgets(livro[totalivros].autor, sizeof(livro[totalivros].autor), stdin);
            printf("\nDigite a editora do livro: ");
            fgets(livro[totalivros].editora, sizeof(livro[totalivros].editora), stdin);
            printf("\nInsira o ano: ");
            scanf(" %d", &livro[totalivros].ano);
            printf("\nInsira a quantidade: ");
            scanf(" %d", &livro[totalivros].quantidade);
            totalivros++;
            mensagemretorno();
            selecaomenu();

        }else if (totalivros>100){
            printf("Sem espaço disponivel para novos cadastros. Exclua um livro para continuar.");
            selecaomenu();
        }else{
            totalivros++;
        }

    
    

}

void cadastroautor(){
    printf("Digite o código do autor: ");
    scanf(" %d", &autores[totalautor].codigo);
    getchar();
    printf("Digite o nome do autor: ");
    fgets(autores[totalautor].nome, sizeof(autores[totalautor].nome), stdin);
    printf("Digite a nacionalidade do autor: ");
    fgets(autores[totalautor].nacionalidade, sizeof(autores[totalautor].nacionalidade), stdin);
    totalautor++;
    mensagemretorno();
    selecaomenu();
}


void cadastroeditora(){  
    printf("Digite o código do livro: ");
    scanf(" %d ", &editora[totaleditora].codigo);
    getchar();
    printf("Digite o nome da editora: ");
    fgets(editora[totaleditora].nome, sizeof(editora[totaleditora].nome), stdin);
    printf("Digite a cidade da editora: ");
    fgets(editora[totaleditora].cidade, sizeof(editora[totaleditora].cidade), stdin);
    totaleditora++;
    mensagemretorno();
    selecaomenu();
}


void cadastrousuarios(){
    printf("Digite o codigo do usuário: ");
    scanf(" %d",&usuario[totalusuario].codigo);
    getchar();
    printf("Digite o nome do usuario: ");
    fgets(usuario[totalusuario].nome, sizeof(usuario[totalusuario].nome), stdin);
    printf("Digite o CPF do usuario: ");
    scanf(" %d", &usuario[totalusuario].CPF);
    printf("Digite o numero de celular do usuario: ");
    scanf(" %d", &usuario[totalusuario].telefone);
    totalusuario++;
    mensagemretorno();
    selecaomenu();

}


void consulta_livros(){
    
    for(int i = 0; i < totalivros; i++){
        printf("Informacoes do livro %d\n", i);//codigo, titulo, autor, editora, ano, quantidade
        printf("Codigo: %d \n", livro[i].codigo);
        printf("Titulo: %s", livro[i].titulo);
        printf("Autor: %s", livro[i].autor);
        printf("Editora: %s", livro[i].editora);
        printf("Ano: %d \n", livro[i].ano);
        printf("Quantidade: %d\n", livro[i].quantidade);
        
    }
    mensagemretorno();
    selecaomenu();
}

void altera_livro(){
    int codigo = 0;
    printf("Insira o codigo do livro a ser alterado para pesquisa: ");
    scanf("%d", &codigo);

    
    for (int i = 0; i < totalivros; i++){
        if (codigo == livro[i].codigo){
            printf("Digite o codigo de livro atualizado: "); 
            scanf(" %d", &livro[i].codigo);
            printf("\nDigite o titulo do livro atualizado: ");
            getchar();
            fgets(livro[i].titulo, sizeof(livro[i].titulo), stdin );
            printf("\nDigite o nome do autor: ");
            fgets(livro[i].autor, sizeof(livro[i].autor), stdin);
            printf("\nDigite a editora do livro: ");
            fgets(livro[i].editora, sizeof(livro[i].editora), stdin);
            printf("\nInsira o ano: ");
            scanf(" %d", &livro[i].ano);
            printf("\nInsira a quantidade: ");
            scanf(" %d", &livro[i].quantidade);
        }else{
            printf("Codigo não encontrado. Retornando ao menu.");
            selecaomenu();
        }

    }
    mensagemretorno();
    selecaomenu();
    
    
}

void apaga_livro(){
    int codigo = 0;
    printf("Iniciando processo de exclusao de dados de livros. \n");
    printf("Insira o numero do codigo do livro para localizacao: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalivros; i++){
        if(codigo == livro[i].codigo){
            livro[i].codigo = 0;
            strcpy(livro[i].titulo, "");
            strcpy(livro[i].autor, "");
            strcpy(livro[i].editora, "");
            livro[i].ano = 0;
            livro[i].quantidade = 0;

        }
        
    }

    mensagemretorno();
    selecaomenu();
    
}

void incializa_codigo_livro(){
    for (int i = 0; i < (sizeof(livro) / sizeof(livro[0])); i++){
        livro[i].codigo = 0;
    }
    
}

int main(){

    strcpy(LIVRO, "Livros");
    strcpy(AUTOR, "Autor");
    strcpy(EDITORA, "Editora");
    strcpy(USUARIOS, "Usuarios");
    strcpy(EMPRE_DEV, "Emprestimos e Devolucoes");
    
    incializa_codigo_livro();
    
    imprimecabecario();

    selecaomenu();
}