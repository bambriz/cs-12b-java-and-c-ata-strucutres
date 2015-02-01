// $Id: bigint.c,v 1.13 2014-01-24 18:33:47-08 - - $
//Bryan Ambriz bambriz
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

static void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

//initializes big int with default values
bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity*2, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}


bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;
}

static bigint *do_add (bigint *this, bigint *that) {
    DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   bigint *add = this;
  add->size++;
  int digit = 0;
  int carry = 0; 
  int thatBI = 0;
  int thisBI = 0;

  for(int index = 0; index <=(int)(add->size);index++){
    if((int)(that->size-1)<index) thatBI = 0;
    else thatBI = that->digits[index];
    if((int)(this->size-1)<index) thisBI = 0;
    else thisBI = this->digits[index];
    digit = thisBI + thatBI + carry;
    add->digits[index] = digit%10;
    digit/=10;
    carry = digit;
   
  }

  trim_zeros(add);
  return add;
}

static bigint *do_sub (bigint *this, bigint *that) {
  bigint *minus = this;
   minus->size++;
   int digit = 0;
   int carry = 0;
   int thisBI = 0;
   int thatBI = 0;

   for(int index = 0; index <(int)(minus->size); index++){
      if((int)(this->size-1)<index) thatBI = 0;
        else thatBI = that->digits[index];
      if((int)(this->size-1) < index) thisBI = 0;
        else thisBI = this->digits[index];
      digit = thisBI - thatBI - carry;
      carry = 0;
      if(digit<0){
         carry ++;
         digit+=10;
      }
      minus->digits[index] = digit%10;
   }
  
   trim_zeros(minus);
   return minus;


   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   STUB (return NULL);
}
void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

char comparador(bigint *this, bigint *that){
    char returner;
    if(this->size > that->size)
         returner = 1;
    else if(that->size> this->size)
            returner = -1;
           else
              returner = 0;
              
              
     return returner;
}
 

char overCompensating (bigint *this, bigint *that){
    size_t Phallic = this->size;
      do{
          Phallic--;
          if(this->digits[Phallic] > that->digits[Phallic])
                  return 1;
             else if (this->digits[Phallic]< that->digits[Phallic])
                      return -1;
                      
             } while (Phallic != 0);
             
             return 0;
             
     }


void print_bigint (bigint *this, FILE *file) {
  
   /*while(*file != NULL){
        for(size_t i =0; i<file->size; i++){
              fp
        }
   }*/
    if(this == NULL){
      printf("mydc: stack empty\n");
      return;
   }
   int num = 0;
   if(this->negative == true){
      fprintf(file,"-");
      for(int i = this->size-1; i >=0; i--){
         printf("%d", this->digits[i]);
         num++;
         if(num >= 70){
            printf("\n");
            num = 0;
        }
    }
      printf("\n");
   } else{
      for(int i = this->size-1; i>=0; i--){
         printf("%d",this->digits[i]);
         num++;
         if(num >= 70){
           printf("\n");
           num = 0;
         }  
      }
      printf("\n");
   DEBUGS ('b', show_bigint (this));
}
}
bigint *add_bigint (bigint *this, bigint *that) {
  /* DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   bigint *result = new_bigint (this->capacity);
   if ( (this->negative == true && that->negative == true)
   || (this->negative == false && that->negative == false) ){
   result = do_add(this, that);
       if (this->negative ==true){
           result->negative = true;
       }else{
           result->negative = false;
       }
   }else{ 
       if(comparador(this, that) > 0){
            result=do_sub(this,that);
            result->negative = this->negative;
           } else if(comparador(this, that) < 0){
                     result=do_sub(that,this);
            result->negative = that->negative; 
           }else{
                 if(overCompensating(this,that)>=0){
                      result = do_sub(this,that);
                      result->negative=this->negative;
                }else if(overCompensating(this,that)<0){
                             result = do_sub(that,this);
                              result->negative=this->negative;
                }
           }
   }
       return result;
   
  // STUB (return NULL);
 //  return NULL;
 */
 
   DEBUGS ('b', show_bigint (this));
  DEBUGS ('b', show_bigint (that));
  bigint *result;
  bigint *max = NULL;
  bigint *min = NULL;
  bool isEqual = false;
  int great = 0;
  if(this->size > that->size){ 
     great = this->size; 
  }else if (that->size > this->size){ 
     great = that->size;
  }else{ 
     great = this->size;
    }

  for(int i = great; i >=0; i--){ 
     if(this->digits[i] > that->digits[i]){
        isEqual = false; break;
     } else if (that->digits[i] > this->digits[i]){
        isEqual = true; break;
      } else if (this->digits[i] == that->digits[i]) {
          continue;
      } else{
          continue;
      }
    }

  if(isEqual == false){
    max = this;
    min = that;
  }else if (isEqual == true){
    min = this;
    max = that;
   }
  
  if(this->negative == that->negative)
    result = do_add(max,min);
   else{
    result = do_sub(max,min);
  }
  result->negative = max->negative;
  return result;
}

