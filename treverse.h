#ifndef _CS_TREVERSE_
#define _CS_TREVERSE_

#include "Tree.h"
#include <queue>

namespace CS{
    
    void traverseBreadthOrder(CS::Tree::Node* node, CS::Pred operation){
        
        std::queue<CS::Tree::Node*> queue;
        
        queue.push_back(node);
        
        while(!queue.isempty()){
            
            CS::Tree::Node* tmp = queue.pop_front();
            
            if(tmp->left != nullptr)
                queue.push_back(tmp->left);
            if(tmp->right != nullptr)
                queue.push_back(tmp->right);
            
            operation(node);
            
        }
        
    }
    
};

#endif //_CS_TREVERSE_