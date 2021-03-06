#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define LOWL_OK 1
#define LOWL_FAIL 0
#define LOWL_SUCCESS 0
#define BOUNDARY_REACHED 1

typedef struct OWN{
	float data;
	struct OWN *next;
}OWN;

typedef struct{
	OWN *beg;
	OWN *cur;
}LOWL;

LOWL *lowl_create_empty(void){
	
	LOWL *l;
	
	if((l = malloc(sizeof(LOWL))) == NULL)
		return NULL;

	l->beg = NULL;
	l->cur = NULL;
	
	return l;
}

char lowl_cur_step_left(LOWL *list){
	
	OWN *prev;
	
	if(list->beg == list->cur)
		return BOUNDARY_REACHED;
		
	prev = list->beg;
	
	while(prev != list ->cur){
		if(prev->next == (struct OWN *)list->cur){
			list->cur == prev;
			return LOWL_SUCCESS;
		}
		prev = (OWN *)prev->next;	
	}
}

char lowl_cur_step_right(LOWL *list){
	
	if(list->cur->next != NULL){
		list->cur = list->cur->next;
		return LOWL_SUCCESS;
	}
	
	else 
		return BOUNDARY_REACHED;
}

OWN *lowl_insert_right(LOWL* list, float val){
	
	OWN *l;
	
	if((l = malloc(sizeof(LOWL))) == NULL)
		return NULL;
	
	l->data = val;
	
	if(list->cur == NULL && list->cur->next == NULL){
		list->cur = l;
		
		return list->cur;
	}
	
	
	l->next = list->cur->next;
	list->cur->next = l;
	
	return l;
	
}

char lowl_delete(LOWL* list){
	
	OWN *l;
	
	if(list->cur == NULL)
		return LOWL_FAIL;

	l = list->cur;
	
	if(l->next != NULL){
		
		free(list->cur);
		list->cur = l->next;
		
		return LOWL_OK;
		
	}
	
	free(list->cur);
	
	lowl_cur_step_left(list);
	
	free(l);
	
	if(l != NULL)
		return LOWL_FAIL;
	
	return LOWL_OK;

}

LOWL *lowl_create_random(unsigned int size){
	
	int i;
	LOWL *l;

	l = lowl_create_empty();
	
	for(i = 0; i < size; i++){
		l->cur = lowl_insert_right(l, (float)rand());
	}
	
	return l;
}

void lowl_destroy(LOWL *list){
	
	while(list->cur != NULL){
		lowl_delete(list);
	}
	
	free(list);

}

void lowl_print(LOWL *list){
	
	OWN *c;
	
	c = list->cur;
	list->cur = list->beg;
	
	do{
		if(c == list->cur)
			printf("-> ");
		
		printf("%f\n", list->cur->data);
		lowl_cur_step_right(list);
		
	}while(list->cur != NULL);
		
	
}

void lowl_concatenate(LOWL *a, LOWL *b){
		
	LOWL *c;
	
	c = lowl_create_empty();
		
	a->cur = a->beg;
	
	do{
		
		c->cur->data = a->cur->data;
		c->cur = c->cur->next;
		lowl_cur_step_right(a);
	
	}while(a->cur != NULL);
	
	b->cur = b->beg;
	
	do{
		
		c->cur->data = b->cur->data;
		c->cur = c->cur->next;
		lowl_cur_step_right(b);
		
	}while(b->cur != NULL);
	
	free(a);
	free(b);
}

main(){
	
	srand(time(0));
	
	LOWL *listA, *listB;
	
	listA = lowl_create_random(3);
	listB = lowl_create_random(5);
	lowl_print(listA);
	lowl_print(listB);
	
	lowl_concatenate(listA, listB);
	
	lowl_destroy(listA);
	lowl_destroy(listB);
	
	
	
}
