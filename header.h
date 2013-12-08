#ifndef HEADER2_H
#define HEADER2_H

typedef FILE *plik;

typedef struct element
{
        struct element *next;
        char  nazwa[50];
        int tryb;
        int rozmiarx;
        int rozmiary;
        int odcien;
        int **tab;
} element;


element * push(element * first, element * newone);
void wyswietl(element * first);
element * usun(element * first);
element * pozycja(element *first, int pos);
element * dodaj(element *first, plik obraz);
void zapisz(element *first,plik obraz);

void menuglowne(element *first,plik obraz);
void komendymenuglownego();
void wyswietlinfo(element *first);
void wykryjkrawedz(element *first);
void negatyw(element *first);
void obrot(element *first);
void komendyobrotu();
void obrot90(element *first);
void obrot180(element *first);
void obrot270(element *first);
void inittab(element *temp);


void menuglowne(element *lista, plik obraz)
{
	int koniec=0;
	char znak;
	int poz=0;
   
	komendymenuglownego();
	
	
	while(koniec!=1)
	{
	znak=getchar();
	switch (znak)
	{
		case '1':
			lista=dodaj(lista,obraz);
			break;
		case '2':
			wyswietl(lista);
			wyswietlinfo(pozycja(lista,poz));
			break;
		case '3':
			negatyw(lista);
			break;
		case 'a':
			wykryjkrawedz(lista);
			break;
		case '3.3':
			
			break;
		case '4.1':
			
			break;
		case '4':
			obrot(lista);
			break;
		case '5':
			zapisz(lista,obraz);
			break;
		case '6':
			lista=usun(lista);
			koniec=1;
				break;
		 default:
			 komendymenuglownego();
	}
	}	

}

void komendymenuglownego()
{
	printf("\nMENU GLOWNE: \n");
	 printf("1-wczytaj obraz\n");
	 printf("2-wyswietl liste\n");
	 printf("3.1-negatyw\n");
	 printf("3.2-krawedzie\n");
	 printf("3.3-cos jeszcze\n");
	 printf("4.1-zmien rozmiar\n");
	 printf("4.2-obroc\n");
	 printf("5-zapisz\n");
	 printf("6-zakoncz\n");
}

