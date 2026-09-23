# Sistema de Gerenciamento de Biblioteca

Sistema de gerenciamento de biblioteca desenvolvido em linguagem C, com operações CRUD completas para livros, autores, editoras e usuários, além de controle de empréstimos e devoluções com persistência em arquivos binários.

---

## Informações Acadêmicas

| Campo        | Informação                                      |
|--------------|-------------------------------------------------|
| Universidade | Universidade São Francisco — Bragança Paulista  |
| Disciplina   | Linguagem de Programação                        |
| Ano          | 2026                                            |
| Entrega      | Parcial                                         |

### Integrantes

| Nome                               | RA          |
|------------------------------------|-------------|
| Guilherme Henrique de Souza Ramos  | 202319276   |
| Júlio Cesar Grilo dos Santos       | 202641939   |
| Pablo Pericles de Assis Souza      | 202239733   |
| Thiago Aldeia Duarte               | 202615867   |

---

## Objetivo

Desenvolver um sistema de gerenciamento de biblioteca capaz de cadastrar, consultar, alterar e excluir (CRUD) informações de livros, autores, editoras e usuários, além de registrar e controlar empréstimos e devoluções, mantendo automaticamente a quantidade de exemplares disponíveis. Todos os dados são persistidos em arquivos binários, garantindo que nenhuma informação seja perdida ao encerrar o programa.

---

## Funcionalidades

### Autores
- Cadastrar autor (código gerado automaticamente)
- Consultar lista de autores
- Alterar nome e nacionalidade
- Excluir autor (bloqueado se houver livros vinculados)

### Editoras
- Cadastrar editora (código gerado automaticamente)
- Consultar lista de editoras
- Alterar nome e cidade
- Excluir editora (bloqueado se houver livros vinculados)

### Livros
- Cadastrar livro com vínculo a autor e editora já cadastrados
- Consultar lista de livros e ver detalhes completos de um livro (nome do autor e da editora resolvidos)
- Alterar título, ano e quantidade total de exemplares
- Excluir livro (bloqueado se houver empréstimo em aberto)

### Usuários
- Cadastrar usuário com nome, CPF e telefone
- Consultar lista de usuários
- Alterar nome, CPF e telefone
- Excluir usuário (bloqueado se houver empréstimo em aberto)

### Empréstimos e Devoluções
- Registrar empréstimo com data automática (bloqueado se não houver exemplar disponível)
- Registrar devolução com data automática e atualização do estoque
- Consultar histórico completo de empréstimos (em aberto e devolvidos)

---

## Estruturas de Dados

As cinco `struct` do sistema, copiadas do código-fonte:

```c
struct Livro {
    int codigo;                  /* identificador unico do livro            */
    char titulo[100];            /* titulo do livro                         */
    int codigoAutor;             /* liga o livro a um registro de Autor     */
    int codigoEditora;           /* liga o livro a um registro de Editora   */
    int ano;                     /* ano de publicacao                       */
    int quantidade;              /* total de exemplares que a biblioteca tem */
    int quantidadeDisponivel;    /* quantos exemplares NAO estao emprestados */
};

struct Autor {
    int codigo;
    char nome[100];
    char nacionalidade[50];
};

struct Editora {
    int codigo;
    char nome[100];
    char cidade[50];
};

struct Usuario {
    int codigo;
    char nome[100];
    char cpf[15];
    char telefone[20];
};

struct Emprestimo {
    int codigo;
    int codigoUsuario;           /* liga o emprestimo a um Usuario */
    int codigoLivro;             /* liga o emprestimo a um Livro   */
    char dataEmprestimo[11];     /* formato DD/MM/AAAA (10 caracteres + '\0') */
    char dataDevolucao[11];      /* fica vazia ("") ate o livro ser devolvido */
    int status;                  /* STATUS_EMPRESTADO ou STATUS_DEVOLVIDO     */
};
```

### Relacionamentos entre structs

| Campo em           | Referencia                  | Como é usado                                                    |
|--------------------|-----------------------------|-----------------------------------------------------------------|
| `Livro.codigoAutor`    | `Autor.codigo`          | Busca o nome do autor na exibição de detalhes do livro          |
| `Livro.codigoEditora`  | `Editora.codigo`        | Busca o nome da editora na exibição de detalhes do livro        |
| `Emprestimo.codigoUsuario` | `Usuario.codigo`    | Busca o nome do usuário na exibição do histórico de empréstimos |
| `Emprestimo.codigoLivro`   | `Livro.codigo`      | Busca o título do livro na exibição do histórico de empréstimos |

---

## Regras de Negócio Implementadas

**Códigos automáticos**
O código de cada novo registro é gerado como `(maior código existente no vetor) + 1`. O usuário nunca digita nem escolhe códigos.

