# Jogo de Perguntas - Projeto em C

Este é um jogo de perguntas de múltipla escolha desenvolvido como parte da atividade de prática de **alocação dinâmica**, **tipos abstratos de dados (struct, enum)** e **manipulação de arquivos de texto**.

## 🎯 Objetivo do Projeto

Criar uma aplicação em C que leia perguntas de múltipla escolha a partir de arquivos de texto organizados por níveis de dificuldade, apresentando-as ao jogador de forma dinâmica e segura.

## 📋 Requisitos Atendidos

- ✅ Leitura de arquivos de texto diferentes para cada nível de perguntas (`nivel1.txt` a `nivel5.txt`);
- ✅ Todas as perguntas são de múltipla escolha;
- ✅ Uso de `struct` para representar perguntas e níveis;
- ✅ A quantidade de perguntas e de alternativas é detectada automaticamente (sem codificação fixa);
- ✅ Memória alocada dinamicamente com `malloc`, `realloc` e `free`;
- ✅ Uso de `enum` para representar as opções do menu de operações;
- ✅ Validação da entrada do usuário;
- ✅ Embaralhamento das perguntas por nível.

## 🗃️ Estrutura de Arquivos

- `main.c`: Código-fonte principal;
- `nivel1.txt` a `nivel5.txt`: Arquivos com as perguntas de cada nível;
- `README.md`: Este documento.

## ▶️ Como compilar

No terminal, use:

```PowerShell
gcc -o jogo.exe main.c

$OutputEncoding = [Console]::OutputEncoding = [System.Text.Encoding]::UTF8
```

Para executar, use:
```
./jogo.exe

```
