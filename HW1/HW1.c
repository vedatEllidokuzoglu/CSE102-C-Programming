/*********************************************************************************
 *       HW1_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-1                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 01.03.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>
#include <math.h>

#define SQUARE 1
#define RECTANGULAR 2
#define	CIRCULAR 3
#define RED 0
#define YELLOW 1
#define	BLUE 2
#define BLACK 3
#define	WHITE 4
#define	PI 3

double CreateBody (int shape);
int SetColor (int color);
double LoadMoves(int shape, double body_size);
int SetAttackPower(int lower_bound, int upper_bound);
void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power);

int main(){
	int shape, color, attack_power;
	double size_of_body, move_length;
	shape = CIRCULAR;
	size_of_body = CreateBody(shape);
	color = 798;
	color = SetColor(color);
	move_length = LoadMoves(shape, size_of_body);
	attack_power = SetAttackPower(0,150);
	ShowPokemon(shape, size_of_body, color, move_length, attack_power);
	return 0;
}

double CreateBody (int shape){	/*Gets edge values from user and calculates the area*/
	double area,edge1,edge2;
	if(shape==SQUARE){
		printf("Enter a edge value for square=");
		scanf("%lf",&edge1);
		area=edge1*edge1;
	}
	if(shape==RECTANGULAR){
		printf("Enter a value for edge 1 of the rectangular=");
		scanf("%lf",&edge1);
		printf("Enter a value for edge 2 of the rectangular=");
		scanf("%lf",&edge2);
		area=edge1*edge2;
	}
	if(shape==CIRCULAR){
		printf("Enter a value for radius of the circular=");
		scanf("%lf",&edge1);
		area=edge1*edge1*PI;
	}
	return area;
}

int SetColor (int color){	/*Finds and returns the color code 0 to 4*/
	if (color<0 && color>1000)	return 1;
	else{
		color=color%5;
		return color;
	}
}

double LoadMoves(int shape, double body_size){	/*Calculates the move of the shape*/
	double perimeter;
	if(shape==SQUARE){
		perimeter=sqrt(body_size)*4;
		return perimeter;
	}
	if(shape==RECTANGULAR){
		perimeter=((body_size/5)+5)*2;
		return perimeter;
	}
	if(shape==CIRCULAR){
		perimeter=sqrt(body_size/PI)*2*PI;
		return perimeter;
	}
}

int SetAttackPower(int lower_bound, int upper_bound){	/*Specifies attack power of the Pokemon by generating a random number between the bounds */
	int attack_power=0;
	srand(time(NULL));
	attack_power=(rand()%(upper_bound-lower_bound+1))+lower_bound;
	return attack_power;
}

void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power){
	int edge1,edge2=5,radius,temp1,temp2,temp3,flag=0,total,left_space,right_space=0;
	if(shape==SQUARE){	/*Prints the figure of the square*/
		edge1=sqrt(body_size);
		temp1=edge1;
		temp2=edge1;
		while(temp2>0){
			while(temp1>0){
				printf("X");
				temp1--;
			}
			printf("\n");
			temp1=edge1;
			temp2--;
		}
	}
	if(shape==RECTANGULAR){	/*Prints the figure of the rectangle*/
		edge1=body_size/edge2;
		temp1=edge1;
		while(edge2>0){
			while(temp1>0){
				printf("X");
				temp1--;
			}
			printf("\n");
			temp1=edge1;
			edge2--;
		}
	}
	if(shape==CIRCULAR){	/*Prints the figure of the circle */
		radius=sqrt(body_size/PI);
		total=radius-1;
		left_space=total/2;
		if(radius%2==0)	temp3=radius+1;
		else{temp3=radius;}
		temp1=left_space;
		temp2=right_space;
		while(temp3>0){
			if(right_space==total)	flag=1;
			temp1=left_space;
			temp2=right_space;
			if((radius%2==1 &&(temp3==radius || temp3==1)) || (radius%2==0 && (temp3==radius+1 || temp3==1))){	/*Condition for the first and last line while printing*/
				if(radius%2==0 && temp3==1)	temp1--;
				while(temp1>0){
					printf("\t");
					temp1--;
				}
				if(radius%2==0){
					printf("    ");
				}
				if(radius%2==1)	left_space--;
				if(radius%2==1) right_space=right_space+2;
				else{right_space++;}
				printf("X\n");
			}
			else{
				while(temp1>0){
					printf("\t");
					temp1--;
				}
				printf("X");
				while(temp2>0){
					printf("\t");
					temp2--;
				}
				printf("X\n");
				if(flag==0){
					left_space--;
					right_space=right_space+2;
				}
				else{
					left_space++;
					right_space=right_space-2;
				}
			}
			temp3--;
		}
	}
	/*Prints the other specifications of the created Pokemon*/
	printf("Name: ");
	if (shape==SQUARE) printf("Square");
	if (shape==RECTANGULAR) printf("Rectangular");
	if (shape==CIRCULAR) printf("Circular");
	printf(" Pokémon\nSize: %.0f\nColor: ",body_size);
	if (color==RED) printf("Red");
	if (color==YELLOW) printf("Yellow");
	if (color==BLUE) printf("Blue");
	if (color==BLACK) printf("Black");
	if (color==WHITE) printf("White");
	printf("\nMove: %.0f\nAttack Power: %d\n",move_length,attack_power);
}
