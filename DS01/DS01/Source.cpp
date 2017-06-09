#include "stdio.h"
#include "iostream"
using namespace std;
struct Student
{
	char* nume;
	int varsta;
	float medie;
};

Student initStudent()
{
	Student s;
	char name[100];
	scanf(" %[^\n]s", name);
	s.nume = (char*)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(s.nume, name);
	scanf("%d", &s.varsta);
	scanf("%f", &s.medie);
	return s;
}
void printfS(Student s)
{
	printf("Nume:%s\n", s.nume);
	printf("Varsta:%d\n", s.varsta);
	printf("Medie:%f\n", s.medie);
}
void initStudent(Student* s)
{
	char buffer[100];
	scanf(" %[^\n]s", buffer);
	(*s).nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(s->nume, buffer);
	scanf("%d", &s->varsta);
	scanf("%f", &s->medie);
}
void switchSV(Student s1, Student s2)
{
	Student aux = s1;
	s1 = s2;
	s2 = aux;
}
void switchSR(Student& s1, Student& s2)
{
	Student aux = s1;
	s1 = s2;
	s2 = aux;
}
void switchSP(Student* s1, Student* s2)
{
	Student aux = *s1;
	*s1 = *s2;
	*s2 = aux;
}
void main()
{
	Student s1;
	Student s2;
	s1 = initStudent();
	initStudent(&s2);
	switchSV(s1, s2);
	printfS(s1); printfS(s2);
	switchSR(s1, s2);
	printfS(s1); printfS(s2);
	switchSP(&s1, &s2);
	printfS(s1); printfS(s2);
}