#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Mname 40
#define Max 10
#define Hashmax 410
struct node{
	char name[Mname];
	int score;
	struct node *next;
};

struct node *add(int n, struct node *curr);
struct node *init(char *name, int s);
void *del(char *name, struct node *head);
struct node *nmergesort(struct node *list);
struct node *nsplit(struct node *list);
struct node *merge(struct node *list1, struct node *list2);
void show(struct node *head);
int node_count =0;

int main(){
	struct node *head = NULL;
	struct node *curr = NULL;
	head = init("head",0);
	curr = head;

	int hashtable[Hashmax]={0};
	
	int n;
	int choice;
	do{
		puts("\ninput your action:0=end, 1=add players, 2=remove players, 3=show current info,4=sort");
		scanf("%d", &choice);
		switch (choice){
			case 0:
				break;
			case 1:
				puts("how many players you want to add?");
				scanf("%d", &n);
				curr = add(n,curr);
				break;
			case 2:
				hash(head, hashtable);
				puts("who do you want to delete?");
				char hash_name[Mname];
				fflush(stdin);
				gets(hash_name);
				del_hash(hash_name,head,hashtable);
				break;
			case 3:
				show(head);		
				break;
			case 4:
				head->next = nmergesort(head->next);
				puts("complete sorting");
				break;
			
		}
	}while(choice != 0);
	return 0;
}

struct node *init(char *name, int s){
	struct node *tmp;
	tmp = (struct node *)malloc(sizeof(struct node ));
	tmp->next = NULL;
	tmp->score = s;
	strcpy(tmp->name, name);
	node_count ++;
	return tmp;
}

struct node *add(int n, struct node *curr){
	int i,id;
	char name[Mname];
	int s;
	struct node *tmp;
	while(curr){
		if(!curr->next){
			for(i=0;i<n;i++){
			printf("input the %d'th players info:\n", i+1);
			printf("name:");
			fflush(stdin);
			gets(name);
			printf("score:");
			scanf("%d",&s);
			tmp = init(name,s);
			curr->next=tmp;
			curr=curr->next;
			}
		}
		curr = curr->next;
	}
	return tmp;
}

void show(struct node *head){
	int i=0;
	puts("");
	while(head){
		if(head->score>0){
			printf("%s,avg = %d\n",head->name, head->score);
		}
		head= head->next;
		i++;
	}
	printf("there are %d players\n",node_count-1);
}

struct node *nmergesort(struct node *list){
	struct node *list1 = list;
	struct node *list2 = NULL;
	if(list1->next){
		list2 = nsplit(list1);
		list2 = nmergesort(list2);
		list1 = merge(list1,list2); 
	}
	return list1;
}

struct node *nsplit(struct node *list){
	struct node *list2 = NULL;
	while((list->score>list->next->score)&&(list->next->next)){
		list=list->next;
	}
	list2 = list->next;
	list->next = NULL;
	return list2;
}

struct node *merge(struct node *list1, struct node *list2){
	struct node *head = init("head",0.0);
	node_count --;
	struct node *tail=head;
	while(list1 && list2){
		if(list1->score>=list2->score){
			tail->next = list1;
			list1 = list1->next;
		}
		else{
			tail->next = list2;
			list2 = list2->next;
		}
		tail = tail->next;
	}
	if(list1){
		tail->next = list1;
	}
	else{
		tail->next = list2;
	}
	return head->next;
}

int hashfunction(char *name){
	int i=0;
	int sum =0;
	while(name[i]){
		sum += name[i];	
		i++;	
	}
	sum = (sum)%(Hashmax);
	return sum;
}

void hash(struct node *head, int hashtable[]){
	int i=0;
	int index=0;
	while(head){
		index = hashfunction(head->name);
		hashtable[index] = i;
		i++;
		head = head->next;
	}
}

void del_hash(char *name,struct node *head, int hashtable[]){
	int index=0;
	index = hashfunction(name);
	int i=0;
	int k;
	k = hashtable[index];
	while(head){
		if(k==i+1){
			struct node *tmp;
			tmp = head->next;
			printf("%s has been removed!\n", head->next->name);
			head->next = head->next->next;
			free(tmp);
			node_count--;
			break;
		}
		i++;
		head = head->next;
		if(i==node_count){
			puts("not found");
		}
		
	}	
}

/*
void *del(char *name, struct node *head){
	int count=0;
	while(head){
		if(strcmp(head->next->name, name)==0){
			printf("%s has been removed!\n", head->next->name);
			head->next = head->next->next;
			count ++;
			node_count--;
			break;
		}
		head=head->next;
		if(head->next==NULL){
			break;
		}
	}
	if(count ==0){
		puts("student not found");
	}
}
*/
