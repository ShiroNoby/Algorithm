#ifndef _CS_A_TREE_
#define _CS_A_TREE_

namespace CS{
    
    class ATree{
        
        ATree(const ATree&) = delete;
        ATree(ATree&&) = delete; 
        
    public:
    
        struct Node {

            char                hight = 1;
            int                 data;
            Node*               left = nullptr;
            Node*               right = nullptr;

        };
    
        ATree() {}
        ~ATree();

        void                    push(int val);
        void                    erase(int val);
        
        Node*                   find(int val); 
        Node*                   data();
        
    private:
        
        Node                    startNode;
        
        Node*                   makeNode(int val);
        
        int                     hight(Node* node);
        void                    makeHight(Node* node);
        
        Node*                   balance(Node* node);
        Node*                   leftRotate(Node* node);
        Node*                   rightRotate(Node* node);  
        
        void                    deleteNode(Node* node);
        void                    destructTree(Node* node);

        friend Node* downPush(int val, ATree::Node* node);
        friend Node* downErase(int val, ATree::Node* node);
        friend Node* downEraseRightFind(Node* node, Node* tmp);
        
        
    } empty;
    
    ATree::~ATree(){
        
        Node* tmp = startNode.right;
        
        if(tmp == nullptr)
            return;
        
        destructTree(tmp);
        
    }
    
    ATree::Node* ATree::find(int val){
        
        Node* tmp = startNode.right;

        if (tmp == nullptr)
            return nullptr;
        
        while(tmp->data != val){
            
            if(tmp->left == nullptr && tmp->right == nullptr)
                return nullptr;
            
            tmp = (val < tmp->data) ? tmp->left: tmp->right;
            
        }
            
        return tmp;
    } 
    ATree::Node* ATree::data(){
        
        return startNode.right;
        
    }
    ATree::Node* ATree::makeNode(int val){
        
        Node* tmp = new Node;
        tmp->data = val;
        
        return tmp;
    }
    ATree::Node* ATree::rightRotate(Node* node){
        
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        
        makeHight(node);
        makeHight(tmp);
        
        return tmp; 
        
    }
    ATree::Node* ATree::leftRotate(Node* node){
        
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        
        makeHight(node);
        makeHight(tmp);
        
        return tmp; 
        
    }
    ATree::Node* ATree::balance(Node* node){

        if (node == nullptr)
            return nullptr;
        
        int balance = hight(node->left) - hight(node->right);
        
        if( balance > 1 ){
            
            Node* tmp = node->left;
            
            int subBalance = hight(tmp->left) - hight(tmp->right);
            
            if( subBalance >= 0 ){
                
                return rightRotate(node);
                
            } else if( subBalance < 0 ){
                
                node->left = leftRotate(tmp);                
                return rightRotate(node);
                
            }
            
        }else if( balance < - 1 ){
            
            Node* tmp = node->right;
            
            int subBalance = hight(tmp->left) - hight(tmp->right);
            
            if( subBalance > 0 ){
                
                node->right = rightRotate(tmp);                
                return leftRotate(node);
                
            } else if( subBalance <= 0 ){
                
                return leftRotate(node);
                
            }
            
        }
        
        return node;
        
    }    
    ATree::Node* downPush(int val, ATree::Node* node = nullptr){
                
        if (node == nullptr)
            return empty.makeNode(val);
        
        if(node->data == val)
            return node;
        
        if(node->data > val){
            
            node->left = downPush(val, node->left);
            empty.makeHight(node);

            return empty.balance(node);
            
        }else{
            
            node->right = downPush(val, node->right);
            empty.makeHight(node);

            return empty.balance(node);
            
        }
        
    }
    ATree::Node* downErase(int val, ATree::Node* node){
                
        if(node == nullptr)
            return nullptr;
        
        if(node->data == val){
            
            if(node->left != nullptr){

                ATree::Node* tmp = node->left;
                
                if(node->left->right != nullptr){  
                
                    node->left = downEraseRightFind(node, tmp);

                    empty.makeHight(node);
                    return empty.balance(node);
                    
                }
                
                node->data = tmp->data;
                node->left = tmp->left;
                node->right = tmp->right;
                
                empty.deleteNode(tmp);  
                empty.makeHight(node);

                return empty.balance(node);
                
            }
            
            if(node->right != nullptr){
                
                ATree::Node* tmp = node->right;
                
                node->data = tmp->data;
                node->left = tmp->left;
                node->right = tmp->right;
                
                empty.deleteNode(tmp);  
                empty.makeHight(node);

                return empty.balance(node);
                
            }
            
            empty.deleteNode(node);
            node = nullptr;

            return node;
        }
        
        if(node->data > val){
            
            node->left = downErase(val, node->left);
            empty.makeHight(node);

            return empty.balance(node);
            
        }else{
            
            node->right = downErase(val, node->right);
            empty.makeHight(node);

            return empty.balance(node);
            
        }
        
    }
    ATree::Node* downEraseRightFind(ATree::Node* node, ATree::Node* tmp) {
    
        if (tmp->right == nullptr) {
            
            ATree::Node* tt = tmp->left;

            node->data = tmp->data;
            empty.deleteNode(tmp);

            return tt;
        
        }

        tmp->right = downEraseRightFind(node, tmp->right);
        empty.makeHight(tmp);

        return empty.balance(tmp);
    
    }


    int ATree::hight(Node* node){
        
        return (node != nullptr) ? node->hight : 0;
        
    }

    void ATree::push(int val){
        
        startNode.right = downPush(val, startNode.right);
        
    }
    void ATree::erase(int val){
        
        startNode.right = downErase(val, startNode.right);
        
    }
    void ATree::makeHight(Node* node){
        
        char left  = (node->left != nullptr)? hight(node->left): 0;
        char right = (node->right != nullptr)? hight(node->right): 0;
        node->hight = ( (left < right)? right : left ) + 1;
        
    }
    void ATree::deleteNode(Node* node){
        
        delete node;
        
    }
    void ATree::destructTree(Node* node){
        
        if(node == nullptr)
            return;
        
        if(node->left != nullptr) destructTree(node->left);
        if(node->right != nullptr) destructTree(node->right);
        
        deleteNode(node);
        
    }
    
};

#endif //_CS_A_TREE_