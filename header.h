#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


typedef FILE *plik;
typedef struct element
{
        struct element *next;
        struct element *prev;
        char  nazwa[15];
} element;

element * push(element * first, element * newone);
element * usun(element * first);
element * pozycja(element *first, int pos);
element * dodaj(element *first);
element * dodajlosowo(element *first,element *temp2);
void wyswietl(element * first);
void  menuglowne(element *lista,plik asdf);
void komendymenuglownego();
element * pozycja(element *first, int pos);
element * zamiana(element *lista,int i,int j);
int maxlista(element *lista);
int wybor(element *lista);
element * usunjeden(element *lista);
void wyswietl2(element * first);
element * sortuj(element *first);
element *generuj(element *lista);
element * wczytaj(element *first,plik asdf,char *nazwa, int i, int counter);
int checkplik (plik asdf,char * nazwa);
void zapisz(element *first,plik asdf,char *nazwa ,int czywczytano);






element * generuj(element *lista)
{
    int ileznakow=0;
    int znak;
    int j=0;

    element *temp;
    temp=(element *)malloc(sizeof(element));

         ileznakow=(rand()%14)+1;

        for(j=0;j<15;j++)
        {
            temp->nazwa[j]=0;
        }

        for(j=0;j<ileznakow;j++)
        {
         znak=(rand()%26)+97;

         temp->nazwa[j]=znak;
        }

        return  dodajlosowo(lista,temp);

}


element * dodaj(element *first)
{
        element *temp;
        temp=(element *)malloc(sizeof(element));
        temp->next=NULL;

if(maxlista(first)>0)
    {
    temp->prev=pozycja(first,maxlista(first)-1);


        printf("podaj napis:");
        scanf("%s",temp->nazwa);
        return push(first,temp);
        usun(temp);

    }
    else
    {
        temp->prev=NULL;
        printf("podaj napis:");
        scanf("%s",temp->nazwa);
        return push(first,temp);
        usun(temp);

    }


}



element * dodajlosowo(element *first, element *temp)
{
        temp->next=NULL;

if(maxlista(first)>0)
    {
    temp->prev=pozycja(first,maxlista(first)-1);

        return push(first,temp);
        usun(temp);

    }
    else
    {
        temp->prev=NULL;
        return push(first,temp);
        usun(temp);

    }


}




element * push(element * first, element * newone)
{
        element * temp=first;
        if(first==NULL)
    {
                return newone;
    }
        while(temp->next!=NULL)
    {
                temp=temp->next;
    }
        temp->next=newone;
        return first;
}

element * usun(element * first)
{
        if(first==NULL)
                return NULL;
        usun(first->next);
        free(first);
        free(first->prev);
        return NULL;
}

void wyswietl(element * first)
{
        int i=0;
        element *temp=first;
        printf("\n");

        if(first==NULL)
        {
                printf("Brak elementow na liscie\n");
                return ;
        }
        else
    {
    do
        {
        printf("%d - %s\n",i++,temp->nazwa);
                temp=temp->next;



        }while(temp!=NULL);

        }
    free(temp);

}

void wyswietl2(element * first)
{
        int i=0;
        element *temp=pozycja(first,maxlista(first)-1);
        printf("\n");

        if(first==NULL)
        {
                printf("Brak elementow na liscie\n");
                return ;
        }
        else
    {

    do
        {
        printf("%d - %s\n",maxlista(first)-i-1,temp->nazwa);
                temp=temp->prev;

                i++;



        }while(temp!=NULL);

        }
    free(temp);

}