bigint *sub_bigint (bigint *this, bigint *that) {  
  /* DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   bigint *result = new_bigint (this->capacity);
   if ( (this->negative != true && that->negative != true)
   || (this->negative != false && that->negative != false) ){
   result = do_add(this, that);
       if (this->negative == true){
           result->negative = true;
       }else{
           result->negative = false;
       }
   }else{ 
       if(comparador(this, that) > 0){
            result=do_sub(this,that);
            result->negative = this->negative;
           } else if(comparador(this, that) < 0){
                     result=do_sub(that,this);
            result->negative = that->negative; 
           }else{
                 if(overCompensating(this,that)>=0){
                      result = do_sub(this,that);
                      result->negative=this->negative;
                }else if(overCompensating(this,that)<0){
                             result = do_sub(that,this);
                              result->negative=this->negative;
                }
           }
   }
       return result;

   STUB (return NULL);
   return NULL; */
   DEBUGS ('b', show_bigint (this));
  DEBUGS ('b', show_bigint (that));
  bigint *result;
  bigint *max = NULL;
  bigint *min = NULL;
  bool isEqual = false;
  int great = 0;

  if(this->size > that->size){ 
      great = this->size; 
  } else if (that->size > this->size){ 
      great = that->size;
  } else{ 
      great = this->size;
  }

for(int i = great; i >=0; i--){ 
      if(this->digits[i] > that->digits[i]){
          isEqual = false; break;
      } else if (that->digits[i] > this->digits[i]){
          isEqual = true; break;
      } else if (this->digits[i] == that->digits[i]) {
          continue;
      } else{
          continue;
      }
    }

   if(isEqual == false){
      max = this;
      min = that;
   }else if (isEqual == true){
      min = this;
      max = that;
   }

   if(this->negative == that->negative){
      result = do_sub(max,min);
   if(max == that)
      result->negative = (max->negative == true)?false:true;
   }else{
    result = do_add(max,min);
    result->negative = (that->negative == true)?false:true;
   }
   return result; 
}


bigint *mul_bigint (bigint *this, bigint *that) {
   bigint *final = new_bigint(this->size + that->size +1);
   int maxCap = final->capacity;
   for (int i = 0; i < maxCap; i++) {
      final->digits[i] = 0;
   }
   int digit = 0;
   int sizeOfThis = this->size;
   int sizeOfThat = that->size;
   for (int a = 0; a < sizeOfThis; a++) {
      int carry = 0;
      for (int b = 0; b < sizeOfThat; b++) {
         digit = final->digits[a+b] + 
                 this->digits[a] * that->digits[b] + carry;
         final->digits[a+b] = digit % 10;
         carry = digit / 10;
      
       } final->digits[a+that->size] = carry;
   }
   final->size = final->capacity;
   trim_zeros(final);
   if(this->negative != that->negative)
      final->negative = true;
   return final;
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
     fprintf (stderr, "}\n");
}

