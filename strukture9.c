#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 128

struct _BinaryTree;
typedef struct _BinaryTree* Position;
typedef struct _BinaryTree{
    int data;
    Position left;
    Position right;
}BinaryTree;

struct _stack;
typedef struct _stack *stackPointer;
typedef struct _stack{
	int n;
	stackPointer next;
}stack;

Position CreateNewElement(int);
Position InsertElement(int, Position);
int Replace(Position);
Position GenerateTree(Position);
int DeleteAll(Position);
int InorderToStog(Position, stackPointer);
int PrintInorder(Position);
int WriteInFile(char* fileName, stackPointer);
int InOrderPrintInFile(FILE* f, Position);
stackPointer CreateNewStogElement(int);
int DeleteAllStog(stackPointer);
int InsertAfter (stackPointe, stackPointer);
stackPointer FindLast (stackPointer);
int AddEnd (stackPointer, int);

int main()
{
    Position Root = NULL;
    Root=GenerateTree(Root);
    
    int situation=0;
    
    while(1)
    {
        printf("\n1 -> Add a new element to the tree\n"
                "2 -> Print inorder\n"
                "3 -> Replace all elements with the sum of their branches\n"
                "4 -> Print inorder in file\n"
                "5 -> Generate new tree\n"
                "6 -> Exit\n");
        scanf(" %d", &situation);
        switch(situation)
        {
            case 1:
            {
                int n;
                printf("\n");
                printf("Enter the value you would like to add:\n");
                scanf(" %d", &n);
                Root=Insert(Root, CreateNewElement(n));
                situation=0;
                break;
            }
            case 2:
            {
                printf("\n");
                PrintInorder(Root);
                printf("\n");
                situation=0;
                break;
            }
            case 3:
            {
                printf("\n");
                Replace(Root);
                printf("\n");
                situation=0;
                break;
            }
            case 4:
            {
                stack head={.n=0, .next=NULL};
                stackPointer h=&head;
                char str[20]="0";
                
                printf("Enter the name of the .txt file:\n");
                scanf(" %s", str);
                strcat(str,".txt");
                InorderToStog(Root, h);
                PrintListInFile(str, h->next);
                printf("\n");
                situation=0;
                break;
            }
            case 5:
            {
                printf("\n");
                DeleteAll(Root);
                Root=NULL;
                Root=GenerateTree(Root);
                printf("\n");
                situation=0;
                break;
            }
            case 6:
            {
                DeleteAll(Root);
                return 0;
            }
            default:
            {
                printf("\n");
                printf("Wrong input.\n");
                situation=0;
                break;
            }
        }
    }
    
    return 0;
}


Position GenerateTree(Position root)
{
    int i=0;
    Position temp=NULL;
    
    srand(time(0));
    
    for(i=0;i<10;i++)
    {
        temp=CreateNewElement(rand()%79+11);
        if(!temp)
            return NULL;
        root=Insert(root, temp);
    }
    
    return root;
}

Position CreateNewElement(int n)
{
    Position newElement=NULL;
    
    newElement=(Position)malloc(sizeof(BinaryTree));
    if(!newElement)
    {
        printf("Couldn't allocate memory.\n");
        return NULL;
    }
    
    newElement->data=n;
    newElement->right=NULL;
    newElement->left=NULL;
    
    return newElement;
}

Position InsertElement(int newElement, Position root)
{
	if (!root)
        return newElement;
	else if (newElement < root->data)
		root->left = InsertElement(newElement, root->left);
	else if (newElement > root->data)
		root->right = InsertElement(newElement, root->right);
	return root;
}

int PrintInorder(Position root);
{
	if (root)
	{
		PrintInorder(root->left);
		printf("%d\n", root->data);
		PrintInorder(root->right);
	}
	return 0;
}

int Replace(Position p)
{
    int temp=0;
    if(p == NULL)
        return 0;
    else
    {
        temp=p->data;
        p->data=Replace(p->right)+Replace(p->left);
        return p->data+temp;
    }
}

int DeleteAll(Position root)
{
    if(!root)
        return 0;
    if(!root->left && !root->right)
        free(root);
    else
    {
        if(root->left)
            DeleteAll(root->left);
        if(root->right)
            DeleteAll(root->right);
    free(root);
    }
    return 0;
}

stackPointer CreateNewStogElement(int n)
{
  stackPointer newElement=NULL;
  
  newElement = (Pointer) malloc (sizeof (stack));
  if(!newElement)
  {
      perror("Couldn't allocate memmory.\n");
      return NULL;
  }

  newElement->n = n;
  newElement->next=NULL;
  
  return newElement;
}

int InsertAfter (stackPointer p, stackPointer newElement)
{
  newElement->next = p->next;
  p->next = newElement;

  return 0;
}

stackPointer FindLast (stackPointer head)
{
  stackPointer last = head;

  while (last->next)
      last = last->next;

  return last;
}

int AddEnd (stackPointer head, int n)
{
  stackPointer newElement = NULL;

  newElement = CreateNewStogElement (n);
  if (!newElement)
    return 1;
  
  InsertAfter(FindLast(head), newElement);

  return 0;
}

int InorderToStog(Position p, stackPointer h)
{
    if(!p)
        return 0;
    InorderToStog(p->left,h);
    AddEnd(h, p->data);
    InorderToStog(p->right,h);
    return 0;
}

int WriteInFile(char* fileName, stackPointer root)
{
    stackPointer temp=root;
    FILE* f=NULL;
    
    f=fopen(fileName, "w");
    if(f==NULL)
    {
        printf("error.");
        return 1;
    }
    
   InOrderPrintInFile(f, root);
	fclose(f);
	return 0;
}
int InOrderPrintInFile(FILE* f, Position root)
{
	if (root)
	{
		InOrderPrintInFile(f, root->left);
		fprintf(f, "%c ", root->data);
		InOrderPrintInFile(f, root->right);
	}
	return 0;
}

int DeleteAllStog(stackPointer head)
{
    stackPointer temp=NULL;
    
    while (head->next!=NULL)
    {
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    
    return 0;
}
