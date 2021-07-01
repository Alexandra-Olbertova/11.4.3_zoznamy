#include <stdio.h>
#include<stdlib.h>
#include<time.h>

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
	
	l = (LOWL *)malloc(sizeof(LOWL));
	
	if(l == NULL)
		return NULL;
		
	l->beg = NULL;
	l->cur = NULL;
	
	return l;
}

char lowl_cur_step_left(LOWL *list){
	
	OWN *prev;
	
	if(list->beg == list->cur)
		BOUNDARY_REACHED;
		
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
	
	if(list->cur != NULL){
		list->cur = list->cur->next;
		return LOWL_SUCCESS;
	}
	
	else 
		return BOUNDARY_REACHED;
}

OWN *lowl_insert_left(LOWL* list, float val){
	
	OWN *l;
	
	l = malloc(sizeof(LOWL));
	
	if(l == NULL)
		return NULL;
	
}

OWN *lowl_insert_right(LOWL* list, float val){
	
	OWN *l;
	
	l = malloc(sizeof(LOWL));
	
	if(l == NULL)
		return NULL;
	
	l->data = val;
	
	if( list == NULL){
		
		list->beg = l;
		list->cur = list->beg;
		
	}
	
	
	l->next = list->cur->next;
	list->cur->next = l;
	
	return l;
	
}


LOWL *lowl_create_random(unsigned int size){
	
	int i;
	LOWL *l;
	
	l = (LOWL *)malloc(sizeof(LOWL));
	if(l = NULL)
		return NULL;
		
	l = lowl_create_empty();
	
	for(i = 0; i < size; i++){
		
		l->cur->data = rand();
		lowl_cur_step_right(l);
		
	}
}

void lowl_destroy(LOWL *list){
	
	while(list->cur != NULL){
		lowl_delete(list);
	}

}

void lowl_print(LOWL *list){

	list->cur = list->beg;
	
	while(list->cur != NULL){
		
		printf(" %f ", list->cur->data);
		lowl_cur_step_right(list);
		
	}
		
	
}

void lowl_concatenate(LOWL *a, LOWL *b){
	
	int i;
	
	a->cur = a->beg;
	
	for(i = 0; i < sizeof(a); i++)
		a->cur = a->cur->next;	
	
	b->cur = b->beg;
	
	for(i = 0; i < sizeof(b); i++){
		
		a->cur = a->cur->next;
		a->cur->data = b->cur->data;
		b->cur = b->cur->next;
			
	}
	
	free(b);
	
}

main(){
	
	LOWL *list;
	
	list = lowl_create_empty();
	list = lowl_create_random(3);
	lowl_print(list);
	
}
