#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include "graph.h"

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo **g, int cod, char cidade[TAM])
{
    Grafo *novo = malloc(sizeof(struct grafo));
    if (novo != NULL)
    {
        novo->cod = cod;
        strcpy(novo->cidade, cidade);
        novo->seguinte = *g;
        *g = novo;
        return (1);
    }
    else
        return (0);
}


// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVerticePeso(VerticePeso **vp,int verticeO, int vertice, float peso)
{
    VerticePeso *novo = malloc(sizeof(VerticePeso));
    if (novo != NULL)
    {
        novo->verticeOrigem = verticeO;
        novo->vertice = vertice;
        novo->peso = peso;
        novo->seguinte = *vp;
        *vp = novo;
        return (1);
    }
    else
        return (0);
}

// Devolve 1 se o vertice existe no grafo ou 0 caso contrário
bool existeGrafo(Grafo *g, int cod)
{
    while (g != NULL)
    {
        if (g->cod == cod)
            return true;
        else
            g = g->seguinte;
    }
    return false;
}

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarAresta(Grafo *g, int vOrigem, int vDestino, float peso)
{
    Adjacente *novo;
    if (existeGrafo(g, vOrigem) && existeGrafo(g, vDestino))
    {
        while (g->cod != vOrigem)
            g = g->seguinte;

        if (existeAdjacentes(g->adjacentes, vDestino))
            return 0;

        novo = malloc(sizeof(struct adjacente));
        if (novo != NULL)
        {
            novo->verticeDest = vDestino;
            novo->peso = peso;
            novo->seguinte = g->adjacentes;
            g->adjacentes = novo;
            return (1);
        }
        else
            return (0);
    }
    else
        return (0);
}

bool existeAdjacentes(Adjacente *h, int cod)
{
    if (h == NULL)
        return false;
    if (h->verticeDest == cod)
        return true;
    return existeAdjacentes(h->seguinte, cod);
}

void mostraAdjacencias(Adjacente *a)
{
    if (a == NULL)
        return;
    printf("\tAdj: %d - (%.0f)\n", a->verticeDest, a->peso);
    mostraAdjacencias(a->seguinte);
}

void mostraGrafo(Grafo *g)
{
    if (g == NULL)
        return;
    printf("V: %d - %s\n", g->cod, g->cidade);
    mostraAdjacencias(g->adjacentes);
    mostraGrafo(g->seguinte);
}

Grafo *destroyGraph(Grafo *g)
{
    if (g == NULL)
        return NULL;
    Grafo *aux = NULL;
    while (g)
    {
        if (g->seguinte)
            aux = g->seguinte;
        g->adjacentes = destroyAdj(g->adjacentes);
        free(g);
        g = aux;
        aux = NULL;
    }
    return g;
}

Adjacente *destroyAdj(Adjacente *h)
{
    if (h == NULL)
        return NULL;
    Adjacente *aux = NULL;
    while (h)
    {
        if (h->seguinte != NULL)
            aux = h->seguinte;
        free(h);
        h = aux;
        aux = NULL;
    }
    return h;
}


int numeroVertices(Grafo* verticeAtual){
    int numVertices = 0;

    // Conta o número de vértices no grafo
    while (verticeAtual != NULL)
    {
        numVertices++;
        verticeAtual = verticeAtual->seguinte;
    }

    return numVertices;
}


Grafo* procuraVerticeCod(Grafo* g, int cod) {
	if (g == NULL) return NULL;
	if (g->cod==cod) return g;
	return(procuraVerticeCod(g->seguinte, cod));
}


