/*408415035 盧佳玟	408415049 施湘芸
  408415055 朱沛哲	408415057 郭宗翰*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define size 300
#define Q1_time 1
#define Q2_time 3
#define Q3_time 7
#define max_time 30
typedef struct node // the type of list
{
	int item;	 	// item name
	int type;		// item type
	int arrival; 	// the arrival time of item
	struct node *next;
} dType;

typedef struct Q	//the type of production line
{
	int count;		// calculate how many item in
	struct node *front, *rear;
} qType;

typedef struct T	//record the data and process time of deleted data
{
	struct node *temp;
	int process_time;
} tType;

///*these function are completed*///
dType *create_node(dType *, int, int, int);				
void create_data(dType **, int, int, int);				
void print_data(dType *, FILE *);
qType *create_queue();
qType *enQ(qType *, dType *);
int emptyQ(qType *);
dType *deQ(qType *);
void process_Q(dType *, qType *, qType *, qType *);
void printdata(dType *);
void PrintTime(int, int, int);

int main()
{
	srand(time(NULL));

	dType *list = NULL;			// list is the data
	//put the data into three production line
	qType *q1 = create_queue(), *q2 = create_queue(), *q3 = create_queue(); 
	int i, RandNum;
	char filename[10], check[1000];

	FILE *inp;

	for (i = 0; i < size; i++)
		check[i] = 0;

	printf("Enter your filename:");
	scanf("%s", filename);

	inp = fopen(filename, "w");

	i = 0;
	while (i < size){
		RandNum = rand() % 1000;
		/*make sure the name of data do not repeat*/
		if (check[RandNum] == 0){
			//create the data with random number
			create_data(&list, RandNum, rand() % 3 + 1, rand() % 20); 
			i++;
			check[RandNum] = 1;
		}
	}
	/* show the data */
	print_data(list, inp);
	fclose(inp);
	process_Q(list, q1, q2, q3);
}

