#ifndef _CS_STACK_
#define _CS_STACK_

#include "list.h"

namespace CS{
    
    class Stack{
        
        Stack(const Stack&) = delete;
        Stack(Stack&&) = delete;
        
    public:    

        Stack() {}
            
        void push(int val);
        
        int size();
        int pop();
        
        int& top();
        
    private:
    
        forward_list data;
        
        int m_size = 0;
        
    };
    
    void    Stack::push(int val){
        
        data.addFront(val);
        ++m_size;
        
    }
    
    int     Stack::size(){
        
        return m_size;
        
    }
    int     Stack::pop(){
        
        if(m_size == 0)
            return -1;        

        int result = data.front()->next->data;
        data.erase(data.front()->next);
        --m_size;
        
        return result;
        
    }
    
    int&    Stack::top(){

        if (m_size == 0) {
        
            int error = -1;
            return error;
        
        }            
        
        return data.front()->next->data;
        
    }
    
};

#endif //_CS_STACK_