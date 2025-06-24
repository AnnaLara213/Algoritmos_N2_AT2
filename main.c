#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TAM_LINHA 512
#define VIDAS_INICIAIS 3
#define NIVEIS 5

typedef struct
{
    char *pergunta;
    char **opcoes;
    int qtd_opcoes;
    char resposta_correta;
} Pergunta;

typedef struct
{
    Pergunta *perguntas;
    int qtd_perguntas;
} Nivel;

typedef enum
{
    JOGAR = 1,
    SAIR
} Menu;

void embaralharIndices(int *indices, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        int j = rand() % tamanho;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}

void exibirCabecalho()
{
    printf("=====================================\n");
    printf("         JOGO DE PERGUNTAS!\n");
    printf("     Responda corretamente para avançar.\n");
    printf("     Voce tem %d vidas. Boa sorte!\n", VIDAS_INICIAIS);
    printf("=====================================\n\n");
}

Nivel carregarNivel(const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    Nivel nivel = {NULL, 0};
    char linha[TAM_LINHA];
    Pergunta p;
    memset(&p, 0, sizeof(Pergunta));
    p.opcoes = NULL;

    while (fgets(linha, TAM_LINHA, arquivo))
    {
        if (strncmp(linha, "PERGUNTA:", 9) == 0)
        {
            p.pergunta = strdup(linha + 9);
            p.qtd_opcoes = 0;
            p.opcoes = NULL;
        }
        else if ((linha[0] >= 'A' && linha[0] <= 'Z') && linha[1] == ')')
        {
            p.opcoes = realloc(p.opcoes, sizeof(char *) * (p.qtd_opcoes + 1));
            p.opcoes[p.qtd_opcoes++] = strdup(linha);
        }
        else if (strncmp(linha, "RESPOSTA:", 9) == 0)
        {
            char letra;
            sscanf(linha, "RESPOSTA: %c", &letra);
            p.resposta_correta = letra;

            nivel.perguntas = realloc(nivel.perguntas, sizeof(Pergunta) * (nivel.qtd_perguntas + 1));
            nivel.perguntas[nivel.qtd_perguntas++] = p;

            memset(&p, 0, sizeof(Pergunta));
            p.opcoes = NULL;
        }
    }

    fclose(arquivo);
    return nivel;
}

void liberarNivel(Nivel nivel)
{
    for (int i = 0; i < nivel.qtd_perguntas; i++)
    {
        free(nivel.perguntas[i].pergunta);
        for (int j = 0; j < nivel.perguntas[i].qtd_opcoes; j++)
        {
            free(nivel.perguntas[i].opcoes[j]);
        }
        free(nivel.perguntas[i].opcoes);
    }
    free(nivel.perguntas);
}

int main()
{
    srand(time(NULL));
    exibirCabecalho();

    Nivel niveis[NIVEIS];
    char nome_arquivo[20];
    for (int i = 0; i < NIVEIS; i++)
    {
        sprintf(nome_arquivo, "nivel%d.txt", i + 1);
        niveis[i] = carregarNivel(nome_arquivo);
    }

    int pontuacao = 0;
    int vidas = VIDAS_INICIAIS;

    for (int nivel_atual = 0; nivel_atual < NIVEIS; nivel_atual++)
    {
        printf("----------- Nível %d -----------\n", nivel_atual + 1);
        Nivel nivel = niveis[nivel_atual];

        int *indices = malloc(sizeof(int) * nivel.qtd_perguntas);
        for (int i = 0; i < nivel.qtd_perguntas; i++)
            indices[i] = i;
        embaralharIndices(indices, nivel.qtd_perguntas);

        int perguntas_respondidas = 0;
        while (perguntas_respondidas < 3 && perguntas_respondidas < nivel.qtd_perguntas)
        {
            Pergunta p = nivel.perguntas[indices[perguntas_respondidas]];
            printf("\nPergunta %d: %s", perguntas_respondidas + 1, p.pergunta);
            for (int j = 0; j < p.qtd_opcoes; j++)
            {
                printf("%s", p.opcoes[j]);
            }

            char resposta;
            int resposta_valida = 0;

            do
            {
                printf("Sua resposta (A-%c): ", 'A' + p.qtd_opcoes - 1);
                scanf(" %c", &resposta);
                resposta = toupper(resposta);

                if (resposta >= 'A' && resposta < 'A' + p.qtd_opcoes)
                {
                    resposta_valida = 1;
                }
                else
                {
                    printf("Opção inválida. Tente novamente.\n");
                    while (getchar() != '\n')
                        ; 
                }
            } while (!resposta_valida);

            if (resposta == p.resposta_correta || resposta == p.resposta_correta + 32)
            {
                printf("Correto!\n");
                pontuacao += 5 * (nivel_atual + 1);
            }
            else
            {
                vidas--;
                printf("Errado! Resposta correta: %c\n", p.resposta_correta);
                if (vidas == 0)
                {
                    printf("FIM DE JOGO! Pontuação final: %d\n", pontuacao);
                    return 0;
                }
            }

            perguntas_respondidas++;
        }

        printf(">>> Nível %d completo! Pontuação: %d <<<\n", nivel_atual + 1, pontuacao);
        printf("Pressione ENTER para continuar...\n");
        getchar();
        getchar();

        free(indices);
    }

    printf("Parabéns! Você terminou o jogo!\nPontuação final: %d\n", pontuacao);

    for (int i = 0; i < NIVEIS; i++)
    {
        liberarNivel(niveis[i]);
    }

    return 0;
}