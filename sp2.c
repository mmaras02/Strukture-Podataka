#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

#define MAX_SIZE 50
#define MAX_LINE 1024

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} Person;

void Menu(Position p);
void InputInfo(char* name, char* surname, int* birthYear);
int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindPerson(Position first, char* surname);
int DeletePerson(Position head, char* surname);
int AddAfter(Position p, char* name, char* surname, int birthYear);
Position FindBefore(Position head, char* surname);
int AddBefore(Position head, char* name, char* surname, int birthYear);
int Sort(Position head);
int PrintListToFile(Position p, char* file);
int ReadListFromFile(Position head, char* file, char* name, char* surname, int* birthYear);

int main(int argc, char** argv)
{
	Person head = { .next = NULL,.name = {0},.surname = {0},.birthYear = 0 };

	Position p = &head;

	Menu(p);

	return EXIT_SUCCESS;
}

void Menu(Position p)
{
	char option = 'X';
	int error = 0;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	char surnameInput[MAX_SIZE] = "";
	Position searchPosition = NULL;

	do
	{
		printf("Unosom slova odaberite zelite li:\n1)Add new person to the begining of list\n"
			"2) Print list\n"
			"3) Add new person to the end of the list\n"
			"4) Find person in list by surname\n"
			"5) Delete person from the list(by surname)\n"
			"6) Add new person after chosen person(choose by surname)\n"
			"7) Add new person before chosen person(choose by surname)\n"
			"8) Sort list\n"
			"9) Write list in file\n"
			"10) ReadIspisati listu u file\n"
			"11) Izaci iz programa\n");
		scanf(" %c", &option);
	

		switch (option)
		{
		case '1':
			InputInfo(name, surname, &birthYear);
			error = PrependList(p, name, surname, birthYear);
			if (error == -1)
			{
				printf("Neuspjesno dodavanje osobe!\n");


			}
			else if (error == EXIT_SUCCESS)
			{
				printf("Uspjesno ste dodali osobu!\n");

			}
			break;

		case '2':
			PrintList(p->next);
			break;

		case '3':
			InputInfo(name, surname, &birthYear);
			error = AppendList(p, name, surname, birthYear);
			if (error == -1)
			{
				printf("Neuspjesno dodavanje osobe");
			}
			else if (error == EXIT_SUCCESS)
			{
				printf("Uspjesno ste dodali osobu\n");

			}
			break;

		case '4':
			if (p->next == NULL)
			{
				printf("Prazna lista\n");
				break;
			}
			printf("Unesite prezime: ");
			scanf(" %s", surnameInput);
			searchPosition = FindPerson(p->next, surnameInput);
			printf("Ime: %s, prezime: %s, godina rodenja: %d\n", searchPosition->name, searchPosition->surname, searchPosition->birthYear);

			break;

		case '5':
			if (p->next == NULL)
			{
				printf("Prazna lista\n");
				break;
			}
			printf("Unesite prezime: ");
			scanf(" %s", surnameInput);
			DeletePerson(p, surnameInput);
			break;
		case '6':
			InputInfo(name, surname, &birthYear);
			AddAfter(p, name, surname, birthYear);
			break;
		case '7':
			InputInfo(name, surname, &birthYear);
			AddBefore(p, name, surname, birthYear);
			break;
		case '8':
			Sort(p);
			break;
		case '9':
			PrintListToFile(p->next, "file.txt");
			break;
		case '10':
			ReadListFromFile(p, "file.txt", name, surname, &birthYear);
			break;
		case '11':
			break;
		default:
			printf("Krivi unos\n");
			break;

		}
	} while (option != '11');

}

void InputInfo(char* name, char* surname, int* birthYear)
{

	printf("Unesite ime: ");
	scanf(" %s", name);
	printf("Unesite prezime: ");
	scanf(" %s", surname);
	printf("Unesite godinu rodenja: ");
	scanf(" %d", birthYear);

}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	if (temp == NULL)
	{
		printf("Prazna lista\n");
		return 0;
	}

	while (temp)
	{
		printf("Ime: %s, prezime: %s, godina rodenja: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		return -1;
	}

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

Position FindPerson(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}

	return NULL;
}

int DeletePerson(Position head, char* surname)
{
	Position temp = head;
	Position toDelete = NULL;
	while (temp->next)
	{

		if (strcmp(temp->next->surname, surname) == 0)
		{
			toDelete = temp->next;
			temp->next = toDelete->next;
			free(toDelete);
			printf("Izbrisali ste osobu\n");
			return 0;

		}
		temp = temp->next;


	}

	return 0;
}
int AddAfter(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL, searchPosition = NULL;
	char surnameInput[MAX_SIZE] = "";

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		printf("Neuspjela dinamicka alokacija");
		return -1;
	}
	if (head->next == NULL)
	{
		printf("Prazna lista\n");
		return -1;
	}

	printf("Unesite prezime: ");
	scanf(" %s", surnameInput);
	searchPosition = FindPerson(head->next, surnameInput);


	InsertAfter(searchPosition, newPerson);

	return EXIT_SUCCESS;
}
Position FindBefore(Position head, char* surname)
{
	Position temp = head, searchPosition = NULL;
	if (temp->next == NULL)
	{
		printf("Prazna lista\n");
		return NULL;
	}
	if (temp->next->next == NULL)
		if (strcmp(temp->next->surname, surname) == 0)
			return temp;
		else
			return NULL;
	while (temp->next->next)
	{
		if (strcmp(temp->next->next->surname, surname) == 0)
			return temp->next;
		temp = temp->next;

	}
	return NULL;


}
int AddBefore(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL, searchPosition = NULL;
	char surnameInput[MAX_SIZE] = "";

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson)
	{
		printf("Neuspjela dinamicka alokacija");
		return -1;
	}


	printf("Unesite prezime: ");
	scanf(" %s", surnameInput);
	searchPosition = FindBefore(head, surnameInput);


	InsertAfter(searchPosition, newPerson);

	return EXIT_SUCCESS;
}
int Sort(Position head)
{
	Position p = head;
	Position q = NULL;
	Position beforeQ = NULL;
	Position last = NULL;

	while (p->next != last)
	{
		beforeQ = p;
		q = beforeQ->next;

		while (q->next != last)
		{
			if (strcmp(q->surname, q->next->surname) > 0)
			{
				beforeQ->next = q->next;
				q->next = q->next->next;
				beforeQ->next->next = q;
				q = beforeQ->next;
			}
			beforeQ = q;
			q = q->next;
		}
		last = q;
	}

	return 0;
}
int PrintListToFile(Position p, char* file)
{
	Position temp = p;
	FILE* f = NULL;

	f = fopen(file, "w");
	if (!f)
	{
		printf("Greska kod otvaranja datoteke!");
		return -1;
	}

	while (temp)
	{
		fprintf(f, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);

		temp = temp->next;
	}

	fclose(f);

	return EXIT_SUCCESS;
}
int ReadListFromFile(Position head, char* file, char* name, char* surname, int* birthYear)
{
	Position temp = head;
	FILE* f = NULL;
	char buffer[MAX_LINE] = { 0 };
	Position newPerson = NULL;

	f = fopen(file, "r");

	if (!feof(f))
	{
		return -1;
	}

	do
	{
		fgets(buffer, MAX_LINE, f);
		if (sscanf(buffer, "%s %s %d", name, surname, birthYear) == 3)
		{
			newPerson = CreatePerson(name, surname, *birthYear);
			InsertAfter(head, newPerson);
		}
	} while (!feof(f));

	fclose(f);

	return EXIT_SUCCESS;
}