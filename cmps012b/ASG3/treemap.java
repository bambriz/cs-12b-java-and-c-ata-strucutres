// $Id: treemap.java,v 1.1 2014-01-16 17:44:47-08 - - $
//Bryan Ambriz
//bambriz

import static java.lang.System.*;

class treemap <key_t extends Comparable <key_t>, value_t> {

   private class node {
      key_t key;
      value_t value;
      node left;
      node right;
   }
   private node root;

   private void debug_dump_rec (node tree, int depth) {
      if(tree != null){
            debug_dump_rec (tree.left, depth+1);
            for(int tits = 0; tits<depth; tits++){
            out.print(" ");
            }
             out.printf("%d, %s, %s",depth, tree.key, tree.value);
             debug_dump_rec (tree.right, depth+1);
        }
   }

   private void do_visit_rec (visitor <key_t, value_t> visit_fn,
                              node tree) {
       if(tree != null){
            do_visit_rec(visit_fn, tree.left);
            visit_fn.visit(tree.key, tree.value);
            do_visit_rec(visit_fn, tree.right);
        }
   }

   public value_t get (key_t key) {
      if (root == null){
            return null;
        }else{
        node focusNode = root;
        node parent;
            while(true){
            parent = focusNode;
            if(key.compareTo(focusNode.key) == 0) {
            return focusNode.value;     
            }else if(key.compareTo(focusNode.key) < 0){
                focusNode = focusNode.left;
                    if (focusNode == null){
                        return null;
                    }
                }else{
                    focusNode = focusNode.right;
                    if(focusNode == null){
                        return null;
                    }
                }                
            }
        }
   }

   public value_t put (key_t key, value_t value) {
      node newNode = new node();
        newNode.key = key;
        newNode.value= value;
        if (root == null){
            root = newNode;
        }else{
        node focusNode = root;
        node parent;
            while(true){
            parent = focusNode;
            if(key.compareTo(focusNode.key) == 0) {
            node temp = focusNode;
            focusNode.value = value;
            return temp.value;     
            }else if(key.compareTo(focusNode.key) < 0){
                focusNode = focusNode.left;
                    if (focusNode == null){
                        parent.left = newNode;
                        return null;
                    }
                }else{
                    focusNode = focusNode.right;
                    if(focusNode == null){
                        parent.right = newNode;
                        return null;
                    }
                }                
            }
        }
        return null; 
   }

   public void debug_dump () {
      debug_dump_rec (root, 0);
   }

   public void do_visit (visitor <key_t, value_t> visit_fn) {
      do_visit_rec (visit_fn, root);
   }

}