**Datas automáticas**
As datas de empréstimo e devolução são preenchidas automaticamente com a data do sistema, no formato `DD/MM/AAAA`, usando `strftime`. O usuário não digita datas.

**Bloqueio de empréstimo sem exemplar disponível**
Um empréstimo só é registrado se `livro.quantidadeDisponivel > 0`. Caso contrário, o sistema informa que não há exemplares disponíveis e solicita outro livro.

**Bloqueio de exclusão de autor com livros vinculados**
Antes de excluir um autor, o sistema verifica se algum `Livro.codigoAutor` corresponde ao código a ser removido. Se sim, a exclusão é bloqueada.

**Bloqueio de exclusão de editora com livros vinculados**
Mesma lógica: verifica `Livro.codigoEditora` antes de permitir a exclusão.

**Bloqueio de exclusão de livro com empréstimo em aberto**
Um livro só pode ser excluído se não houver nenhum `Emprestimo` com `codigoLivro` igual ao código do livro e `status == STATUS_EMPRESTADO`.

**Bloqueio de exclusão de usuário com empréstimo em aberto**
Mesma lógica: verifica `Emprestimo.codigoUsuario` com `status == STATUS_EMPRESTADO`.

**Ajuste de quantidade disponível ao alterar o total**
Ao alterar a quantidade total de exemplares de um livro, a quantidade disponível é recalculada pela diferença (`novaQtd - qtdAntiga`), com garantias de que o resultado nunca fique negativo nem maior que o novo total.

**Validação de entrada numérica**
Toda leitura de número inteiro usa `strtol` internamente. Se o usuário digitar texto, valor vazio ou número seguido de caracteres, o sistema exibe `"Valor invalido. Digite somente numeros."` e pede novamente.

---

## Persistência em Arquivos

Os dados são armazenados em arquivos binários na mesma pasta do executável:

| Arquivo           | Conteúdo              |
|-------------------|-----------------------|
| `autores.dat`     | Registros de Autor    |
| `editoras.dat`    | Registros de Editora  |
| `livros.dat`      | Registros de Livro    |
| `usuarios.dat`    | Registros de Usuario  |
| `emprestimos.dat` | Registros de Emprestimo |

**Formato de cada arquivo:** um `int` com o total de registros, seguido do vetor de `struct` em modo binário (`fwrite`/`fread`). Exemplo esquemático:

```
[ totalRegistros (int) ][ struct[0] ][ struct[1] ] ... [ struct[N-1] ]
```

**Quando os arquivos são lidos:** uma única vez no início do programa, pela função `carregarTudo()`, que chama em sequência `carregarAutores`, `carregarEditoras`, `carregarLivros`, `carregarUsuarios` e `carregarEmprestimos`. Se o arquivo não existir (primeira execução), o total é iniciado em zero.

**Quando os arquivos são gravados:** imediatamente após cada operação de escrita (cadastro, alteração, exclusão, empréstimo ou devolução), garantindo que nenhuma alteração seja perdida mesmo se o programa encerrar inesperadamente.

---

## Como Compilar e Executar

### Pré-requisito

Um compilador C compatível com C89/C90 ou superior. Recomenda-se GCC.

### Linux / macOS

```bash
gcc projetocrud.c -o biblioteca
./biblioteca
```

Com avisos de compilação ativados (recomendado):

```bash
gcc -Wall -Wextra projetocrud.c -o biblioteca
./biblioteca
```

### Windows — linha de comando (MinGW / MSYS2)

```cmd
gcc projetocrud.c -o biblioteca.exe
biblioteca.exe
```

### Windows — Dev-C++ ou Code::Blocks

1. Abra o programa e crie um novo projeto do tipo **Console Application** em C.
2. Adicione (ou substitua o `main.c` padrão por) o arquivo `projetocrud.c`.
3. Compile e execute normalmente pelo menu do IDE.

> **Nota sobre acentuação:** os textos do programa foram escritos sem acentuação de propósito, para evitar o problema clássico de caracteres estranhos no Prompt de Comando do Windows quando o compilador não usa UTF-8 por padrão — situação comum no Dev-C++ e no Code::Blocks.

---

## Estrutura do Menu

