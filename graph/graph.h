/*****************************************************************/ /**
 * @file   Graph.h
 * @brief  Library for managing the graph that contains vehicles and users
 * 
 * @author Diogo
 * @date   May 2023
 *********************************************************************/
#include <stdio.h>
#include <stdbool.h>

#ifndef GRAPHLIB
#define GRAPHLIB
#define TAM 50

// Representação de um grafo orientado e pesado
typedef struct adjacente
{
    float peso;
    int verticeDest; // geocódigo what3words
    struct adjacente *seguinte;
} Adjacente;

typedef struct grafo
{
    int cod; // geocódigo what3words
    char cidade[TAM]; // geocódigo what3words
    bool visitado;
    Adjacente *adjacentes;
    struct grafo *seguinte;
} Grafo;

typedef struct AdjFile {
	int codOrigem;
	int codDestino;		/*!< Código da Adjacência */
	float weight;		/*!< Peso */
}AdjFile;

typedef struct VerticeFile {
	int cod;					/*!< Código do Vértice */
	char cidade[TAM];				/*!< Nome da Cidade */
} VerticeFile;

// Estrutura para armazenar o vértice e o peso acumulado
typedef struct verticePeso
{
    int vertice;
    int verticeOrigem;
    float peso;
    struct verticePeso * seguinte;
} VerticePeso;

// Função para criar um novo vértice no grafo
int criarVertice(Grafo **g, int cod, char cidade[TAM]);

// Função para verificar se um vértice existe no grafo
bool existeVertice(Grafo *g, int cod);

// Função para criar uma nova aresta entre dois vértices no grafo
int criarAresta(Grafo *g, int vOrigem, int vDestino, float peso);

// Função para verificar se um vértice adjacente existe na lista de adjacências
bool existeAdjacentes(Adjacente *h, int cod);

// Função para mostrar as adjacências de um vértice
void mostraAdjacencias(Adjacente *a);

// Função para mostrar o grafo
void mostraGrafo(Grafo *g);

// Função para carregar o grafo a partir de um arquivo
Grafo *loadGraph(Grafo **h, char *fileName);

// Função para carregar as adjacências do grafo a partir de arquivos
Grafo *loadAdj(Grafo *g);

// Função para salvar as adjacências de um vértice em um arquivo
int saveAdj(Adjacente *h, char *fileName, int codVerticeOrigem);

// Função para salvar o grafo em um arquivo
int saveGraph(Grafo *g, char *fileName);

VerticePeso* obterVerticesPesoAlcancaveis(Grafo* g, int verticeOrigem, float pesoMaximo);

int depthFirstSearchRec(Grafo* g, int origem, float pesoMaximo,float  pesoAtual ,VerticePeso** vpAux);
Grafo* procuraVerticeCod(Grafo* g, int cod);
int numeroVertices(Grafo* verticeAtual);
Grafo *resetVerticesVisitados(Grafo* g);
Grafo* destroyGraph(Grafo* g);

Adjacente* destroyAdj(Adjacente* h);
#endif