void menuglowne(element *lista, plik asdf)
{
        int koniec=0;
        int znak;
        int ile=0;
        int i=0;
        int j=0;
        int k=0;
        int czywczytano=0;
        char znaczek;
        char nazwa[15];
        int counter=0;

        komendymenuglownego();

        while(koniec!=1)
        {
                scanf("%d",&znak);
                switch (znak)
                {
                case 1:
                        lista=dodaj(lista);
                        komendymenuglownego();
                        break;
                case 2:
                        wyswietl(lista);
                        komendymenuglownego();
                        break;
                    case 3:
                        wyswietl2(lista);
                        komendymenuglownego();
                        break;
                    case 4:

if(maxlista(lista)>=2)
    {
    printf("Ktore elementy chcesz zamienic?\npierwszy:");
    i=wybor(lista);
    printf("drugi:");
    j=wybor(lista);

 if(i>j)
     {
         j=k;
         j=i;
         i=k;
     }

                        lista=zamiana(lista,i,j);
                        komendymenuglownego();
                        }
                    else
                    {
                        printf("za malo elementow lub lista pusta\n");
                        komendymenuglownego();
                    }
                        break;
                    case 5:
                    if(maxlista(lista)>=2)
                        {
                        lista=sortuj(lista);
                        komendymenuglownego();
                        }
                        else
                        {
                        printf("za malo elementow lub lista pusta\n");
                        komendymenuglownego();
                        }
                        break;
                    case 6:
                        lista=usunjeden(lista);
                        komendymenuglownego();
                        break;
                     case 7:
                        lista=usun(lista);
                        komendymenuglownego();
                        break;

                    case 8:
                        printf("ile elementow wygenerowac?\n");
                        scanf("%d",&ile);
                        for(i=0;i<ile;i++)
                        {
                        lista=generuj(lista);
                        }
                        komendymenuglownego();
                        break;
                      case 9:


       printf("podaj nazwe pliku:");
       scanf("%s",nazwa);
         strcat(nazwa,".asdf");
        if(checkplik(asdf,nazwa))
        {
    asdf=fopen(nazwa,"rb");
       while((znaczek=getc(asdf))!=EOF)
                {
               if(znaczek=='\n') counter++;
                }
          fclose(asdf);

                         for(i=1;i<counter;i++)
                         {
                        lista=wczytaj(lista,asdf,nazwa,i,counter);
                         }

        }
        else
        {
                printf("nie ma takiego pliku lub plik nieprawidlowego typu\n");
                 wczytaj(lista,asdf,nazwa,i,counter);
        }
                        czywczytano=1;
                         counter=0;
                        komendymenuglownego();
                        break;
                     case 10:
                        zapisz(lista,asdf,nazwa,czywczytano);
                        komendymenuglownego();
                        break;
                     case 11:
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
        printf("1-dodaj\n");
        printf("2-wyswietl od poczatku\n");
         printf("3-wyswietl od konca\n");
        printf("4-zamiana miejscami\n");
        printf("5-sortowanie\n");
        printf("6-usun wybrany element \n");
         printf("7-usun cala liste\n");
         printf("8-generuj liste\n");
        printf("9-wczytaj\n");
        printf("10-zapisz\n");
         printf("11-koniec\n");


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
element * zamiana(element *lista,int i,int j)
{


    element *temp=pozycja(lista,i);
    element *temp2=pozycja(lista,j);
    element *temp3=pozycja(lista,j)->next;
    element *temp4=pozycja(lista,i)->prev;
    element *temp5=pozycja(lista,j)->prev;



    if(i==0  && j!=1)
    {
    pozycja(lista,j)->next=temp->next;

    if(pozycja(lista,j)->prev!=NULL) pozycja(lista,j)->prev->next=temp;
    pozycja(lista,i)->next=temp3;
    if(pozycja(lista,i)->prev!=NULL) pozycja(lista,i)->prev->next=temp2;
    else lista=temp2;




    if(pozycja(lista,j)->next!=NULL) pozycja(lista,j)->next->prev=temp;
    pozycja(lista,j)->prev=temp5;

    if(pozycja(lista,i)->next!=NULL) pozycja(lista,i)->next->prev=temp2;
    pozycja(lista,i)->prev=temp4;


    }
    else if(j-i>1)
    {
    pozycja(lista,j)->next=temp->next;
    if(pozycja(lista,j)->prev!=NULL) pozycja(lista,j)->prev->next=temp;
    pozycja(lista,i)->next=temp3;
    if(pozycja(lista,i)->prev!=NULL) pozycja(lista,i)->prev->next=temp2;

    if(pozycja(lista,j)->next!=NULL) pozycja(lista,j)->next->prev=temp;
    pozycja(lista,j)->prev=temp5;
    if(pozycja(lista,i)->next!=NULL) pozycja(lista,i)->next->prev=temp2;
    pozycja(lista,i)->prev=temp4;
    }
    else if(j-i==1 && i!=0 && j!=maxlista(lista)-1)
    {
    pozycja(lista,j)->prev->next=temp;
    pozycja(lista,j)->next=temp3;

    pozycja(lista,i)->prev->next=temp2;
    pozycja(lista,i)->next=temp;

   pozycja(lista,j)->next->prev=temp;
   pozycja(lista,j)->prev=temp2;
   pozycja(lista,i)->prev=temp4;
    }
    else if(i==0 && j==1)
    {



    lista=temp2;
    pozycja(lista,i)->next=temp;
    pozycja(lista,j)->next=temp3;
     pozycja(lista,i)->prev=NULL;
    pozycja(lista,j)->next->prev=temp;
   pozycja(lista,i)->next->prev=temp2;


    }
    else if(j==maxlista(lista)-1 && i==maxlista(lista)-2)
    {
         pozycja(lista,j)->next=temp;
        pozycja(lista,i)->next=NULL;
        pozycja(lista,i)->prev->next=temp2;

        pozycja(lista,i)->next->prev=temp2;
        pozycja(lista,i)->prev=temp4;
    }


return lista;


}

int maxlista(element *lista)
{
        element *temp=lista;
        int counter=0;
        if(lista==NULL)
        {
                return 0;
        }
        do
        {

                counter++;
                temp=temp->next;

        }while(temp!=NULL);
        usun(temp);
        return counter;
}

int wybor(element *lista)
{
        if(lista!=NULL)
        {
                int poz=0;
                if((maxlista(lista)-1)!=0)
                {
                        scanf("%d",&poz);
                        if( poz<=maxlista(lista)-1 && poz>=0) return poz;
                        else
                        {
                                printf("wartosc spoza zakresu\n");
                                return wybor(lista);

                        }
                }
                else return 0;
        }
         else return 0;
}

element *usunjeden(element *lista)
{
    int poz=0;
    if(lista!=NULL)
    {

    printf("Ktory element chcesz usunac?\n");
    poz=wybor(lista);
    element *temp=pozycja(lista,poz);

    if(pozycja(lista,poz)->next) pozycja(lista,poz)->next->prev=pozycja(lista,poz)->prev;
    if(pozycja(lista,poz)->prev)pozycja(lista,poz)->prev->next=pozycja(lista,poz)->next;
    else lista=pozycja(lista,poz)->next;
    free(temp);
    }
    else printf("Brak elementow na liscie\n");

return lista;
}



element * sortuj(element *lista)
{

    int i=0,j=0,k=0,dlugosc=0,check=0;

    for(i=0;i<maxlista(lista);i++)
    {
       for(j=0;j<maxlista(lista);j++)
       {
         if(strlen(pozycja(lista,j+1)->nazwa)<strlen(pozycja(lista,j)->nazwa)) dlugosc=strlen(pozycja(lista,j+1)->nazwa);
         else dlugosc=strlen(pozycja(lista,j)->nazwa);
         check=0;
        for(k=0;k<=dlugosc;k++)
        {
          if(pozycja(lista,j)->nazwa[k]>pozycja(lista,j+1)->nazwa[k] && check==0)
           {
             lista=zamiana(lista,j,j+1);
                check=1;
           }
        else if(pozycja(lista,j)->nazwa[k]<pozycja(lista,j+1)->nazwa[k] && check==0) check=1;

        }
       }
    }
return lista;
}

element * wczytaj(element *first,plik asdf,char* nazwa,int i , int counter)
{
        element *temp;
        int j=0;
        char znak=NULL;
        temp=(element *)malloc(sizeof(element));

        asdf=fopen(nazwa,"rb");

while(j!=i)
{
    znak=getc(asdf);
    while(znak!='\n')
    {
    znak=getc(asdf);
    }
    j++;
}
fscanf(asdf,"%s",temp->nazwa);
fclose(asdf);
return first=dodajlosowo(first,temp);
}

int checkplik (plik asdf, char *nazwa)
{
    char napis[15];
     asdf=fopen(nazwa,"rb");

    if (asdf!=NULL)
    {
        fscanf(asdf,"%s",napis);
        if (strcmp(napis,"$asdf$")==0)
        {
            return 1;
            fclose(asdf);
        }
        else
        {
             fclose(asdf);
            return 0;

        }

    }
    else
    {
        fclose(asdf);
         return 0;
    }

}

void zapisz(element *first,plik asdf, char* nazwa, int czywczytano)
{
        int i=0;
        int znak;
        if(first==NULL)
        {
                printf("brak listy do zapisania\n");
        }
        else
        {
if(czywczytano==0)
{
    printf("podaj nazwe pliku:");
       scanf("%s",nazwa);
        strcat(nazwa,".asdf");
         asdf=fopen(nazwa,"wb");
         fprintf(asdf,"$asdf$\n");

         for(i=0;i<maxlista(first);i++)
         {
            fprintf(asdf,"%s\n",pozycja(first,i)->nazwa);

        }
        fclose(asdf);

}
else if(czywczytano==1)
{
      printf("\n1-nadpisac obecny plik?\n2-zapisac jako odrebny?\n");
                        getchar();
                        znak=getchar();
                        if(znak=='1')
                        {
                             asdf=fopen(nazwa,"wb");
                            fprintf(asdf,"$asdf$\n");
         for(i=0;i<maxlista(first);i++)
         {
            fprintf(asdf,"%s\n",pozycja(first,i)->nazwa);
        }
        fclose(asdf);
                        }
                        else if(znak=='2')
                        {
                           printf("podaj nazwe pliku:");
       scanf("%s",nazwa);
       strcat(nazwa,".asdf");
         asdf=fopen(nazwa,"wb");
         fprintf(asdf,"$asdf$\n");
         for(i=0;i<maxlista(first);i++)
         {
            fprintf(asdf,"%s\n",pozycja(first,i)->nazwa);
        }
        fclose(asdf);
                        }
                else printf ("niepoprawne polecenie\n");
}


}
}
#endif // HEADER_H_INCLUDED

