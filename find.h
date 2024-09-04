#ifndef _CS_FIND_
#define _CS_FIND_

#include "common.h"

namespace CS{
    
    int* search(int* start, int* end, int val){

        for (int* it = start; it != end + 1; ++it)
            if(*it == val)
                return it;

        return nullptr;

    }
    
    bool isSort(int* start, int* end, Pred pred = CS::less){
        
        for (int* it = start; it != end; ++it) {
            
            if( pred( *(it + 1), *it ) )
                return false;
            
        }
        
        return true;
        
    }
    
    int* bSrch(int* start, int* end, int val){
        
        if(start == end)
            return (*start == val)? start: nullptr;
            
        int size = end - start + 1;
        int* derive = start + (size / 2);
        
        if(*derive == val) return derive;
        
        return (*derive < val)? bSrch(derive + 1, end, val)
                              : bSrch(start, derive - 1, val);
        
    }

    int* bSearch(int* start, int* end, int val){
        
        if(!isSort(start, end))
            return nullptr;
        
        return bSrch(start, end, val);
                    
    }
   
};

#endif //_CS_FIND_