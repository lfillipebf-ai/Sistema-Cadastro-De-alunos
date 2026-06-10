# 📚 Sistema de Cadastro de Alunos em C

Sistema de gerenciamento de alunos desenvolvido em linguagem C, com persistência de dados em arquivo binário.

## 📋 Funcionalidades

- ✅ Cadastrar alunos (matrícula, nome, email, notas)
- ✅ Listar todos os alunos com média e situação (Aprovado/Reprovado)
- ✅ Buscar aluno por matrícula
- ✅ Remover aluno
- ✅ Salvar e carregar dados automaticamente em arquivo binário

## 🛠️ Tecnologias

- Linguagem C (padrão C11)
- GCC (compilador)
- Manipulação de arquivos binários (`fread` / `fwrite`)
- Estruturas de dados com `struct`

## 🚀 Como rodar

### Pré-requisitos
- GCC instalado ([MinGW](https://www.mingw-w64.org/) no Windows ou `sudo apt install gcc` no Linux)

### Compilar e executar

```bash
# Clonar o repositório
git clone https://github.com/seu-usuario/sistema-cadastro.git
cd sistema-cadastro

# Compilar
make

# Executar
./sistema-cadastro
```

### Ou manualmente:
```bash
gcc -Wall -std=c11 src/main.c -o sistema-cadastro
./sistema-cadastro
```

## 📁 Estrutura do projeto

```
sistema-cadastro/
├── src/
│   └── main.c        # Código fonte principal
├── data/
│   └── alunos.dat    # Arquivo de dados (gerado automaticamente)
├── Makefile
└── README.md
```

## 📸 Preview

```
========================================
     SISTEMA DE CADASTRO DE ALUNOS      
========================================
 1. Cadastrar novo aluno
 2. Listar todos os alunos
 3. Buscar aluno por matricula
 4. Remover aluno
 0. Sair
========================================
```

## 📖 O que aprendi com esse projeto

- Uso de `struct` para modelar entidades do mundo real
- Persistência de dados com leitura e escrita em arquivos binários (`fread`/`fwrite`)
- Organização de código com funções e protótipos em C
- Gerenciamento de arrays e manipulação de strings
- Uso de Makefile para automatizar compilação

## 👨‍💻 Autor

**Rafael** — Estudante de Sistemas de Informação - UniLaSalle Rio de Janeiro  
📧 [seu-email@email.com]  
🔗 [linkedin.com/in/seu-perfil]
