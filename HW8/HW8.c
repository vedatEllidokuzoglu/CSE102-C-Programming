/*********************************************************************************
 *       HW8_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-8                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 05.05.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define START_MONEY 100000
#define PASS_MONEY 10000
#define DICE 6
#define SIZE 24
#define TAB_SIZE 8
#define ROW_COUNT 5
#define COLUMN_COUNT 7
#define MINES_COUNT1 169
#define MINES_COUNT2 33
#define MIDDLE_ROW_TAB 15
#define MIN_HOME_COUNT 1
#define MAX_HOME_COUNT 3
#define FREE_HOUSE 1
#define TIME_TRAVEL 2
#define GARNISHMENT 5000
#define GENEROSITY 10000
#define TREASURE_HUNTER 20000

typedef enum {noone,cap,car}player_type;
typedef enum {start,property,tax,punish,fortune}block_type;

struct player{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char name[20];
};

struct block{
	int block_id;
	char name[20];
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	struct player owner;
	block_type type;
	struct block *next;
};

struct fortune_card{
	int card_no;
	char name[15];
	int explanation;
};

void init_the_board(struct block *board){
	int i=0;
	struct block *ptr;
	char name[24][20]={"Start","Esenyurt","Car Park","Fortune Card","Tuzla","Arnavutkoy","Wait 2 Turn","Catalca","Beykoz","Fortune Card","Car Fix","Maltepe","Bills","Sisli","Oil","Fortune Card","Atasehir","Sariyer","Wait 1 Turn","Kadikoy","Besiktas","Fortune Card","Vocation","Bebek"};
	int price[24]={0,16000,0,0,16500,17000,0,20000,23000,0,0,30000,0,33000,0,0,35000,40000,0,43000,60000,0,0,70000};
	int rent[24]={0,800,1500,0,850,875,2,1000,1100,0,1750,1350,2000,1500,2250,0,1600,1750,1,1900,2500,0,5000,3500};
	int rent_1[24]={0,4000,0,0,4250,4500,0,5000,5500,0,0,7000,0,8000,0,0,8500,9500,0,11000,15000,0,0,20000};
	int rent_2[24]={0,9000,0,0,9500,10000,0,12000,125000,0,0,15000,0,16000,0,0,17000,19000,0,21500,28000,0,0,35500};
	int rent_3[24]={0,25000,0,0,26000,28000,0,30000,33000,0,0,40000,0,42000,0,0,45000,48000,0,55000,60000,0,0,65000};
	int house_price[24]={0,10000,0,0,12000,12000,0,13000,13000,0,0,15000,0,16000,0,0,17000,19000,0,23000,30000,0,0,35000};
	block_type type[24]={start,property,tax,fortune,property,property,punish,property,property,fortune,tax,property,tax,property,tax,fortune,property,property,punish,property,property,fortune,tax,property};
	ptr=board;
	while(i<SIZE){
		ptr->next=malloc(sizeof(struct block));
		strcpy(ptr->name,name[i]);
		ptr->block_id=i;
		ptr->price=price[i];
		ptr->rent=rent[i];
		ptr->rent_1=rent_1[i];
		ptr->rent_2=rent_2[i];
		ptr->rent_3=rent_3[i];
		ptr->house_price=house_price[i];
		ptr->house_count=0;
		ptr->owner.type=noone;
		ptr->type=type[i];
		if(i!=SIZE-1)ptr=ptr->next;
		else ptr->next=board;
		i++;
	}
	return;
}

void show_board(struct block *board,struct player player_one, struct player player_two){
	int i=0,j=0,count=0,tab_space=0,index1,index2;
	struct block *ptr1,*ptr2;
	ptr1=board;
	while(i<MINES_COUNT1){
		printf("-");
		i++;
	}
	printf("\n");
	i=0;
	while(i<COLUMN_COUNT){
		printf("|\t%s\t",ptr1->name);
		if(strlen(ptr1->name)<TAB_SIZE) printf("\t");
		ptr1=ptr1->next;
		i++;
	}
	printf("|\n");
	ptr1=board;
	i=0;
	while(i<COLUMN_COUNT){
		if(ptr1->type==property) printf("|\t%d$\t\t",ptr1->price);
		else if(ptr1->type==tax) printf("|\t%d$\t\t",ptr1->rent);
		else printf("|\t\t\t");
		ptr1=ptr1->next;
		i++;
	}
	printf("|\n");
	ptr1=board;
	i=0;
	while(i<COLUMN_COUNT){
		if(i==player_one.current_block_id && i==player_two.current_block_id)	printf("|    %s,%s    ",player_one.name,player_two.name);
		else if(i==player_one.current_block_id)	printf("|\t%s\t\t",player_one.name);
		else if(i==player_two.current_block_id)	printf("|\t%s\t",player_two.name);
		else printf("|\t\t\t");
		i++;
	}
	printf("|\n");
	i=0;
	while(i<MINES_COUNT1){
		printf("-");
		i++;
	}
	printf("\n");
	ptr1=board;
	ptr2=board;
	i=0; j=0; index1=23; index2=7;
	ptr2=board;
	j=0;
	while(j<index2){
		ptr2=ptr2->next;
		j++;
	}
	while(count<ROW_COUNT){
		ptr1=board;
		i=0;
		while(i<index1){
			ptr1=ptr1->next;
			i++;
		}
		index1--;
		printf("|\t%s\t",ptr1->name);
		if(strlen(ptr1->name)<TAB_SIZE) printf("\t");
		printf("|");
		while(tab_space<MIDDLE_ROW_TAB){
			printf("\t");
			tab_space++;
		}
		tab_space=0;
		printf("|\t%s\t",ptr2->name);
		if(strlen(ptr2->name)<TAB_SIZE) printf("\t");
		printf("|\n");
		if(ptr1->type==property) printf("|\t%d$\t\t|",ptr1->price);
		else if(ptr1->type==tax) printf("|\t%d$\t\t|",ptr1->rent);
		else printf("|\t\t\t|");
		while(tab_space<MIDDLE_ROW_TAB){
			printf("\t");
			tab_space++;
		}
		tab_space=0;
		if(ptr2->type==property) printf("|\t%d$\t\t|\n",ptr2->price);
		else if(ptr2->type==tax) printf("|\t%d$\t\t|\n",ptr2->rent);
		else printf("|\t\t\t|\n");
		if(i==player_one.current_block_id && i==player_two.current_block_id)	printf("|    %s,%s    |",player_one.name,player_two.name);
		else if(i==player_one.current_block_id)	printf("|\t%s\t\t|",player_one.name);
		else if(i==player_two.current_block_id)	printf("|\t%s\t|",player_two.name);
		else printf("|\t\t\t|");
		while(tab_space<MIDDLE_ROW_TAB){
			printf("\t");
			tab_space++;
		}
		tab_space=0;
		if(j==player_one.current_block_id && j==player_two.current_block_id)	printf("|    %s,%s    |\n",player_one.name,player_two.name);
		else if(j==player_one.current_block_id)	printf("|\t%s\t\t|\n",player_one.name);
		else if(j==player_two.current_block_id)	printf("|\t%s\t|\n",player_two.name);
		else printf("|\t\t\t|\n");
		if(count!=ROW_COUNT-1){
			while(tab_space<MINES_COUNT1/COLUMN_COUNT+1){
				printf("-");
				tab_space++;
			}
			tab_space=0;
			while(tab_space<MIDDLE_ROW_TAB){
				printf("\t");
				tab_space++;
			}
			tab_space=0;
			while(tab_space<MINES_COUNT1/COLUMN_COUNT+1){
				printf("-");
				tab_space++;
			}
			printf("\n");
			tab_space=0;
		}
		ptr2=ptr2->next;
		j++; count++;
	}
	i=0;
	while(i<MINES_COUNT1){
		printf("-");
		i++;
	}
	printf("\n");
	index1=18;
	while(index1>11){
		ptr1=board;
		i=0;
		while(i<index1){
			ptr1=ptr1->next;
			i++;
		}
		printf("|\t%s\t",ptr1->name);
		if(strlen(ptr1->name)<TAB_SIZE) printf("\t");
		index1--;
	}
	printf("|\n");
	index1=18;
	while(index1>11){
		ptr1=board;
		i=0;
		while(i<index1){
			ptr1=ptr1->next;
			i++;
		}
		if(ptr1->type==property) printf("|\t%d$\t\t",ptr1->price);
		else if(ptr1->type==tax) printf("|\t%d$\t\t",ptr1->rent);
		else printf("|\t\t\t");
		index1--;
	}
	printf("|\n");
	index1=18;
	while(index1>11){
		ptr1=board;
		i=0;
		while(i<index1){
			ptr1=ptr1->next;
			i++;
		}
		if(index1==player_one.current_block_id && index1==player_two.current_block_id)	printf("|    %s,%s    ",player_one.name,player_two.name);
		else if(index1==player_one.current_block_id)	printf("|\t%s\t\t",player_one.name);
		else if(index1==player_two.current_block_id)	printf("|\t%s\t",player_two.name);
		else printf("|\t\t\t");
		index1--;
	}
	printf("|\n");
	i=0;
	while(i<MINES_COUNT1){
		printf("-");
		i++;
	}
	printf("\n");
	return;
}

void show_properties(struct block *board){
	struct block *ptr;
	ptr=board;
	int i=0,selection;
	printf("Please select a property to see details:\n");
	while(i<SIZE){
		if(ptr->type==property) printf("%d -\t%s\n",i,ptr->name);
		ptr=ptr->next;
		i++;
	}

	do{
		scanf("%d",&selection);
		i=0;
		ptr=board;
		while(i<selection){
			ptr=ptr->next;
			i++;
		}
		if(ptr->type!=property)	printf("Your selection is invalid, please try again:");
	}while(ptr->type!=property);
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	printf("|\t    %s    \t",ptr->name);
	if(strlen(ptr->name)<TAB_SIZE) printf("\t");
	printf("|\n");
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	printf("|\tRent\t\t%d$\t|\n",ptr->rent);
	printf("|\tRent 1 H\t%d$\t|\n",ptr->rent_1);
	printf("|\tRent 2 H\t%d$\t|\n",ptr->rent_2);
	printf("|\tRent 3 H\t%d$\t|\n",ptr->rent_3);
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	printf("|\tHouse Price\t%d$\t|\n",ptr->house_price);
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	return;
}

void buy_property(struct block* current_block, struct player* current_player){
	char selection1,selection2;
	int i=0,count;
	if(current_player->current_block_id==current_block->block_id && current_block->type==property && current_block->owner.type==noone && current_player->account>=current_block->price){
		printf("Do you want to buy this property? (Enter Y or N):");
		do{
			scanf(" %c",&selection1);
			if(selection1!='Y' && selection1!='N' && selection1!='y' && selection1!='n') printf("Your selection is invalid!\nPlease try again (Enter Y or N):");
		}while(selection1!='Y' && selection1!='N' && selection1!='y' && selection1!='n');
		if(selection1=='Y' || selection1=='y'){
			current_player->account-=current_block->price;
			while(current_player->owned_block_ids[i]!=EOF){
				i++;
			}
			current_player->owned_block_ids[i]=current_block->block_id;
			if (current_player->type==cap) current_block->owner.type=cap;
			if (current_player->type==car) current_block->owner.type=car;
			printf("You bought the property.\n");
			printf("Your current total money= %d $\n",current_player->account);
			if(current_block->house_count!=MAX_HOME_COUNT && current_player->account>current_block->house_price){ 
				printf("You can build houses on this property.\nWould you like to build a house? (Enter Y or N):");
				do{
					scanf(" %c",&selection2);
					if(selection2!='Y' && selection2!='N' && selection2!='y' && selection2!='n') printf("Your selection is invalid, please try again (Enter Y or N):");
				}while(selection2!='Y' && selection2!='N' && selection2!='y' && selection2!='n');
				if (selection2=='Y' || selection2=='y'){
					printf("You can build Minimum:1 Maximum:%d houses on this property.\nHow many houses do you want to build=",MAX_HOME_COUNT-current_block->house_count);
					do{
						scanf("%d",&count);
						if(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-current_block->house_count) printf("3You entered invalid count!\nPlease try again (Min:1 Max:%d)=",MAX_HOME_COUNT-current_block->house_count);
						else if(current_player->account<current_block->house_price*count) printf("You don't have enough money to build %d house/s\n",count); printf("Please try again (Min:1 Max:%d)=",MAX_HOME_COUNT-current_block->house_count); 
					}while(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-current_block->house_count || current_player->account<current_block->house_price*count);
					current_player->account-=current_block->house_price*count;
					current_block->house_count+=count;
					printf("You built %d houses on the property.\n",count);
					printf("Your current total money= %d $\n",current_player->account);
				}
				else if(selection2=='N' || selection2=='n') printf("You didn't build any house.\n");
			}
		}
		else if(selection1=='N' || selection1=='n') printf("You stopped buying the property.\n");
	}
	else if(current_block->type!=property) printf("It's not a property. It can not be purchased!\n");
	else if(current_block->owner.type!=noone) printf("This property already has an owner!\n");
	else if(current_player->account<current_block->price) printf("You don't have enough money to buy this property!\n");
	return;
}

void sell_property(struct block *board, struct player* current_player){
	struct block *ptr;
	int i=0,j=0,index,max,selection,total_payment=0;
	char status1,status2='Y';
	ptr=board;
	if(status2=='Y' || status2=='y'){
		printf("Bank only pays back half of the price of the property and the houses that are on the property.\n");
		printf("Properties you have:\n");
		while(current_player->owned_block_ids[j]!=EOF){
			index=(current_player->owned_block_ids[j]);
			i=0;
			ptr=board;
			while(i<index){
				ptr=ptr->next;
				i++;
			}
			printf("%d - %s:\n",j+1,ptr->name);
			j++;
		}
		max=j;
		j=0;
		printf("Select a property you want to sell (1 to %d):",max);
		do{
			scanf("%d",&selection);
			if(selection<1 || selection>max) printf("Your selection is invalid!\nPlease try again (Min:1 Max:%d)=",max);
		}while(selection<1 || selection>max);
		index=current_player->owned_block_ids[selection-1];
		i=0;
		ptr=board;
		while(i<index){
			ptr=ptr->next;
			i++;
		}
		total_payment+=(ptr->price+(ptr->house_price*ptr->house_count))/2;
		printf("Bank will pay %d $ for this property and the houses that are on the property.\nWill you accept? (Y or N):",total_payment);
		do{
			scanf(" %c",&status1);
			if(status1!='Y' && status1!='N' && status1!='y' && status1!='n') printf("Your selection is invalid!\nPlease try again (Enter Y or N):");
		}while(status1!='Y' && status1!='N' && status1!='y' && status1!='n');
		if (status1=='Y' || status1=='y'){
			ptr->owner.type=noone;
			ptr->house_count=0;
			current_player->account+=total_payment;
			current_player->owned_block_ids[selection-1]=EOF;
			i=selection-1;
			while(i<12){
				current_player->owned_block_ids[i]=current_player->owned_block_ids[i+1];
				i++;
			}
			current_player->owned_block_ids[11]=EOF;
			printf("You sold the property.\n");
			printf("Your current total money= %d $\n",current_player->account);
		}
		else if(status1=='N' || status1=='n') printf("You canceled the sales process.\nThe property was not sold.\n");
	}
	return;
}

void gameplay (struct block *board, struct player player_one, struct player player_two){
	srand(time(NULL));
	int i=0,j=0,selection,dice,count,index,temp_player_one_index,temp_player_two_index,game_status=1,avg_cost=0,temp,temp_max=0,flag1=0,flag2=0;
	struct block *ptr;
	struct player player_noone; player_noone.type=noone;
	struct fortune_card free_house,time_travel,garnishment,generosity,treasue_hunter;
	free_house.card_no=1; strcpy(free_house.name,"Free House"); free_house.explanation=FREE_HOUSE;
	time_travel.card_no=2; strcpy(free_house.name,"Time Travel"); time_travel.explanation=TIME_TRAVEL;
	garnishment.card_no=3; strcpy(free_house.name,"Garnishment"); garnishment.explanation=GARNISHMENT;
	generosity.card_no=4; strcpy(free_house.name,"Generosity"); generosity.explanation=GENEROSITY;
	treasue_hunter.card_no=5; strcpy(free_house.name,"Treasure Hunter"); treasue_hunter.explanation=TREASURE_HUNTER;
	strcpy(player_one.name,"Player"); player_one.type=cap; player_one.account=START_MONEY; player_one.current_block_id=0; player_one.turn_to_wait=0;
	strcpy(player_two.name,"Computer"); player_two.type=car; player_two.account=START_MONEY; player_two.current_block_id=0; player_two.turn_to_wait=0;
	while(i<12){
		player_one.owned_block_ids[i]=EOF;
		player_two.owned_block_ids[i]=EOF;
		i++;
	}
	i=0;
	ptr=board;
	while(i<SIZE){
		avg_cost+=ptr->price;
		ptr=ptr->next;
		i++;
	}
	avg_cost/=SIZE;
	i=0;
	ptr=board;
	show_board(board,player_one,player_two);
	while(game_status){
		if(player_one.turn_to_wait==0 && flag1==0){
			printf("It's %s turn.\n",player_one.name);
			do{
				index=player_one.current_block_id;
				i=0;
				ptr=board;
				while(i<index){
					ptr=ptr->next;
					i++;
				}
				printf("1 - Roll the dice\n2 - Show my account\n3 - Show my properties\n4 - Show property deeds\n5 - Buy Property\n6 - Buy house\n7 - Sell property\nPlease select an option to continue:");
				scanf("%d",&selection); 
				switch(selection){
					case 1:		if(flag2==0) dice=(rand()%DICE)+1;
								else dice=0;
								flag2=0;
								player_one.current_block_id+=dice;temp_player_one_index=player_one.current_block_id;
								player_one.current_block_id%=SIZE;
								if(temp_player_one_index!=player_one.current_block_id)	player_one.account+=PASS_MONEY;
								show_board(board,player_one,player_two);
								i=0;
								ptr=board;
								while(i<player_one.current_block_id){
									ptr=ptr->next;
									i++;
								}
								if(ptr->type==punish){
									player_one.turn_to_wait=ptr->rent;
									break;
								}	
								if(ptr->type==tax){
									while(player_one.account<ptr->rent){
										if(player_one.owned_block_ids[0]==EOF){
											printf("You don't have enough money to pay the tax and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!",player_two.name);	
											return;
										}
										else{
											printf("You don't have enough money to pay the tax.\nYou have to sell some properties.\n");
											sell_property(board,&player_one);
									
										}
									}
									player_one.account-=ptr->rent;
									printf("You paid the rent (%d $).\n",ptr->rent);
								}
								if(ptr->type==fortune){
									dice=(rand()%5)+1;
									if(dice==1){
										printf("%s have chosen a %s card from fortune cards\n",player_one.name,free_house.name);
										j=0;
										while(player_one.owned_block_ids[j]!=EOF){
											i=0;
											ptr=board;
											while(i<player_one.owned_block_ids[j]){
												ptr=ptr->next;
												i++;
											}
											if(ptr->house_price>temp_max && ptr->house_count!=MAX_HOME_COUNT) temp=player_one.owned_block_ids[j];
											j++;
										}
										i=0;
										ptr=board;
										while(i<temp){
											ptr=ptr->next;
											i++;
										}
										if(ptr->owner.type==car && ptr->house_count!=MAX_HOME_COUNT){
											ptr->house_count++;
											printf("The house was built in %s.\n",ptr->name);
										}
									}
									else if(dice==2){
										printf("%s have chosen a %s card from fortune cards\n",player_one.name,time_travel.name);
										dice=(rand()%DICE)+1;
										printf("%s rolled the dice again: %d\n",player_one.name,dice);
										if(dice<4){
											player_one.current_block_id+=time_travel.explanation;
											temp_player_two_index=player_one.current_block_id;
											player_one.current_block_id%=SIZE;
											if(temp_player_two_index!=player_one.current_block_id)	player_one.account+=PASS_MONEY;
											i=0;
											ptr=board;
											while(i<player_one.current_block_id){
												ptr=ptr->next;
												i++;
											}
											printf("Moved forward by %d blocks.\n",time_travel.explanation);
										}
										else{
											player_one.current_block_id-=time_travel.explanation;
											i=0;
											ptr=board;
											while(i<player_one.current_block_id){
												ptr=ptr->next;
												i++;
											}
											printf("Moved backward by %d blocks.\n",time_travel.explanation);
										}
										flag1=0;
									}
									else if(dice==3){
										printf("%s have chosen a %s card from fortune cards\n",player_one.name,garnishment.name);
										if(player_one.account>=garnishment.explanation){
											player_one.account-=garnishment.explanation;
											printf("%s paid %d $ to the bank.\n",player_one.name,garnishment.explanation);
											printf("%s current total money= %d $\n",player_one.name,player_one.account);

										}
										else{
											printf("%s doesn't have enough money to pay the garnishment\n",player_one.name);
											while(player_one.account<ptr->rent){
												if(player_one.owned_block_ids[0]==EOF){
													printf("%s doesn't have enough money to pay the garnishment and doesn't have any property to sell.\n%s went bankrupt.\n%s won the game!",player_two.name,player_two.name,player_one.name);	
													return;
												}
												else{ 
													j=0;
													while(player_one.owned_block_ids[j]!=EOF){
														i=0;
														ptr=board;
														while(i<player_one.owned_block_ids[j]){
															ptr=ptr->next;
															i++;
														}
														temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
														if(temp>temp_max){
															temp_max=temp;
															index=j;
														}
														j++;
													}
													i=0;
													ptr=board;
													while(i<player_one.owned_block_ids[index]){
														ptr=ptr->next;
														i++;
													}
													printf("%s sold the property %s.\n",player_one.name,ptr->name);
													ptr->owner.type=noone;
													ptr->house_count=0;
													player_one.account+=temp_max;
													player_one.owned_block_ids[index]=EOF;
													i=index;
													while(i<12){
														player_one.owned_block_ids[i]=player_one.owned_block_ids[i+1];
														i++;
													}
													player_one.owned_block_ids[11]=EOF;
													printf("%s current total money= %d $\n",player_one.name,player_one.account);
												}
											}
										}
									}
									else if(dice==4){
										printf("%s have chosen a %s card from fortune cards\n",player_one.name,generosity.name);
										if(player_one.account>=generosity.explanation){
											player_one.account-=generosity.explanation;
											player_one.account+=generosity.explanation;
											printf("%s paid %d $ to %s.\n",player_one.name,generosity.explanation,player_one.name);
											printf("%s current total money= %d $\n",player_one.name,player_one.account);
										}
										else{
											printf("%s doesn't have enough money to pay the generosity\n",player_one.name);
											while(player_one.account<ptr->rent){
												if(player_one.owned_block_ids[0]==EOF){
													printf("%s doesn't have enough money to pay the generosity and doesn't have any property to sell.\n%s went bankrupt.\n%s won the game!",player_two.name,player_two.name,player_one.name);	
													return;
												}
												else{ 
													j=0;
													while(player_one.owned_block_ids[j]!=EOF){
														i=0;
														ptr=board;
														while(i<player_one.owned_block_ids[j]){
															ptr=ptr->next;
															i++;
														}
														temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
														if(temp>temp_max){
															temp_max=temp;
															index=j;
														}
														j++;
													}
													i=0;
													ptr=board;
													while(i<player_one.owned_block_ids[index]){
														ptr=ptr->next;
														i++;
													}
													printf("%s sold the property %s.\n",player_one.name,ptr->name);
													ptr->owner.type=noone;
													ptr->house_count=0;
													player_one.account+=temp_max;
													player_one.owned_block_ids[index]=EOF;
													i=index;
													while(i<12){
														player_one.owned_block_ids[i]=player_one.owned_block_ids[i+1];
														i++;
													}
													player_one.owned_block_ids[11]=EOF;
													printf("%s current total money= %d $\n",player_one.name,player_one.account);
												}
											}
										}
									}
									else if(dice==5){
										printf("%s have chosen a %s card from fortune cards\n",player_one.name,treasue_hunter.name);
										printf("%s took %d $ from the bank.\n",player_one.name,treasue_hunter.explanation);
										player_one.account+=treasue_hunter.explanation;
										printf("%s current total money= %d $\n",player_one.name,player_one.account);
									}
								}
								if(ptr->owner.type==car){
									if (ptr->house_count==0){
										while(player_one.account<ptr->rent){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=ptr->rent;
										player_two.account+=ptr->rent;
										printf("You paid the rent (%d $) to player %s.\n",ptr->rent,player_two.name);
									}
									if (ptr->house_count==1){
										while(player_one.account<ptr->rent_1){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=ptr->rent_1;
										player_two.account+=ptr->rent_1;
										printf("You paid the rent (%d $) to player %s.\n",ptr->rent_1,player_two.name);
									}
									if (ptr->house_count==2){
										while(player_one.account<ptr->rent_2){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=ptr->rent_2;
										player_two.account+=ptr->rent_2;
										printf("You paid the rent (%d $) to player %s.\n",ptr->rent_2,player_two.name);
									}
									if (ptr->house_count==3){
										while(player_one.account<ptr->rent_3){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=ptr->rent_3;
										player_two.account+=ptr->rent_3;
										printf("You paid the rent (%d $) to player %s.\n",ptr->rent_3,player_two.name);
									}
								}
								else if(ptr->owner.type==noone && ptr->type==property){
									printf("This property has no owner.\n");
									buy_property(ptr,&player_one);
								}
								break;

					case 2:		printf("Total money in your account= %d $\n",player_one.account);
								break;

					case 3:		j=0;
								if(player_one.owned_block_ids[j]==EOF)	printf("You don't have any property.\n");
								else{
									printf("Your properties are:\n");
									while(player_one.owned_block_ids[j]!=EOF){
										index=player_one.owned_block_ids[j];
										i=0;
										ptr=board;
										while(i<index){
											ptr=ptr->next;
											i++;
										}
										printf("%d - %s\n",j+1,ptr->name);
										j++;
									}
								}
								break;

					case 4:		show_properties(board);
								break;

					case 5:		buy_property(ptr,&player_one);
								break;

					case 6:		if(ptr->owner.type==player_one.type && ptr->house_count!=MAX_HOME_COUNT && player_one.account>=ptr->house_price){
									printf("You can build Minimum:1 Maximum:%d houses on this property. How many houses do y1ou want to build=",MAX_HOME_COUNT-ptr->house_count);
									do{
										scanf("%d",&count);
										if(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-ptr->house_count) printf("You entered invalid count, please try again (Min:1 Max:%d)=",MAX_HOME_COUNT-ptr->house_count);
									}while(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-ptr->house_count);
									player_one.account-=ptr->house_price*count;
									ptr->house_count+=count;
									printf("You built %d houses on the property.\n",count);
									printf("Your current total money=%d\n",player_one.account);
								}
								else if(ptr->owner.type!=player_one.type)	printf("This property is not yours. You can't build a house.\n");
								else if(ptr->house_count==MAX_HOME_COUNT)	printf("This property has 3 houses. No more houses can be built.\n");
								else if(player_one.account<ptr->house_price)	printf("You don't have enough money to built a house.\n");
								break;

					case 7:		sell_property(board,&player_one);
								break;

					default:	printf("Your selection is invalid, please try again.");
				}
			}while(selection!=1);
		}
		else player_one.turn_to_wait--;

		if(player_two.turn_to_wait==0 && flag2==0){
			if(flag1==0) dice=(rand()%DICE)+1;
			else dice=0;
			player_two.current_block_id+=dice;
			temp_player_two_index=player_two.current_block_id;
			player_two.current_block_id%=SIZE;
			if(temp_player_two_index!=player_two.current_block_id)	player_two.account+=PASS_MONEY;
			show_board(board,player_one,player_two);
			i=0;
			ptr=board;
			while(i<player_two.current_block_id){
				ptr=ptr->next;
				i++;
			}
			if(flag1==0)printf("%s rolled the dice: %d\n",player_two.name,dice);
			flag1=0;
			if(ptr->type==punish){
				player_two.turn_to_wait=ptr->rent;
			}
			else if(ptr->type==tax){
				temp=0;
				temp_max=0;
				while(player_two.account<ptr->rent){
					if(player_two.owned_block_ids[0]==EOF){
						printf("%s doesn't have enough money to pay the tax and doesn't have any property to sell.\n%s went bankrupt.\n%s won the game!",player_two.name,player_two.name,player_one.name);	
						return;
					}
					else{ 
						j=0;
						while(player_two.owned_block_ids[j]!=EOF){
							i=0;
							ptr=board;
							while(i<player_two.owned_block_ids[j]){
								ptr=ptr->next;
								i++;
							}
							temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
							if(temp>temp_max){
								temp_max=temp;
								index=j;
							}
							j++;
						}
						i=0;
						ptr=board;
						while(i<player_two.owned_block_ids[index]){
							ptr=ptr->next;
							i++;
						}
						printf("%s sold the property %s.\n",player_two.name,ptr->name);
						ptr->owner.type=noone;
						ptr->house_count=0;
						player_two.account+=temp_max;
						player_two.owned_block_ids[index]=EOF;
						i=index;
						while(i<12){
							player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
							i++;
						}
						player_two.owned_block_ids[11]=EOF;
						printf("%s current total money= %d $\n",player_two.name,player_two.account);
					}
				}
				player_two.account-=ptr->rent;
				printf("%s paid the rent (%d $).\n",player_two.name,ptr->rent);
				printf("%s current total money= %d $\n",player_two.name,player_two.account);
			}

			else if(ptr->type==fortune){
				dice=(rand()%5)+1;
				if(dice==1){
					printf("%s have chosen a %s card from fortune cards\n",player_two.name,free_house.name);
					j=0;
					while(player_two.owned_block_ids[j]!=EOF){
						i=0;
						ptr=board;
						while(i<player_two.owned_block_ids[j]){
							ptr=ptr->next;
							i++;
						}
						if(ptr->house_price>temp_max && ptr->house_count!=MAX_HOME_COUNT) temp=player_two.owned_block_ids[j];
						j++;
					}
					i=0;
					ptr=board;
					while(i<temp){
						ptr=ptr->next;
						i++;
					}
					if(ptr->owner.type==car && ptr->house_count!=MAX_HOME_COUNT){
						ptr->house_count++;
						printf("The house was built in %s.\n",ptr->name);
					}
				}
				else if(dice==2){
					printf("%s have chosen a %s card from fortune cards\n",player_two.name,time_travel.name);
					dice=(rand()%DICE)+1;
					printf("%s rolled the dice again: %d\n",player_two.name,dice);
					if(dice<4){
						player_two.current_block_id+=time_travel.explanation;
						temp_player_two_index=player_two.current_block_id;
						player_two.current_block_id%=SIZE;
						if(temp_player_two_index!=player_two.current_block_id)	player_two.account+=PASS_MONEY;
						i=0;
						ptr=board;
						while(i<player_two.current_block_id){
							ptr=ptr->next;
							i++;
						}
						printf("Moved forward by %d blocks.\n",time_travel.explanation);
					}
					else{
						player_two.current_block_id-=time_travel.explanation;
						i=0;
						ptr=board;
						while(i<player_two.current_block_id){
							ptr=ptr->next;
							i++;
						}
						printf("Moved backward by %d blocks.\n",time_travel.explanation);
					}
					flag1=0;
				}
				else if(dice==3){
					temp=0;
					temp_max=0;
					printf("%s have chosen a %s card from fortune cards\n",player_two.name,garnishment.name);
					if(player_two.account>=garnishment.explanation){
						player_two.account-=garnishment.explanation;
						printf("%s paid %d $ to the bank.\n",player_two.name,garnishment.explanation);
						printf("%s current total money= %d $\n",player_two.name,player_two.account);

					}
					else{
						printf("%s doesn't have enough money to pay the garnishment\n",player_two.name);
						while(player_two.account<ptr->rent){
							if(player_two.owned_block_ids[0]==EOF){
								printf("%s doesn't have enough money to pay the garnishment and doesn't have any property to sell.\n%s went bankrupt.\n%s won the game!",player_two.name,player_two.name,player_one.name);	
								return;
							}
							else{ 
								j=0;
								while(player_two.owned_block_ids[j]!=EOF){
									i=0;
									ptr=board;
									while(i<player_two.owned_block_ids[j]){
										ptr=ptr->next;
										i++;
									}
									temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
									if(temp>temp_max){
										temp_max=temp;
										index=j;
									}
									j++;
								}
								i=0;
								ptr=board;
								while(i<player_two.owned_block_ids[index]){
									ptr=ptr->next;
									i++;
								}
								printf("%s sold the property %s.\n",player_two.name,ptr->name);
								ptr->owner.type=noone;
								ptr->house_count=0;
								player_two.account+=temp_max;
								player_two.owned_block_ids[index]=EOF;
								i=index;
								while(i<12){
									player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
									i++;
								}
								player_two.owned_block_ids[11]=EOF;
								printf("%s current total money= %d $\n",player_two.name,player_two.account);
							}
						}
					}
				}
				else if(dice==4){
					temp=0;
					temp_max=0;
					printf("%s have chosen a %s card from fortune cards\n",player_two.name,generosity.name);
					if(player_two.account>=generosity.explanation){
						player_two.account-=generosity.explanation;
						player_one.account+=generosity.explanation;
						printf("%s paid %d $ to %s.\n",player_two.name,generosity.explanation,player_one.name);
						printf("%s current total money= %d $\n",player_two.name,player_two.account);
					}
					else{
						printf("%s doesn't have enough money to pay the generosity\n",player_two.name);
						while(player_two.account<ptr->rent){
							if(player_two.owned_block_ids[0]==EOF){
								printf("%s doesn't have enough money to pay the generosity and doesn't have any property to sell.\n%s went bankrupt.\n%s won the game!",player_two.name,player_two.name,player_one.name);	
								return;
							}
							else{ 
								j=0;
								while(player_two.owned_block_ids[j]!=EOF){
									i=0;
									ptr=board;
									while(i<player_two.owned_block_ids[j]){
										ptr=ptr->next;
										i++;
									}
									temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
									if(temp>temp_max){
										temp_max=temp;
										index=j;
									}
									j++;
								}
								i=0;
								ptr=board;
								while(i<player_two.owned_block_ids[index]){
									ptr=ptr->next;
									i++;
								}
								printf("%s sold the property %s.\n",player_two.name,ptr->name);
								ptr->owner.type=noone;
								ptr->house_count=0;
								player_two.account+=temp_max;
								player_two.owned_block_ids[index]=EOF;
								i=index;
								while(i<12){
									player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
									i++;
								}
								player_two.owned_block_ids[11]=EOF;
								printf("%s current total money= %d $\n",player_two.name,player_two.account);
							}
						}
					}
				}
				else if(dice==5){
					printf("%s have chosen a %s card from fortune cards\n",player_two.name,treasue_hunter.name);
					printf("%s took %d $ from the bank.\n",player_two.name,treasue_hunter.explanation);
					player_two.account+=treasue_hunter.explanation;
					printf("%s current total money= %d $\n",player_two.name,player_two.account);
				}
			}

			else if(ptr->owner.type==noone && ptr->type==property){
				if(ptr->price<avg_cost){
					if(player_two.account<ptr->price) printf("%s could not buy this property because does not have enough money.\n",player_two.name);
					else{
						player_two.account-=ptr->price;
						i=0;
						while(player_two.owned_block_ids[i]!=EOF){
							i++;
						}
						player_two.owned_block_ids[i]=ptr->block_id;
						ptr->owner.type=car;
						printf("%s bought this property.\n",player_two.name);
						printf("%s current total money= %d $\n",player_two.name,player_two.account);
					}
				}
				else{
					dice=(rand()%DICE)+1;
					if(dice<4){
						if(player_two.account<ptr->price) printf("%s could not buy this property because does not have enough money.\n",player_two.name);
						else{
							player_two.account-=ptr->price;
							i=0;
							while(player_two.owned_block_ids[i]!=EOF){
								i++;
							}
							player_two.owned_block_ids[i]=ptr->block_id;
							ptr->owner.type=car;
							printf("%s bought this property.\n",player_two.name);
							printf("%s current total money= %d $\n",player_two.name,player_two.account);
						}
					}
					else printf("%s skiped its turn.\n",player_two.name);
				}
			}
			if(ptr->owner.type==cap){
				if(ptr->house_count==0){
					while(player_one.account<ptr->rent){
						temp=0;
						temp_max=0;
						if(player_one.owned_block_ids[0]==EOF){
							printf("%s doesn't have enough money to pay the rent and doesn't have any property to sell.\n%s went bankrupt.\nPlayer %s won the game!\n",player_two.name,player_two.name,player_one.name);
							return;	
						}
						else{
							j=0;
							while(player_two.owned_block_ids[j]!=EOF){
								i=0;
								ptr=board;
								while(i<player_two.owned_block_ids[j]){
									ptr=ptr->next;
									i++;
								}
								temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
								if(temp>temp_max){
									temp_max=temp;
									index=j;
								}
								j++;
							}
							i=0;
							ptr=board;
							while(i<player_two.owned_block_ids[index]){
								ptr=ptr->next;
								i++;
							}
							printf("%s sold the property %s.\n",player_two.name,ptr->name);
							ptr->owner.type=noone;
							ptr->house_count=0;
							player_two.account+=temp_max;
							player_two.owned_block_ids[index]=EOF;
							i=index;
							while(i<12){
								player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
								i++;
							}
							player_two.owned_block_ids[11]=EOF;
							printf("%s current total money= %d $\n",player_two.name,player_two.account);
						}
					}
					player_two.account-=ptr->rent;
					player_one.account+=ptr->rent;
					printf("%s paid the rent (%d $) to player %s.\n",player_two.name,ptr->rent,player_one.name);
				}
				if (ptr->house_count==1){
					while(player_one.account<ptr->rent_1){
						temp=0;
						temp_max=0;
						if(player_one.owned_block_ids[0]==EOF){
							printf("%s doesn't have enough money to pay the rent and doesn't have any property to sell.\n%s went bankrupt.\nPlayer %s won the game!\n",player_two.name,player_two.name,player_one.name);
							return;	
						}
						else{
							j=0;
							while(player_two.owned_block_ids[j]!=EOF){
								i=0;
								ptr=board;
								while(i<player_two.owned_block_ids[j]){
									ptr=ptr->next;
									i++;
								}
								temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
								if(temp>temp_max){
									temp_max=temp;
									index=j;
								}
								j++;
							}
							i=0;
							ptr=board;
							while(i<player_two.owned_block_ids[index]){
								ptr=ptr->next;
								i++;
							}
							printf("%s sold the property %s.\n",player_two.name,ptr->name);
							ptr->owner.type=noone;
							ptr->house_count=0;
							player_two.account+=temp_max;
							player_two.owned_block_ids[index]=EOF;
							i=index;
							while(i<12){
								player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
								i++;
							}
							player_two.owned_block_ids[11]=EOF;
							printf("%s current total money= %d $\n",player_two.name,player_two.account);
						}
					}
					player_one.account-=ptr->rent_1;
					player_two.account+=ptr->rent_1;
					printf("%s paid the rent (%d $) to player %s.\n",player_two.name,ptr->rent_1,player_one.name);
				}
				if (ptr->house_count==2){
					while(player_one.account<ptr->rent_2){
						temp=0;
						temp_max=0;
						if(player_one.owned_block_ids[0]==EOF){
							printf("%s doesn't have enough money to pay the rent and doesn't have any property to sell.\n%s went bankrupt.\nPlayer %s won the game!\n",player_two.name,player_two.name,player_one.name);
							return;	
						}
						else{
							j=0;
							while(player_two.owned_block_ids[j]!=EOF){
								i=0;
								ptr=board;
								while(i<player_two.owned_block_ids[j]){
									ptr=ptr->next;
									i++;
								}
								temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
								if(temp>temp_max){
									temp_max=temp;
									index=j;
								}
								j++;
							}
							i=0;
							ptr=board;
							while(i<player_two.owned_block_ids[index]){
								ptr=ptr->next;
								i++;
							}
							printf("%s sold the property %s.\n",player_two.name,ptr->name);
							ptr->owner.type=noone;
							ptr->house_count=0;
							player_two.account+=temp_max;
							player_two.owned_block_ids[index]=EOF;
							i=index;
							while(i<12){
								player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
								i++;
							}
							player_two.owned_block_ids[11]=EOF;
							printf("%s current total money= %d $\n",player_two.name,player_two.account);
						}
					}
					player_one.account-=ptr->rent_2;
					player_two.account+=ptr->rent_2;
					printf("%s paid the rent (%d $) to player %s.\n",player_two.name,ptr->rent_2,player_one.name);
				}
				if (ptr->house_count==3){
					while(player_one.account<ptr->rent_3){
						temp=0;
						temp_max=0;
						if(player_one.owned_block_ids[0]==EOF){
							printf("%s doesn't have enough money to pay the rent and doesn't have any property to sell.\n%s went bankrupt.\nPlayer %s won the game!\n",player_two.name,player_two.name,player_one.name);
							return;
						}
						else{
							j=0;
							while(player_two.owned_block_ids[j]!=EOF){
								i=0;
								ptr=board;
								while(i<player_two.owned_block_ids[j]){
									ptr=ptr->next;
									i++;
								}
								temp=((ptr->price)+(ptr->house_count*ptr->house_price))/2;
								if(temp>temp_max){
									temp_max=temp;
									index=j;
								}
								j++;
							}
							i=0;
							ptr=board;
							while(i<player_two.owned_block_ids[index]){
								ptr=ptr->next;
								i++;
							}
							printf("%s sold the property %s.\n",player_two.name,ptr->name);
							ptr->owner.type=noone;
							ptr->house_count=0;
							player_two.account+=temp_max;
							player_two.owned_block_ids[index]=EOF;
							i=index;
							while(i<12){
								player_two.owned_block_ids[i]=player_two.owned_block_ids[i+1];
								i++;
							}
							player_two.owned_block_ids[11]=EOF;
							printf("%s current total money= %d $\n",player_two.name,player_two.account);
						}
					}
					player_one.account-=ptr->rent_3;
					player_two.account+=ptr->rent_3;
					printf("%s paid the rent (%d $) to player %s.\n",player_two.name,ptr->rent_3,player_one.name);
				}
			}
			else if(ptr->owner.type==cap && player_two.account>=ptr->house_price && ptr->house_count<MAX_HOME_COUNT){
				i=0;
				while(player_two.owned_block_ids[i]!=EOF){
					i++;
				}
				if(i>=4){
					player_two.account-=ptr->house_price;
					ptr->house_count++;
				}
			}
		}
		else player_two.turn_to_wait--;
	}
	return;
}

int main(){
	struct block board;
	struct player player_one,player_two;
	init_the_board(&board);
	gameplay(&board,player_one,player_two);
	return 0;
}