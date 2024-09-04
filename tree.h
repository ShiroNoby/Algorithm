#ifndef _CS_TREE_
#define _CS_TREE_

#include "common.h"

namespace CS {
    
    class Tree {
        
        Tree(const Tree&) = delete;
        Tree(Tree&&) = delete; 
        
    public:
    
        struct Node {

            int                 data;
            Node*               left = nullptr;
            Node*               right = nullptr;

        };
    
        Tree() {}
        ~Tree();

        void                    push(int val);
        void                    erase(Node* node);
        
        Node*                   find(int val); 
        Node*                   data();
        
    private:
        
        Node                    startNode;
        
        Node*                   makeNode(int val);
        
        void                    deleteNode(Node* node);
        void                    destructTree(Node* node);
        
    };
    
    void Tree::destructTree(Node* node){
        
        if(node == nullptr)
            return;
        
        if(node->left != nullptr) destructTree(node->left);
        if(node->right != nullptr) destructTree(node->right);
        
        deleteNode(node);
        
    }
    
    Tree::~Tree(){
        
        Node* tmp = startNode.right;
        
        if(tmp == nullptr)
            return;
        
        destructTree(tmp);
        
    }

    void Tree::push(int val){
        
        if (startNode.right == nullptr) {
        
            startNode.right = makeNode(val);
            return;
        
        }

        Node* tmp = startNode.right;
            
        while(1){
            
            if(val == tmp->data)
                return;
            
            Node** branch = &( (val < tmp->data) ? tmp->left : tmp->right );
            tmp = *branch;

            if(tmp == nullptr){

                *branch = makeNode(val);
                return;
                
            }            
            
        }        
    }
    void Tree::erase(Node* node){
        
        if(node == nullptr)
            return;
        
        if(node->left != nullptr){

            Node* tmp = node->left;
            
            if(node->left->right != nullptr){  
            
                Node* perent = tmp;

                while(tmp->right != nullptr){
                                    
                    perent = tmp;
                    tmp = tmp->right;
                    
                }
                
                node->data = tmp->data;
                perent->right = tmp->left;
                deleteNode(tmp);
                return;
                
            }
            
            node->data = tmp->data;
            node->left = tmp->left;
            node->right = tmp->right;
            
            deleteNode(tmp);
            
            return;
            
        }
        
        if(node->right != nullptr){
            
            Node* tmp = node->right;
            
            node->data = tmp->data;
            node->left = tmp->left;
            node->right = tmp->right;
            
            deleteNode(tmp);
            
            return;
            
        }
        
        deleteNode(node);
        node = nullptr;
        
    }    
    void Tree::deleteNode(Node* node){
        
        delete node;
        
    }
    
    CS::Tree::Node* Tree::find(int val){
        
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
    CS::Tree::Node* Tree::makeNode(int val){
        
        Node* tmp = new Node;
        tmp->data = val;
        
        return tmp;
    }
    CS::Tree::Node* Tree::data(){
        
        return startNode.right;
        
    }
    
    //travers
    
    typedef bool (*TreePred)(Tree::Node* node);
    
    void traversePreOrder(Tree::Node* node, TreePred operation){
        
        if(node == nullptr)
            return;
        
        operation(node);
        
        if(node->left != nullptr) traversePreOrder(node->left, operation);
        if(node->right != nullptr) traversePreOrder(node->right, operation);
        
        
    }
    
    void traverseInOrder(Tree::Node* node, TreePred operation){
        
        if (node == nullptr)
            return;
        
        if(node->left != nullptr) traverseInOrder(node->left, operation);
        
        operation(node);
        
        if(node->right != nullptr) traverseInOrder(node->right, operation);
        
        
    }
    
    void traversePostOrder(Tree::Node* node, TreePred operation){
        
        if (node == nullptr)
            return;
        
        if(node->left != nullptr) traversePostOrder(node->left, operation);
        if(node->right != nullptr) traversePostOrder(node->right, operation);
        
        operation(node);        
        
    }  
    

};

#endif //_CS_TREE_