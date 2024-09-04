#ifndef _CS_ARRAY_
#define _CS_ARRAY_

#define array_size 10

namespace CS{
    
    class Buffer{
        
        Buffer(const Buffer&) = delete;
        Buffer(Buffer&&) = delete;       
        
    public:
    
        explicit Buffer(int size = array_size)      { if(size > 0) data = new int[size]; }
        ~Buffer()                                   { if(data != nullptr) delete[] data; }
        
        int& operator[](int index)                  { return data[index]; }
        int* front()                                { return data; }
    
    private:
    
        int* data = nullptr;
        
    };
        
    //
    // array
    // |1|2|3|4|5|6| elem
    //  0 1 2 3 4 5  index
    //
    class Array{
        
        Array(const Array&) = delete;
        Array(Array&&) = delete;
        
    public:
    
        explicit Array(int sz = array_size) 
            : data(sz), m_size(0), m_capacity(sz){}

        ~Array() {}
        
        void                    insert(int index, int val);
        void                    push_back(int val);
        void                    erase(int index);
        void                    clear();
        
        int&                    operator[](int index);
        int                     find(int val);
        int                     max();
        int                     min();
        int                     size();
        int                     capacity();

        int*                    front();
        int*                    back();
        
    private:
    
        Buffer data;
        int    m_size;          //local size
        int    m_capacity;      //all size
        
    };
    
    void Array::insert(int index, int val){
        
        if(m_capacity == m_size)
            return ;
        
        for(int prev = m_size; prev > index; --prev){
            
            data[prev] = data[prev - 1];
            
        }

        data[index] = val;        
        ++m_size;
    }
    void Array::push_back(int val){
        
        if(m_capacity == m_size)
            return ;
        
        data[m_size] = val;
        ++m_size;
                
    }
    void Array::erase(int index){
        
        if(m_capacity == 0)
            return ;
        
        if(index < 0 || index > m_capacity)
            return ;
        
        for( ; index + 1 < m_size; ++index){
            
            data[index] = data[index + 1];
            
        }
        
        --m_size;
    }
    void Array::clear() {
    
        m_size = 0;

    }

    int& Array::operator[](int index){
        
        int error = -1;

        if(m_size == 0)
            return error;
        
        if(index < 0 || index >= m_size)
            return error;
        
        return data[index];
        
    }
    int  Array::find(int val){

        if(m_size == 0)
            return -1;
        
        for(int index = 0; index < m_size; ++index ){
            
            if(data[index] == val)
                return index;
            
        }
        
        return -1;
        
    }
    int  Array::max(){
        
        if(m_size == 0)
            return -1;
        
        int max = data[0];
        
        for(int index = 1; index < m_size; ++index ){
            
            if(data[index] > max)
                max = data[index];
            
        }
        
        return max;
    }    
    int  Array::min(){
        
        if(m_size == 0)
            return -1;
        
        int min = data[0];
        
        for(int index = 1; index < m_size; ++index ){
            
            if(data[index] < min)
                min = data[index];
            
        }
        
        return min;
    }
    int  Array::size(){ return m_size; }
    int  Array::capacity() { return m_capacity; }
    
    int* Array::front() {
    
        return data.front();
    
    }
    int* Array::back() {
    
        return data.front() + m_size - 1;
    
    }
};

#endif //_CS_ARRAY_