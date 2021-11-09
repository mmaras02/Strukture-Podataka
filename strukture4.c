#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct _Polinom;
typedef struct _polinom* Position;
typedef struct _Polinom {
    int coef;
    int expon;
    Position next;
}Polinom;

int WriteFileName(char* FileName);
int ReadFromFile(Position head1,Position head2,char* FileName);
Position CreateNewElement(int coef, int expon);
int InsertAfter(Position p, Position NewElement);
int DeleteAfter(Position prev);
int Merge(Position position, Position NewElement);
int InsertSorted(Position head,Position NewElement);
int PrintList(Position head);
int DeleteAll(Position head);
int AddPoly(Position first1, Position first2, Position HeadReasult);
int MultiplyPoly(Position first1, Position first2, Position HeadProduct);

int main()
{
    Polinom head1={.coef=0, .expon=0, .next=NULL};
    Position p1=&head1;
    Polinom head2={.coef=0, .expon=0, .next=NULL};
    Position p2=&head2;
    Polinom HeadSum={.coef=0, .expon=0, .next=NULL};
    Position Sum=&HeadSum;
    Polinom HeadProduct={.coef=0, .expon=0, .next=NULL};
    Position Product=&HeadProduct;
    
    ReadFromFile(p1, p2);
    
    PrintPolynomial(p1->next);
    PrintPolynomial(p2->next);
    
    AddPoly(p1->next, p2->next, Sum);
    PrintPolynomial(Sum->next);

    MultiplyPoly(p1->next, p2->next, Product);
    PrintList(Product->next);

    DeleteAll(p1);
    DeleteAll(p2);
    DeleteAll(Sum);
    DeleteAll(Product);
    
    return 0;
}

int WriteFileName(char* FileName){
    printf("write file name:\n");
    scanf(" %s",FileName);

    return EXIT_SUCCESS;
}
int ReadFromFile(Position head1,Position head2,char* FileName)
{
    FILE* f=NULL;
    char buffer[1024]={0};
    char temp[50]={0};
    int count=1;
    int coef=0;
    int expon=0;
    int n=0;
    Position NewElement=NULL;

    f=fopen(FileName,"r");
    if(!f)
        perror("Can't open file!\n");
        return -1;
    
    fgets(buffer,1024,f);
    p = buffer;
    while(strlen(p) > 0){
        sscanf(p, "%d %d %n", &coef, &expon, &n);
        NewElement = CreateNewElement(coeff, expon);
        if(!NewElement)
        {
            perror("Error\n");
            return EXIT_FAILURE;
        }
        InsertSorted(head1, NewElement);
        p += n;
    }
    

    fgets(buffer,1024, f);
    p = buffer;
    while(strlen(p) > 0){
        sscanf(p, "%d %d %n", &coef, &expon, &n);
        InsertSorted( head2, CreateNewElement(coef, expon));
        p += n;
    }


    fclose(f);

    return EXIT_SUCCESS;
}

Position CreateNewElement(int coef, int expon)
{
    Position NewElement=NULL;

    NewElement=(Position)malloc(sizeof(Polinom));
    if(!NewElement)
    {
        perror("Couldn't allocate memmory.");
        return NULL;
    }

    NewElement->coef=coef;
    NewElement->expon=expon;
    NewElement->next=NULL;

    return NewElement;
}
int InsertAfter(Position p, Position NewElement)
{
    NewElement->next=p->next;
    p->next=NewElement;
    
    return 0;
}
int DeleteAfter(Position prev)
{
    Position ToDelete=NULL;

    ToDelete=prev->next;
    prev->next=ToDelete->next;
    free(ToDelete);

    return 0;
}
int Merge(Position position, Position NewElement)
{
	Position temp = position;
	int result = 0;

	if (temp->next != NULL && temp->next->expon == NewElement->expon)
	{
		result = temp->next->coef + NewElement->coef;

		if (result != 0)
		{
			temp->next->coef = result;
		}
		else
		{
			DeleteAfter(temp);
		}
		free(NewElement);
	}
	else
	{
		InsertAfter(temp, NewElement);
	}

	return SUCCESS;
}
int InsertSorted(Position head, Position NewElement)
{
	Position temp = NULL;
	for (temp = head; temp->next != NULL && temp->next->expon>NewElement->expon; temp=temp->next)

	Merge(temp, NewElement);

	return SUCCESS;
}
int PrintList(Position head)
{
    Position temp = head->next;

    while(temp != NULL)
    {
        printf(" %dx^(%d) ", temp->coef, temp->expon);
        temp = temp->next;
    }

    printf("\n");

    return EXIT_SUCCESS;
}
int DeleteAll(Position head)
{
	Position temp = head;

	if (!temp->next)
	{
		printf("Poly is empty\n");
		return -1;
	}

	for (temp = head; temp->next != NULL;)
	{
		DeleteAfter(head);
	}

	return 0;
}
int AddPoly(Position first1, Position first2, Position HeadReasult)
{
    Position Sum=HeadReasult;
    Position p1=first1;
    Position p2=first2;
    Position NewElement=NULL;
    
    while(p1!=NULL&&p2!=NULL)
    {
        if(p1->expon==p2->expon)
        {
        NewElement=CreateNewElement(p1->coef+p2->coef, p1->expon);
            SortedInsert(Sum, NewElement);
            p1=p1->next;
            p2=p2->next;
        }
        else if(p1->expon<p2->expon)
        {
            NewElement=CreateNewElement(p1->coef, p1->expon);
            SortedInsert(Sum, NewElement);
            p1=p1->next;
        }
        else
        {
            NewElement=CreateNewElement(p2->coef, p2->expon);
            SortedInsert(Sum, NewElement);
            p2=p2->next;
        }
    }
    
    if(p2==NULL);
    else p1=p2;
    
    while(p1!=NULL)
    {
        NewElement=CreateNewElement(p1->coef, p1->expon);
        InsertSorted(pSum, NewElement);
        p1=p1->next;
    }
    return 0;
}
int MultiplyPoly(Position first1, Position first2, Position HeadProduct)
{
    Position product=HeadReasult;

    Position p1=first1;
    Position p2=first2;
    Position NewElement=NULL;
    
    while(p1)
    {
        while(p2)
        {
            NewElement = CreateNewElement(p1->coef*p2->coef, p1->expon+p2->expon);
            InsertSorted(product, NewElement);
            p2=p2->next;
        }
        p2=first2;
        p1=p1->next;
    }
    
    return 0;
}
