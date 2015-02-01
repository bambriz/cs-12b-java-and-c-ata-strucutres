// $Id: dllist.java,v 1.1 2014-04-10 17:01:54-07 - - $
//bryan ambriz
//bambriz
class dllist {

   public enum position {FIRST, PREVIOUS, FOLLOWING, LAST};

   private class node {
      String item;
      node prev;
      node next;
   }

   private node first = null;
   private node current = null;
   private node last = null;
   private int currentposition = 0;

   public void setposition (position pos) {
      //throw new UnsupportedOperationException();
      switch(pos){
           case FIRST:
                     current = first;break;
           case PREVIOUS:
                     if(current == first) break;
                     current = current.prev;break;
           case FOLLOWING:
                     if(current == last)break;
                     current = current.next;break;
           case LAST:
                      current = last; break;
           default:
                    throw new IllegalArgumentException();           
      }
   }

   public boolean isempty () {
      if(first == null)
          return true;
       else
            return false;
      //throw new UnsupportedOperationException();
   }

   public String getitem () {
      if(isempty())
            throw new java.util.NoSuchElementException();
            
       return current.item;     
      //throw new UnsupportedOperationException();
   }

   public int getposition () {
      int pos = 0;
      
      if(current == null)
            throw new java.util.NoSuchElementException();
        //what we will use to iterate through the list    
       node itr = first;
       
       while( itr != current){
             ++pos;
             itr = itr.next;
       }
       // this will give us the exact index of the current node
       return pos;
      //throw new UnsupportedOperationException();
   }

   public void delete () {
            if(current == null) {
                throw new java.util.NoSuchElementException();
            }//in the case that theres only one node
            else if (first == last) { 
                 first = null;
                 last = null;
                 current = null;
            }//just delte like the first thing on the list
            else if (current == first) { 
                  current = first.next;
                  first = current;
                  current.prev = null;
                  }// delte the last node
            else if (current == last){ 
                  current = last.prev;
                  last = current;
                  current.next = null;
                  }
            else{

                 node nextNode = current.next;
                 node prevNode = current.prev;
                 prevNode.next = nextNode;
                 nextNode.prev = prevNode;
                 current = nextNode;                 
      //throw new UnsupportedOperationException();
   }
   }

   public void insert (String item, position pos) {
   //t is out temporary node which 
   //willbe used to travesrse the list
             node t = new node();
             t.item = item;
             
    // first a check to see if its an empty list
             
             if( first == null){
                 t.prev = null;
                 t.next = null;
                 first = t;
                 last = t;
                 current = t;
                 return;
             }
 // a switch that will insert it in the corresponding position
             switch (pos){
                case PREVIOUS:
    // cant go back if first soooo gotta do a lil magic
                     if(current == first){ 
                        current.prev = t;
                        t.next = current;
                        t.prev = null;
                        current = t;
                        first = t;
                        
                     }else {
                        node prevCur = current.prev;
                        current.prev = t;
                        t.next = current;
                        prevCur.next = t;
                        t.prev = prevCur;
                        current = t;
                      } 
                      break;
                case FOLLOWING:
                         if (current == last) {
                             current.next = t;
                             t.prev = current;
                             t.next = null;
                             current = t;
                             last  = t;
                         } else {
                             node nextCur = current.next;
                             current.next = t;
                             t.prev = current;
                             t.next = nextCur;
                             nextCur.prev = t;
                             current = t;
                         }
                         break;
                default:
                       throw new IllegalArgumentException();
             }

     //throw new UnsupportedOperationException();
   }
   
   
    public void print_the_lines (){
      int l = 0; //counts line
      node itr = first;
      
      while (itr != null) {
         System.out.printf("%6d %s%n",l,itr.item);
         ++l;
         itr = itr.next;
      }
   }
   
   //printing code
   /*
        node nodething = first;
        
        while(nodething != null){
             out.println("//print the line and item");
             nodething = nodething.next;
        }
        while(nodestuff != null){
           if(nodestuff.item = key)
           break;
           
           nodestuff = nodestuff.next;
           
        
        }*/
        
}

