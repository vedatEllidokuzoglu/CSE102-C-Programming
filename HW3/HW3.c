/*********************************************************************************
 *       HW3_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-3                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 17.03.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>

/*Defining macros*/
#define SIZE1 10
#define SIZE2 2
#define HW_PERCENTAGE 10
#define LAB_PERCENTAGE 20
#define MID_PERCENTAGE 30
#define FINAL_PERCENTAGE 40

/*Initilazing functions*/
void menu();

/*Part1 Functions*/
int add(int number1,int number2);
int sub(int number1,int number2);
int multiplication(int number1,int number2);
int division(int number1,int number2);
int power(int number1,int number2);
int modulo(int number1,int number2);
int doit (int f(),int first_number,int second_number);

/*Part2 Functions*/
int take_grades(int array[]);
int take_exam_grades(int array[]);
double calculate_homework(int hw[]);
double calculate_lab(int lab[]);
double calculate_all(int avg_hw,int array[],int avg_lab);
void draw_shape();

int main(){
	menu();
	return 0;
}

int add(int number1,int number2){	/*Addition function*/
	return (number1+number2);
}

int sub(int number1,int number2){	/*Substraction function*/
	return (number1-number2);
}

int multiplication(int number1,int number2){ /*Multiplication function*/
	return (number1*number2);
}

int division(int number1,int number2){	/*Division function*/
	return (number1/number2);
}

int power(int number1,int number2){		/*Power function*/
	int result=1;
	while(number2>0){
		result=result*number1;
		number2--;
	}
	return result;
}

int modulo(int number1,int number2){	/*Modulo function*/
	return (number1%number2);
}

int doit (int f(),int first_number,int second_number){
	return f(first_number,second_number);
}

int take_grades(int array[]){	/*Takes hw and lab grades from user*/
	int i=0;
	while(i<SIZE1){
		printf("Enter %d. Grade=",i+1);
		scanf("%d",&array[i]);
		i++;
	}
	return 0;
}

int take_exam_grades(int array[]){	/*Takes exam grades from user*/
	printf("Enter Midterm Exam Grade=");
	scanf("%d",&array[0]);
	printf("Enter Final Exam Grade=");
	scanf("%d",&array[1]);
	return 0;
}

double calculate_homework(int hw[]){ /*Calculate the average of the homework grades*/
	int i=0,avg_hw=0;
	while(i<SIZE1){
		avg_hw+=hw[i];
		i++;
	}
	avg_hw=avg_hw/SIZE1;
	return avg_hw;
}

double calculate_lab(int lab[]){	/*Calculate the average of the lab grades*/
	int i=0,avg_lab=0;
	while(i<SIZE1){
		avg_lab+=lab[i];
		i++;
	}
	avg_lab=avg_lab/SIZE1;
	return avg_lab;
}

double calculate_all(int avg_hw,int array[],int avg_lab){	/*Calculate the total average includes hws,labs,midterm and final exams*/
	int avg_all;
	avg_all=((avg_hw*HW_PERCENTAGE)+(avg_lab*LAB_PERCENTAGE)+(array[0]*MID_PERCENTAGE)+(array[1]*FINAL_PERCENTAGE))/100;
	return avg_all;
}

void draw_shape(){	/*Draws the shape*/
	int height,temp_height,space,temp_space,star=0,temp_star,flag=0;
	printf("Enter a height value:");	/*Takes the height value of the shape from the user*/
	scanf("%d",&height);
	temp_height=height*2;
	space=height-1;
	while(temp_height>0){	/*flag=0 for the first half part of the shape, flag=1 for the rest half of the part*/
		if(temp_height==height && flag==0){
			flag=1;
			star-=2;
			space++;
		}
		temp_space=space;
		while(temp_space>0){
			printf(" ");
			temp_space--;
		}
		if(flag==0){
			printf("/");
			temp_star=star;
			while(temp_star>0){
				printf("*");
				temp_star--;
			}
			star+=2;
			printf("\\\n");
			space--;
		}
		else{
			printf("\\");
			temp_star=star;
			while(temp_star>0){
				printf("*");
				temp_star--;
			}
			star-=2;
			printf("/\n");
			space++;
		}
		temp_height--;
	}
}

void menu(){
	char array[100],operation,exit='e';
	int selection,number1,number2,status=0,total=0,hw[SIZE1],lab[SIZE1],exam[SIZE2];
	double avg_hw,avg_lab,avg_all;
	do{	/*Shows the main menu of the program*/
		printf("\n***** MAIN PROGRAM MENU *****\n");
		printf("1. Simple Calculator\n");
		printf("2. Grade Calculator\n");
		printf("3. Draw Shape\n");
		printf("4. Exit the Program\n");
		printf("Choice:");
		scanf("%d",&selection);
		switch(selection){
			case 1:		printf("Addition\t(+)\nSubstraction\t(-)\nMultiplication\t(*)\nDivision\t(/)\nPower\t\t(**)\nModulo\t\t(%%)\n");
						printf("Press e for exit the Simple Calculator!\n");
						while(array[0]!=exit){
							scanf(" %[^\n]s",array);
							if(array[0]=='*' && array[1]=='*'){
								status=sscanf(array,"%c%c %d %d",&operation,&operation,&number1,&number2);
								/*if user input has two number input and an operator symbol, sscanf returns 3, otherwise (just one number input and an operator symbol) it returns 2.*/
								if(status==4)	total=doit(power,number1,number2);
								if(status==3)	total=doit(power,total,number1);
							}
							else{
								status=sscanf(array,"%c %d %d",&operation,&number1,&number2);
								/*if user input has two number input and an operator symbol, sscanf returns 3, otherwise (just one number input and an operator symbol) it returns 2.*/
								if(operation=='+'){
									if(status==3)	total=doit(add,number1,number2);
									if(status==2)	total=doit(add,total,number1);
								}
								if(operation=='-'){
									if(status==3)	total=doit(sub,number1,number2);
									if(status==2)	total=doit(sub,total,number1);
								}
								if(operation=='*'){
									if(status==3)	total=doit(multiplication,number1,number2);
									if(status==2)	total=doit(multiplication,total,number1);
								}
								if(operation=='/'){
									if(status==3)	total=doit(division,number1,number2);
									if(status==2)	total=doit(division,total,number1);
								}
								if(operation=='%'){
									if(status==3)	total=doit(modulo,number1,number2);
									if(status==2)	total=doit(modulo,total,number1);
								}
							}	
							if(array[0]!=exit)	printf("%d\n",total);
						}
						array[0]='0';
						break;

			case 2:		printf("Enter homework grades:\n");
						take_grades(hw);
						printf("Enter lab grades:\n");
						take_grades(lab);
						take_exam_grades(exam);
						printf("Average of the homeworks is %.2f\n",avg_hw=calculate_homework(hw)); 
						printf("Average of the labs is %.2f\n",avg_lab=calculate_lab(lab)); 
						printf("Total Average is %.2f\n",avg_all=calculate_all((int)avg_hw,exam,(int)avg_lab));
						break;

			case 3:		draw_shape();
						break;

			case 4: 	return;

			default:	printf("This is an invalid choice. Try again!\n");
						printf("Choice:");
						scanf("%d",&selection);
						break;
		}
	}while(1); 
}
