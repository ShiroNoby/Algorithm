#ifndef _CS_LIST_
#define _CS_LIST_

namespace CS{
    
    class forward_list{        
        
        forward_list(const forward_list&) = delete;
        forward_list(forward_list&&) = delete;
        
    public:

        struct Node {

            int                 data;
            Node*               next = nullptr;

        };
    
        forward_list() {}
        ~forward_list();

        void                    insert(Node* node, int val);
        void                    coppy(Node* from, Node* to);
        void                    push_back(int val);
        void                    addFront(int val);
        void                    erase(Node* node);
        
        Node*                   find(int val); 
        Node*                   front();
        
    private:
        
        Node                    startNode;
        
        Node*                   makeNode(int val);
        
        void                    deleteNode(Node* node);
        
    };  
    
    forward_list::~forward_list(){
        
        while(1){
            
            Node* tmp = &startNode;
            
            if(tmp->next != nullptr){
                
                tmp = tmp->next;
                
                startNode.next = tmp->next;
                
                deleteNode(tmp);
                
                continue;
                
            }else{ return; }
        }        
    }
                   
    void    forward_list::coppy(Node* from, Node* to){
        
        if(from == nullptr)
            return;

        while(from->next != nullptr){
        
            from = from->next;
            
            if(to->next != nullptr){
                
                to = to->next;
                
                to->data = from->data;
                
                continue;
                
            }
            
            to->next = makeNode(from->data);
            
            to = to->next;
            
        }
        
        //
        if(to->next != nullptr){
            
            while(1){
            
                Node* tmp = to;
                
                if(tmp->next != nullptr){
                    
                    tmp = tmp->next;
                    
                    to->next = tmp->next;
                    
                    deleteNode(tmp);
                    
                    continue;
                
                }else{ return; }
            }
            
        }
        
    }
    
    void    forward_list::insert(Node* node, int val){

        if (node == nullptr)
            return;
        
        Node* tmp = &startNode;
        while(tmp->next != nullptr){
            
            if(tmp->next == node){
                
                tmp->next = makeNode(val);
                
                tmp->next->next = node;
                
                return;
                
            }
                
            tmp = tmp->next;
    
        }
        
    }
    void    forward_list::push_back(int val){
        
        Node* tmp = &startNode;
        while(tmp->next != nullptr){
            
            tmp = tmp->next;
            
        }
        
        tmp->next = makeNode(val);
        
        tmp->next->next = nullptr;
        
    }
    void    forward_list::addFront(int val){
        
        Node* tmp = makeNode(val);
        
        tmp->next = startNode.next;
        
        startNode.next = tmp;
        
    }
    void    forward_list::erase(Node* node){
        
        if(node == nullptr)
            return;
        
        Node* tmp = &startNode;
        while(tmp->next != nullptr){
            
            if(tmp->next == node){
                
                tmp->next = node->next;
                deleteNode(node);
                
                return;
            }
            
            tmp = tmp->next;
            
        }
        
    }
    void    forward_list::deleteNode(Node* node){
        
        delete node;
        
    }

    CS::forward_list::Node*     CS::forward_list::find(int val){
        
        Node* tmp = &startNode;
        while(tmp->next != nullptr){
            
            tmp = tmp->next;
            
            if(tmp->data == val)
                return tmp;
            
        }
        
        return nullptr;
        
    }
    CS::forward_list::Node*     CS::forward_list::makeNode(int val){
        
        Node* node = new Node;
        node->data = val;
        
        return node;
        
    }
    CS::forward_list::Node*     CS::forward_list::front(){
        
        return &startNode;
        
    }
    
    class List{        
        
        List(const List&) = delete;
        List(List&&) = delete;
        
    public:

        struct Node {

            int                 data;
            Node*               next = nullptr;
            Node*               prev = nullptr;

        };
    
        List();
        ~List();

        void                    insert(Node* node, int val);
        void                    coppy(Node* from, Node* to);
        void                    push_back(int val);
        void                    addFront(int val);
        void                    erase(Node* node);        
        void                    addEnd(int val);
        
        Node*                   find(int val); 
        Node*                   front();
        Node*                   back();
        
    private:
        
        Node                    startNode;
        Node                    endNode;
        
        Node*                   makeNode(int val);
        
        void                    deleteNode(Node* node);
        
    };

    List::List() {
    
        startNode.next  = &endNode;
        endNode.prev    = &startNode;    
    }
    
    List::~List(){
        
        while(1){
            
            Node* tmp = &startNode;
            
            if(tmp->next != &endNode){
                
                tmp = tmp->next;
                
                startNode.next = tmp->next;
                
                deleteNode(tmp);
                
                continue;
                
            }else{ return; }
        }        
    }
    
    void    List::coppy(Node* from, Node* to){
        
        if(from == nullptr)
            return;
        
        //if(to != nullptr)
        //    return;

        while(from->next->next != nullptr){
        
            from = from->next;
            
            if(to->next->next != nullptr){
                
                to = to->next;
                
                to->data = from->data;
                
                continue;
                
            }

            Node* tmp = makeNode(from->data);

            tmp->next = to->next;
            to->next->prev = tmp;

            to->next = tmp;
            tmp->prev = to;

            to = to->next;
            
        }
        
        if(to->next->next != nullptr){
            
            while(1){
                
                Node* tmp = to;
                
                if(tmp->next->next != nullptr){
                    
                    tmp = tmp->next;
                    
                    to->next = tmp->next;
                    
                    deleteNode(tmp);
                    
                    continue;
                    
                }else{ 
                
                    endNode.prev = to;
                    
                    return; 
                    
                }
            }
            
        }
        
    }
    void    List::insert(Node* node, int val){
        
        if(node == nullptr)
            return;
        
        Node* tmp = makeNode(val);
        
        tmp->prev = node->prev;
        node->prev = tmp;
        
        tmp->next = tmp->prev->next;
        tmp->prev->next = tmp;
        
    }
    void    List::deleteNode(Node* node){
        
        delete node;
        
    }
    void    List::push_back(int val){
        
        Node* tmp = makeNode(val);
        
        tmp->prev = endNode.prev;        
        endNode.prev = tmp;
        
        tmp->next = tmp->prev->next;
        tmp->prev->next = tmp;
        
    }
    void    List::addFront(int val){
        
        Node* tmp = makeNode(val);
        
        tmp->next = startNode.next;               
        startNode.next = tmp;
        
        tmp->prev = tmp->next->prev;
        tmp->next->prev = tmp; 
        
    }
    void    List::erase(Node* node){
        
        if(node == nullptr)
            return;
        
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        deleteNode(node);
        
    }
    void    List::addEnd(int val){
        
        push_back(val);
        
    }
    
    CS::List::Node* CS::List::makeNode(int val){
        
        Node* node = new Node;
        node->data = val;
        
        return node;
        
    }
    CS::List::Node* CS::List::find(int val){
        
        Node* tmp = &startNode;
        while(tmp->next != &endNode){
            
            tmp = tmp->next;
            
            if(tmp->data == val)
                return tmp;
            
        }
        
        return nullptr;
        
    }
    CS::List::Node* CS::List::front(){
        
        return &startNode;
        
    }    
    CS::List::Node* CS::List::back(){
        
        return &endNode;
        
    }
    
};

#endif //_CS_LIST_