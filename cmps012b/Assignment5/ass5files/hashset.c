// $Id: hashset.c,v 1.7 2013-05-23 15:41:07-07 - - $
//bryan ambriz
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

void double_the_hash(hashset *this);

typedef struct hashnode hashnode;
struct hashnode {
   char *word;
   hashnode *link;
};
  
struct hashset {
   size_t size;
   size_t load;
   hashnode **word;
};

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_word = this->size * sizeof (hashnode *);
   this->word = malloc (sizeof_word);
   assert (this->word != NULL);
   memset (this->word, 0, sizeof_word);
   DEBUGF ('h', "%p -> struct hashset {size = %d, word=%p}\n",
                this, this->size, this->word);
   return this;
}

void free_hashset (hashset *this) {
	for(unsigned int i = 0; i < this->size; i++){
		if(this->word[i] != NULL){
			hashnode *tmp = malloc(sizeof(hashnode));
			tmp = this->word[i];
			while(tmp != NULL){
				size_t hash_index = strhash(tmp->word) % this->size;
				
				if(this->word[hash_index] != NULL){
					tmp = this->word[hash_index];
					printf("%s", tmp->word);
					while(tmp->link != NULL){
						tmp = tmp->link;
					}
				
					free(tmp->word);
					free(tmp);
				}else{
				
					free(tmp->word);
					free(tmp);
				}
				tmp = tmp->link;
			}
		}
  free(this);
  }
   DEBUGF ('h', "free (%p)\n", this);
}

void put_hashset (hashset *this, char *item) {
	hashnode *node = malloc(sizeof(hashnode));
	char *item2 = malloc(sizeof(char)*strlen(item));
	item2 = item; 
	node->word = item2;
	node->link = NULL;
	size_t hash_index = strhash(node->word) % this->size;
    hashnode *tmp = malloc(sizeof(hashnode));
	tmp = this->word[hash_index];
	if(this->word[hash_index] != NULL){
		tmp = this->word[hash_index];
		while(tmp->link != NULL){
			tmp = tmp->link;
			if(strcmp(tmp->word,node->word) == 0) return;
		}
		tmp->link = node;
		this->load++;	
		
		fflush(stdout);
	}else{
		this->word[hash_index] = node;
		this->load++;
		}

	if(this->load*2 > this->size){
		double_the_hash(this);
	}
	
}

void double_the_hash(hashset *this){
	size_t old_size = this->size;
	this->size *= 2;
	this->size += 1;
	hashnode **newlist;
	size_t sizeof_list = this->size * sizeof (hashnode *);
    newlist = malloc (sizeof_list);
	assert (newlist != NULL);
	memset (newlist, 0, sizeof_list);

	for(unsigned int i = 0; i < old_size; i++){
		if(this->word[i] != NULL){
			hashnode *tmp = malloc(sizeof(hashnode));
			tmp = this->word[i];
			while(tmp != NULL){
				size_t hash_index = strhash(tmp->word) % this->size;
				if(newlist[hash_index] != NULL){
					tmp = newlist[hash_index];
					while(tmp->link != NULL){
						tmp = tmp->link;
					}
					newlist[hash_index] = tmp;
				
				}else{
					newlist[hash_index] = tmp;
			
				}
				tmp = tmp->link;
			}
		}
	}  

	this->word = newlist;
}

bool has_hashset (hashset *this, char *item) {
assert (this->word != NULL);

	printf(" %s %s ",this->word[1]->word, item);
     size_t wordindex = strhash (item) % this->size;
   for (hashnode *cur = this->word[wordindex]; cur != NULL; cur = cur->link) {
      if (strcmp (cur->word, item) == 0){
	
		return true;
	  }
   }

   return false;
}
