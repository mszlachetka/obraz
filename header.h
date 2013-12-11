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
                int czyzapisano;
} element;


element * push(element * first, element * newone);
element * usun(element * first);
element * pozycja(element *first, int pos);
element * dodaj(element *first, plik obraz);

int wybor(element *lista);
int maxlista(element *lista);

void usunjeden(element *temp);
void podmianatablicy(element *first,element *temp);
void wyswietl(element * first);
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
void zapisz(element *first,plik obraz, int trybzapisu);
void zapiskoncowy(element *first,plik obraz);
int  zakres(int wartosc, int max);

void menuglowne(element *lista, plik obraz)
{
        int koniec=0;
        char znak;
   
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
                        wyswietlinfo(pozycja(lista,wybor(lista)));
                        break;
                case '3':
                        negatyw(pozycja(lista,wybor(lista)));
                        break;
                case '4':
                        wykryjkrawedz(pozycja(lista,wybor(lista)));
                        break;
                case '5':
                        
                        break;
                case '6':
                        
                        break;
                case '7':
                        obrot(pozycja(lista,wybor(lista)));
                        break;
                case '8':
                        zapisz((pozycja(lista,wybor(lista))),obraz,0);
                        break;
                case '9':
                        zapiskoncowy(lista, obraz);
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
         printf("2-wyswietl dane pliku\n");
         printf("3-negatyw\n");
         printf("4-krawedzie\n");
         printf("5-cos jeszcze\n");
         printf("6-zmien rozmiar\n");
         printf("7-obroc\n");
         printf("8-zapisz\n");
         printf("9-zakoncz\n");
}

