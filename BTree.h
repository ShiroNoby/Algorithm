#ifndef _CS_23_TREE_
#define _CS_23_TREE_

#include <new>
#include "array.h"

namespace CS{

#define makeLinks(node) &(node)->link
        
    class BTree{
                
        BTree(const BTree&) = delete;
        BTree(BTree&&) = delete; 
        
    public:
    
        //Node = new void[sizeof(Array) + sizeof(Node*) + (2k * sizeof(Node*))]
        //links[0] == *links 
        //links[k + 1] == (2k * sizeof(Node*))
        struct Node {

            Array               data;
            Node*               link = nullptr;
            
            Node(int size = 0) : data(size){}
            ~Node() {}

        };
    
        BTree(int val = 1) : k(val){}
        ~BTree();
        
        void                    push(int val);
        void                    erase(int val);
        
        Node*                   find(int val); 
        Node*                   data();        
    
    private:
    
        int                     k;
        
        Node                    startNode;
        
        Node*                   makeNode(int val);
        
        void                    deleteNode(Node* node);
        void                    destructTree(Node* node);

        void                    balanceUp(Node* node, Node* perent, int val);
        void                    balanceErase(Node* perent);
        void                    balanceMerge(Node* perent, int index);
        void                    balanceBreadth(Node* perent, bool left, int index);

        void                    downPush(Node* node, Node* perent, int val);

        void                    downErase(Node* node, Node* perent, int val);
        void                    downEraseRightFind(Node* node, Node* perent, int &val);        
        
    };
    
    BTree::~BTree(){
        
        Node* tmp = startNode.link;
        
        if(tmp == nullptr)
            return;
        
        destructTree(tmp);
        
    }
    
