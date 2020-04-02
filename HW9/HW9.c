/*********************************************************************************
 *       HW9_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-9                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 16.05.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

struct person{
	char name[SIZE];
	char surname[SIZE];
	char musical_Work[SIZE];
	int age;
	struct person *next;
}*top;

void addNode(char name[SIZE], char surname[SIZE], char creation[SIZE], int age){
	struct person *ptr;
	ptr=malloc(sizeof(struct person));
	strcpy(ptr->name,name);
	strcpy(ptr->surname,surname);
	strcpy(ptr->musical_Work,creation);
	ptr->age=age;
	ptr->next=top;
	top=ptr;
	return;
}

void deleteNode(){
	struct person *ptr;
	ptr=top->next;
	free(top);
	top=ptr;
	return;
}

void Sort_Alphabetically(){
	int count=0,temp_count=0;
	struct person temp,*ptr;
	ptr=top;
	while(ptr->next!=NULL){
		count++;
		ptr=ptr->next;
	}
	ptr=top;
	while(ptr->next!=NULL){
		if(temp_count==count-1) break;
		if(strcmp(ptr->name,ptr->next->name)>0){
			strcpy(temp.name,ptr->name);
			strcpy(temp.surname,ptr->surname);
			strcpy(temp.musical_Work,ptr->musical_Work);
			temp.age=ptr->age;
			strcpy(ptr->name,ptr->next->name);
			strcpy(ptr->surname,ptr->next->surname);
			strcpy(ptr->musical_Work,ptr->next->musical_Work);
			ptr->age=ptr->next->age;
			strcpy(ptr->next->name,temp.name);
			strcpy(ptr->next->surname,temp.surname);
			strcpy(ptr->next->musical_Work,temp.musical_Work);
			ptr->next->age=temp.age;
			ptr=top;
			temp_count=0;
		}
		else{
			ptr=ptr->next;
			temp_count++;
		}
	}
}

void Sort_Increasingly(){
	int count=0,temp_count=0;
	struct person temp,*ptr;
	ptr=top;
	while(ptr->next!=NULL){
		count++;
		ptr=ptr->next;
	}
	ptr=top;
	while(ptr->next!=NULL){
		if(temp_count==count-1) break;
		if(ptr->age>ptr->next->age){
			strcpy(temp.name,ptr->name);
			strcpy(temp.surname,ptr->surname);
			strcpy(temp.musical_Work,ptr->musical_Work);
			temp.age=ptr->age;
			strcpy(ptr->name,ptr->next->name);
			strcpy(ptr->surname,ptr->next->surname);
			strcpy(ptr->musical_Work,ptr->next->musical_Work);
			ptr->age=ptr->next->age;
			strcpy(ptr->next->name,temp.name);
			strcpy(ptr->next->surname,temp.surname);
			strcpy(ptr->next->musical_Work,temp.musical_Work);
			ptr->next->age=temp.age;
			ptr=top;
			temp_count=0;
		}
		else{
			ptr=ptr->next;
			temp_count++;
		}
	}
}

void print_stack(){
	int i=1;
	struct person *ptr;
	ptr=top;
	while(ptr->next!=NULL){
		printf("%d)%s\n%s\n%s\n%d\n",i,ptr->name,ptr->surname,ptr->musical_Work,ptr->age);
		ptr=ptr->next;
		i++;
	}
	return;
}

void menu(){
	int status,age;
	char name[SIZE],surname[SIZE],musical_Work[SIZE];
	do{
		printf("****MENU****\n1- Add a Person to the Stack\n2- Pop a Person from the Stack\n3- Sort Alphabetical Order\n4- Sort Age in Increasing Order\n5- Exit menu\n*************\n");
		printf("Select your Choise:\n");
		scanf("%d",&status);
		switch(status){
			case 1:	printf("Name:");
					scanf(" %[^\n]s",name);
					printf("Surname:");
					scanf(" %[^\n]s",surname);
					printf("Creation:");
					scanf(" %[^\n]s",musical_Work);
					printf("Age:");
					scanf("%d",&age);
					printf("--------------------\n");
					addNode(name,surname,musical_Work,age);
					print_stack();
					break;

			case 2: deleteNode();
					print_stack();
					break;

			case 3: Sort_Alphabetically();
					print_stack();
					break;
			case 4: Sort_Increasingly();
					print_stack();
					break;
			case 5: return;
			default:printf("You entered invalid choice. Please try again.\n"); 
					break;
		}
	}while(status!=5);
	return;
}

int main(){
	top=malloc(sizeof(struct person));
	top->next=NULL;
	menu();
	return 0;
}