void komendyobrotu()
{
        printf("\nOBROT O: \n");
         printf("0-90 w prawo\n");
         printf("1-180\n");
         printf("2-90 w lewo\n");        
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
         usun(temp);       
        
}
element * usun(element * first)
{
	int i=0,j=0;
        if(first==NULL)
                return NULL;

		
        usun(first->next);

         for(i=0;i<first->rozmiary;i++)
				free(first->tab[i]);
		 free(first->tab);
      
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
                 temp->czyzapisano=1;
                znak=fgetc(obraz);
                fseek(obraz,-1,SEEK_CUR);
               
                        znak=fgetc(obraz);
             
                                if(znak=='P')
                                {
                                znak=fgetc(obraz);
                                if(znak=='1') temp->tryb=1;
                                else if (znak=='2') temp->tryb=2;
                                }
                              
	znak=fgetc(obraz);
	while(znak=='\n' || znak=='\r')
            znak=fgetc(obraz);
        while(znak=='#' || znak==EOF)
        {
            while(znak!='\n')
            {
                znak=fgetc(obraz);
				 printf("%c",znak);
            }
            znak=fgetc(obraz);
        }
		fseek(obraz,-1,SEEK_CUR);

                            if(temp->tryb==1)  
                             {
                                fscanf(obraz,"%d%d",&temp->rozmiarx,&temp->rozmiary);
                                 temp->odcien=1;
                                
                                inittab(temp);
                                
                                  for(i=0;i<temp->rozmiary;i++)
                                  {
                                        for(j=0;j<temp->rozmiarx;j++)
                                        {
                                               fscanf(obraz,"%d",&temp->tab[i][j]);
                                                //znak=fgetc(obraz);

                                        }
                                
                                
                                  }
                                }
                                 else if(temp->tryb==2)  
                                     {
                                fscanf(obraz,"%d%d",&temp->rozmiarx,&temp->rozmiary);
                                  fscanf(obraz,"%d",&temp->odcien);
                        
                                
                                inittab(temp);
								//fseek(obraz,-1,SEEK_CUR);

		                 
                                  for(i=0;i<temp->rozmiary;i++)
                                  {
                                        for(j=0;j<temp->rozmiarx;j++)
                                        {
											fscanf(obraz,"%d",&temp->tab[i][j]);
									
                                           znak=fgetc(obraz);

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
		 usun(temp);       
}


void wyswietlinfo(element *first)
{
                if(first==NULL)
        {
                printf("brak plikow do wyswietlenia\n");
        }
        else
        {
              printf("\n%s\nP%d\nrozmiary: %d\nrozmiarx: %d\nodcien: %d\nczyzapisano:",first->nazwa,first->tryb,first->rozmiary,first->rozmiarx,first->odcien);
                  if(first->czyzapisano==1) printf("tak\n");
                  if(first->czyzapisano==0) printf("nie\n");
        }           
}


void wykryjkrawedz(element *first)
{
        int i=0,j=0,k=0,m=0,counter=0;
		
		negatyw(first);
        if(first==NULL)
        {
                printf("brak plikow do przetworzenia\n");
        }
        else
        {
        element *temp;
        
        temp=(element *)malloc(sizeof(element));
        temp->rozmiarx=first->rozmiarx;
        temp->rozmiary=first->rozmiary;//sam podaje rozmiary bo moge potrzebowac tymczasowej np odwroconej
        inittab(temp);


        if(first->tryb==1)
        {
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
                         
           }
          
         
          }
  
        
                }
        

        
        if(first->tryb==2)
        {
        for(i=0;i<first->rozmiary;i++)
      {
          for(j=0;j<first->rozmiarx;j++)
          {
                        
                                temp->tab[i][j]=first->tab[i][j];
                               
                  }
                
                }


        for(i=0;i<first->rozmiary;i++)
      {
          for(j=0;j<first->rozmiarx;j++)
          {
                        if( j>0 && i>0 && i<first->rozmiary-1 && j<first->rozmiarx-1)
                        {

                                               

							 for(k=j;k<j+1;k++)
                                {
                                        for(m=i;m<i+1;m++)
                                        {
                                             
											 if(first->tab[m-1][k]!=first->tab[m+1][k]);
											 else if (first->tab[m][k-1]!=first->tab[m][k+1]);
											  else if (first->rozmiarx<100 && first->rozmiary<100 && first->tab[m][k-1]==first->tab[m][k+1] && first->tab[m][k-1]!=first->tab[m][k]);
											    else if (first->rozmiarx<100 && first->rozmiary<100 && first->tab[m-1][k]==first->tab[m+1][k] && first->tab[m-1][k]!=first->tab[m][k]);
											 else temp->tab[i][j]=0;
                                        }
                                
                                }
										
                                                
                         }
                        
                }
        }

    

        for(i=0;i<first->rozmiary;i++)
           {
           for(j=0;j<first->rozmiarx;j++)
           {
                            first->tab[i][j]=temp->tab[i][j];
           }
           
         
          }
                
        }
		
		usunjeden(temp);

         negatyw(first);
          first->czyzapisano=0;	          

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
        first->czyzapisano=0;
        
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
        int znak=0;
        komendyobrotu();

        znak=zakres(znak,2);
        
                        if(znak==0) obrot90(first);
                        if(znak==1) obrot180(first);
                        if(znak==2) obrot270(first);
                
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
       
        
		podmianatablicy(first,temp);
	usunjeden(temp);     
        


        first->czyzapisano=0;
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
            // printf("\n");
     
          }
		      
        first->czyzapisano=0;
      usunjeden(temp);
}

void podmianatablicy(element *first,element *temp)
{
	int i=0,j=0;
     for(i=0;i<first->rozmiary;i++)
				free(first->tab[i]);
        free(first->tab);

		first->rozmiarx=temp->rozmiarx;
		first->rozmiary=temp->rozmiary;
		inittab(first);

		for(i=0;i<temp->rozmiary;i++)
           {
           for(j=0;j<temp->rozmiarx;j++)
           {
                        first->tab[i][j]=temp->tab[i][j];
           }
            
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
podmianatablicy(first,temp);
first->czyzapisano=0;
 usunjeden(temp);     

}

void inittab(element *temp)
{
        int i=0;
         
         temp->tab=(int**)malloc(temp->rozmiary*sizeof(int*));
          for(i=0;i<temp->rozmiary;i++)
              temp->tab[i] = (int*)malloc(temp->rozmiarx*sizeof(int));
}

void usunjeden(element *temp)
{
	int i=0;
for(i=0;i<temp->rozmiary;i++)
				free(temp->tab[i]);
		 free(temp->tab);
		 free(temp);
}
void zapisz(element *first,plik obraz, int trybzapisu)
{
int i=0,j=0;
int znak=0;
        if(first==NULL)
        {
                printf("brak plikow do zapisania\n");
        }
        else
        {
                

        if(trybzapisu==0)
        {
        
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
				first->czyzapisano=1;
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
		 first->czyzapisano=1;
                fclose(obraz);

        }
        else
        {
                printf("niepoprawna komenda, sproboj ponownie\n");
                zapisz(first,obraz,trybzapisu);

        }
        }
        else if(trybzapisu==1)
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
			first->czyzapisano=1;
                fclose(obraz);
        }
        else if(trybzapisu==2)
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
				first->czyzapisano=1;
                fclose(obraz);

        }

}
}