void komendyobrotu()
{
	printf("\nOBROT O: \n");
	 printf("1-90 w prawo\n");
	 printf("2-180\n");
	 printf("3-90 w lewo\n");	
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
		printf("\n");
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
        int i=0;
        int j=0;

        char znak;
        temp=(element *)malloc(sizeof(element));
        printf("podaj nazwe pliku:");
        scanf("%s",temp->nazwa);

        temp->next=NULL;

        obraz=fopen(temp->nazwa,"r");
        if(obraz!=NULL)
        {
                
                znak=fgetc(obraz);
                fseek(obraz,-1,SEEK_CUR);
                while(znak!=EOF)
                {
                        znak=fgetc(obraz);
                        
                                if(znak=='P')
                                {
                                znak=fgetc(obraz);
                                if(znak=='1') temp->tryb=1;
                                else if (znak=='2') temp->tryb=2;
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

                            if(temp->tryb==1)  
							{
                                fscanf(obraz,"%d%d",&temp->rozmiarx,&temp->rozmiary);
								temp->odcien=1;
                                
                                 temp->tab=(int**)malloc(temp->rozmiary*sizeof(int*));
                                 for(i=0;i<temp->rozmiary;i++)
                                        temp->tab[i] = (int*)malloc(temp->rozmiarx*sizeof(int));

                                
                                  for(i=0;i<temp->rozmiary;i++)
                                  {
                                        for(j=0;j<temp->rozmiarx;j++)
                                        {
                                                fscanf(obraz,"%d",&temp->tab[i][j]);
                                                znak=fgetc(obraz);

                                        }
                                
                                
                                  }
							}
							else if(temp->tryb==2)  
							{
                                fscanf(obraz,"%d%d",&temp->rozmiarx,&temp->rozmiary);
								fscanf(obraz,"%d",&temp->odcien);
                        
                                
                                inittab(temp);

                                
                                  for(i=0;i<temp->rozmiary;i++)
                                  {
                                        for(j=0;j<temp->rozmiarx;j++)
                                        {
                                                fscanf(obraz,"%d",&temp->tab[i][j]);
                                                znak=fgetc(obraz);

                                        }
                                
                                
                                  }
							}    
                                
                    }
                        
        
          

        fclose(obraz);
        }
        else
        {
                printf("nie ma takiego pliku\n");
                temp=usun(temp);
        }
        
        return push(first,temp);
}


void wyswietlinfo(element *first)
{
		if(first==NULL)
	{
		printf("brak plikow do wyswietlenia\n");
	}
	else
	{
	      printf("\nP%d\nrozmiary: %d\nrozmiarx: %d\nodcien: %d\n",first->tryb,first->rozmiary,first->rozmiarx,first->odcien);
	}           
}

void wykryjkrawedz(element *first)
{
	if(first==NULL)
	{
		printf("brak plikow do przetworzenia\n");
	}
	else
	{
	int i=0,j=0,k=0,m=0,counter=0;
	element *temp;
	 temp=(element *)malloc(sizeof(element));
		 temp->tab=(int**)malloc(first->rozmiary*sizeof(int*));
			for(i=0;i<first->rozmiary;i++)
              temp->tab[i] = (int*)malloc(first->rozmiarx*sizeof(int));




//////wydrukuj ile pol jest zapelnionych <na 3x3 od danego pola>
	for(i=0;i<first->rozmiary;i++)
      {
          for(j=0;j<first->rozmiarx;j++)
          {
			if(first->tab[i][j]!=0 && j>0 && i>0 && i<first->rozmiary-1 && j<first->rozmiarx-1)// zewnetrznych nie bede zmienial bo nie wiem jakby co jest poza , krawedz pola nie musi byc krawedzia kszataltu
			{
				for(k=j-1;k<j+2;k++)
				{
					for(m=i-1;m<i+2;m++)
					{
						if(first->tab[m][k]!=0) counter++;
					}
				
				}
				
			 }
			
			if(counter==9) 
			{
				temp->tab[i][j]=1;	
			}
			//printf("%d ",counter);
			counter=0;
		   }
			//printf("\n");
	}
//////////

			
		for(i=0;i<first->rozmiary;i++)
           {
           for(j=0;j<first->rozmiarx;j++)
           {
			   if(temp->tab[i][j]==1) first->tab[i][j]=0;
            // printf("%d ",first->tab[i][j]);
           }
            // printf("\n");
         
          }
  
         
	
	}
}

void negatyw(element *first)
{

	if(first==NULL)
	{
		printf("brak plikow do przetworzenia\n");
	}
	else
	{
		int i=0,j=0;

	for(i=0;i<first->rozmiary;i++)
           {
           for(j=0;j<first->rozmiarx;j++)
           {
			   first->tab[i][j]=first->odcien-first->tab[i][j];
            // printf("%d ",first->tab[i][j]);
           }
             //printf("\n");
         
          }
	}
}

void obrot(element*first)
{
	if(first==NULL)
	{
		printf("brak plikow do przetworzenia\n");
	}
	else
	{
	char znak;
	komendyobrotu();
	getchar();
	znak=getchar();
	switch (znak)
	{
		case '1':
			obrot90(first);
			break;
		case '2':
			obrot180(first);
			break;
		case '3':
			obrot270(first);
			break;
		default:
			komendyobrotu();
	}
	}
}

void obrot90(element *first)
{
	int i=0,j=0;
	int x;
	int y;
	element *temp;
	temp=(element *)malloc(sizeof(element));
	temp->rozmiarx=first->rozmiary;
	temp->rozmiary=first->rozmiarx;
	x=temp->rozmiarx-1;
	y=temp->rozmiary-1;
	inittab(temp);


for(i=0;i<temp->rozmiary;i++)
           {
           for(j=0;j<temp->rozmiarx;j++)
           {
			temp->tab[i][x-j]=first->tab[j][i];//obrot 90 w prawo
           }
            
          }
for(i=0;i<temp->rozmiary;i++)
           {
           for(j=0;j<temp->rozmiarx;j++)
           {
			  //first->tab[i][j]=temp->tab[i][j];
             printf("%d ",temp->tab[i][j]);
           }
             printf("\n");
         
          }
}
void obrot180(element *first)
{
	int i=0,j=0;
	int x=0,y=0;
	element *temp;
	temp=(element *)malloc(sizeof(element));
	temp->rozmiarx=first->rozmiarx;
	temp->rozmiary=first->rozmiary;
	x=temp->rozmiarx-1;
	
	y=temp->rozmiary-1;
	inittab(temp);
	

	for(i=0;i<first->rozmiary;i++)
           {
           for(j=0;j<first->rozmiarx;j++)
           {
			temp->tab[y-i][x-j]=first->tab[i][j];//obrot
			   
           }
            
		}

	for(i=0;i<temp->rozmiary;i++)
           {
           for(j=0;j<temp->rozmiarx;j++)
           {
             first->tab[i][j]=temp->tab[i][j];
           }
             printf("\n");
     
          }


}

void obrot270(element *first)
{
int i=0,j=0;
	int x;
	int y;
	element *temp;
	temp=(element *)malloc(sizeof(element));
	temp->rozmiarx=first->rozmiary;
	temp->rozmiary=first->rozmiarx;
	x=temp->rozmiarx-1;
	y=temp->rozmiary-1;
	inittab(temp);


for(i=0;i<temp->rozmiary;i++)
           {
           for(j=0;j<temp->rozmiarx;j++)
           {
            temp->tab[y-i][j]=first->tab[j][i];//obrot 90 w lewo
			
           }
            
          }
for(i=0;i<temp->rozmiary;i++)
           {
           for(j=0;j<temp->rozmiarx;j++)
           {
			  //first->tab[i][j]=temp->tab[i][j];
             printf("%d ",temp->tab[i][j]);
           }
             printf("\n");
         
          }
}

void inittab(element *temp)
{
	int i=0;
	 
	 temp->tab=(int**)malloc(temp->rozmiary*sizeof(int*));
          for(i=0;i<temp->rozmiary;i++)
              temp->tab[i] = (int*)malloc(temp->rozmiarx*sizeof(int));
}

void zapisz(element *first,plik obraz)
{
	int i=0,j=0;
	int znak;
	printf("\n1-nadpisac obecny plik?\n2-zapisac jako odrebny?\n");
	getchar();
	znak=getchar();
	if(znak=='1')
	{
	 obraz=fopen(first->nazwa,"w");
	 fprintf(obraz,"P%d\n",first->tryb);
	 fprintf(obraz,"%d %d\n",first->rozmiarx,first->rozmiary);
	 if(first->tryb==2) fprintf(obraz,"%d\n",first->odcien);

	 for(i=0;i<first->rozmiary;i++)
           {
           for(j=0;j<first->rozmiarx;j++)
           {
             if(j!=first->rozmiarx-1) fprintf(obraz,"%d ",first->tab[i][j]);
			 else fprintf(obraz,"%d",first->tab[i][j]);
           }
             if(i!=first->rozmiary-1) fprintf(obraz,"\n");
          }
		fclose(obraz);
	}
	else if(znak=='2')
	{
		char nazwa[50];
		printf("podaj nazwe pliku:");
		scanf("%s",nazwa);
	obraz=fopen(nazwa,"w");
	 fprintf(obraz,"P%d\n",first->tryb);
	 fprintf(obraz,"%d %d\n",first->rozmiarx,first->rozmiary);
	 if(first->tryb==2) fprintf(obraz,"%d\n",first->odcien);

	 for(i=0;i<first->rozmiary;i++)
           {
           for(j=0;j<first->rozmiarx;j++)
           {
             if(j!=first->rozmiarx-1) fprintf(obraz,"%d ",first->tab[i][j]);
			 else fprintf(obraz,"%d",first->tab[i][j]);
           }
             if(i!=first->rozmiary-1) fprintf(obraz,"\n");
          }
		fclose(obraz);

	}
	else
	{
		printf("niepoprawna komenda, sproboj ponownie\n");
		zapisz(first,obraz);

	}
	
}


#endif // HEADER2_H



