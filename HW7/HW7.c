/*********************************************************************************
 *       HW7_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-7                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 28.04.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DICE 6
#define SIZE 20
#define TAB_SIZE 8
#define ROW_COUNT 4
#define COLUMN_COUNT 6
#define MINES_COUNT1 145
#define MINES_COUNT2 33
#define MIDDLE_ROW_TAB 12
#define MIN_HOME_COUNT 1
#define MAX_HOME_COUNT 3
#define PASS_MONEY 10000
#define START_MONEY 100000

typedef enum {noone,cap,car}player_type;
typedef enum {start,property,tax,punish}block_type;

struct player{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
};

struct block{
	int block_id;
	char *name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	struct player owner;
	block_type type;
};

void init_the_board(struct block board[SIZE]){
	board[0].name="Start";
	board[0].block_id=0; board[0].price=0; board[0].rent=0; board[0].rent_1=0; board[0].rent_2=0; board[0].rent_3=0; board[0].house_price=0; board[0].house_count=0; board[0].type=start;
	board[1].name="Esenyurt";
	board[1].block_id=1; board[1].price=16000; board[1].rent=800; board[1].rent_1=4000; board[1].rent_2=9000; board[1].rent_3=25000; board[1].house_price=10000; board[1].house_count=0; board[1].type=property;
	board[2].name="Car Park";
	board[2].block_id=2; board[2].price=0; board[2].rent=1500; board[2].rent_1=0; board[2].rent_2=0; board[2].rent_3=0; board[2].house_price=0; board[2].house_count=0; board[2].type=tax;
	board[3].name="Tuzla";
	board[3].block_id=3; board[3].price=16500; board[3].rent=850; board[3].rent_1=4250; board[3].rent_2=9500; board[3].rent_3=26000; board[3].house_price=12000; board[3].house_count=0; board[3].type=property;
	board[4].name="Arnavutkoy";
	board[4].block_id=4; board[4].price=17000; board[4].rent=875; board[4].rent_1=4500; board[4].rent_2=10000; board[4].rent_3=28000; board[4].house_price=12000; board[4].house_count=0; board[4].type=property;
	board[5].name="Wait 2 Turn";
	board[5].block_id=5; board[5].price=0; board[5].rent=2; board[5].rent_1=0; board[5].rent_2=0; board[5].rent_3=0; board[5].house_price=0; board[5].house_count=0; board[5].type=punish;
	board[6].name="Catalca";
	board[6].block_id=6; board[6].price=20000; board[6].rent=1000; board[6].rent_1=5000; board[6].rent_2=12000; board[6].rent_3=30000; board[6].house_price=13000; board[6].house_count=0; board[6].type=property;
	board[7].name="Beykoz";
	board[7].block_id=7; board[7].price=23000; board[7].rent=1100; board[7].rent_1=5500; board[7].rent_2=12500; board[7].rent_3=33000; board[7].house_price=13000; board[7].house_count=0; board[7].type=property;
	board[8].name="Car Fix";
	board[8].block_id=8; board[8].price=0; board[8].rent=1750; board[8].rent_1=0; board[8].rent_2=0; board[8].rent_3=0; board[8].house_price=0; board[8].house_count=0; board[8].type=tax;
	board[9].name="Maltepe";
	board[9].block_id=9; board[9].price=30000; board[9].rent=1350; board[9].rent_1=7000; board[9].rent_2=15000; board[9].rent_3=40000; board[9].house_price=15000; board[9].house_count=0; board[9].type=property;
	board[10].name="Bills";
	board[10].block_id=10; board[10].price=0; board[10].rent=2000; board[10].rent_1=0; board[10].rent_2=0; board[10].rent_3=0; board[10].house_price=0; board[10].house_count=0; board[10].type=tax;
	board[11].name="Sisli";
	board[11].block_id=11; board[11].price=33000; board[11].rent=1500; board[11].rent_1=8000; board[11].rent_2=16000; board[11].rent_3=42000; board[11].house_price=16000; board[11].house_count=0; board[11].type=property;
	board[12].name="Oil";
	board[12].block_id=12; board[12].price=0; board[12].rent=2250; board[12].rent_1=8; board[12].rent_2=0; board[12].rent_3=0; board[12].house_price=0; board[12].house_count=0; board[12].type=tax;
	board[13].name="Atasehir";
	board[13].block_id=13; board[13].price=35000; board[13].rent=1600; board[13].rent_1=8500; board[13].rent_2=17000; board[13].rent_3=45000; board[13].house_price=17000; board[13].house_count=0; board[13].type=property;
	board[14].name="Sariyer";
	board[14].block_id=14; board[14].price=40000; board[14].rent=1750; board[14].rent_1=9500; board[14].rent_2=19000; board[14].rent_3=48000; board[14].house_price=19000; board[14].house_count=0; board[14].type=property;
	board[15].name="Wait 1 Turn";
	board[15].block_id=15; board[15].price=0; board[15].rent=1; board[15].rent_1=0; board[15].rent_2=0; board[15].rent_3=0; board[15].house_price=0; board[15].house_count=0; board[15].type=punish;
	board[16].name="Kadikoy";
	board[16].block_id=16; board[16].price=43000; board[16].rent=1900; board[16].rent_1=11000; board[16].rent_2=21500; board[16].rent_3=55000; board[16].house_price=23000; board[16].house_count=0; board[16].type=property;
	board[17].name="Besiktas";
	board[17].block_id=17; board[17].price=60000; board[17].rent=2500; board[17].rent_1=15000; board[17].rent_2=28000; board[17].rent_3=60000; board[17].house_price=30000; board[17].house_count=0; board[17].type=property;
	board[18].name="Vocation";
	board[18].block_id=18; board[18].price=0; board[18].rent=5000; board[18].rent_1=0; board[18].rent_2=0; board[18].rent_3=0; board[18].house_price=0; board[18].house_count=0; board[18].type=tax;
	board[19].name="Bebek";
	board[19].block_id=19; board[19].price=70000; board[19].rent=3500; board[19].rent_1=20000; board[19].rent_2=35500; board[19].rent_3=65000; board[19].house_price=35000; board[19].house_count=0; board[19].type=property;
	return;
}

void show_board(struct block board[20],struct player player_one, struct player player_two){
	int i=0,j=0,count=0,tab_space=0;
	while(i<MINES_COUNT1){
		printf("-");
		i++;
	}
	printf("\n");
	i=0;
	while(i<COLUMN_COUNT){
		printf("|\t%s\t",board[i].name);
		if(strlen(board[i].name)<TAB_SIZE) printf("\t");
		i++;
	}
	printf("|\n");
	i=0;
	while(i<COLUMN_COUNT){
		if(board[i].type==property) printf("|\t%d$\t\t",board[i].price);
		else if(board[i].type==tax) printf("|\t%d$\t\t",board[i].rent);
		else printf("|\t\t\t");
		i++;
	}
	printf("|\n");
	i=0;
	while(i<COLUMN_COUNT){
		if(i==player_one.current_block_id && i==player_two.current_block_id)	printf("|    %s\t%s     ",player_one.name,player_two.name);
		else if(i==player_one.current_block_id)	printf("|\t%s\t\t",player_one.name);
		else if(i==player_two.current_block_id)	printf("|\t%s\t\t",player_two.name);
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
	i=19; j=6;
	while(count<ROW_COUNT){
		printf("|\t%s\t",board[i].name);
		if(strlen(board[i].name)<TAB_SIZE) printf("\t");
		printf("|");
		while(tab_space<MIDDLE_ROW_TAB){
			printf("\t");
			tab_space++;
		}
		tab_space=0;
		printf("|\t%s\t",board[j].name);
		if(strlen(board[j].name)<TAB_SIZE) printf("\t");
		printf("|\n");
		if(board[i].type==property) printf("|\t%d$\t\t|",board[i].price);
		else if(board[i].type==tax) printf("|\t%d$\t\t|",board[i].rent);
		else printf("|\t\t\t|");
		while(tab_space<MIDDLE_ROW_TAB){
			printf("\t");
			tab_space++;
		}
		tab_space=0;
		if(board[j].type==property) printf("|\t%d$\t\t|\n",board[j].price);
		else if(board[j].type==tax) printf("|\t%d$\t\t|\n",board[j].rent);
		else printf("|\t\t\t|\n");
		if(i==player_one.current_block_id && i==player_two.current_block_id)	printf("|     %s\t%s     |",player_one.name,player_two.name);
		else if(i==player_one.current_block_id)	printf("|\t%s\t\t|",player_one.name);
		else if(i==player_two.current_block_id)	printf("|\t%s\t\t|",player_two.name);
		else printf("|\t\t\t|");
		while(tab_space<MIDDLE_ROW_TAB){
			printf("\t");
			tab_space++;
		}
		tab_space=0;
		if(j==player_one.current_block_id && j==player_two.current_block_id)	printf("|     %s\t%s     |\n",player_one.name,player_two.name);
		else if(j==player_one.current_block_id)	printf("|\t%s\t\t|\n",player_one.name);
		else if(j==player_two.current_block_id)	printf("|\t%s\t\t|\n",player_two.name);
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
		i--; j++; count++;
	}
	i=0;
	while(i<MINES_COUNT1){
		printf("-");
		i++;
	}
	printf("\n");
	i=15;
	while(i>=SIZE-(COLUMN_COUNT+ROW_COUNT)){
		printf("|\t%s\t",board[i].name);
		if(strlen(board[i].name)<TAB_SIZE) printf("\t");
		i--;
	}
	printf("|\n");
	i=15;
	while(i>=SIZE-(COLUMN_COUNT+ROW_COUNT)){
		if(board[i].type==property) printf("|\t%d$\t\t",board[i].price);
		else if(board[i].type==tax) printf("|\t%d$\t\t",board[i].rent);
		else printf("|\t\t\t");
		i--;
	}
	printf("|\n");
	i=15;
	while(i>=SIZE-(COLUMN_COUNT+ROW_COUNT)){
		if(i==player_one.current_block_id && i==player_two.current_block_id)	printf("|    %s\t%s     ",player_one.name,player_two.name);
		else if(i==player_one.current_block_id)	printf("|\t%s\t\t",player_one.name);
		else if(i==player_two.current_block_id)	printf("|\t%s\t\t",player_two.name);
		else printf("|\t\t\t");
		i--;
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

void show_properties(struct block board[20]){
	int i=0,selection;
	printf("Please select a property to see details:\n");
	while(i<SIZE){
		if(board[i].type==property) printf("%d -\t%s\n",i,board[i].name);
		i++;
	}
	do{
		scanf("%d",&selection);
		if(board[selection].type!=property)	printf("Your selection is invalid, please try again:");
	}while(board[selection].type!=property);
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	printf("|\t    %s    \t",board[selection].name);
	if(strlen(board[selection].name)<TAB_SIZE) printf("\t");
	printf("|\n");
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	printf("|\tRent\t\t%d$\t|\n",board[selection].rent);
	printf("|\tRent 1 H\t%d$\t|\n",board[selection].rent_1);
	printf("|\tRent 2 H\t%d$\t|\n",board[selection].rent_2);
	printf("|\tRent 3 H\t%d$\t|\n",board[selection].rent_3);
	i=0;
	while(i<MINES_COUNT2){
		printf("-");
		i++;
	}
	printf("\n");
	printf("|\tHouse Price\t%d$\t|\n",board[selection].house_price);
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

void sell_property(struct block board[20], struct player* current_player){
	int i=0,j=0,index,max,selection,total_payment=0;
	char status1,status2='Y';
	if(status2=='Y' || status2=='y'){
		printf("Bank only pays back half of the price of the property and the houses that are on the property.\n");
		printf("Properties you have:\n");
		while(current_player->owned_block_ids[i]!=EOF){
			index=(current_player->owned_block_ids[i]);
			printf("%d - %s:\n",i+1,board[index].name);
			i++;
		}
		max=i;
		i=0;
		printf("Select a property you want to sell (1 to %d):",max);
		do{
			scanf("%d",&selection);
			if(selection<1 || selection>max) printf("Your selection is invalid!\nPlease try again (Min:1 Max:%d)=",max);
		}while(selection<1 || selection>max);
		index=current_player->owned_block_ids[selection-1];
		total_payment+=(board[index].price+(board[index].house_price*board[index].house_count))/2;
		printf("Bank will pay %d $ for this property and the houses that are on the property.\nWill you accept? (Y or N):",total_payment);
		do{
			scanf(" %c",&status1);
			if(status1!='Y' && status1!='N' && status1!='y' && status1!='n') printf("Your selection is invalid!\nPlease try again (Enter Y or N):");
		}while(status1!='Y' && status1!='N' && status1!='y' && status1!='n');
		if (status1=='Y' || status1=='y'){
			board[index].owner.type=noone;
			board[index].house_count=0;
			current_player->account+=total_payment;
			total_payment=0;
			current_player->owned_block_ids[selection-1]=EOF;
			i=selection-1;
			while(i<12){
				current_player->owned_block_ids[i]=current_player->owned_block_ids[i+1];
				i++;
			}
			current_player->owned_block_ids[12]=EOF;
			printf("You sold the property.\n");
			printf("Your current total money= %d $\n",current_player->account);
		}
		else if(status1=='N' || status1=='n') printf("You canceled the sales process.\nThe property was not sold.\n");
	}
	return;
}

void gameplay (struct block board[20], struct player player_one, struct player player_two){
	srand(time(NULL));
	int i=0,selection,dice,count,index,temp_player_one_index,temp_player_two_index,game_status=1;
	struct player player_noone; player_noone.type=noone;
	/*strcpy(player_one.name,"Cap");*/ player_one.type=cap; player_one.account=START_MONEY; player_one.current_block_id=0; player_one.turn_to_wait=0;
	/*strcpy(player_two.name,"Car");*/ player_two.type=car; player_two.account=START_MONEY; player_two.current_block_id=0; player_two.turn_to_wait=0;
	while(i<12){
		player_one.owned_block_ids[i]=EOF;
		player_two.owned_block_ids[i]=EOF;
		i++;
	}
	i=0;
	while(i<SIZE){
		if(board[i].type==property) board[i].owner=player_noone;
		i++;
	}
	i=0;
	show_board(board,player_one,player_two);
	while(game_status){
		if(player_one.turn_to_wait==0){
			printf("It's %s turn.\n",player_one.name);
			do{
				index=player_one.current_block_id;
				printf("1 - Roll the dice\n2 - Show my account\n3 - Show my properties\n4 - Show property deeds\n5 - Buy Property\n6 - Buy house\n7 - Sell property\nPlease select an option to continue:");
				scanf("%d",&selection); 
				switch(selection){
					case 1:		dice=(rand()%DICE)+1;
								player_one.current_block_id+=dice;
								show_board(board,player_one,player_two);
								temp_player_one_index=player_one.current_block_id;
								player_one.current_block_id%=SIZE;
								if(temp_player_one_index!=player_one.current_block_id)	player_one.account+=PASS_MONEY;
								if(board[player_one.current_block_id].type==punish){
									player_one.turn_to_wait=board[player_one.current_block_id].rent;
									break;
								}	
								if(board[player_one.current_block_id].type==tax){
									while(player_one.account<board[player_one.current_block_id].rent){
										if(player_one.owned_block_ids[0]==EOF){
											printf("You don't have enough money to pay the tax and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!",player_two.name);	
											return;
										}
										else{
											printf("You don't have enough money to pay the tax.\nYou have to sell some properties.\n");
											sell_property(board,&player_one);
									
										}
									}
									player_one.account-=board[player_one.current_block_id].rent;
									printf("You paid the rent (%d $).\n",board[player_one.current_block_id].rent);
								}
								if(board[player_one.current_block_id].owner.type==car){
									if (board[player_one.current_block_id].house_count==0){
										while(player_one.account<board[player_one.current_block_id].rent){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=board[player_one.current_block_id].rent;
										player_two.account+=board[player_one.current_block_id].rent;
										printf("You paid the rent (%d $) to player %s.\n",board[player_one.current_block_id].rent,player_two.name);
									}
									if (board[player_one.current_block_id].house_count==1){
										while(player_one.account<board[player_one.current_block_id].rent_1){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=board[player_one.current_block_id].rent_1;
										player_two.account+=board[player_one.current_block_id].rent_1;
										printf("You paid the rent (%d $) to player %s.\n",board[player_one.current_block_id].rent_1,player_two.name);
									}
									if (board[player_one.current_block_id].house_count==2){
										while(player_one.account<board[player_one.current_block_id].rent_2){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=board[player_one.current_block_id].rent_2;
										player_two.account+=board[player_one.current_block_id].rent_2;
										printf("You paid the rent (%d $) to player %s.\n",board[player_one.current_block_id].rent_2,player_two.name);
									}
									if (board[player_one.current_block_id].house_count==3){
										while(player_one.account<board[player_one.current_block_id].rent_3){
											if(player_one.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_two.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_one);
											}
										}
										player_one.account-=board[player_one.current_block_id].rent_3;
										player_two.account+=board[player_one.current_block_id].rent_3;
										printf("You paid the rent (%d $) to player %s.\n",board[player_one.current_block_id].rent_3,player_two.name);
									}
								}
								else if(board[player_one.current_block_id].owner.type==noone && board[player_one.current_block_id].type==property){
									printf("This property has no owner.\n");
									buy_property(&board[player_one.current_block_id],&player_one);
								}
								break;

					case 2:		printf("Total money in your account= %d $\n",player_one.account);
								break;

					case 3:		i=0;
								if(player_one.owned_block_ids[i]==EOF)	printf("You don't have any property.\n");
								else{
									printf("Your properties are:\n");
									while(player_one.owned_block_ids[i]!=EOF){
										index=player_one.owned_block_ids[i];
										printf("%d - %s\n",i+1,board[index].name);
										i++;
									}
								}
								break;

					case 4:		show_properties(board);
								break;

					case 5:		buy_property(&board[index],&player_one);
								break;

					case 6:		if(board[index].owner.type==player_one.type && board[index].house_count!=MAX_HOME_COUNT && player_one.account>=board[index].house_price){
									printf("You can build Minimum:1 Maximum:%d houses on this property. How many houses do y1ou want to build=",MAX_HOME_COUNT-board[index].house_count);
									do{
										scanf("%d",&count);
										if(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-board[index].house_count) printf("You entered invalid count, please try again (Min:1 Max:%d)=",MAX_HOME_COUNT-board[index].house_count);
									}while(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-board[index].house_count);
									player_one.account-=board[index].house_price*count;
									board[index].house_count+=count;
									printf("You built %d houses on the property.\n",count);
									printf("Your current total money=%d\n",player_one.account);
								}
								else if(board[index].owner.type!=player_one.type)	printf("This property is not yours. You can't build a house.\n");
								else if(board[index].house_count==MAX_HOME_COUNT)	printf("This property has 3 houses. No more houses can be built.\n");
								else if(player_one.account<board[index].house_price)	printf("You don't have enough money to built a house.\n");
								break;

					case 7:		sell_property(board,&player_one);
								break;

					default:	printf("Your selection is invalid, please try again.");
				}
			}while(selection!=1);
		}
		else player_one.turn_to_wait--;
		if(player_two.turn_to_wait==0){
			printf("It's %s turn.\n",player_two.name);
			do{
				index=player_two.current_block_id;
				printf("1 - Roll the dice\n2 - Show my account\n3 - Show my properties\n4 - Show property deeds\n5 - Buy Property\n6 - Buy house\n7 - Sell property\nPlease select an option to continue:");
				scanf("%d",&selection); 
				switch(selection){
					case 1:		dice=(rand()%DICE)+1;
								player_two.current_block_id+=dice;
								show_board(board,player_two,player_one);
								temp_player_one_index=player_two.current_block_id;
								player_two.current_block_id%=SIZE;
								if(temp_player_one_index!=player_two.current_block_id)	player_two.account+=PASS_MONEY;
								if(board[player_two.current_block_id].type==punish) player_two.turn_to_wait=board[player_two.current_block_id].rent;
								if(board[player_two.current_block_id].type==tax){
									while(player_two.account<board[player_two.current_block_id].rent){
										if(player_two.owned_block_ids[0]==EOF){
											printf("You don't have enough money to pay the tax and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!",player_one.name);	
											return;
										}
										else{
											printf("You don't have enough money to pay the tax.\nYou have to sell some properties.\n");
											sell_property(board,&player_two);
									
										}
									}
									player_two.account-=board[player_two.current_block_id].rent;
									printf("You paid the rent (%d $).\n",board[player_two.current_block_id].rent);
								}
								if(board[player_two.current_block_id].owner.type==car){
									if (board[player_two.current_block_id].house_count==0){
										while(player_two.account<board[player_two.current_block_id].rent){
											if(player_two.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_one.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_two);
											}
										}
										player_two.account-=board[player_two.current_block_id].rent;
										player_one.account+=board[player_two.current_block_id].rent;
										printf("You paid the rent (%d $) to player %s.\n",board[player_two.current_block_id].rent,player_one.name);
									}
									if (board[player_two.current_block_id].house_count==1){
										while(player_two.account<board[player_two.current_block_id].rent_1){
											if(player_two.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_one.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_two);
											}
										}
										player_two.account-=board[player_two.current_block_id].rent_1;
										player_one.account+=board[player_two.current_block_id].rent_1;
										printf("You paid the rent (%d $) to player %s.\n",board[player_two.current_block_id].rent_1,player_one.name);
									}
									if (board[player_two.current_block_id].house_count==2){
										while(player_two.account<board[player_two.current_block_id].rent_2){
											if(player_two.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_one.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_two);
											}
										}
										player_two.account-=board[player_two.current_block_id].rent_2;
										player_one.account+=board[player_two.current_block_id].rent_2;
										printf("You paid the rent (%d $) to player %s.\n",board[player_two.current_block_id].rent_2,player_one.name);
									}
									if (board[player_two.current_block_id].house_count==3){
										while(player_two.account<board[player_two.current_block_id].rent_3){
											if(player_two.owned_block_ids[0]==EOF){
												printf("You don't have enough money to pay the rent and you don't have any property to sell.\nYou went bankrupt.\nPlayer %s won the game!\n",player_one.name);
												return;	
											}
											else{
												printf("You don't have enough money to pay the rent.\nYou have to sell some properties.\n");
												sell_property(board,&player_two);
											}
										}
										player_two.account-=board[player_two.current_block_id].rent_3;
										player_one.account+=board[player_two.current_block_id].rent_3;
										printf("You paid the rent (%d $) to player %s.\n",board[player_two.current_block_id].rent_3,player_one.name);
									}
								}
								else if(board[player_two.current_block_id].owner.type==noone && board[player_two.current_block_id].type==property){
									printf("This property has no owner.\n");
									buy_property(&board[player_two.current_block_id],&player_two);
								}
								break;

					case 2:		printf("Total money in your account= %d $\n",player_two.account);
								break;

					case 3:		i=0;
								if(player_two.owned_block_ids[i]==EOF)	printf("You don't have any property.\n");
								else{
									printf("Your properties are:\n");
									while(player_two.owned_block_ids[i]!=EOF){
										index=player_two.owned_block_ids[i];
										printf("%d - %s\n",i+1,board[index].name);
										i++;
									}
								}
								break;

					case 4:		show_properties(board);
								break;

					case 5:		buy_property(&board[index],&player_two);
								break;

					case 6:		if(board[index].owner.type==player_two.type && board[index].house_count!=MAX_HOME_COUNT && player_two.account>=board[index].house_price){
									printf("You can build Minimum:1 Maximum:%d houses on this property. How many houses do y1ou want to build=",MAX_HOME_COUNT-board[index].house_count);
									do{
										scanf("%d",&count);
										if(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-board[index].house_count) printf("You entered invalid count, please try again (Min:1 Max:%d)=",MAX_HOME_COUNT-board[index].house_count);
									}while(count<MIN_HOME_COUNT || count>MAX_HOME_COUNT-board[index].house_count);
									player_two.account-=board[index].house_price*count;
									board[index].house_count+=count;
									printf("You built %d houses on the property.\n",count);
									printf("Your current total money=%d\n",player_two.account);
								}
								else if(board[index].owner.type!=player_two.type)	printf("This property is not yours. You can't build a house.\n");
								else if(board[index].house_count==MAX_HOME_COUNT)	printf("This property has 3 houses. No more houses can be built.\n");
								else if(player_two.account<board[index].house_price)	printf("You don't have enough money to built a house.\n");
								break;

					case 7:		sell_property(board,&player_two);
								break;

					default:	printf("Your selection is invalid, please try again.");
				}
			}while(selection!=1);
		}
		else player_two.turn_to_wait--;
	}
	return;
}

int main(){
	struct block board[SIZE];
	struct player player_one,player_two;
	player_one.name="Cap";
	player_two.name="Car";
	init_the_board(board);
	gameplay(board,player_one,player_two);
	return 0;
}
