#include "stdio.h"
#include "stdlib.h"
struct NodArbore
{
	int info;
	NodArbore* right;
	NodArbore* left;
	int balanceFactor;
};
NodArbore* creareNod(int value)
{
	NodArbore* nod = (NodArbore*)malloc(sizeof(NodArbore));
	nod->info = value;
	nod->balanceFactor = 0;
	nod->left = nod->right = NULL;
	return nod;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int getHeight(NodArbore* root)
{
	if (root != NULL)
		return 1 + max(getHeight(root->left), getHeight(root->right));
	else
		return 0;
}
int getBalancingFactor(NodArbore* root)
{
	//getHeight()
	int bfactor = getHeight(root->right) - getHeight(root->left);
	return bfactor;
}

void SRS(NodArbore*& pivot)
{
	NodArbore* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	pivot->balanceFactor = getBalancingFactor(pivot);
	desc->balanceFactor = getBalancingFactor(desc);
	pivot = desc;
}

void SRD(NodArbore*& pivot)
{
	NodArbore* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	pivot->balanceFactor = getBalancingFactor(pivot);
	desc->balanceFactor = getBalancingFactor(desc);
	pivot = desc;
}

void rebalansareArbore(NodArbore*& pivot)
{
	NodArbore* desc = NULL;
	if (pivot->balanceFactor == 2)
	{
		desc = pivot->right;
		if (desc->balanceFactor == 1)
			//simple rotation to the left in pivot
			SRS(pivot);
		else
		{
			//simple rotation to the right in desc
			SRD(pivot->right);
			//simple rotation to the left in pivot
			SRS(pivot);
		}
	}
	else if (pivot->balanceFactor == -2)
	{
		desc = pivot->left;
		if (desc->balanceFactor == -1)
			//simple rotation to the right in pivot
			SRD(pivot);
		else
		{
			//simple rotation to the left in desc
			SRS(pivot->left);
			//simple rotation to the right in pivot
			SRD(pivot);
		}
	}
}

void inserareNod(NodArbore*& root, NodArbore* nod)
{
	if (root == NULL)
		root = nod;
	else
	{
		if (root->info > nod->info)
			inserareNod(root->left, nod);
		else if (root->info < nod->info)
			inserareNod(root->right, nod);
		else
			printf("Key already exists!");
	}
	root->balanceFactor = getBalancingFactor(root);
	rebalansareArbore(root);
}

void printArbore(NodArbore* root)
{
	if (root)
	{
		printArbore(root->left);
		printf("Key:%d, bfactor:%d\n",
			root->info, root->balanceFactor);
		printArbore(root->right);
	}
}

void main()
{
	FILE* pFile = fopen("Text.txt", "r");
	if (pFile)
	{
		NodArbore* radacina = NULL;
		int info;
		fscanf(pFile, "%d", &info);
		while (!feof(pFile))
		{
			NodArbore* nod = creareNod(info);
			inserareNod(radacina, nod);
			fscanf(pFile, "%d", &info);
		}
		printArbore(radacina);
	}
}