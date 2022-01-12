#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LEN 128
#define MAX 1024

struct _Country;
typedef struct _Country* Pointer;
typedef struct _Country {
	char name[MAX_LEN];
    Pointer next;
    int population;
}Country;

struct _City;
typedef struct _City* Position;
typedef struct _City {
	char name[MAX_LEN];
    Pointer next;
	Position Left;
	Position Right;
}City;

Position CreateNewCountry(char* name);
Pointer CreateNewCity(char* name, int pop);
Pointer AddCity(Position p, Position newElement);
Position AddCountry(Pointer head, Pointer newElement);
int ReadCountriesFromFile(char* fileName, Pointer p);
Position ReadCitiesFromFile(char* fileName, Pointer p);
int PrintCities(Position p);
int PrintList(Pointer first);
Position FindCountry(char* name, Pointer first);
int FindMorePopulated(Position city, int population);
int FindMorePopulatedCountry(Pointer country, int n);

int main()
{
    list head={.next=NULL, .name={0}, .root=NULL};
    Pointer pHead=&head;

    int situation=0;
    
    while(1)
    {
        printf("\n1 -> Read from a file\n"
                "2 -> Print everything\n"
                "3 -> Print cities in a country with a population over n\n"
                "4 -> Exit\n");
        scanf(" %d",  situation);
        switch (situation)
        {
            case 1:
            {
                char str[20]="0";
                printf("Enter the name of the .txt file you wish to read from:\n");
                scanf(" %s", str);
                if(strlen(str)>4&&strcmp(&str[strlen(str)-4],".txt"))
                    strcat(str, ".txt");
                ReadCountriesFromFile(str, pHead);
             situation=0;
                break;
            }
            case 2:
            {
            PrintList(pHead->next);
             situation=0;
                break;
            }
            case 3:
            {
                char str[20]="0";
                int n=0;
                printf("Enter the name of the country and the population:\n");
                scanf(" %s %d", str, &n);
                FindMorePopulatedCountry(FindCountry(str, pHead->next), n);
             situation=0;
                break;
            }
            default:
            {
                printf("\n");
                printf("Wrong input. Try again.\n");
             situation=0;
                break;
            }
        }
    }
    
    return -1;
}
Position CreateNewCountry(char* name)
{
    Position newCountry=NULL;
    
    newCountry=(Position)malloc(sizeof(Country));
    if(!newCountry)
    {
        printf("Couldn't allocate memory.\n");
        return NULL;
    }
    
    strcpy(newCountry->name, name);
    newCountry->next=NULL;
    newCountry->Right=NULL;
    newCountry->Left=NULL;

    return newCountry;
}

Pointer CreateNewCity(char* name, int population)
{
    Pointer newCity=NULL;
    
    newCity=(Pointer)malloc(sizeof(City));
    if(!newCity)
    {
        printf("Couldn't allocate memory.\n");
        return NULL;
    }
    
    strcpy(newCity->name, name);
    newCity->next=NULL;
    newCity->population=population;
    newCountry->Right=NULL;
    newCountry->Left=NULL;  
    return newCity;
}

Pointer AddCity(Position p, Position newElement)
{
    Pointer temp=NULL;
    
    if(!p)
        return newElement;
    
    temp=p;
    while(1)
    {
        if(temp->next!=NULL&&(temp->next->pop<newElement->pop||temp->next->pop==newElement->pop&&strcmp(temp->next->name, newElement->name)<0))
            temp=temp->next;
        else 
            break;
    }
    if(temp->next==NULL)
        temp->next=newElement;
    
    else if(strcmp(newElement->name, temp->next->name)==0)
        free(newElement);
        return NULL;

    else
        newElement->next=temp->next;
        temp->next=newElement;
    
    return NULL;
}


Position AddCountry(Pointer head, Pointer newElement)
{
    if(p == NULL)
        return newElement;

    else if(strcmp(p->name, "0")==0)
    {
        strcpy(p->name, newElement->name);
        p->Left=newElement->Left;
        p->Right=newElement->Right;
        p->next=newElement->next;
        free(newElement);
    }
    else if(strcmp(p->name, newElement->name)>0)
        p->Left=AddCountry(p->Left,newElement);
    
    else if(strcmp(p->name, newElement->name)<0)
        p->Right=AddCountry(p->Right,newElement);
    
    else
        free(newElement);
    
    return p;
}

int ReadCountriesFromFile(char* fileName, Position p)
{
    Position temp=NULL;
    char buffer[MAX_SIZE]={0};
    char name[128]={0};
    char fName[128]={0};
    
	FILE* f=NULL;
    f=fopen(fileName, "r");
    if(f==NULL)
        perror("File not found!");
		return EXIT_FAILURE;
    
    while(!feof(f))
    {
        fgets(buffer, MAX, f);
        if(sscanf(buffer, " %s %s", name, fName)==2)
        {
           temp=CreateNewCountry(name);
            ReadCitiesFromFile(fName, temp);
            AddCountry(p, temp);
        }
    }
    
    fclose(f);
    
    temp=p->next;
    pFiles=pFiles->next;
    while(pFiles)
    {
        ReadCitiesFromFile(pFiles->name, temp);
        pFiles=pFiles->next;
        temp=temp->next;
    }    
    return 0;
}

Position ReadCitiesFromFile(char* fileName, Pointer p)
{
    char buffer[MAX_SIZE]={0};
    char name[128]={0};
    int population=0;
	Position newCity=NULL;

    FILE* f=NULL;
    f=fopen(fileName, "r");

    if(f==NULL)
        perror("File not found!");
		return EXIT_FAILURE;
    
    while(!feof(f))
    {
        fgets(buffer, MAX, f);
        if(sscanf(buffer, " %s %d", name, &population)==2)
         Pointer temp=CreateNewCity(name, population);
            if(!p->next)
                p->next=temp;
            else if(p->next->pop>temp->pop)
                temp->next=p->next;
                p->next=temp;
        
            else if(p->next->pop==temp->pop&&strcmp(p->next->name, name)>0)
                temp->next=p->next;
                p->next=temp;

            else
                AddCity(p->next, temp);
        }
    }
    
    fclose(f);
    
    return p->root;
}
int PrintCities(Position p)
{
	if(!p)
        return 0;
    printf("\t%-12s %d\n", p->name, p->population);
    PrintCities(p->next);
    return 0;
}

int PrintList(Pointer p)
{
	if(!p||strcmp(p->name, "0")==0)
        return 0;
    PrintAll(p->Left);
    printf("%s:\n", p->name);
    PrintCities(p->next);
    PrintAll(p->Right);
    
    return 0;
}
Position FindCountry(char* name, Position first)
{
    Position temp=first;

    if(strcmp(temp->name, name)==0)
        return temp;
    else if(strcmp(temp->name, name)<0)
        temp=FindCountry(name, temp->Right);
    else if(strcmp(temp->name, name)>0)
        temp=FindCountry(name, temp->Left);
        
    return temp;
}
int FindMorePopulated(Position city, int population)
{
	int cityNumber = 0;
	if (city->population > population) {
		cityNumber++;
		printf("\t%s %d\n", city->name, city->population);
		if (city->Right != NULL) PrintCities(city->Right);
		cityNumber += FindMorePopulated(city->Left, population);
	}
	else return cityNumber;
}
int FindMorePopulatedCountry(Pointer country, int n)
{
    if(!country)
        perror("There is no such country on the list.\n");
        return EXIT_FAILURE;
    
    FindMorePopulated(country->root, n);
    
    return 0;
}