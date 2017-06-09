#include "iostream"
#include "stdio.h"
using namespace std;
enum TipHardware
{
	MONITOR = 10,
	HARD_DRIVE = 20,
	RAM = 30
};
FILE* pFile = fopen("Text.txt", "r");
union TipIndicator
{
	float inchi;
	long double capacitate;
	int frecventa;
};
struct ComponentaHardware
{
	char* denumire;
	TipHardware tipHardware;
	TipIndicator tipIndicator;
};
struct QueueNode
{
	ComponentaHardware* ch;
	QueueNode* next;
};
struct DummyQueue
{
	QueueNode* head = nullptr;
	QueueNode* tail = nullptr;
};

void initCoada(DummyQueue& coada)
{
	coada.head = coada.tail = nullptr;
}
bool isQueueEmpty(const DummyQueue& coada)
{
	return coada.head == nullptr ? true : false;
}
ComponentaHardware* creareHdw(char* den, int hdwType)
{
	ComponentaHardware* result =
		(ComponentaHardware*)malloc(sizeof(ComponentaHardware));
	result->denumire = (char*)malloc(strlen(den) + 1);
	strcpy(result->denumire, den);
	switch (hdwType)
	{
	case 10:
		result->tipHardware = MONITOR;
		fscanf(pFile, "%f", &result->tipIndicator.inchi);
		break;
	case 20:
		result->tipHardware = HARD_DRIVE;
		fscanf(pFile, "%lf", &result->tipIndicator.capacitate);
		break;
	case 30:
		result->tipHardware = RAM;
		fscanf(pFile, "%d", &result->tipIndicator.frecventa);
		break;
	default:
		break;
	}
	return result;
}
QueueNode* creareNodCoada(ComponentaHardware* hdw)
{
	QueueNode* nod = (QueueNode*)malloc(sizeof(QueueNode));
	nod->ch = hdw;
	nod->next = NULL;
	return nod;
}
void enqueue(DummyQueue& coada, QueueNode* nod)
{
	if (isQueueEmpty(coada))
		coada.head = coada.tail = nod;
	else
	{
		coada.tail->next = nod;
		coada.tail = nod;
	}
}
ComponentaHardware* dequeue(DummyQueue& coada)
{
	ComponentaHardware* tmpch = nullptr;
	if (!isQueueEmpty(coada))
	{
		//1.salvare info util ptr. return
		tmpch = coada.head->ch;
		//2.salavare nod eliminat pt. dezalocare mem.
		QueueNode* tmpq = coada.head;
		//3.refacere legaturi head = second;
		coada.head = tmpq->next;
		//4.dezaloc memorie
		free(tmpq);
	}
	return tmpch;
}
void main()
{

	DummyQueue coada;
	initCoada(coada);
	if (pFile)
	{
		char buffer[50]; int hdwType;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			fscanf(pFile, "%d", &hdwType);
			//1.creare element info util
			ComponentaHardware* chdw = creareHdw(buffer, hdwType);
			//2.creare nod coada
			QueueNode* nod = creareNodCoada(chdw);
			//3.inserare nod in structura
			enqueue(coada, nod);
			fscanf(pFile, "%s", buffer);
		}
		fclose(pFile);
	}
	while (!isQueueEmpty(coada))
	{
		ComponentaHardware* hwd = dequeue(coada);
		printf("Componenta: %s\n", hwd->denumire);
	}
}