///** be used to store new  data **///
dType *create_node(dType *p, int item, int type, int arrival)
{
	p = malloc(sizeof(dType));
	p->item = item;		  // item name
	p->type = type;		  // item type
	p->arrival = arrival; // the arrival time of item
	p->next = NULL;
	return p;
}
///** sort the data by time **///
void create_data(dType **L, int item, int type, int arrival)
{
	dType *p = NULL, *head = *L; //head is to remember the first place
	p = create_node(p, item, type, arrival);

	if (*L == NULL) //when L is empty
		*L = p;
	else if (p->arrival < (*L)->arrival){ //when p->arrival_time is smallest
		p->next = *L;
		*L = p;
	}
	else{			//others
		/*find the right place the new data should be placed*/
		while (head->next != NULL && head->next->arrival < p->arrival)
			head = head->next;
		p->next = head->next;
		head->next = p;
	}
}
///** SHOW the data inside  **///
void print_data(dType *L, FILE *inp)
{
	while (L != NULL){
		//printf("item%4d of type%d arriving at time%2d\n",L->item,L->type,L->arrival);
		fprintf(inp, "item%4d of type%d arriving at time%2d\n", L->item, L->type, L->arrival);
		L = L->next;
	}
	printf("\n");
}
///** create_queue  **///
qType *create_queue()
{
	//initialize the queue and return the pointer
	qType *q = malloc(sizeof(qType)); 
	q->count = 0;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

///*insert the node into the queue*///
qType *enQ(qType *q, dType *to_remove)
{
	dType *t = create_node(t, to_remove->item, to_remove->type, to_remove->arrival);
	// t is a temporary node

	if (q->count == 0){		 //when q is empty
		q->front = t;
		q->rear = t;
	}
	else{
		q->front = q->front; //put at the rear
		q->rear->next = t;
		q->rear = t;
	}
	q->count++; //add the the number of counter
	return q;
}

///** support the  <process_Q> below **///
int emptyQ(qType *q)
{
	if (q->count == 0)
		return 1;
	else
		return 0;
}

///** delete a node **///
dType *deQ(qType *q)
{
	dType *temp;
	q->count--;
	temp = q->front;
	q->front = q->front->next; //remove the first node
	return temp;			   //update the pointer
}
///*process the data of the production line*///
void process_Q(dType *list, qType *q1, qType *q2, qType *q3)
{
	dType *to_remove = NULL, *head = list;
	int don_repeat_print_time = 1;
	int time = 0;	//now time
	//data have to go out the queue
	tType *to_go_1 = NULL, *to_go_2 = NULL, *to_go_3 = NULL;	
	int total_waiting_time_1 = 0, total_waiting_time_2 = 0, total_waiting_time_3 = 0;
	//item has processed
	int processed_item_Q1 = 0, processed_item_Q2 = 0, processed_item_Q3 = 0;
	while (time <= max_time){	//a counter
		if (don_repeat_print_time == 1)
			printf("Now Time(Counter):%d\n", time);
		if (head != NULL)
			to_remove = create_node(to_remove, head->item, head->type, head->arrival);

		if (time == to_remove->arrival){
			printf("enQ item%3d of type%d\n", to_remove->item, to_remove->type);
			switch (to_remove->type){
			case 1:
				q1 = enQ(q1, to_remove); //enQ the item to line
				break;
			case 2:
				q2 = enQ(q2, to_remove);
				break;
			default:
				q3 = enQ(q3, to_remove);
				break;
			}
			head = head->next; //remove the first node
		}

		if (!emptyQ(q1) || to_go_1 != NULL){
			if (to_go_1 == NULL){	//make a node
				to_go_1 = malloc(sizeof(tType));
				to_go_1->temp = deQ(q1);
				to_go_1->process_time = Q1_time;
			}
			//deQ the item and show the waiting time
			if (time >= to_go_1->temp->arrival && to_go_1->process_time == Q1_time){
				total_waiting_time_1 += time - to_go_1->temp->arrival;
				//record the time
				printf("deQ item%d of type%d, ", to_go_1->temp->item, to_go_1->temp->type); 
				printf("waiting time is %d\n", time - to_go_1->temp->arrival);
				processed_item_Q1++;
			}
			if (to_go_1->process_time == 0){
				free(to_go_1); //free the temp data
				to_go_1 = NULL;
			}
		}
		if (!emptyQ(q2) || to_go_2 != NULL){ //same thing
			if (to_go_2 == NULL){
				to_go_2 = malloc(sizeof(tType));
				to_go_2->temp = deQ(q2);
				to_go_2->process_time = Q2_time;
			}
			if (time >= to_go_2->temp->arrival && to_go_2->process_time == Q2_time){
				total_waiting_time_2 += time - to_go_2->temp->arrival;
				printf("deQ item%d of type%d, ", to_go_2->temp->item, to_go_2->temp->type);
				printf("waiting time is %d\n", time - to_go_2->temp->arrival);
				processed_item_Q2++;
			}
			if (to_go_2->process_time == 0){
				free(to_go_2);
				to_go_2 = NULL;
			}
		}
		if (!emptyQ(q3) || to_go_3 != NULL) //same thing
		{
			if (to_go_3 == NULL){
				to_go_3 = malloc(sizeof(tType));
				to_go_3->temp = deQ(q3);
				to_go_3->process_time = Q3_time;
			}
			if (time >= to_go_3->temp->arrival && to_go_3->process_time == Q3_time){
				total_waiting_time_3 += time - to_go_3->temp->arrival;
				printf("deQ item%d of type%d, ", to_go_3->temp->item, to_go_3->temp->type);
				printf("waiting time is %d\n", time - to_go_3->temp->arrival);
				processed_item_Q3++;
			}
			if (to_go_3->process_time == 0){
				free(to_go_3);
				to_go_3 = NULL;
			}
		}
		if (to_go_1 != NULL)
			to_go_1->process_time--; //count the the remaining process time
		if (to_go_2 != NULL)
			to_go_2->process_time--;
		if (to_go_3 != NULL)
			to_go_3->process_time--;

		//if the time have more two item stop the counter and continue read the data
		if (head != NULL && head->arrival == time) 
			don_repeat_print_time = 0;
		else if (head != NULL && head->arrival != time){
			don_repeat_print_time = 1;
			time++;
		}
		else if (head == NULL){
			don_repeat_print_time = 1;
			time++;
		}
		printf("\n");
	}
	PrintTime(1, total_waiting_time_1, processed_item_Q1); //print the time and item
	PrintTime(2, total_waiting_time_2, processed_item_Q2);
	PrintTime(3, total_waiting_time_3, processed_item_Q3);
}

void printdata(dType *L)
{
	//print the arrival time
	while (L != NULL){
		printf("item%4d of type%d arriving at time%2d\n", L->item, L->type, L->arrival); 
		L = L->next;
	}
	printf("\n");
}
void PrintTime(int type, int total_waiting_time, int number_of_item)
{
	//record the average time
	float average = (float)total_waiting_time / number_of_item; 
	printf("total waiting time of Q%d is %d\n", type, total_waiting_time);
	printf("average waiting time for type%d of items is %f\n", type, average);
	printf("number of processed item: %d\n", number_of_item);
	printf("\n");
}
