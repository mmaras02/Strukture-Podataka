#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* position;
typedef struct _Person{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthyear;
    position next;
}Person;

position CreatePerson(char* name,char* surname,int birthyear){
    position NewPerson=NULL;
  
    NewPerson = (position) malloc (sizeof (Person));
    if(!NewPerson){
        perror("can't allocate memory");
        return NULL;
    }
    strcpy(NewPerson->name,name);
    strcpy(NewPerson->surname,surname);
    NewPerson->birthyear=birthyear;
    NewPerson->next=NULL;

    return NewPerson;
}
int InsertAfter(position p,position NewPerson){

    NewPerson->next=p->next;
    p->next=NewPerson;

    return 0;
}
position FindLast(position head){
    position last=head;

    while(last->next!=NULL)
        last=last->next;

    return last;
}
position FindBySurname(position first,char* surname){
    position temp=first;

    while(temp!=NULL && strcmp(temp->surname,surname)!=NULL){
        temp=temp->next;
    if(temp==NULL)
        printf("doesn't exist\n");
        //if((temp->surname,surname)==0){return temp;}
    }
    return temp;
    //while(temp!=NULL && temp->surname=surname){
    //    temp=temp->next;
    //}
    //return temp;
}
position FindPrev(position p,char* surname){
    position prev=p;
    position curr=NULL;

    curr=prev->next;
    while(curr!=NULL && strcmp(curr->surname,surname)!=0){
        prev=curr;
        curr=prev->next;
    }
    if(curr==NULL)
        return NULL;
    return prev;
}
int DeleteAll(position head){
    position temp=NULL;
    
    while (head->next!=NULL)
    {
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    
    return 0;
}

int AddStart(position head,char* name,char* surname,int birthyear){
    position NewPerson=NULL;

    NewPerson = CreatePerson(name,surname,birthyear);

    if(!NewPerson){
        return -1;
    }
    InsertAfter(head,NewPerson);

    return 0;
}

int AddEnd(position head,char* name,char* surname,int birthyear){
    position NewPerson=NULL;
    position last=NULL;

    //NewPerson=(position)malloc(sizeof(Person));
    NewPerson=CreatePerson(name,surname,birthyear);
    if (!NewPerson)
        return -1;

    last=FindLast(head);
    InsertAfter(last,NewPerson);

    return 0;
}

int Delete(position p,char* surname){
    position curr=NULL;
    position prev=NULL;

    prev=FindPrev(p,surname);
    if(prev==NULL)
        return -1;
    curr=prev->next;
    prev->next=curr->next;
    free(curr);
    return 0;
}
int PrintList(position first){
    position temp=first;

    if(!temp)
        printf("list is empty\n");
    while(temp!=NULL){
        printf("Name: %s\tSurmame: %s\tBirth Year: %d\n",temp->name,temp->surname,temp->birthyear);
        temp=temp->next;
    }
    return 0;
}
int AddAfter(position p,char* name,char* surname,int birthyear,char* after){
    position prev=NULL;
    position NewPerson=NULL;

    prev=FindBySurname(p->next,after);
     if(prev==NULL)
        return -1;

    NewPerson=CreatePerson(name,surname,birthyear);
    if(NewPerson==NULL){
        return -1;
    }
    InsertAfter(prev,NewPerson);

    return 0;
    
}
int AddBefore(position p,char* name,char* surname,int birthyear,char* before){
    position NewPerson=NULL;
    position temp=NULL;

    temp=FindPrev(p,before);
    if(temp==NULL){
        return -1;
    }

    NewPerson=CreatePerson(name,surname,birthyear);
    if(NewPerson==NULL){
        return -1;
    }

    InsertAfter(temp,NewPerson);

    return 0;
}
int Sort(position p,char* name,char* surname,int birthyear){
    position NewPerson=NULL;
    position temp=p;

    for(temp;temp->next;temp=temp->next)
    {
        if(strcmp(temp->next->surname,surname)==0)
        {
            if(strcmp(temp->next->name,name)>0)
                break;
            if(strcmp(temp->next->name,name)==0)
            {
                if(temp->next->birthyear>birthyear)
                    break;
            }
        }
        if(strcmp(temp->next->surname,surname)>0)
            break;
    }
    
    NewPerson=CreatePerson(name, surname, birthyear);
    if (!NewPerson)
        return -1;

    InsertAfter (temp, NewPerson);
    
    return 0;

}
int PrintInFile(position first,char* FileName)
{
    position temp=first;
    FILE* f=NULL;
    
    f=fopen(FileName, "w");
    if(f==NULL)
    {
        printf("Neuspjesno otvaranje datoteke.");
        return -1;
    }
    
    fprintf(f, " Name        Surname        Birthyear");
    for (temp; temp; temp = temp->next)
        fprintf (f, "\n %s %s %d",temp->name, temp->surname, temp->birthyear);
    printf("\n");
    
    fclose(f);
    
    return 0;
}

int ReadFromFile(position head,char* FileName)
{
    position temp=head;
    FILE* f=NULL;
    char buffer[MAX_SIZE]={0};
    char name[30]={0};
    char surname[30]={0};
    int birthyear=0;
    
    f=fopen(FileName, "r");
    if(f==NULL)
    {
        printf("Neuspjesno otvaranje datoteke.");
        return -1;
    }
    
    while(!feof(f))
    {
        fgets(buffer, MAX_SIZE, f);
        if(sscanf(buffer, " %s %s %d", name, surname, &birthyear)==3)
        {
            Sort(temp, name, surname, birthyear);
        }
    }
    
    fclose(f);
    
    return 0;
}

int Sortagain(position head)
{
    PrintInFile(head->next,"Sort.txt");
    DeleteAll(head);
    ReadFromFile(head,"Sort.txt");
    
    return 0;
}

int main(){
    Person head = {.name = {0},.surname = {0},.birthyear = 0,.next = NULL };
    position p = &head;

    AddStart(&head,"Maja" ,"Majic",2001);
    AddEnd(&head,"Sime" ,"Simic",1999);
    AddStart(&head,"Ivo" ,"Ivic",2003);

    PrintList(p->next);
    printf("\n");

    Delete(&head,"Majic");
    Delete(&head,"Simic");

    PrintList(p->next);
    printf("\n");

    FindBySurname(head.next,"Simic");

    AddEnd(&head,"Maja" ,"Majic",2001);
    AddStart(&head,"Sime" ,"Simic",1999);
    AddEnd(&head,"Ivo" ,"Ivic",2003);

    PrintList(p->next);
    printf("\n");

    AddAfter(&head,"Dijana","Maroje",2010,"Simic");

    PrintList(p->next);
    printf("\n");

    AddBefore(&head,"Anita","Plejic",1987,"Ivic");

    PrintList(p->next);
    printf("\n");

    Sortagain(&head);

    PrintList(p->next);
    printf("\n");

    



    return 0;
}