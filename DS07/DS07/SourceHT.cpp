#include "iostream"
#include "stdio.h"
using namespace std;
enum state { IN_PROGRESS = 11, KILLED = 12, WAITING = 13, NOT_RESPONDING = 14 };
struct Process
{
	int PID;
	char* pName;
	state pState;
};
struct CollisionList
{
	Process* data;
	CollisionList* next;
};
struct HashTable
{
	CollisionList** buckets;
	int htDim;
};
void initHashTable(HashTable& hashTable, int dim)
{
	hashTable.htDim = dim;
	hashTable.buckets = (CollisionList**)malloc
	(sizeof(CollisionList*)*dim);
	memset(hashTable.buckets, 0, dim * sizeof(CollisionList*));
}

Process* createProcess(int pid, char* name, state pstate)
{
	Process* process = (Process*)malloc(sizeof(Process));
	process->PID = pid;
	process->pName = (char*)malloc(strlen(name) + 1);
	strcpy(process->pName, name);
	process->pState = pstate;
	return process;
}
int fhash(state pstate, int dim)
{
	int position = pstate % dim;
	return position;
}
CollisionList* createNode(Process* node)
{
	CollisionList* nodeCL = (CollisionList*)malloc(sizeof(CollisionList));
	nodeCL->data = node;
	nodeCL->next = NULL;
	return nodeCL;
}
void insertProcessHashTable(HashTable ht, Process* process)
{
	int index = fhash(process->pState, ht.htDim);
	CollisionList* node = createNode(process);
	if (ht.buckets[index] == NULL)
		ht.buckets[index] = node;
	else
	{
		CollisionList* tmp = ht.buckets[index];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
CollisionList* getListHT(HashTable ht, state pstate)
{
	int index = fhash(pstate, ht.htDim);
	return ht.buckets[index];
}
void main()
{
	FILE* pFile = fopen("Text.txt", "r");
	HashTable hashTable;
	initHashTable(hashTable, 4);
	if (pFile)
	{
		int pid; char buffer[30]; state pstate;
		fscanf(pFile, "%d", &pid);
		while (!feof(pFile))
		{
			fscanf(pFile, "%s", buffer);
			fscanf(pFile, "%d", &pstate);
			//1.create process element
			Process* process = createProcess(pid, buffer, pstate);
			//2.insert element into hash table
			insertProcessHashTable(hashTable, process);
			fscanf(pFile, "%d", &pid);
		}
		fclose(pFile);
		CollisionList* lista = getListHT(hashTable, NOT_RESPONDING);
		while (lista)
		{
			printf("Nume:%s, PID:%d\n",
				lista->data->pName,
				lista->data->PID);
			lista = lista->next;
		}
	}
}