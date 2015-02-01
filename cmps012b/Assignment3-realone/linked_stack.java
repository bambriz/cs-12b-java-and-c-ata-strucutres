//Bryan Ambriz Bambriz
// $Id: linked_stack.java,v 1.1 2013-10-16 12:58:29-07 - - $
//
// NAME
//    class linked_stack - implementation of stack
//

import java.util.NoSuchElementException;

class linked_stack<item_t> {

   private class node {
      item_t value;
      node link;
   }

   private node top = null;

   public boolean empty() {
      return top == null;
   }

   public item_t pop() {
      if (empty()) {
         throw new NoSuchElementException ("linked_stack.pop");
      }
      //FIXME
      return null;
   }

   public void push (item_t value) {
      //FIXME
   }

}

