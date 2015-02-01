// $Id: queue.java,v 1.1 2014-01-16 17:44:47-08 - - $
// Bryan Ambriz
// Bambriz

import java.util.Iterator;
import java.util.NoSuchElementException;

class queue <item_t> implements Iterable <item_t> {

   private class node {
      item_t item;
      node link;
   }
   private node head = null;
   private node tail = null;

   public boolean isempty () {
      return tail == null;
   }

   public void insert (item_t newitem) {
      node t = new node();
	  t.item = newitem;
	  t.link = head;
	  head = t;
   }

   public Iterator <item_t> iterator () {
      return new itor ();
   }

   class itor implements Iterator <item_t> {
      node next = head;
      public boolean hasNext () {
         return next != null;
      }
      public item_t next () {
         if (! hasNext ()) throw new NoSuchElementException ();
         item_t result = next.item;
         next = next.link;
         return result;
      }
      public void remove () {
         for (node newtail = head; newtail != null; newtail = newtail.link){
            node oldtail = new node();
            oldtail = newtail.link;
            if (oldtail.link == null){
                tail = newtail;
                break;
                }
            }
      }
   }

}
