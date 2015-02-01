//Bryan Ambriz
//Bambriz
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int exit_status = EXIT_SUCCESS;
#define EMPTY (-1)
#define SIZE 16

struct stack {
   int top;
   double numbers[SIZE];
};

void bad_operator (const char *oper) {
   fflush (NULL);
   fprintf (stderr, "oper=\"%s\"\n", oper);
   fflush (NULL);
   exit_status = EXIT_FAILURE;
}

void push (struct stack *the_stack, double number) {
   if(the_stack->top >= SIZE - 1){
          printf ("the_stack=%p, top=%d, number=%.15g\n",
         the_stack, the_stack->top, number);
    } else {
          the_stack->numbers[++the_stack->top] = number;
	}
}

void do_binop (struct stack *the_stack, char oper) {
   if(the_stack->top <1){
          printf(" stack overflow\n");
		  printf ("the_stack=%p, top=%d, number=%.15g\n",
         the_stack, the_stack->top, the_stack->numbers[the_stack->top]);
   }else {
          double right = the_stack->numbers[the_stack->top--];
          double left = the_stack->numbers[the_stack->top--];
           switch (oper) {
              case '+': push (the_stack, (left + right)); break;
              case '-': push (the_stack, (left - right)); break;
              case '*': push (the_stack, (left * right)); break;
              case '/': push (the_stack, (left / right)); break;
            // default: bad_operator(oper); break;
         }
   }
   
} 

void do_print (struct stack *the_stack) { 

     if (the_stack->top == EMPTY) {
           printf("stack is empty    \n ");	 
		   printf ("the_stack=%p, top=%d, number=%.15g\n",
         the_stack, the_stack->top, the_stack->numbers[the_stack->top]);
      }else{         
           for (int pos = 0; pos <= the_stack->top; ++pos) {
                printf("%.15f\n",the_stack->numbers[pos]); 
            }
      }
  // printf ("the_stack=%p, 
}

void do_clear (struct stack *the_stack) {
   the_stack->top= EMPTY;
   //printf ("the_stack=%p, top=%d\n", the_stack, the_stack->top);
}

void do_operator (struct stack *the_stack, const char *oper) {
         switch (oper[0]) {
                case '+': do_binop (the_stack, '+'); break;
                case '-': do_binop (the_stack, '-'); break;
                case '*': do_binop (the_stack, '*'); break;
                case '/': do_binop (the_stack, '/'); break;
                case ';': do_print (the_stack);      break;
                case '@': do_clear (the_stack);      break;
                default : bad_operator (oper);   break; 
       }
   
   
  // printf ("the_stack=%p, top=%d, oper=\"%s\"\n",
          // the_stack, the_stack->top, oper);
}


int main (int argc, char **argv) {
   if (argc != 1) {
      fprintf (stderr, "Usage: %s\n", basename (argv[0]));
      fflush (NULL);
      exit (EXIT_FAILURE);
   }
   struct stack the_stack;
   the_stack.top = EMPTY;
   char buffer[1024];
   for (;;) {
      int scanrc = scanf ("%1023s", buffer);
      if (scanrc == EOF) break;
      assert (scanrc == 1);
      if (buffer[0] == '#') {
         scanrc = scanf ("%1023[^\n]", buffer);
         continue;
      }
      char *endptr;
      double number = strtod (buffer, &endptr);
      if (*endptr == '\0') {
         push (&the_stack, number);
      }else if (buffer[1] != '\0') {
         bad_operator (buffer);
      }else {
         do_operator (&the_stack, buffer);
      }
   }
   return exit_status;
}