int depthFirstSearchRec(Grafo* g, int origem, float pesoMaximo,float  pesoAtual ,VerticePeso** vpAux)
{
    

	Grafo* aux = procuraVerticeCod(g, origem);
	aux->visitado = true;

	Adjacente* adj = aux->adjacentes;

	while (adj) {
		Grafo*  aux2 = procuraVerticeCod(g, adj->verticeDest);
		if (aux2->visitado == false )
		{   
            if(pesoAtual + adj->peso <= pesoMaximo){
                criarVerticePeso(vpAux,origem,adj->verticeDest , pesoAtual + adj->peso);
			    depthFirstSearchRec(g, adj->verticeDest,pesoMaximo, pesoAtual + adj->peso, vpAux);
            } 

			
		}
        adj = adj->seguinte;
        
	}
	return 1;
}
// Função para obter todos os vértices alcançáveis a partir de um vértice de origem com um peso máximo
// Retorna um vetor de estruturas VerticePeso
VerticePeso* obterVerticesPesoAlcancaveis(Grafo* g, int verticeOrigem, float pesoMaximo) {
    float pesoInicio = 0.0;
    int nVertices = numeroVertices(g);

    // Cria um vetor para armazenar os vértices e pesos
    VerticePeso* verticesPeso = NULL;

    // Chama a função de busca em profundidade para encontrar os vértices alcançáveis
    depthFirstSearchRec(g, verticeOrigem, pesoMaximo, pesoInicio, &verticesPeso);
    
    
    return verticesPeso;
}

Grafo *resetVerticesVisitados(Grafo* g) {
	Grafo* aux = g;
	while (aux) {
		aux->visitado = false;
		aux = aux->seguinte;
	}
	return g;
}

Grafo *loadGraph(Grafo **h, char *fileName)
{
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL)
        return NULL;
    VerticeFile aux;
    while (fread(&aux, 1, sizeof(VerticeFile), fp))
    {
        criarVertice(h, aux.cod, aux.cidade);
    }
    fclose(fp);
}

Grafo *loadAdj(Grafo *g)
{
    FILE *fp;

    AdjFile aux;
    Grafo *auxGraph = g;
    char fileNameAdj[100] = "./graph/"; // Assuming a maximum file name length of 100 characters

    while (auxGraph)
    {
        strcat(fileNameAdj, auxGraph->cidade);
        fp = fopen(fileNameAdj, "rb");
        if (fp != NULL)
        {
            while (fread(&aux, 1, sizeof(AdjFile), fp))
            {
                criarAresta(g, aux.codOrigem, aux.codDestino, aux.weight);
            }
            fclose(fp);
        }
        auxGraph = auxGraph->seguinte;
        strcpy(fileNameAdj, "./graph/");
    }
    return g;
}

int saveAdj(Adjacente *h, char *fileName, int codGrafoOrigem)
{

    if (h == NULL)
        return 0;

    FILE *fp = fopen(fileName, "wb+");
    if (!fp)
        return -1;

    Adjacente *aux = h;
    AdjFile auxAdj;

    while (aux)
    {
        auxAdj.codOrigem = codGrafoOrigem;
        auxAdj.codDestino = aux->verticeDest;
        auxAdj.weight = aux->peso;
        fwrite(&auxAdj, 1, sizeof(auxAdj), fp);
        aux = aux->seguinte;
    }
    fclose(fp);
    return 1;
}

int saveGraph(Grafo *g, char *fileName)
{
    FILE *fp;
    int res = 0;
    char fileNameAdja[100] = "./graph/"; // Assuming a maximum file name length of 100 characters

    if (g == NULL) return 0;
    fp = fopen(fileName, "wb+"); //ficheiro binário
    if (fp == NULL)
    	return -1;						//erro ao abrir ficheiro

    Grafo *aux = g;
    VerticeFile verticeFile;
    while (aux)
    {
        strcat(fileNameAdja, aux->cidade);
        strcpy(verticeFile.cidade, aux->cidade);
        verticeFile.cod = aux->cod;
        fwrite(&verticeFile, 1, sizeof(verticeFile), fp);
        res = saveAdj(aux->adjacentes, fileNameAdja, aux->cod);
        if (res < 0)
        { //erro ao gravar as adjacencias
            return -2;
        }
        aux = aux->seguinte;
        strcpy(fileNameAdja, "./graph/");
    }

    fclose(fp);
    return 1; //sucesso
}
