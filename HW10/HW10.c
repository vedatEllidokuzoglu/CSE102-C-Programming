#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

typedef struct stack{
	int data;
	struct stack *next;
}stack;

typedef struct queue{
	int data;
	struct queue *next;
}queue;

typedef struct bst{
	int data;
	struct bst *left;
	struct bst *right;
}bst;


void print_stack(stack *stack_){
	stack *stack_head=stack_;
	while(stack_head!=NULL){
		printf("%d ",stack_head->data);
		stack_head=stack_head->next;
	}
	printf("\n");
	return;
}

void print_queue(queue *queue_){
	queue *queue_head=queue_;
	while(queue_head->next!=NULL){
		printf("%d ",queue_head->data);
		queue_head=queue_head->next;
	}
	printf("\n");
	return;
}

void print_bst(bst *bst){
	if (bst==NULL) return;
	print_bst(bst->right);
	printf("%d ",bst->data);
	print_bst(bst->left);
	return;
}

void fill_mines_one(int array[SIZE]){
	int i=0;
	while(i<SIZE){
		array[i]=EOF;
		i++;
	}
	return;
}

void fill_structures(stack **stack_,queue **queue_,bst **bst_,int data[SIZE]){
	clock_t start_t,end_t;
	double total_t1,total_t2,total_t3;
	int i=0;
	stack *stack_head=*stack_,*ptr1=NULL;
	queue *queue_head;
	bst *bst_head;
	
	start_t=clock();
	while(i<SIZE+1){
		stack_head=(stack*)malloc(sizeof(stack));
		stack_head->data=data[i];
		stack_head->next=ptr1;
		ptr1=stack_head;
		stack_head=stack_head->next;
		i++;
	}
	*stack_=stack_head;
	end_t=clock();
	
	total_t1=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	
	start_t=clock();
	*queue_=(queue*)malloc(sizeof(queue));
	i=0;
	queue_head=*queue_;
	while(i<SIZE){
		queue_head->data=data[i];
		queue_head->next=(queue*)malloc(sizeof(queue));
		queue_head=queue_head->next;
		i++;
	}
	queue_head=NULL;
	end_t=clock();
	
	total_t2=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	i=0;
	
	start_t=clock();
	*bst_=(bst*)malloc(sizeof(bst));
	bst_head=*bst_;
	bst_head->data=data[i];
	bst_head->left=NULL;
	bst_head->right=NULL;
	i++;
	while(i<SIZE){
		if(data[i]<=bst_head->data){
			if (bst_head->left==NULL){
				bst_head->left=(bst*)malloc(sizeof(bst));
				bst_head=bst_head->left;
				bst_head->data=data[i];
				bst_head->left=NULL;
				bst_head->right=NULL;
				i++;
				bst_head=*bst_;
			}
			else bst_head=bst_head->left;
		}
		if(data[i]>bst_head->data){
			if (bst_head->right==NULL){
				bst_head->right=(bst*)malloc(sizeof(bst));
				bst_head=bst_head->right;
				bst_head->data=data[i];
				bst_head->left=NULL;
				bst_head->right=NULL;
				i++;
				bst_head=*bst_;
			}
			else bst_head=bst_head->right;
		}
	}
	end_t=clock();
	
	total_t3=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	printf("FILL STRUCTURES\n");
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.2f\t%.2f\t%.2f\n",total_t1,total_t2,total_t3);
	return;

}

void ordered_print(stack * stack_, queue * queue_, bst * bst_){
	clock_t start_t,end_t;
	double total_t1,total_t2,total_t3;
	int temp;
	stack *temp_stack1,*temp_stack2;
	queue *temp_queue1,*temp_queue2;
	temp_stack1=stack_;
	temp_stack2=stack_;
	
	start_t=clock();
	while(temp_stack1!=NULL){
		while(temp_stack2->next!=NULL){
			if(temp_stack1->data > temp_stack2->data){
				temp=temp_stack1->data;
				temp_stack1->data=temp_stack2->data;
				temp_stack2->data=temp;
			}
			temp_stack2=temp_stack2->next;
		}
		temp_stack2=stack_;
		temp_stack1=temp_stack1->next;
	}
	printf("\nORDERED PRINT\n");
	printf("Stack: ");
	print_stack(stack_);
	end_t=clock();
	
	total_t1=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	temp_queue1=queue_;
	temp_queue2=queue_;
	
	start_t=clock();
	while(temp_queue1!=NULL){
		while(temp_queue2->next!=NULL){
			if(temp_queue1->data > temp_queue2->data){
				temp=temp_queue1->data;
				temp_queue1->data=temp_queue2->data;
				temp_queue2->data=temp;
			}
			temp_queue2=temp_queue2->next;
		}
		temp_queue2=queue_;
		temp_queue1=temp_queue1->next;
	}
	printf("Queue: ");
	print_queue(queue_);
	end_t=clock();
	
	total_t2=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	
	start_t=clock();
	printf("BST: ");
	print_bst(bst_);
	printf("\n");
	end_t=clock();
	
	total_t3=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.2f\t%.2f\t%.2f\n\n",total_t1,total_t2,total_t3);
	return;
}

