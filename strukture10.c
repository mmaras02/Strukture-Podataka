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
	Position root;
	Pointer next;
}Country;

struct _City;
typedef struct _City* Position;
typedef struct _City {
	char name[MAX_LEN];
	int population;
	Position Left;
	Position Right;
}City;

Pointer CreateNewCountry(char* name);
Position CreateNewCity(char* name, int pop);
Position AddCity(Position p, Position newElement);
int AddCountry(Pointer head, Pointer newElement);
int ReadCountriesFromFile(char* fileName, Pointer p);
Position ReadCitiesFromFile(char* fileName, Pointer p);
int PrintCities(Position p);
int PrintList(Pointer first);
Pointer FindCountry(char* name, Pointer first);
int PrintCountryBiggerThan(Pointer country, int n);
int PrintCitiesBiggerThan(Position p, int n);

int main()
{
    Country head={.next=NULL, .name={0}, .root=NULL};
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
                PrintCountryBiggerThan(FindCountry(str, pHead->next), n);
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
Pointer CreateNewCountry(char* name)
{
    Pointer newCountry=NULL;
    
    newCountry=(Pointer)malloc(sizeof(Country));
    if(!newCountry)
    {
        printf("Couldn't allocate memory.\n");
        return NULL;
    }
    
    strcpy(newCountry->name, name);
    newCountry->next=NULL;
    newCountry->root=NULL;
    
    return newCountry;
}

Position CreateNewCity(char* name, int population)
{
    Position newCity=NULL;
    
    newCity=(Position)malloc(sizeof(City));
    if(!newCity)
    {
        printf("Couldn't allocate memory.\n");
        return NULL;
    }
    
    strcpy(newCity->name, name);
    newCity->population=population;
    newCity->Right=NULL;
    newCity->Left=NULL;
    
    return newCity;
}

Position AddCity(Position p, Position newElement)
{
    if(p == NULL)
        return newElement;
	
	else if(p->population<newElement->population)
        p->Right=AddCity(p->Right,newElement);

    else if(p->population>newElement->population)
        p->Left=AddCity(p->Left,newElement);
	
	else if(strcmp(p->name, newElement->name)<0)
        p->Right=AddCity(p->Right,newElement);

    else if(strcmp(p->name, newElement->name)>0)
        p->Left=AddCity(p->Left,newElement);

    else
        free(newElement);
    return p;
}

int AddCountry(Pointer head, Pointer newElement)
{
    Pointer temp=NULL;
    
    temp=head;
    while(1)
    {
        if(temp->next!=NULL&&strcmp(temp->next->name, newElement->name)<0)
            temp=temp->next;
        else 
            break;
    }
    
    
    if(temp->next==NULL)
        temp->next=newElement;

    else if(strcmp(newElement->name, temp->next->name)==0)
        free(newElement);
        return -1;

    else
        newElement->next=temp->next;
        temp->next=newElement;
    
    return 0;
}

int ReadCountriesFromFile(char* fileName, Pointer p)
{
    Pointer temp=NULL;
    char buffer[MAX_LEN]={0};
    char name[128]={0};
    char fName[128]={0};
    Country files={.next=NULL, .name={0}, .root=NULL};
    Pointer pFiles=&files;
    
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
            AddCountry(pFiles, CreateNewCountry(fName));
            AddCountry(p, CreateNewCountry(name));
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
    char buffer[MAX_LEN]={0};
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
        {            
            newCity=CreateNewCity(name, population);
            p->root=AddCity(p->root, newCity);
        }
    }
    
    fclose(f);
    
    return p->root;
}
int PrintCities(Position p)
{
	if(p->Left != NULL) 
		PrintCities(p->Left);
		printf("\t%s %d\n", p->name, p->population);
	if (p->Right != NULL)
		PrintCities(p->Right);

	return EXIT_SUCCESS;
}
int PrintList(Pointer p)
{
	while (p != NULL) {
		printf("%s\n", p->name);
		PrintCities(p->root);
		p = p->next;
	}
	
	return EXIT_SUCCESS;
}
Pointer FindCountry(char* name, Pointer first)
{
    Pointer temp=first;
    while(temp!=NULL&&strcmp(temp->name, name)!=0)
    {
        temp=temp->next;
    }
    return temp;
}

int PrintCountryBiggerThan(Pointer country, int n)
{
    if(!country)
    {
        printf("There is no such country.\n");
        return -1;
    }
    
    PrintCitiesBiggerThan(country->root, n);
    
    return 0;
}

int PrintCitiesBiggerThan(Position p, int n)
{
    if(!p)
        return 0;
    PrintCitiesBiggerThan(p->Right, n);
    if(p->population>=n)
    {
        printf("\t%-12s - %d\n", p->name, p->population);
        PrintCitiesBiggerThan(p->Left, n);
    }
    
    return 0;
}