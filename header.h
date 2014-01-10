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
void usunjeden(element *temp);
void inittab(element *temp);
int wybor(element *lista);
int maxlista(element *lista);

void wyswietl(element * first);
void menuglowne(element *first,plik obraz);
void komendymenuglownego();
void wyswietlinfo(element *first);

int  zakres(int wartosc, int max);
void podmianatablicy(element *first,element *temp);

void wykryjkrawedz(element *first);
void negatyw(element *first);
void rozmycie(element *first);
void cien(element *first);
void zmienrozmiar(element *first);
void obrot(element *first);
void obrot90(element *first);
void obrot180(element *first);
void obrot270(element *first);
void komendyobrotu();

void zapisz(element *first,plik obraz, int trybzapisu);
void zapiskoncowy(element *first,plik obraz);




void menuglowne(element *lista, plik obraz)
{
        int koniec=0;
        int znak;

        komendymenuglownego();

        while(koniec!=1)
        {
                scanf("%d",&znak);
                switch (znak)
                {
                case 1:
                        lista=dodaj(lista,obraz);
                        komendymenuglownego();
                        break;
                case 2:
                        wyswietlinfo(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 31:
                        negatyw(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 32:
                        wykryjkrawedz(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 33:
                        rozmycie(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 41:
                        cien(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 42:
                        zmienrozmiar(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 43:
                        obrot(pozycja(lista,wybor(lista)));
                        komendymenuglownego();
                        break;
                case 5:
                        zapisz((pozycja(lista,wybor(lista))),obraz,0);
                        komendymenuglownego();
                        break;

                case 6:
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
        printf("31-negatyw\n");
        printf("32-krawedzie\n");
        printf("33-rozmycie\n");
        printf("41-zmiany cieniowania\n");
        printf("42-zmien rozmiar\n");
        printf("43-obroc\n");
        printf("5-zapisz\n");
        printf("6-zakoncz\n");
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
        int i=0;
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
        int flag=0;
        int licznik=0;
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
                else
                {
                        printf("blad odczytu pliku\n");
                        return first;
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
                fseek(obraz,-3,SEEK_CUR);
                if(temp->tryb==1)
                {
                        fscanf(obraz,"%d%d",&temp->rozmiarx,&temp->rozmiary);
                        temp->odcien=1;

                        inittab(temp);

                        for(i=0;i<temp->rozmiary;i++)
                                for(j=0;j<temp->rozmiarx;j++)
                                {
                                        if(fscanf(obraz,"%d",&temp->tab[i][j])) licznik++;
                                        if(temp->tab[i][j]<0) 
                                        {
                                                temp->tab[i][j]=0;
                                                flag=1; // male naprawianie niepoprawnych plikow
                                        }
                                        if(temp->tab[i][j]>1) 
                                        {
                                                temp->tab[i][j]=1;
                                                flag=1;
                                        }

                                }
                                if(licznik==temp->rozmiarx*temp->rozmiary) 
                                {
                                        if(flag==1) printf("\nplik zawieral dane spoza dozwolonego zakresu\nzostaly one przyblizone do najblizszych prawidlowych\nzalecane sprawdzenie pliku\n");
                                        return push(first,temp);
                                }
                                else
                                {
                                        printf("blad odczytu pliku\n");
                                        return first;
                                }
                }
                else if(temp->tryb==2)
                {
                        fscanf(obraz,"%d%d",&temp->rozmiarx,&temp->rozmiary);
                        fscanf(obraz,"%d",&temp->odcien);
                        inittab(temp);

                        for(i=0;i<temp->rozmiary;i++)
                                for(j=0;j<temp->rozmiarx;j++)
                                {
                                        if(fscanf(obraz,"%d",&temp->tab[i][j])) licznik++;
                                        if(temp->tab[i][j]<0) 
                                        {
                                                temp->tab[i][j]=0;
                                                flag=1; // male naprawianie niepoprawnych plikow
                                        }
                                        if(temp->tab[i][j]>temp->odcien) 
                                        {
                                                temp->tab[i][j]=temp->odcien;
                                                flag=1;
                                        }

                                }

                                if(licznik==temp->rozmiarx*temp->rozmiary)
                                {
                                        if(flag==1) printf("\nplik zawieral dane spoza dozwolonego zakresu\nzostaly one przyblizone do najblizszych prawidlowych\nzalecane sprawdzenie pliku\n");
                                        return push(first,temp);

                                }
                                else
                                {
                                        printf("blad odczytu pliku\n");
                                        return first;
                                }
                }
                else
                {
                        printf("blad odczytu pliku\n");
                        return first;
                }

        }
        else
        {
                printf("nie ma takiego pliku\n");
                return dodaj(first,obraz);
        }
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
                printf("\n%s\nP%d\nrozmiary: %d\nrozmiarx:%d\n",first->nazwa,first->tryb,first->rozmiary,first->rozmiarx);

                if(first->tryb==1) printf("czarno-bialy\nczy zapisano:");
                if(first->tryb==2) printf("liczba odcieni szarosci:%d\nczy zapisano:",first->odcien);
                if(first->czyzapisano==1) printf("tak\n");
                if(first->czyzapisano==0) printf("nie\n");
        }
}


void wykryjkrawedz(element *first)
{
        int i=0,j=0,k=0,m=0;


        if(first==NULL)
        {
                printf("brak plikow do przetworzenia\n");
        }
        else
        {
                element *temp;
                element *temp2;
                int stala=0;
                temp=(element *)malloc(sizeof(element));
                temp2=(element *)malloc(sizeof(element));
                temp->rozmiarx=first->rozmiarx;
                temp->rozmiary=first->rozmiary;//sam podaje rozmiary bo moge potrzebowac tymczasowej np odwroconej
                temp2->rozmiarx=first->rozmiarx;
                temp2->rozmiary=first->rozmiary;
                inittab(temp);
                inittab(temp2);
                negatyw(first);


                /*filtr sklada sie z dwoch czesci .
                1 to filtr cieniowany , wychodza grube krawedzie , ale uzwgledni roznice w odcieniach (krawedzie roznych barw) ,
                2 czesc to filtr czarno-bialy, ktory odchudza powstale krawedzie i zostawia czarne brzegi rysunku
                */

                //CZESC I
                for(i=0;i<first->rozmiary;i++)//przypisanie wartosc do temp , temp2
                        for(j=0;j<first->rozmiarx;j++)
                        {
                                temp->tab[i][j]=first->tab[i][j];
                                temp2->tab[i][j]=first->tab[i][j];
                                stala=stala+first->tab[i][j];
                        }
                        stala=stala/(first->rozmiarx*first->rozmiary); // dobierane dla dobrych efektow



                        for(i=0;i<first->rozmiary;i++)
                        {
                                for(j=0;j<first->rozmiarx;j++)
                                {
                                        if( j>0 && i>0 && i<first->rozmiary-1 && j<first->rozmiarx-1)
                                        {
                                                for(k=j;k<j+1;k++)//sprawdzanie czy krawedz w 3x3 , przypisanie zmian do temp2
                                                {
                                                        for(m=i;m<i+1;m++)
                                                        {
                                                                if(temp->tab[m-1][k]!=temp->tab[m+1][k]);
                                                                else if (temp->tab[m][k-1]!=temp->tab[m][k+1]);
                                                                else if (  temp->tab[m][k-1]==temp->tab[m][k+1] && temp->tab[m][k-1]!=temp->tab[m][k]);
                                                                else if (temp->tab[m-1][k]==temp->tab[m+1][k] && temp->tab[m-1][k]!=temp->tab[m][k]);
                                                                else temp2->tab[i][j]=0;
                                                        }
                                                }

                                                for(k=j;k<j+1;k++)//powrot wartosci w temp
                                                        for(m=i;m<i+1;m++)
                                                                temp->tab[i][j]=first->tab[i][j];
                                        }
                                }
                        }

                        for(i=0;i<first->rozmiary;i++)
                        {
                                for(j=0;j<first->rozmiarx;j++)
                                {
                                        first->tab[i][j]=temp2->tab[i][j];
                                }


                        }


                        //CZESC II
                        for(i=0;i<first->rozmiary;i++)
                        {
                                for(j=0;j<first->rozmiarx;j++)
                                {
                                        if(first->tab[i][j]<=stala)
                                        {
                                                first->tab[i][j]=first->tab[i][j]-first->odcien;
                                                if(first->tab[i][j]<0) first->tab[i][j]=0;
                                        }
                                        else if(first->tab[i][j]>stala)
                                        {
                                                first->tab[i][j]=first->tab[i][j]+first->odcien;
                                                if(first->tab[i][j]>first->odcien) first->tab[i][j]=first->odcien;
                                        }

                                }

                        }


                        for(i=0;i<first->rozmiary;i++)
                                for(j=0;j<first->rozmiarx;j++)
                                        temp->tab[i][j]=first->tab[i][j];





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
                                for(j=0;j<first->rozmiarx;j++)
                                        first->tab[i][j]=temp->tab[i][j];

                        negatyw(first);
                        usunjeden(temp);
                        usunjeden(temp2);
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

                        }


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
        element *temp;
        temp=(element *)malloc(sizeof(element));
        temp->rozmiarx=first->rozmiary;
        temp->rozmiary=first->rozmiarx;
        x=temp->rozmiarx-1;
        inittab(temp);


        for(i=0;i<temp->rozmiary;i++)
                for(j=0;j<temp->rozmiarx;j++)
                        temp->tab[i][x-j]=first->tab[j][i];//obrot 90 w prawo

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
                for(j=0;j<first->rozmiarx;j++)
                        temp->tab[y-i][x-j]=first->tab[i][j];//obrot 180

        podmianatablicy(first,temp);
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
                for(j=0;j<temp->rozmiarx;j++)
                        first->tab[i][j]=temp->tab[i][j];




}

void obrot270(element *first)
{
        int i=0,j=0;

        int y;
        element *temp;
        temp=(element *)malloc(sizeof(element));
        temp->rozmiarx=first->rozmiary;
        temp->rozmiary=first->rozmiarx;
        y=temp->rozmiary-1;
        inittab(temp);


        for(i=0;i<temp->rozmiary;i++)
                for(j=0;j<temp->rozmiarx;j++)
                        temp->tab[y-i][j]=first->tab[j][i];//obrot 90 w lewo

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
                                return wybor(lista);

                        }
                }
                else return 0;
        }
        else return 0;
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
                printf("niepoprawna wartosc\n");
                return zakres(wartosc,max);
        }
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

void cien(element *first)
{
        if(first==NULL || first->tryb==1)
        {
                printf("brak plikow do przetworzenia lub obraz czarno-bialy\n");
        }
        else
        {
                int j=0,i=0;
                int kierunek=0;
                int kontrast=0;//zeby nie tworzyc nowej zmiennej kontrast posluzy tez do zmiany jasnosci
                printf("\n0-zmniejsz kontrast\n1-zwieksz kontrast\n2-rozjasnij obraz\n3-przyciemnij obraz\n");
                kierunek=zakres(kierunek,3);
                printf("liczba odcieni szarosci:%d\n",first->odcien);
                if(kierunek==0) printf("podaj o ile odcieni zmniejszyc kontrast\n");
                if(kierunek==1) printf("podaj o ile odcieni zwiekszyc kontrast\n");
                if(kierunek==2) printf("podaj o ile odcieni rozjasnic obraz\n");
                if(kierunek==3) printf("podaj o ile odcieni przyciemnic obraz\n");
                kontrast=zakres(kontrast,first->odcien);

                if(kierunek==0 || kierunek==1)
                {
                        for(i=0;i<first->rozmiary;i++)
                        {
                                for(j=0;j<first->rozmiarx;j++)
                                {
                                        if(first->tab[i][j]<=(first->odcien/2))
                                        {
                                                if(kierunek==0)
                                                {
                                                        first->tab[i][j]=first->tab[i][j]+kontrast;
                                                        if(first->tab[i][j]>first->odcien) first->tab[i][j]=first->odcien;
                                                }
                                                else if(kierunek==1)
                                                {
                                                        first->tab[i][j]=first->tab[i][j]-kontrast;
                                                        if(first->tab[i][j]<0) first->tab[i][j]=0;
                                                }



                                        }
                                        else if(first->tab[i][j]>(first->odcien/2))
                                        {
                                                if(kierunek==0)
                                                {
                                                        first->tab[i][j]=first->tab[i][j]-kontrast;
                                                        if(first->tab[i][j]<0) first->tab[i][j]=0;
                                                }
                                                else if(kierunek==1)
                                                {
                                                        first->tab[i][j]=first->tab[i][j]+kontrast;
                                                        if(first->tab[i][j]>first->odcien) first->tab[i][j]=first->odcien;
                                                }
                                        }

                                }

                        }
                }
                if(kierunek==2 || kierunek==3)
                {
                        for(i=0;i<first->rozmiary;i++)
                        {
                                for(j=0;j<first->rozmiarx;j++)
                                {

                                        if(kierunek==2)
                                        {
                                                first->tab[i][j]=first->tab[i][j]+kontrast;
                                                if(first->tab[i][j]>first->odcien) first->tab[i][j]=first->odcien;
                                        }
                                        else if(kierunek==3)
                                        {
                                                first->tab[i][j]=first->tab[i][j]-kontrast;
                                                if(first->tab[i][j]<0) first->tab[i][j]=0;
                                        }



                                }

                        }
                }
        }
}

void zmienrozmiar(element *first)
{
        if(first==NULL)
        {
                printf("brak plikow do przetworzenia\n");
        }
        else
        {
                int x=0,y=0;
                int j=0,i=0;
                int p=0,k=0;
                double ratiox=0,ratioy=0;
                element *temp;
                temp=(element *)malloc(sizeof(element));

                printf("podaj wymiary nowego obrazu:\nrozmiar X =");
                x=zakres(x,10000);
                printf("rozmiar Y =");
                y=zakres(y,10000);

                temp->rozmiarx=x;
                temp->rozmiary=y;
                inittab(temp);
                ratiox=(double)first->rozmiarx/x;
                printf("ratiox:%lf\n",ratiox);
                ratioy=(double)first->rozmiary/y;
                printf("ratioy:%lf\n",ratioy);

                for(i=0;i<temp->rozmiary;i++)
                {
                        for(j=0;j<temp->rozmiarx;j++)
                        {
                                p=(int)(j*ratiox);
                                k=(int)(i*ratioy);
                                if(p>=first->rozmiarx) p=first->rozmiarx;
                                if(k>=first->rozmiary) k=first->rozmiary;
                                temp->tab[i][j]=first->tab[k][p];


                        }

                }
                podmianatablicy(first,temp);
                usunjeden(temp);
                first->czyzapisano=0;
        }
}

void rozmycie(element *first)
{
        int i=0,j=0,m=0,k=0;
        int srednia=0;
        int odleglosc=0;

        if(first==NULL || first->tryb==1)
        {
                printf("brak plikow do przetworzenia lub obraz czarno-bialy\n");
        }
        else
        {
                element *temp;
                temp=(element *)malloc(sizeof(element));
                temp->rozmiarx=first->rozmiarx;
                temp->rozmiary=first->rozmiary;
                inittab(temp);
        
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

                                if( j>1 && i>1 && i<first->rozmiary-2 && j<first->rozmiarx-2)
                                {
                                        for(k=j-2;k<j+3;k++)
                                        {
                                                for(m=i-2;m<i+3;m++)
                                                {
                                                        if(m>i) odleglosc=odleglosc+m-i;
                                                        if(m<=i) odleglosc=odleglosc+i-m;
                                                        if(k>j) odleglosc=odleglosc+k-j;
                                                        if(k<=j) odleglosc=odleglosc+j-k;

                                                        if(odleglosc==0) srednia=srednia+8*(temp->tab[m][k]);
                                                        else if(odleglosc==1) srednia=srednia+4*(temp->tab[m][k]);
                                                        else if(odleglosc==2 &&(m==i || k==j)) srednia=srednia+2*temp->tab[m][k];
                                                        else if(odleglosc==2) srednia=srednia+2*temp->tab[m][k];
                                                        else if(odleglosc==3) srednia=srednia+1*temp->tab[m][k];
                                                        else if(odleglosc==4) srednia=srednia+1*temp->tab[m][k];

                                                        odleglosc=0;
                                                }
                                        }
                                        srednia=srednia/(8+4*4+2*8+12*1);
                                        temp->tab[i][j]=srednia;
                                        srednia=0;
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
                
                usunjeden(temp);
                first->czyzapisano=0;
        }
}

#endif // HEADER2_H
