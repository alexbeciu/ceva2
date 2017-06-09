#include "stdlib.h"
#include "stdio.h"
#include "memory.h"

struct AdjNodes
{
	int vertex;
	AdjNodes* next;
};
struct Graf
{
	int noVertices;
	AdjNodes** adjLists;
};
AdjNodes* createNode(int vertex)
{
	AdjNodes* node = (AdjNodes*)malloc(sizeof(AdjNodes));
	node->vertex = vertex;
	node->next = NULL;
	return node;
}
void insertNode(AdjNodes*& head, AdjNodes* node)
{
	if (head == NULL)
		head = node;
	else
	{
		AdjNodes* tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
void BF(int** mat, int noVertices, int spoint)
{
	//initializare
	int* vizitat = (int*)malloc(sizeof(int)*noVertices);
	int* queue = (int*)malloc(sizeof(int)*noVertices);
	memset(vizitat, 0, sizeof(int)*noVertices);
	int first = 0, last = -1;
	queue[++last] = spoint - 1;
	vizitat[spoint - 1] = 1;
	//test de coada vida
	while (last >= first)
	{
		for (int k = 0; k < noVertices; k++)
		{
			if (mat[queue[first]][k] == 1 && vizitat[k] == 0)
			{
				vizitat[k] = 1;
				queue[++last] = k;
			}
		}
		printf("%2d", ++queue[first++]);
	}
}

void BFAL(Graf graf, int noVertices, int spoint)
{
	//initializare
	int* vizitat = (int*)malloc(sizeof(int)*noVertices);
	int* queue = (int*)malloc(sizeof(int)*noVertices);
	memset(vizitat, 0, sizeof(int)*noVertices);
	int first = 0, last = -1;
	queue[++last] = spoint - 1;
	vizitat[spoint - 1] = 1;
	//test de coada vida
	while (last >= first)
	{
		AdjNodes* list = graf.adjLists[queue[first]];
		for (; list; list = list->next)
		{
			if (vizitat[list->vertex] == 0)
			{
				vizitat[list->vertex] = 1;
				queue[++last] = list->vertex;
			}
		}
		printf("%2d", ++queue[first++]);
	}
}

void main()
{
	FILE* pFile = fopen("Text.txt", "r");
	if (pFile)
	{
		int noVertices; int start, end; Graf graf;
		int** mat = NULL;
		fscanf(pFile, "%d", &noVertices);

		//initializare structura graf (vector de liste)
		graf.noVertices = noVertices;
		graf.adjLists = (AdjNodes**)malloc(sizeof(AdjNodes*)*noVertices);
		memset(graf.adjLists, NULL, sizeof(AdjNodes*)*noVertices);

		mat = (int**)malloc(sizeof(int*)*noVertices);
		for (int i = 0; i < noVertices; i++)
		{
			mat[i] = (int*)malloc(sizeof(int)*noVertices);
			memset(mat[i], 0, sizeof(int)*noVertices);
		}
		while (!feof(pFile))
		{
			fscanf(pFile, "%d	%d", &start, &end);
			mat[start - 1][end - 1] = mat[end - 1][start - 1] = 1;

			AdjNodes* node = createNode(start - 1);
			insertNode(graf.adjLists[end - 1], node);
			node = createNode(end - 1);
			insertNode(graf.adjLists[start - 1], node);
		}
		for (int i = 0; i < noVertices; i++)
		{
			printf("Starting point: %d\n", i + 1);
			BF(mat, noVertices, i + 1);
			printf("\n-----------------\n");
		}

		for (int i = 0; i < noVertices; i++)
		{
			printf("Starting point: %d\n", i + 1);
			BFAL(graf, noVertices, i + 1);
			printf("\n-----------------\n");
		}

		fclose(pFile);
	}
}