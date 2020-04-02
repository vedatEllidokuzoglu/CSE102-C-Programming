/*********************************************************************************
 *       HW5_161044098_VEDAT_ELLIDOKUZOGLU.c                                     *
 *       CSE 102/501 - Computer Programming Homework-5                           *
 *       Author: Vedat ELLIDOKUZOGLU                                             *
 *       Date: 03.04.2019                                                        *
 *-------------------------------------------------------------------------------*
 * See descriptions from the Homework PDF to understand the program details      *
 ********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

void fill_mines1(int array[DICT_SIZE][4]){
	int i=0,j=0;
	while(i<DICT_SIZE){
		while(j<4){
			array[i][j]=-1;
			j++;
		}
		j=0;
		i++;
	}
	return;
}

int generate_char(){
	int i;
	i=(rand()%25)+97;
	return i;
}

void print_map(char map[DICT_SIZE][DICT_SIZE]){
	int i=0,j=0;
	printf("\n");
	while(i<DICT_SIZE){
		while(j<DICT_SIZE){
			printf("%c",map[i][j]);
			j++;
		}
		printf("\n");
		j=0;
		i++;
	}
	printf("\n");
	return;
}
void place_word(char map[DICT_SIZE][DICT_SIZE],char *dict[DICT_SIZE],int coord[DICT_SIZE][4]){
	int i=0,j=0,x1,x2,y1,y2,opx,opy,counter;
	while(1){
		if(coord[i][0]==-1 || i==DICT_SIZE) break;
		x1=coord[i][0]; y1=coord[i][1]; x2=coord[i][2]; y2=coord[i][3];
		if(x1<x2) opx=1; else if(x1>x2) opx=-1; else if(x1==x2) opx=0;
		if(y1<y2) opy=1; else if(y1>y2) opy=-1; else if(y1==y2) opy=0;
		if(opx==1) counter=x2-x1; else if(opx==-1) counter=x1-x2; else if(opy==1) counter=y2-y1; else if(opy==-1) counter=y1-y2;
		counter++;
		while(counter>0){
			map[x1][y1]=dict[i][j];
			x1+=opx; y1+=opy; j++; counter--;
		}
		j=0; i++;
	}
	return;
}

int north_east(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--;	x--; y++; i++;
	}
	if(counter==temp_size){
		x+=temp_size;
		y-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			x--; y++;
			temp_size--;
		}
		status=1;
	}
	return status;
}

int east(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--;	y++; i++;
	}
	if(counter==temp_size){
		y-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			y++;
			temp_size--;
		}
		status=1;
	}
	return status;
}

int south_east(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--; x++; y++; i++;
	}
	if(counter==temp_size){
		x-=temp_size;
		y-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			x++; y++; temp_size--;
		}
		status=1;
	}
	return status;
}

int south(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--;	x++; i++;
	}
	if(counter==temp_size){
		x-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			x++;
			temp_size--;
		}
		status=1;
	}
	return status;
}

int south_west(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	x+=size-1; y-=size-1;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--;	x--; y++; i++;
	}
	if(counter==temp_size){
		x+=temp_size;
		y-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			x--; y++;
			temp_size--;
		}
		status=1;
	}
	return status;
}

int west(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	y-=size-1;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--;	y++; i++;
	}
	if(counter==temp_size){
		y-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			y++;
			temp_size--;
		}
		status=1;
	}
	return status;
}

int north_west(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	x-=size-1; y-=size-1;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--; x++; y++; i++;
	}
	if(counter==temp_size){
		x-=temp_size;
		y-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			x++; y++; temp_size--;
		}
		status=1;
	}
	return status;
}

int north(char map[DICT_SIZE][DICT_SIZE],char word[DICT_SIZE],int x,int y,char temp_map[DICT_SIZE][DICT_SIZE]){
	int i=0,size,temp_size,counter=0,status=0;
	size=get_line_size(word);
	temp_size=size;
	x-=size-1;
	while(size>0){
		if(temp_map[x][y]==word[i]) counter++;
		else break;
		size--;	x++; i++;
	}
	if(counter==temp_size){
		x-=temp_size;
		while(temp_size>0){
			if(map[x][y]>=97) map[x][y]-=32;
			x++;
			temp_size--;
		}
		status=1;
	}
	return status;
}

int checkin_dictionary(char *dict[DICT_SIZE],char word[DICT_SIZE],int size){
	int i=0,j=0,size1,size2,counter=0,status=0;
	while(size>0){
		size1=get_line_size(dict[i])-1;
		size2=get_line_size(word);
		if(size1==size2){
			while(size1>0){
				if(dict[i][j]==word[j])	counter++;
				size1--;
			}
			if(counter==size2){
				status=1; break;
			}
		}
		i++; j=0; size--;
	}
	return status;
}

int exit_game(char word[DICT_SIZE]){
	char array[9] = "exit game";
	int i=0,status;
	while(i<9){
		if(word[i]==array[i])	status++;
		else return 0;
		i++;
	}
	if(status==9 && word[i]==0)	status=1;
	return status;
}

int main(){
	srand(time(NULL));
	char a,*dict[DICT_SIZE],line[LINE_LEN],map[DICT_SIZE][DICT_SIZE],temp_map[DICT_SIZE][DICT_SIZE],word[DICT_SIZE];
    int coord[DICT_SIZE][4],line_counter=0,dict_counter=0,i=0,j=0,row,column,status1=0,status2=0,total=0,temp_total;    
	FILE *fp = fopen("word_hunter.txt", "r");
	fill_mines1(coord);
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	fclose(fp);
	while(i<DICT_SIZE){
		while(j<DICT_SIZE){
			map[i][j]=generate_char();
			j++;
		}
		j=0;
		i++;
	}
	i=0; j=0;
	printf("RANDOM MAP\n");
	print_map(map);
	place_word(map,dict,coord);
	while(i<DICT_SIZE){
		while(j<DICT_SIZE){
			temp_map[i][j]=map[i][j];
			j++;
		}
		j=0;
		i++;
	}
	i=0; j=0;
	printf("WORDS PLACED ON MAP\n");
	print_map(map);
	while(1){
		if(total==dict_counter){
			printf("You found all the words.\nCongratulations, you won the game!\n"); break;
		}
		printf("Enter a word: ");
		scanf(" %[^\n]s",word);
		status1=exit_game(word);
		if(status1==1)	break;
		printf("Enter a row coordinate (R)= ");
		scanf("%d",&row);
		printf("Enter a column coordinate (C)= ");
		scanf("%d",&column);
		status2=checkin_dictionary(dict,word,dict_counter);
		temp_total=total;
		if(status2==1){
			total+=north_east(map,word,row,column,temp_map);
			total+=east(map,word,row,column,temp_map);
			total+=south_east(map,word,row,column,temp_map);
			total+=south(map,word,row,column,temp_map);
			total+=north(map,word,row,column,temp_map);
			total+=west(map,word,row,column,temp_map);
			total+=south_west(map,word,row,column,temp_map);
			total+=north_west(map,word,row,column,temp_map);
			if(temp_total!=total){
				printf("You found the word!\n");
				print_map(map);
			}
			status2=0;
		}
		if (temp_total==total) printf("No such words. Try again.\n");
		temp_total=total;
	}
	return 0;
}
