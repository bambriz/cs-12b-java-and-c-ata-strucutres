//Bryan Ambriz Bambriz

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   char *word;
   node *link;

};

int main (int argc, char **argv){
     node *head = NULL;
     for (int argi = 0; argi < 5; ++argi){
          node *node= malloc (sizeof (struct node));
          assert (node != NULL);
          node->word = argv[argi];
          node->link = head;
          head = node;

     }
     for (node *curr = head; curr->link != NULL; curr->link){
         printf ("%p->node {word=%p->[%s], link=%p}/n",
                   curr, curr->word, curr->word, curr->link);


       }

  return 9;

}