void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search){
	int array[SIZE],i=0,index=0,flag=0;
	clock_t start_t,end_t;
	double total_t1,total_t2,total_t3;
	stack *stack_head;
	queue *queue_head;
	bst *bst_head;
	bst_head=bst_;
	stack_head=stack_;
	queue_head=queue_;
	fill_mines_one(array);
	printf("SEARCH\n");
	start_t=clock();
	while(stack_head!=NULL){
		if(stack_head->data==val_to_search){
			array[i]=index;
			i++;
		}
		stack_head=stack_head->next;
		index++;
	}
	printf("Stack: ");
	if(array[0]==EOF) printf("No result founded.\n");
	else{
		printf("%d result founded on ",i);
		i=0;
		while(array[i]!=EOF){
			printf("%d. ",array[i]+1);
			i++;
		}
		printf("step.\n");	
	}
	fill_mines_one(array);
	i=0;
	index=0;
	end_t=clock();
	total_t1=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;

	start_t=clock();
	while(queue_head->next!=NULL){
		if(queue_head->data==val_to_search){
			array[i]=index;
			i++;
		}
		queue_head=queue_head->next;
		index++;
	}
	printf("Queue: ");
	if(array[0]==EOF) printf("No result founded.\n");
	else{
		printf("%d result founded on ",i);
		i=0;
		while(array[i]!=EOF){
			printf("%d. ",array[i]+1);
			i++;
		}
		printf("step.\n");	
	}
	fill_mines_one(array);
	i=0;
	index=0;
	end_t=clock();
	total_t2=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;

	start_t=clock();
	do{
		if(bst_head->data==val_to_search){
			flag=1;
			array[i]=index;
			i++;
			if(bst_head->left==NULL) break;
			if(bst_head->left->data==val_to_search){
 				while(bst_head->data==val_to_search){
					index++;
					array[i]=index;
					i++;
					if(bst_head->left==NULL ||  bst_head->left->data!=val_to_search) break;
					bst_head=bst_head->left;
				}
			}
		}
		if(flag==1) break;
		if(val_to_search<=bst_head->data){
			bst_head=bst_head->left;
		}
		else{
			bst_head=bst_head->right;
		}
		index++;
	}while(flag==0);
	printf("BST: ");
	if(array[0]==EOF) printf("No result founded.\n");
	else{
		if(i!=1){
			printf("%d result founded on ",i-1);
			i=0;
			while(array[i+1]!=EOF){
				printf("%d. ",array[i]+1);
				i++;
			}
		}
		else{
			printf("%d result founded on ",i);
			i=0;
			while(array[i]!=EOF){
				printf("%d. ",array[i]+1);
				i++;
			}
		}
		printf("step.\n");	
	}
	end_t=clock();
	total_t3=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.2f\t%.2f\t%.2f\n\n",total_t1,total_t2,total_t3);
	return;
}

void special_traverse(stack * stack_, queue * queue_, bst * bst_){
	int flag=0;
	clock_t start_t,end_t;
	double total_t1,total_t2,total_t3=0.0;
	stack *stack_head,*stack_tail,*stack_temp_tail;
	queue *queue_head,*queue_tail,*queue_temp_tail;
	printf("SPECIAL TRAVERSE\n");
	start_t=clock();
	stack_head=stack_;
	stack_tail=stack_;
	stack_temp_tail=stack_;
	while(stack_temp_tail->next->next!=NULL){
		stack_temp_tail=stack_temp_tail->next;
		stack_tail=stack_temp_tail->next;
	}
	printf("Stack: ");
	while(flag==0){
		printf("%d ",stack_head->data);
		printf("%d ",stack_tail->data);
		stack_tail=stack_temp_tail;
		stack_head=stack_head->next;
		stack_temp_tail=stack_;
		while(stack_temp_tail->next!=stack_tail){
			stack_temp_tail=stack_temp_tail->next;
		}
		if(stack_head->next==stack_temp_tail->next){
			printf("%d ",stack_head->data);
			printf("%d  \n",stack_tail->data);
			flag=1;
		}
	}
	end_t=clock();
	total_t1=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	flag=0;

	start_t=clock();
	queue_head=queue_;
	queue_tail=queue_;
	queue_temp_tail=queue_;
	while(queue_temp_tail->next->next->next!=NULL){
		queue_temp_tail=queue_temp_tail->next;
	}
	queue_tail=queue_temp_tail->next;
	printf("Queue: ");
	while(flag==0){		
		printf("%d ",queue_head->data);
		printf("%d ",queue_tail->data);
		queue_tail=queue_temp_tail;
		queue_head=queue_head->next;
		queue_temp_tail=queue_;
		while(queue_temp_tail->next!=queue_tail){
			queue_temp_tail=queue_temp_tail->next;
		}
		if(queue_head->next==queue_temp_tail->next){
			printf("%d ",queue_head->data);
			printf("%d  \n",queue_tail->data);
			flag=1;
		}
	}
	end_t=clock();
	total_t2=((double)(end_t-start_t))/CLOCKS_PER_SEC*1000;
	printf("Structures\tStack\tQueue\tBST\n");
	printf("Exec. Time\t%.2f\t%.2f\t%.2f\n\n",total_t1,total_t2,total_t3);
	return;
}

int main(){
	int data[20]={5,2,7,8,11,3,21,7,6,15,19,35,24,1,8,12,17,8,23,4};
	bst *bst_;
	queue *queue_;
	stack *stack_;
	fill_structures(&stack_,&queue_,&bst_,data);
	ordered_print(stack_,queue_,bst_);
	search(stack_,queue_,bst_,5);
	special_traverse(stack_,queue_,bst_);
	return 0;
}