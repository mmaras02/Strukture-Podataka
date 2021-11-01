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
position FindBySurname(char* surname,position first){
    position temp=first;

    while(temp!=NULL){
        if((temp->surname,surname)==0){return temp;}
    }
    return NULL;
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
    Delete(&head,"Ivic");

    PrintList(p->next);

    FindBySurname("Simic",head.next);

    AddEnd(&head,"Maja" ,"Majic",2001);
    AddStart(&head,"Sime" ,"Simic",1999);
    AddEnd(&head,"Ivo" ,"Ivic",2003);

    PrintList(p->next);

    return 0;
}