    void BTree::balanceUp(Node* node, Node* perent, int val){
        
        Node** nodelinks = makeLinks(node);

        if(perent == nullptr){

            int size = node->data.size();
            for (int index = 0; index < size; ++index) {
            
                if (node->data[index] == val) {
                   
                    Node* tmp1 = makeNode(node->data[0]);                    

                    int in = 1;
                    for (; in != index; ++in)
                        tmp1->data.push_back(node->data[in]);                        

                    in = index + 2;
                    Node* tmp2 = makeNode(node->data[index + 1]);
                    for (; in != size; ++in)
                        tmp2->data.push_back(node->data[in]);

                    int tmp = 0;
                    Node** prevlinks = makeLinks(tmp1);
                    Node** nextlinks = makeLinks(tmp2);
                    for (in = 0; in <= size; ++in) {
                    
                        if (in <= index) {
                        
                            prevlinks[in] = nodelinks[in];
                            nodelinks[in] = nullptr;

                        }
                        if (in > index) {
                        
                            nextlinks[tmp] = nodelinks[in];
                            nodelinks[in] = nullptr;
                            ++tmp;
                        
                        }                    
                    }

                    nodelinks[0] = tmp1;
                    nodelinks[1] = tmp2;
                    break;
                }            
            }

            node->data.clear();
            node->data.push_back(val);

            return;
        }
        
        Node** perentlinks = makeLinks(perent);

        int PSize = perent->data.size();
        for(int index = 0; index < PSize; ++index){
                        
            if(perent->data[index] > val){
            
                for(int indexEnd = PSize; indexEnd != index; --indexEnd){
                    
                    perentlinks[indexEnd + 1] = perentlinks[indexEnd];
                    perentlinks[indexEnd] = nullptr;
                    
                }
                
                perent->data.insert(index, val);
                
                int NSize = node->data.size();
                for(int in = 0; in < NSize; ++in){
                    
                    if(node->data[in] == val){
                        
                        perentlinks[index + 1] = makeNode(node->data[in + 1]);
                        Node** dlinks = makeLinks(perentlinks[index]);
                        Node** nextdlinks = makeLinks(perentlinks[index + 1]);

                        for (int indexEnd = NSize, tmp = 0; indexEnd != in; --indexEnd, ++tmp) {

                            nextdlinks[tmp] = dlinks[indexEnd];
                            dlinks[indexEnd] = nullptr;

                        }

                        node->data.erase(in);
                        node->data.erase(in);
                        while (in < node->data.size()) {

                            perentlinks[index + 1]->data.push_back(node->data[in]);
                            node->data.erase(in);

                        }

                        return;
                                             
                    }                      
                }
            }

            if (index == PSize - 1) {
            
                ++index;

                perent->data.push_back(val);

                int NSize = node->data.size();
                for (int in = 0; in < NSize; ++in) {

                    if (node->data[in] == val) {

                        perentlinks[index + 1] = makeNode(node->data[in + 1]);
                        Node** dlinks = makeLinks(perentlinks[index]);
                        Node** nextdlinks = makeLinks(perentlinks[index + 1]);

                        for (int indexEnd = NSize, tmp = 0; indexEnd != in; --indexEnd, ++tmp) {

                            nextdlinks[tmp] = dlinks[indexEnd];
                            dlinks[indexEnd] = nullptr;

                        }

                        node->data.erase(in);
                        node->data.erase(in);
                        while (in < node->data.size()) {
                        
                            perentlinks[index + 1]->data.push_back(node->data[in]);
                            node->data.erase(in);
                        
                        }

                        return;
                    }
                }
            }

        }        
    }
    void BTree::balanceErase(Node* perent){

        Node** perentlinks = makeLinks(perent);
        
        if(perent == nullptr)
            return;
                
        int index = 0;
        int size = perent->data.size();
        
        for(; index <= size; ++index){
            
            if (perentlinks[index] == nullptr)
                return;
            
            if (perentlinks[index]->data.size() < k) {
                
                if( index &&
                    perentlinks[index - 1]->data.size() > k) {
                    
                    balanceBreadth(perent, true, index);
                    return;
                    
                }
                
                if( index != size && 
                    perentlinks[index + 1]->data.size() > k) {
                        
                    balanceBreadth(perent, false, index);
                    return;
                    
                } 
                
                balanceMerge(perent, index);
                return;
                
            }            
        }        
    }
    void BTree::balanceMerge(Node* perent, int index){

        Node** perentlinks = makeLinks(perent);

        if(index == perent->data.size())
            --index;

        perentlinks[index]->data.push_back(perent->data[index]);
        Node* tmp = perentlinks[index + 1];
        
        for(int in = index + 1; in <= perent->data.size(); ++in){
            
            perentlinks[in] = perentlinks[in + 1];
            perentlinks[in + 1] = nullptr;
            
        }
        
        perent->data.erase(index);
        Node** tmplinks = makeLinks(tmp);
        Node** dLinks = makeLinks(perentlinks[index]);
        
        for(int in = 0; in < tmp->data.size(); in++ ){
            
            int sz = perentlinks[index]->data.size();

            //perent->links[index]->links[sz] = tmplinks[in];
            dLinks[sz] = tmplinks[in];
            tmplinks[in] = nullptr;
            perentlinks[index]->data.push_back(tmp->data[in]);
            
        }
        
        int sz1 = perentlinks[index]->data.size();
        int sz2 = tmp->data.size();
        dLinks[sz1] = tmplinks[sz2];
        tmplinks[sz2] = nullptr;

        deleteNode(tmp);

        if (!perent->data.size()) {

            tmp = perentlinks[0];
            int size = perentlinks[0]->data.size();

            for (int index = 0; index < size; ++index)
                perent->data.push_back(tmp->data[index]);

            Node** Dlinks = makeLinks(tmp);

            for (int index = 0; index <= size; ++index){

                perentlinks[index] = Dlinks[index];
                Dlinks[index] = nullptr;

            }

            deleteNode(tmp);

        } 
        
        return;
        
    }
    void BTree::balanceBreadth(Node* perent, bool left, int index){
                
        Node** perentlinks = makeLinks(perent);
        Node** dlinks = makeLinks(perentlinks[index]);        

        if(left){
            
            perentlinks[index]->data.insert(0, perent->data[index - 1]);
            for (int in = perentlinks[index]->data.size(); in > 0; --in){
                                
                dlinks[in] = dlinks[in - 1];
                dlinks[in - 1] = nullptr;
                
            }            
            
            perent->data[index - 1] = *perentlinks[index - 1]->data.back();
            Node** prevdlinks = makeLinks(perentlinks[index - 1]);

            int size = perentlinks[index - 1]->data.size();
            dlinks[0] = prevdlinks[size];
            prevdlinks[size] = nullptr;
            
            perentlinks[index - 1]->data.erase(size);
                       
        }else{
                        
            perentlinks[index]->data.push_back(perent->data[index]);
            perent->data[index] = *perentlinks[index + 1]->data.front();
            perentlinks[index + 1]->data.erase(0);

            Node** nextdlinks = makeLinks(perentlinks[index + 1]);

            int sz = perentlinks[index]->data.size();
            int size = perentlinks[index + 1]->data.size();
            dlinks[sz] = nextdlinks[0];
            
            for(int in = 0; in < size; ++in){
                
                nextdlinks[in] = nextdlinks[in + 1];
                nextdlinks[in + 1] = nullptr;
                
            }            
        }        
    }
        
