/*********************************************************************************
 *       HW2_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-2                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 10.03.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>
#include <time.h>	/*time for rand() function.*/
#include <stdlib.h>	/*for rand() function. If it's not added, some gcc compiler may gives warning*/

#define TRIAL 10
#define MIN 1
#define MAX 1024

void menu();
int make_a_guess(int trial, int min, int max);
void show_scores(int score_human, int score_program);
void draw_hourglass(int height);
void draw_mountain_road(int length, int max_radius);

int main(){
	srand(time(NULL));	/*For generating random value depend on time*/
	menu();
	return 0;
}

void menu(){
	int selection,score_human=0,score_program=0,height,n,r;
	do{
		printf("***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("Choice:");
		scanf("%d",&selection);
		while(selection<1 || selection>4){	/*If the user enters an invalid choice, program asks repeatedly until user enters valid choice.*/
			printf("This is an invalid choice. Try again!\n");
			printf("Choice:");
			scanf("%d",&selection);
		}
		switch(selection){
			case 1:	if(make_a_guess(TRIAL,MIN,MAX)==1)	score_human++;
					else	score_program++;
					show_scores(score_human,score_program);
					break;
			case 2:	printf("Enter a height value for hourglass:");
					scanf("%d",&height);
					while(height%2==0){	/*Asks to the user again for entering an odd number until the user enters an odd number.*/
						printf("This is an invalid value. Please enter odd number:");
						scanf("%d",&height);
					}
					draw_hourglass(height);
					break;
			case 3:	printf("Enter a length value for N:");	/*N means lenght*/
					scanf("%d",&n);
					printf("Enter a maximum radius value for R:");	/*R means maximum radius*/
					scanf("%d",&r);
					draw_mountain_road(n,r);
					break;
			case 4: return;
		}
	}while(selection);
}

int make_a_guess(int trial,int min,int max){
	int temp_trial=1,lucky_number,guess,distance,counter=0;
	lucky_number=rand()%max+1;
	while(temp_trial<=trial){
		printf("(Trial: %d) Make a guess between %d and %d:",temp_trial,min,max);
		scanf("%d",&guess);
		distance=lucky_number-guess;
		if (distance<0)	distance=distance*-1; /*If the result is negative, turns it to positive*/
		if(distance==0){
			printf("Distance: %d. You win!\n",distance);
			return 1;	/*returning 1 means human won.*/
		}
		while(distance!=0){
			distance=distance/2;
			counter++;
		}
		distance=counter;
		printf("Distance: %d\n",distance);
		counter=0;
		if (guess<lucky_number)	min=guess;	/*Sets a new min or max bound.*/
		else	max=guess;
		temp_trial++;
	}
	return 0;	/*returning 0 means program won.*/
}

void show_scores(int score_human, int score_program){
	printf("Your Score: %d Program Score: %d\n",score_human,score_program);
	return;
}

void draw_hourglass(int height){
	int counter,temp,total,space,flag=0;
	counter=height;
	temp=counter;
	total=height;
	while(total>0){
		if(counter==1)	flag=1;	/*If the upper part of the hour glass is done flag value turns to 1 for the rest of the part*/
		temp=counter;
		space=(height-counter)/2;
		while(space>0){
			printf(" ");
			space--;
		}
		while(counter>0){
			printf("*");
			counter--;
		}
		printf("\n");
		counter=temp;
		if(flag==0)	counter-=2;
		if(flag==1)	counter+=2;
		total--;
	}
}

void draw_mountain_road (int length, int max_radius){
	int radius,counter,space,temp_space,step=1,flag=0;
	space=max_radius;
	temp_space=space;
	while(length>0){
		radius=rand()%(max_radius+1);	/*Generate random value for radius of the current circle.*/
		counter=radius*2;	/*Counter for the current half cirlce so it's looping for two times of the radius value*/
		while(counter>=0){
			while(temp_space>0){
				printf(" ");
				temp_space--;
			}
			if(counter==radius){
				printf("|\n");
				if(flag==0){
					space++;
					flag=1;
				}
				else{
					space--;
					flag=0;
				}
			}
			else{
				if(flag==0){
					printf("/\n");
					space--;
				}
				if(flag==1){
					printf("\\\n");
					space++;
				}
			}
			temp_space=space;
			counter--;
		}
		length--;
	}
}
