/*********************************************************************************
 *       HW6_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-6                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 13.04.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>
#define SIZE1 10
#define SIZE2 1024
#define DECIMAL 10

void menu();
int common_recursive(int arr_common[SIZE1],int index);
int common(int number1,int number2,int arr_common[SIZE1]);
void merge_sort_recursive(int number[SIZE2],int size);
void calculate_formula_recursive(int number);
int check_recursive(int number,int *total_digit);
char capital_letter_recursive(char array[SIZE2]);

int main(){
	menu();	
	return 0;
}

void menu(){
	int selection,arr_common[SIZE1],num[SIZE2],number,number1,number2,count,i=0,result,index,total_digit=0;
	char array[SIZE2];
	do{
		printf("1)PART 1\n2)PART 2\n3)PART 3\n4)PART 4\n5)PART 5\n6)EXIT\n");
		scanf("%d",&selection);
		switch(selection){
		case 1:	printf("Enter a value for number1:");
				scanf("%d",&number1);
				printf("Enter a value for number2:");
				scanf("%d",&number2);
				index=common(number1,number2,arr_common)-1;
				result=common_recursive(arr_common,index);
				printf("%d\n",result);
				break;
		case 2:	printf("Enter the length of the list:");
				scanf("%d",&count);
				while(i<count){
					scanf("%d",&num[i]);
					i++;
				}
				merge_sort_recursive(num,count);
				i=0;
				while(i<count){
					printf("%d ",num[i]);
					i++;
				}
				printf("\n");
				break;
		case 3:	printf("Enter a number:");
				scanf("%d",&number);	
				calculate_formula_recursive(number);
				break;
		case 4:	printf("Input=");
				scanf("%d",&number);
				result=check_recursive(number,&total_digit);
				printf("Output: ");
				if(result==number) printf("Equal\n");
				else printf("Not Equal\n");
				break;
		case 5:	printf("Enter a string:");
				scanf("%s",array);
				printf("The first capital letter is:%c\n",capital_letter_recursive(array));
				break;
		case 6:
				break;
		default:printf("Your selection is invalid! Please enter a valid selection:\n");
		}
	}while(selection!=6);
	return;
}

int common_recursive(int arr_common[SIZE1],int index){	/*PART1 Recursive Common Function*/
	int result=1;
	if(index==0)	return result*arr_common[index];
	else{
		result=(result*arr_common[index])*common_recursive(arr_common,index-1);
		return result;
	}
}

int common(int number1,int number2,int arr_common[SIZE1]){	/*PART1 Common Function*/
	int multipliers_num1[SIZE1],multipliers_num2[SIZE1],i=2,j=0,index=0,size_1,size_2;
	if(number1%number2==0){arr_common[0]=number2;	return 1;}
	if(number2%number1==0){arr_common[0]=number1;	return 1;}
	while(number1>1){
		while(number1%i!=0){
			i++;
		}
		multipliers_num1[index]=i;
		number1/=i;
		i=2; index++;
	}
	size_1=index; i=2; index=0;
	while(number2>1){
		while(number2%i!=0){
			i++;
		}
		multipliers_num2[index]=i;
		number2/=i;
		i=2; index++;
	}
	size_2=index; i=0; index=0;
	while(1){
		if(multipliers_num1[i]==multipliers_num2[j])break;
		if(multipliers_num1[i]<multipliers_num2[j]) i++;
		else j++;
	}
	while(multipliers_num1[i]==multipliers_num2[j] && index<SIZE1){
		arr_common[index]=multipliers_num1[i];
		i++; j++; index++;
	}
	return index;
}

void merge_sort_recursive(int number[SIZE2],int size){		/*PART2 Recursive Merge Sort*/
	int list1[SIZE2],list2[SIZE2],i=0,j=0,x=0,half_size=size/2;
	while(i<half_size){
		list1[i]=number[i];
		i++;
	}
	i=0;
	while(i<size-half_size){
		list2[i]=number[half_size+i];
		i++;
	}
	if(half_size!=1) merge_sort_recursive(list1,half_size);
	if(size-half_size!=1) merge_sort_recursive(list2,size-half_size);
	i=0;
	while(x<size){
		if(i==half_size) { number[x]=list2[j]; j++; }
		else if(j==size-half_size) { number[x]=list1[i]; i++; }
		else if(list1[i]<list2[j]){ number[x]=list1[i]; i++; }
		else if(list2[j]<list1[i]){ number[x]=list2[j]; j++; }
		x++;
	}
	return;
}

void calculate_formula_recursive(int number){		/*PART3 Recursive Function for the calculation depending on the formula*/
	printf("%d ",number);
	if(number==1){printf("\n"); return;}
	else if(number%2==0) calculate_formula_recursive(number/2);
	else if(number%2==1) calculate_formula_recursive((number*3)+1);
	return;
}

int check_recursive(int number,int *total_digit){	/*PART4 Recursive ZCVN Equal or Not Equal*/
	int result=0,current_digit,temp_digit,temp_result=1;
	if(number==0)	return 0;
	if(number>0){
		*total_digit+=1;
		current_digit=number%DECIMAL;
		number/=DECIMAL;
		result=check_recursive(number,total_digit);
		temp_digit=*total_digit;
		while(temp_digit>0){
			temp_result*=current_digit;
			temp_digit--;
		}
		result+=temp_result;
	}
	return result;
}

char capital_letter_recursive(char array[SIZE2]){	/*PART5 Finding the first capital letter in the string*/
	if(array[0]>=65 && array[0]<=96)	return array[0];
	else return capital_letter_recursive(&array[1]);
}
