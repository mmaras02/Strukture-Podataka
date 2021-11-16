#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement{
    double number;
    Position* next;
}StackElement;

Position CreateNewElement(double number);
int InsertAfter(Position position,Position NewElement);
int Push(Position head,double number);
int DeleteAfter(Position position);
int Pop(double* destination,Position head);
int PerformOperation(Position head,char operation);
int FileName(char* file);
int ReadPostfixFromFile(char* FileName);
int CalculatePostfix(double* destination);

int main(int argc,char* argv[])
{
    double result=0;
    char file[MAX]={0}
    
    FileName(&file);
    CalculatePostfix(&result);
    printf("the result is: %lf\n",result);

    return 0;

}
Position CreateNewElement(double number)
{
    Position NewElement=NULL;
    NewElement=(Position)malloc(sizeof(StackElement));
    if(!NewElement)
        perror("cant allocate memory\n");
        return -1;

    NewElement->number=number;
    NewElement->next=NULL;
}
int InsertAfter(Position position,Position NewElement)
{
    NewElement->next=position->next;
    position->next=NewElement;

    return 0;
}
int Push(Position head,double number)
{
    Position NewElement=NULL;
    NewElement=CreateNewElement(number);
    if(!NewElement)
        return -1;

    InsertAfter(head,NewElement);
    return 0;
}
int DeleteAfter(Position position)
{
    Position temp=position->next;
    if(!temp)
        return EXIT_SUCCESS;

    position->next=temp->next;
    free(temp);
    return 0;
}
int Pop(double* destination,Position head)
{
    Position first=head->next;
    if(!first)
        perror("Not valid\n");
        return -1;
    *destination=head->next->number;
    DeleteAfter(head);

    return 0;
}
int PerformOperation(Position head,char operation)
{
    double operand1=0;
    double operand2=0;
    int status1=EXIT_SUCCESS;
    int status2=EXIT_SUCCESS;
    double result=0;

    status2=Pop(&operand2,head);
    if(status2!=EXIT_SUCCESS)
        return -1;

    status1=Pop(&operand1,head);
        if(status1!=EXIT_SUCCESS)
            return -2;

    switch(opertion)
    {
        case '+':
        {
            result=operand1+operand2;
            break;
        }
        case '-':
        {
            result=operand1-operand2;
            break;
        }
        case '*':
        {
            result=operand1*operand2;
            break;
        }
        case '/':
        {
            if(operand1==0)
                return -3;

            result=operand1/operand2;
            break;
        }
        default:
            printf("operation not supported\n");
            return -4;
    }
    Push(head,result);

    return EXIT_SUCCESS;
}
int FileName(char* file)
{
    printf("write file name: ");
    scanf(" %s",FileName);

    return 0;
}
char* ReadPostfixFromFile(char* FileName)
{
    FILE* file = NULL;
    char* buffer = NULL;
    int FileLength = 0;

    file = fopen(FileName, "rb");
    if (!file)
    {
        perror("Can't open file!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    FileLength = ftell(file);

    buffer = (char*)calloc(fileLength + 1, sizeof(char));
    if (!buffer)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    rewind(file);
    fread(buffer, sizeof(char), FileLength, file);
    printf(" %s\n", buffer);
    fclose(file);

    return buffer;
}
int CalculatePostfix(double* destination)
{
    FILE* file=NULL;
    int FileLenght=0;
    char* buffer=NULL;
    char* currentbuffer=NULL;
    int NumBytes=0;
    char operation=0;
    int number=0;
    int status=0;
    StackElement head={.next=NULL,.number=0};

    status=ReadPostfixFromFile(&buffer);
    if(status!=0)
    {
        return -1;
    }

    currentbuffer=buffer;

    while(strlen(currentbuffer)>0)
    {
        status=sscanf(currentbuffer," %lf %n",&number,&NumBytes);
        if(status==1)
        {
            Push(&head,number);
            currentbuffer+=NumBytes;
        }
        else
        {
            status=sscanf(currentbuffer," %c %n",&operation,&NumBytes);
            status=PerformOperation(&head,operation);

            if(status!=EXIT_SUCCESS){
                free(buffer);
                while(head.next!=NULL)
                {
                    DeleteAfter(&head);
                }
                return -2;
            }
            currentbuffer+=NumBytes;
        }
    }
    free(buffer);

    status=Pop(destination,&head);
    if(status!=EXIT_SUCCESS){
        while(head.next!=NULL)
        {
            DeleteAfter(&head);
        }
        return -3;

    return 0;
}