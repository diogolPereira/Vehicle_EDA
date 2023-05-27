#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include "graph.h"

//Funçoes de validação
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

// Verifica se existe a adjacencia na lista de adjacencias
bool existeAdjacentes(Adjacente *h, int cod)
{
    if (h == NULL)
        return false;
    if (h->verticeDest == cod)
        return true;
    return existeAdjacentes(h->seguinte, cod);
}

// Funçoes de criação
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

// Criar um novo vértice Peso
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVerticePeso(VerticePeso **vp, char *caminho, float peso)
{
    VerticePeso *novo = malloc(sizeof(VerticePeso));
    if (novo != NULL)
    {
        strcpy(novo->caminho, caminho);
        novo->peso = peso;
        novo->seguinte = *vp;
        *vp = novo;
        return (1);
    }
    else
        return (0);
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

Vehicle *criarVeiculoAux(Vehicle *veiculo)
{
    Vehicle *novo = malloc(sizeof(struct Vehicle));
    novo->battery = veiculo->battery;
    novo->id = veiculo->id;
    strcpy(novo->name, veiculo->name);
    novo->rentCost = veiculo->rentCost;
    novo->next = NULL;
    return novo;
}

// Adicionar Veiculo a vertice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int adicionarVeiculoVerticePeso(VerticePeso **g, Vehicle *veiculo)
{
    Vehicle *novo = criarVeiculoAux(veiculo);

    if (novo)
    {
        insertVehicle(novo, &(*g)->veiculos);
        return 1;
    }
    else
        return (0);
}
// Adicionar Veiculo a vertice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int adicionarVeiculoVertice(Grafo *g, int verticeCod, Vehicle *veiculo)
{
    Vehicle *novo = criarVeiculoAux(veiculo);
    if (existeGrafo(g, verticeCod))
    {
        g = procuraVerticeCod(g, verticeCod);
        if (novo)
        {
            insertVehicle(novo, &g->veiculos);
            return 1;
        }
    }
    else
        return (0);
}

//Funções de mostragem
// Mostra adjacencias
void mostraAdjacencias(Adjacente *a)
{
    if (a == NULL)
        return;
    printf("\tAdj: %d - (%.0f)\n", a->verticeDest, a->peso);
    mostraAdjacencias(a->seguinte);
}

// Mostra Grafo
void mostraGrafo(Grafo *g)
{
    if (g == NULL)
        return;
    printf("V: %d - %s\n", g->cod, g->cidade);
    mostraAdjacencias(g->adjacentes);
    displayVehiclesList(g->veiculos);
    mostraGrafo(g->seguinte);
}

//Funçoes de limpeza
// Limpa Memoria Grafo
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

// Limpa Memoria das Adjacencias
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

//Funçoes Algoritmo
// Conta numero de vertices
int numeroVertices(Grafo *verticeAtual)
{
    int numVertices = 0;

    // Conta o número de vértices no grafo
    while (verticeAtual != NULL)
    {
        numVertices++;
        verticeAtual = verticeAtual->seguinte;
    }

    return numVertices;
}

//Procura um vertice por Código
Grafo *procuraVerticeCod(Grafo *g, int cod)
{
    if (g == NULL)
        return NULL;
    if (g->cod == cod)
        return g;
    return (procuraVerticeCod(g->seguinte, cod));
}

//Funçao de construir a variavel Caminho
char *constroiCaminhoAux(char caminhoAtual[TAM], int verticeDestNum)
{
    char verticeDest[10];
    sprintf(verticeDest, "%d", verticeDestNum);
    strcat(caminhoAtual, " -> ");
    return strcat(caminhoAtual, verticeDest);
}

//Função para pesquisar caminhos possiveis até um determinado peso
int depthFirstSearchRec(Grafo *g, int atual, int origem, float pesoMaximo, float pesoAtual, VerticePeso **vpAux, char caminhoAt[TAM])
{
    char caminhoAux[TAM];
    strcpy(caminhoAux, caminhoAt);
    Grafo *aux = procuraVerticeCod(g, atual);
    aux->visitado = true;

    Adjacente *adj = aux->adjacentes;

    while (adj)
    {
        Grafo *aux2 = procuraVerticeCod(g, adj->verticeDest);
        if (aux2->visitado == false)
        {
            if (pesoAtual + adj->peso <= pesoMaximo)
            {
                constroiCaminhoAux(caminhoAux, adj->verticeDest);
                criarVerticePeso(vpAux, caminhoAux, pesoAtual + adj->peso);
                Vehicle *copiaVeiculos = aux2->veiculos;
                while (copiaVeiculos != NULL)
                {
                    adicionarVeiculoVerticePeso(vpAux, copiaVeiculos);
                    copiaVeiculos = copiaVeiculos->next;
                }

                depthFirstSearchRec(g, adj->verticeDest, origem, pesoMaximo, pesoAtual + adj->peso, vpAux, caminhoAux);
            }
        }
        strcpy(caminhoAux, caminhoAt);
        adj = adj->seguinte;
    }
    return 1;
}

// Função para obter todos os vértices alcançáveis a partir de um vértice de origem com um peso máximo
// Retorna um vetor de estruturas VerticePeso
VerticePeso *obterVerticesPesoAlcancaveis(Grafo *g, int verticeOrigem, float pesoMaximo)
{
    float pesoInicio = 0.0;
    char origem[100] = "";
    sprintf(origem, "%d", verticeOrigem);
    char caminho[100] = "";
    strcat(caminho, origem);
    int nVertices = numeroVertices(g);

    // Cria um vetor para armazenar os vértices e pesos
    VerticePeso *verticesPeso = NULL;

    // Chama a função de busca em profundidade para encontrar os vértices alcançáveis
    depthFirstSearchRec(g, verticeOrigem, verticeOrigem, pesoMaximo, pesoInicio, &verticesPeso, caminho);

    return verticesPeso;
}

Grafo *resetVerticesVisitados(Grafo *g)
{
    Grafo *aux = g;
    while (aux)
    {
        aux->visitado = false;
        aux = aux->seguinte;
    }
    return g;
}

// Ficheiros
//Ler Grafo de binarios
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

//Ler Adjacencias de binarios
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

//Ler Veiculos de binarios
Grafo *loadVei(Grafo *g)
{
    FILE *fp;

    VeiFile aux;
    Grafo *auxGraph = g;
    char fileNameAdj[100] = "./graph/"; // Assuming a maximum file name length of 100 characters

    while (auxGraph)
    {
        strcat(fileNameAdj, auxGraph->cidade);
        strcat(fileNameAdj, "-Veic");
        printf("%s",fileNameAdj);
        fp = fopen(fileNameAdj, "rb");
        if (fp != NULL)
        {
            while (fread(&aux, 1, sizeof(VeiFile), fp))
            {
                Vehicle *newVehicle = malloc(sizeof(Vehicle));
                if (newVehicle != NULL)
                {
                    newVehicle->id = aux.id;
                    newVehicle->battery = aux.battery;
                    strcpy(newVehicle->name, aux.name);
                    newVehicle->rentCost = aux.rentCost;
                    newVehicle->next = NULL;
                    insertVehicle(newVehicle, &auxGraph->veiculos);
                }
            }
            fclose(fp);
        }
        auxGraph = auxGraph->seguinte;
        strcpy(fileNameAdj, "./graph/");
    }
    return g;
}

//Guarda Adjacencias em binarios
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

//Guarda Adjacencias em binarios
int saveVei(Adjacente *h, char *fileName, int codGrafoOrigem)
{

    if (h == NULL)
        return 0;

    FILE *fp = fopen(fileName, "wb+");
    if (!fp)
        return -1;

    Vehicle *aux = h;
    VeiFile auxVei;

    while (aux)
    {
        auxVei.rentCost = aux->rentCost;
        auxVei.codOrigem = codGrafoOrigem;
        auxVei.battery = aux->battery;
        auxVei.id = aux->id;
        strcpy(auxVei.name, aux->name);
        fwrite(&auxVei, 1, sizeof(struct veiFile), fp);
        aux = aux->next;
    }
    fclose(fp);
    return 1;
}

//Guarda Vertice em binarios
int saveGraph(Grafo *g, char *fileName)
{
    FILE *fp;
    int res = 0;
    char fileNameAdja[100] = "./graph/"; // Assuming a maximum file name length of 100 characters

    if (g == NULL)
        return 0;
    fp = fopen(fileName, "wb+"); //ficheiro binário
    if (fp == NULL)
        return -1; //erro ao abrir ficheiro

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
        strcat(fileNameAdja, "-Veic");
        res = saveVei(aux->veiculos, fileNameAdja, aux->cod);

        aux = aux->seguinte;
        strcpy(fileNameAdja, "./graph/");
    }

    fclose(fp);
    return 1; //sucesso
}
