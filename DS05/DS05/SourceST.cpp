#include "iostream"
#include "stdio.h"
using namespace std;
struct InternetProvider
{
	char* name;
	float subscription;
};
struct SQNode
{
	InternetProvider* data;
	SQNode* next;
	SQNode* prev;
};

InternetProvider* createIP(char* name, float value)
{
	InternetProvider* ip = (InternetProvider*)malloc(sizeof(InternetProvider));
	ip->name = (char*)malloc(strlen(name) + 1);
	strcpy(ip->name, name);
	ip->subscription = value;
	return ip;
}

SQNode* createNode(InternetProvider* ip)
{
	SQNode* node = (SQNode*)malloc(sizeof(SQNode));
	node->data = ip;
	node->next = node->prev = NULL;
	return node;
}

void pushNode(SQNode*& head, SQNode* node)
{
	if (head == NULL)
		head->next = head->prev = head = node;
	else
	{
		node->next = head;
		node->prev = head->prev;
		head->prev = node;
		node->prev->next = node;
		head = node;
	}
}

InternetProvider* popNode(SQNode*& head)
{
	InternetProvider* ip = NULL;
	if (head != NULL)
	{
		ip = head->data;
		if (head->next == head && head->prev == head)
		{
			free(head);
			head = NULL;
		}
		else
		{
			SQNode* tmp = head;
			head->next->prev = head->prev;
			head->prev->next = head->next;
			head = tmp->next;
			free(tmp);
		}
	}
	return ip;
}


void previewList(SQNode* head)
{
	SQNode* tmp = head->prev;
	//while (tmp != head)
	//{
	//	printf("Provider:%s, subscription:%f\n",
	//		tmp->data->name, tmp->data->subscription);
	//	tmp = tmp->prev;
	//}
	//printf("Provider:%s, subscription:%f\n",
	//	tmp->data->name, tmp->data->subscription);
	do
	{
		printf("Provider:%s, subscription:%f\n",
			tmp->data->name, tmp->data->subscription);
		tmp = tmp->prev;
	} while (tmp != head->prev);
}

void filterList(SQNode* head, float pValue)
{
	SQNode* tmp = head->prev;
	do
	{
		if (tmp->data->subscription > pValue)
			printf("Provider:%s, subscription:%f\n",
				tmp->data->name, tmp->data->subscription);
		tmp = tmp->prev;
	} while (tmp != head->prev);
}

void insertAfter(SQNode* head, SQNode* node, char* value)
{
	SQNode* tmp = head;
	do
		tmp = tmp->next;
	while (tmp != head && strcmp(tmp->data->name, value));
	if (strcmp(tmp->data->name, value) == 0)
	{
		//1.legam nodul de structura
		node->next = tmp->next;
		node->prev = tmp;
		//2.structura de nod
		tmp->next->prev = node;
		tmp->next = node;
	}
}

InternetProvider* deleteList(SQNode*& head, char* value)
{
	InternetProvider* result = nullptr;
	SQNode* tmp = head;
	do
		tmp = tmp->next;
	while (tmp != head && strcmp(tmp->data->name, value));
	if (strcmp(tmp->data->name, value) == 0)
	{
		result = tmp->data;
		SQNode* tmpNode = tmp;
		if (tmp == head)
			head = tmp->next;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp);
	}
	return result;
}

int countNoSubscriptions(SQNode* head, float value)
{
	static SQNode* tmp = head->prev;
	if (tmp != head)
	{
		if (head->data->subscription > value)
			return 1 + countNoSubscriptions(head->next, value);
		else
			return countNoSubscriptions(head->next, value);
	}
	else
		if (head->data->subscription > value)
			return 1;
		else
			return 0;
}

void main()
{
	FILE* pFile = fopen("Text.txt", "r");
	SQNode* lista = NULL;
	if (pFile)
	{
		char buffer[30]; float value;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			fscanf(pFile, "%f", &value);
			//1.creare element tip IP*
			InternetProvider* ip = createIP(buffer, value);
			//2.creare element tip SQNode*
			SQNode* node = createNode(ip);
			//3.inserare nod in lista
			pushNode(lista, node);
			fscanf(pFile, "%s", buffer);
		}
		fclose(pFile);
	}

	printf("-----------Results:------------\n");
	previewList(lista);

	printf("-----------Results:------------\n");
	filterList(lista, 12.3);

	InternetProvider* newIp = createIP("AT&T", 14.3);
	SQNode* newNode = createNode(newIp);
	insertAfter(lista, newNode, "VODAFONE");

	printf("-----------Results:------------\n");
	previewList(lista);

	int value = countNoSubscriptions(lista, 12.3);
	printf("No. of subscriptions:%d\n", value);

	InternetProvider* result = deleteList(lista, "UPC");
	printf("-----------Results:------------\n");
	previewList(lista);

	printf("-----------Results:------------\n");
	while (lista != NULL)
	{
		InternetProvider* ip = popNode(lista);
		printf("Provider:%s, subscription:%f\n",
			ip->name, ip->subscription);
	}
}