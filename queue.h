#ifndef _CS_queue_
#define _CS_queue_

#include "list.h"

namespace CS{
    
    class Queue{
        
        Queue(const Queue&) = delete;
        Queue(Queue&&) = delete;
        
    public: 

        Queue() {}
            
        void push(int val);
        
        int size();
        int pop();     

        int& front();
        int& back();
        
    private:
    
        List data;
        
        int m_size = 0;
        
    };
    
    void    Queue::push(int val){
        
        data.addEnd(val);
        ++m_size;
        
    }
    
    int     Queue::size() {
        
        return m_size;
        
    }
    int     Queue::pop(){
        
        if(m_size == 0)
            return -1;        
        
        int result = data.front()->next->data;
        data.erase(data.front()->next);
        --m_size;
        
        return result;
        
    }
    
    int&    Queue::front(){

        if (m_size == 0) {

            int error = -1;
            return error;

        }
        
        return data.front()->next->data;
        
    }
    int&    Queue::back(){

        if (m_size == 0) {

            int error = -1;
            return error;

        }
        
        return data.back()->prev->data;
        
    }
};

#endif //_CS_queue_