```
Menu Principal
├── 1 - Gerenciar Livros
│   ├── 1 - Cadastrar Livro
│   ├── 2 - Consultar Livros
│   ├── 3 - Alterar Livro
│   ├── 4 - Excluir Livro
│   └── 0 - Voltar ao menu principal
├── 2 - Gerenciar Autores
│   ├── 1 - Cadastrar Autor
│   ├── 2 - Consultar Autores
│   ├── 3 - Alterar Autor
│   ├── 4 - Excluir Autor
│   └── 0 - Voltar ao menu principal
├── 3 - Gerenciar Editoras
│   ├── 1 - Cadastrar Editora
│   ├── 2 - Consultar Editoras
│   ├── 3 - Alterar Editora
│   ├── 4 - Excluir Editora
│   └── 0 - Voltar ao menu principal
├── 4 - Gerenciar Usuarios
│   ├── 1 - Cadastrar Usuario
│   ├── 2 - Consultar Usuarios
│   ├── 3 - Alterar Usuario
│   ├── 4 - Excluir Usuario
│   └── 0 - Voltar ao menu principal
├── 5 - Gerenciar Emprestimos e Devolucoes
│   ├── 1 - Registrar Emprestimo
│   ├── 2 - Registrar Devolucao
│   ├── 3 - Consultar Emprestimos
│   └── 0 - Voltar ao menu principal
└── 0 - Sair
```

---

## Conceitos de C Aplicados

| Conceito                       | Onde aparece no código                                                                              |
|--------------------------------|-----------------------------------------------------------------------------------------------------|
| `struct`                       | `Livro`, `Autor`, `Editora`, `Usuario`, `Emprestimo` — representam as entidades do sistema          |
| Vetores de struct              | `livros[MAX_LIVROS]`, `autores[MAX_AUTORES]` etc. — armazenam todos os registros em memória         |
| Funções                        | Cada operação é uma função dedicada; utilitários (`lerLinha`, `lerInteiro`, `obterDataAtual`) são reaproveitados em todo o sistema |
| Variáveis globais              | Os vetores e contadores (`totalLivros` etc.) são globais para serem acessados por todas as funções  |
| `do...while` e `switch`        | Todos os menus usam `do { ... switch(opcao) { ... } } while (opcao != 0)`                          |
| Estruturas de repetição (`for`, `while`) | Busca sequencial nos vetores, validação de entrada em laço, descarte de buffer             |
| Ponteiros e strings (`char *`) | `lerLinha` recebe `char *destino`; `fgets`, `strlen`, `strftime` manipulam strings em C            |
| Manipulação de arquivos        | `fopen`, `fwrite`, `fread`, `fclose` em modo binário (`"wb"`/`"rb"`) para persistência             |
| `time.h`                       | `time()`, `localtime()` e `strftime()` para obter e formatar a data atual automaticamente          |
| `strtol`                       | Conversão segura de string para inteiro com detecção de entrada inválida em `lerInteiro`           |
| Diretivas de pré-processador   | `#define` para constantes (`MAX_*`, `ARQ_*`, `STATUS_*`); `#ifdef _WIN32` para portabilidade do `limparTela` |
| Protótipos de função           | Declarados antes do `main` para permitir que funções se referenciem mutuamente                     |

---

## Status do Projeto

| Etapa | Descrição                              | Situação        |
|-------|----------------------------------------|-----------------|
| 1     | Levantamento de requisitos             | Concluído       |
| 2     | Definição das structs                  | Concluído       |
| 3     | Implementação dos menus                | Concluído       |
| 4     | CRUD das entidades                     | Concluído       |
| 5     | Módulo de empréstimos e devoluções     | Concluído       |
| 6     | Gravação e leitura de arquivos         | Concluído       |
| 7     | Integração do sistema                  | Concluído       |
| 8     | Testes e correções                     | Em andamento    |
| 9     | Organização e documentação             | Em andamento    |
| 10    | Apresentação final                     | Pendente        |

---

## Limitações Conhecidas

**Limites dos vetores fixos em tempo de compilação**
Os vetores são alocados estaticamente com tamanhos máximos definidos por `#define`: 200 livros, 100 autores, 100 editoras, 200 usuários e 500 empréstimos. Ao atingir o limite, o sistema exibe uma mensagem e bloqueia novos cadastros.

**Textos sem acentuação**
Toda a interface do programa usa textos sem acentos para garantir compatibilidade com o Prompt de Comando do Windows em ambientes onde o compilador não configura UTF-8 por padrão.

**CPF sem validação de formato**
O CPF é armazenado como texto (`char cpf[15]`) e aceita qualquer sequência digitada. Não há verificação de formato (000.000.000-00) nem validação dos dígitos verificadores.

**Busca apenas por código**
Não há busca de registros por nome ou outros campos. Para localizar um autor, editora, livro ou usuário é necessário conhecer o código ou percorrer a listagem exibida na tela.

**Sem validação de ano de publicação**
O ano informado no cadastro do livro é aceito como qualquer inteiro positivo, sem verificação de intervalo razoável.

**Arquivo binário dependente de plataforma**
Os arquivos `.dat` gerados em uma plataforma (ex.: Windows 64-bit) podem não ser lidos corretamente em outra com tamanhos de `struct` diferentes (diferenças de alinhamento ou tamanho de `int`).
