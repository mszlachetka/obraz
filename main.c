#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>

typedef FILE *plik;

typedef struct element
{
	struct element *next;
	char  nazwa[50];
	int tryb;
	int rozmiarx;
	int rozmiary;
	int odcien;
} element;

element * push(element * first, element * newone);
void wyswietl(element * first);
element * usun(element * first);
element * pozycja(element *first, int pos);
element * dodaj(element *first);


int main()
{
	element * lista=NULL;

	lista=dodaj(lista);
	//wyswietl(lista);
	lista=usun(lista);
	system("pause");
	return 0;
}

element * push(element * first, element * newone)
{
	element * temp=first;
	if(first==NULL)
		return newone;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=newone;
	return first;
}
void wyswietl(element * first)
{
	int i=0;
	element *temp=first;
	if(first==NULL)
	{
		printf("Brak elementow na liscie\n");
		return;
	}
	do
	{
		
		printf("%d - %s\n",i++,temp->nazwa);
		temp=temp->next;
		
	}while(temp!=NULL);
	
}
element * usun(element * first)
{
	if(first==NULL)
		return NULL;

	usun(first->next);
	
	free(first);
	return NULL;
}

element * pozycja(element *first, int pos)
{
	if(first)
	{
		while(first->next && pos>0)
		{
			first=first->next;
			pos--;
		}
	}
	return first;
}



element * dodaj(element *first,plik obraz)
{
	element *temp;
	char znak=NULL;
	temp=(element *)malloc(sizeof(element));
	printf("podaj nazwe pliku:");
	scanf("%s",temp->nazwa);
	temp->next=NULL;

	obraz=fopen(temp->nazwa,"r");
	if(obraz!=NULL)
	{
		znak=fgetc(obraz);
		while(znak!=EOF)
			{
				fseek(obraz,-1,SEEK_CUR);
				znak=fgetc(obraz);
				if(znak=='P')
				{
				znak=fgetc(obraz);
				if(znak=='1') temp->tryb=1;
				else if (znak=='2') temp->tryb=2;
				else if (znak=='3') temp->tryb=2;
				}
				else if(znak=='#')
				{
					fseek(obraz,-1,SEEK_CUR);
					while(znak!='\n') 
					{
						znak=fgetc(obraz);
						printf("%c",znak);
					}
				} 
				else if(znak!='\0');
				{
					//temp->rozmiarx=znak;
					znak=fgetc(obraz);
					//temp->rozmiary=znak;
					printf("innyczytany\n");
				}
			}
	
			printf("P%d\nrozmiarx: %d\nrozmiary: %d\n",temp->tryb,temp->rozmiarx,temp->rozmiary);
	fclose(obraz);
	}
	else
	{
		printf("nie ma takiego pliku\n");
		temp=usun(temp);
	}
	
	return push(first,temp);
}