    void BTree::downPush(Node* node, Node* perent, int val){
        
        Node** nodelinks = makeLinks(node);

        if(node == nullptr) 
            return;        
        
        int size = node->data.size();
        
        if(node->link == nullptr){
            
            //add
            for(int index = 0; index < size; ++index){
                
                if(node->data[index] > val){
                    
                    node->data.insert(index, val);  
                    break;
                    
                }

                if (index == size - 1)
                    node->data.push_back(val);
            }
            
            size = node->data.size();
            if( size > (k * 2) )
                balanceUp(node, perent, node->data[k]);
            
            return;
        }

        for(int index = 0; index < size; ++index){
            
            if(node->data[index] > val){
                
                downPush(nodelinks[index], node, val);
                
                size = node->data.size();
                if( size > (k * 2) )
                    balanceUp(node, perent, node->data[k]);
                
                return;
            }
            
            if(index == size - 1){
                
                downPush(nodelinks[index + 1], node, val);
                
                size = node->data.size();
                if( size > (k * 2) )
                    balanceUp(node, perent, node->data[k]);
                
                return;
            } 
        }
    }
    void BTree::downErase(Node* node, Node* perent, int val){
        
        Node** nodelinks = makeLinks(node);

        if(node == nullptr)
            return;
        
        int size = node->data.size();        
        for(int index = 0; index < size; ++index){
            
            if(node->data[index] == val){
                
                //erase
                if (nodelinks[index] != nullptr) {
                    
                    downEraseRightFind(nodelinks[index], node, node->data[index]);
                    break;
                    
                }                
                
                node->data.erase(index);                
                break;

            }
            
            if(node->data[index] > val){
                
                downErase(nodelinks[index], node, val);
                break;
            }
            
            if(index == size - 1){
                
                downErase(nodelinks[index + 1], node, val);
                break;
            }
        }
        
        balanceErase(perent);
        
    }    
    void BTree::downEraseRightFind(Node* node, Node* perent, int &val){
        
        Node** nodelinks = makeLinks(node);

        int size = node->data.size();
        
        if (nodelinks[size] == nullptr) {
            
            val = *node->data.back();
            node->data.erase(size - 1);
            
            return balanceErase(perent);
            
        }
        
        downEraseRightFind(nodelinks[size], node, val);
        balanceErase(perent);
    }
    
    void BTree::push(int val){
        
        if(startNode.link == nullptr){
            
            startNode.link = makeNode(val);
            return;
            
        }
        
        downPush(startNode.link, nullptr, val);        
        
    }
    void BTree::erase(int val){
        
        if(startNode.link == nullptr)
            return;
        
        downErase(startNode.link, nullptr, val);    
        
    }
    void BTree::deleteNode(Node* node){

        node->data.~Array();
        delete[] (char*)node;

        node = nullptr;

    }
    void BTree::destructTree(Node* node){
        
        Node** nodelinks = makeLinks(node);

        if(node == nullptr)
            return;
        
        int size = 2 * k;
        for(int index = 0; index < (size + 2); ++index)
            destructTree(nodelinks[index]);
        
        deleteNode(node);
    }
    
    BTree::Node* BTree::find(int val){
                
        Node* tmp = data();

        while(tmp != nullptr){
            
            int index = 0;
            int size = tmp->data.size();
            Node** nodelinks = makeLinks(tmp);
            
            for(; index < size; ++index){
                
                if(tmp->data[index] == val) return tmp;
                if(tmp->data[index] > val) {
                    
                    tmp = nodelinks[index];
                    break;
                    
                }
                
            }
            
            if(index == size)
                tmp = nodelinks[index];
            
        }
        
        return nullptr;
        
    }
    BTree::Node* BTree::data(){
        
        return startNode.link;
        
    }
    BTree::Node* BTree::makeNode(int val){       
        
        int size = 2 * k;
        int tmpSize = sizeof(CS::Array) + ( sizeof(Node*) * (size + 2) );
        void* tmp = new char[ tmpSize ]();

        new(tmp) Node(size + 1);
        ((Node*)tmp)->data.push_back(val);
        
        return (Node*)tmp;
    }
        
};

#endif //_CS_23_TREE_