int wybor(element *lista)
{
        if(lista!=NULL)
        {
        int poz=0;
        if((maxlista(lista)-1)!=0)
        {
        wyswietl(lista);
        printf("Na ktorym elemencie listy chcesz pracowac?\n");
        scanf("%d",&poz);
        if( poz<maxlista(lista) && poz>=0) return poz;
        else
        {
                printf("wartosc spoza zakresu\n");
            wybor(lista);
                return -1;
        }
        }
        else return 0;
        }
        return -1;
}

int zakres(int wartosc, int max)
{
        scanf("%d",&wartosc);
        if( wartosc<=max && wartosc>=0) 
        {
                return wartosc;
        }
        else
        {
                printf("nie znana komenda\n");
                zakres(wartosc,max);
                return 0;
        }
}

int maxlista(element *lista)
{
        element *temp=lista;
        int counter=0;
        if(lista==NULL)
        {
              return -1;
        }
        do
        {
                
               counter++;
                temp=temp->next;
                
        }while(temp!=NULL);
		 usun(temp);       
                return counter;
}

void zapiskoncowy(element *lista,plik obraz)
{
        int trybzapisu=0;//0-zapisuj pytajac pokolei , 1-zapisz wszystkie zmienione (nadpisujac), 2-zapisz wszystkie zmienione podajac nazwe nowego pliku
        int czyzapisaczmiany=0;
		int counter=0;
        element *temp=lista;
        
        if(lista!=NULL)
        {
		do
        {
        
              if(temp->czyzapisano==1) counter++;
                temp=temp->next;
                
        }while(temp!=NULL);

		temp=lista;
        if(counter<maxlista(lista))
        {
        int ile=maxlista(lista);
        printf("czy chcesz zapisac niezapisane zmiany?\n0-nie\n1-tak\n");
        czyzapisaczmiany=zakres(czyzapisaczmiany,1);
        if(czyzapisaczmiany==1)
        {
        printf("wybierz sposob zapisu:\n0-zapis pojedynczego pliku\n1-zapisz wszystkie zmienione nadpisujac\n2-zapisz wszystkie zmienione podajac nazwe nowego pliku\n");
        trybzapisu=zakres(trybzapisu,2);

        while(temp!=NULL)
		{
                if(temp->czyzapisano==0)
				{
				 printf("%s\n",temp->nazwa);
				zapisz(temp,obraz,trybzapisu);
                  ile--;
				}
             temp=temp->next;
                
        }

         if(temp==NULL)
        {

             printf("wszystkie pliki sa zaatualizowane\n");
        }
                usun(temp);
        }
        
        }
        }
	
}


#endif // HEADER2_H
