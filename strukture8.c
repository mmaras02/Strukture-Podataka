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

Position AllocateMemory(int);
Position InsertElement(int, Position);
int PrintInorder(Position);
int PrintPreorder(Position);
int PrintPostorder(Position);
int PrintLevel(Position,int,int);
Position SearchElement(Position root, int element);
Position SearchMin(Position root);
Position SearchMax(Position root);
int DeleteAll(Position);
Position Delete(Position root, int element);

int main()
{
    int situation=0;
    Position root=NULL;

    
    while(1)
    {
        printf("\n1 -> Add a new element to the tree\n"
                "2 -> Print inorder\n"
                "3 -> Print preorder\n"
                "4 -> Print postorder\n"
                "6 -> Print level order\n"
                "7 -> Find an element\n"
                "8 -> Delete an element\n"
                "9 -> Exit\n");
        scanf(" %d", &situation);
        switch(situation)
        {
            case 1:
            {
                int n;
                printf("\n");
                printf("Enter the value you want to add:\n");
                scanf(" %d", &n);
                root=Insert(root,n);
                situation=0;
                break;
            }
            case 2:
            {
                printf("\n");
                PrintInorder(root);
                printf("\n");
                situation=0;
                break;
            }
            case 3:
            {
                printf("\n");
                PrintPreorder(root);
                printf("\n");
                situation=0;
                break;
            }
            case 4:
            {
                printf("\n");
                PrintPostorder(root);
                printf("\n");
                situation=0;
                break;
            }
            case 5:
            {
                int n=0;
                printf("\n");
                printf("Enter the value you would like to check for:\n");
                scanf(" %d", &n);
                if(Find(root, n))
                    printf("The value %d exists in the tree.\n", n);
                else
                    printf("The value %d doesn't exist in the tree.\n", n);
                situation=0;
                break;
            }
            case 6:
            {
                int n=0;
                printf("\n");
                printf("Enter the value you would like to delete:\n");
                scanf(" %d", &n);
                if(!Find(root, n));
                else
                    Delete(root, n);
                situation=0;
                break;
            }
            case 7:
            {
                DeleteAll(root);
                return 0;
            }
            default:
            {
                printf("\n");
                printf("Wrong input. Try again.\n");
                action=0;
                break;
            }
        }
    }
    
    return -1;
}
}

Position AllocateMemory(int element)
{
	Position new = (Position)malloc(sizeof(struct _BinaryTree));
	if (!new)
	{
		printf("Couldn't allocate memory!\n");
		return new;
	}
	new->data = element;
	new->left = NULL;
	new->right = NULL;
	return new;

}
Position InsertElement(int element, Position root)
{
	if (!root)
		return AllocateMemory(element);
	else if (element < root->data)
		root->left = InsertElement(element, root->left);
	else if (element > root->data)
		root->right = InsertElement(element, root->right);
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
int PrintPostorder(Position root);
{
	if (root)
	{
		PrintPostorder(root->left);
		PrintPostorder(root->right);
		printf("%d\n", root->data);
	}
	return 0;
}
int PrintPreorder(Position root);
{
	if (root)
	{
		printf("%d\n", root->data);
		PrintPreorder(root->left);
		PrintPreorder(root->right);
	}
	return 0;
}

Position SearchElement(Position root, int element)
{
	if (root == NULL)
		return NULL;

	if (element < root->data)
		return SearchElement(root->left, element);

	else if (element > root->data)
		return SearchElement(root->right, element);

	else
		return root;
}
Position SearchMin(Position root)
{
	if (root == NULL)
	{
		return NULL;
	}

	while (root->left != NULL)
	{
		root = root->left;
	}
	return root;
}

Position SearchMax(Position root)
{
	if (root == NULL)
	{
		return NULL;
	}

	while (root->right != NULL)
	{
		root = root->right;
	}
	return root;
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
Position Delete(Position root, int element)
{
	if (root == NULL)
		return NULL;

	if (element == root->data)
	{
		if (root->left != NULL)
		{
			Position temp = SearchMax(root->left);
			root->data = temp->data;
			root->Left = Delete(root->left, temp->data);
		}
		else if (root->right != NULL)
		{
			Position temp = SearchMin(root->right);	
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
		else
		{
			free(root);
			return NULL;
		}
	}
	else if (element < root->data)
		root->left = Delete(root->left, element);
	
	else
		root->right = Delete(root->right, element);

	return root;

}