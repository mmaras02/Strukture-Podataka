#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

struct _Dir;
typedef struct _Dir* Position;
typedef struct _Dir{
    char name[MAX];
    Position sibling;
    Position child;
}Dir;

typedef struct stack* PositionS;
typedef struct stack {
	Position data;
	PositionS next;
} Stack;

Position Insert(Position current, Position newDir);
Position AllocateMemoryForDirectory();
PositionS AllocateMemoryForStack();
Position MakeDirectory(Position current, char* name);
int PushStack(Position current, PositionS stackHead);
Position PopStack(PositionS stackHead);
Position ChangeDirectory(Position current, PositionS stackHead, char* name)
int PrintDirectory(Position current);
int Delete(Position current);

int main()
{
    int case=0;
    char name[MAX];
    Position current;
    Dir c;
	c.sibling = NULL;
	c.child = NULL;
	strcpy(c.name, "c:");

	Stack stackHead;
	stackHead.data = NULL;
	stackHead.next = NULL;

	PushStack(&c, &stackHead);

    printf("==========Options==========\n");
    printf("\n1 - md\n"
             "2 - cd dir\n"
             "3 - cd..\n"
             "4 - dir\n"
             "5 - exit\n");
    scanf(" %d", &case);

    switch(case)
    {
        case 1:
        {
            printf("Enter the name of the new directory:\n");
                scanf(" %s", name);
                current->child=MakeDirectory(current,name);
                break;
        }
        case 2:
        {
            current=ChangeDirectory(current,stackHead,name);
            break;
        }
        case 3:
        {
            current=PopStack(stackHead);
            break;
        }
        case 4:
        {
            PrintDirectory(current);
            break;
        }
        case 5:
        {
            Delete(current);
            break;
        }
        default:
        {
            printf("wrong input\n");
            break;
        }
    }

return 0;    

}
Position Insert(Position current, Position newDirectory)
{
    if(!current)
    {
        return newDirectory;
    }
    else if(strcmp(current->name, newDirectory->name)<0)
    {
        newDirectory->sibling=insert(current->sibling,newDirectory);
    }
    else if(strcmp(current->name, newDirectory->name)>0)
    {
        newDirectory->sibling=current;
        return newDirectory;
    }
    else
    {
        printf("A file or directory with such a name already exists.\n");
        free(newDirectory);
    return current;
    }
}
Position AllocateMemoryForDirectory()
{
	Position newDirectory = (Position)malloc(sizeof(Dir));
	if (!newDirectory)
	{
		printf("Can not allocate memory!\n");
	}
	newDirectory->child = NULL;
	newDirectory->sibling = NULL;
	return newDirectory;	
}
PositionS AllocateMemoryForStack()
{
	PositionS new = (PositionS)malloc(sizeof(Dir));
	if (!new)
	{
		printf("Can not allocate memory!\n");
	}
	return new;
}
Position MakeDirectory(Position current, char* name)
{
	Position newDirectory;
	newDirectory = AllocateMemoryForDirectory();

	strcpy(newDirectory->name, name);
		if (!current->child)
		{
			current->child = newDirectory;
		}
		else
		{
			Position currentChild = current->child;
			while (currentChild->sibling)
				currentChild = currentChild->sibling;
			currentChild->sibling = newDirectory;
		}
		return current;
}
int PushStack(Position current, PositionS stackHead)
{
	PositionS new;
	PositionS temp = stackHead;
	if (new = AllocateMemoryForStack()) 
	{
		while (temp->next)
			temp = temp->next;
		new->next = temp->next;
		temp->next = new;
		new->data = current;
		return 0;
	}
	else
		return 1;
}
Position PopStack(PositionS stackHead)
{
	PositionS temp = stackHead->next, prev = stackHead->next;
	if (!temp->next)
		return NULL;
	while (temp->next)
	{
		prev = temp;
		temp= temp->next;
	}
		Position directory = temp->data;
		prev->next = temp->next;
		free(temp);
		return directory;
}
Position ChangeDirectory(Position current, PositionS stackHead, char* name)
{
	if (!current->child)
	{
	    printf("Directory is empty!\n");
		return current;
	}
	else
	{
		Position temp = current->child;
		while (temp)
		{
			if (!strcmp(temp->name, name))
			{
				PushStack(temp, stackHead);
				return temp;
			}
			temp = temp->sibling;
		}
		printf("That directory doesn't exist!\n");
		return current;
	}
}
int PrintDirectory(Position current)
{
	if (!current->child)
		printf("Directory is empty!\n");
	else
	{
		current = current->child;
		while (current)
		{
			printf(" %s\n", current->name);
			current = current->sibling;
		}
	}
}
int Delete(Position current)
{
    if(!current)
        return 0;
    else if(!current->sibling && !current->child)
    {
        free(current);
        return 0;
    }
    else
    {
       if(current->child)
        {
            Delete(current->child);
            current->child=NULL;
        }
        if(current->sibling)
        {
            Delete(current->sibling);
            current->sibling=NULL;
        }
        free(current);
    }
    return 0;
}
