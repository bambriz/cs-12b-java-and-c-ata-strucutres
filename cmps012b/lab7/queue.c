// Bryan Ambriz Bambriz

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
     queue *new_queue = malloc (sizeof (struct queue));
     //assert (this != NULL); 
 // STUBPRINTF ("return NULL\n");
   return new_queue;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   memset (this, 0, sizeof (struct queue));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
     queue_node *tmp = malloc (sizeof (struct queue));
     tmp->item = item;
     
     if(this->rear != NULL){
        this->rear->link = tmp;
        this->rear = tmp;
     }else{
         this->front = tmp;
         this->rear = tmp;
         }
      
 // STUBPRINTF ("item =\n\t\"%s\"\n", item);
}

queue_item_t remove_queue (queue *this) {
   assert (! isempty_queue (this));
   queue_node *t = this->front->link;
   queue_item_t r = this->front->item;
   free(this->front->item);
   free(this->front);
   this->front = t;
   return r;
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}

