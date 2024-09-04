#ifndef _CS_SORT_
#define _CS_SORT_

#include "common.h"

namespace CS{
    
    //n2    
    void insertSort(int* start, int* end, Pred pred = CS::less){
        
        for(int* index1 = start ; index1 != end + 1; ++index1){

            for(int* index2 = start; index2 != index1; ++index2 ){
                
                if(pred(*index1, *index2)){
                    
                    int tmp = *index1;
                    
                    for(int* i = index1; i != index2; --i){
                        
                        *i = *(i - 1);
                        
                    }
                    
                    *index2 = tmp;
                    
                    break;
                    
                }                    
            }                
        }            
    }
    
    void selectSort(int* start, int* end, Pred pred = less){
        
        for(int* index = start; index != end; ++index){
            
            int* min = index;  
            for (int* i = index + 1; i != end + 1; ++i) {
            
                if (pred(*i, *min))
                    min = i;

            }
               
            int tmp = *index;
            *index = *min;
            *min = tmp;
            
        }
    }
    
    void bubbleSort(int* start, int* end, Pred pred = less){
        
        while(1){
            
            bool sort = true;
            
            for(int* index = start; index + 1 != end + 1; ++index){
            
                if(pred(*(index + 1), *index )){
                    
                    sort = false;
                    
                    int tmp = *index;
                    *index = *(index + 1);
                    *(index + 1) = tmp;
                    
                }                        
                
            }
            
            if(sort) return;;
            
        }
    }
    
    //NxlogN
    
    void makeHeap(int* start, int* end){
        
        int size = end - start;
        
        for(int index = 0; index != size + 1; ++index){
            
            int cell = index;
            while(cell != 0){
                
                int perent = ( cell - 1 )/2;
                
                if(start[cell] <= start[perent]) break;
                
                int tmp = start[perent];
                start[perent] = start[cell];
                start[cell] = tmp;
                
                cell = perent;
                    
            }                
        }            
    }
    
    void ressHeap(int* start, int* end){
        
        if(start == end)
            return;
        
        int size = (end - start) + 1;
        int index = 0;
        
        while(1){
            
            int child1 = 2 * index + 1;
            int child2 = 2 * index + 2;
            if(child1 >= size) child1 = index;
            if(child2 >= size) child2 = index;
            
            if(start[index] >= start[child1] && 
               start[index] >= start[child2] ) break;
               
            int swap = start[child1] < start[child2]? child2 : child1;
            
            int tmp = start[index];
            start[index] = start[swap];
            start[swap] = tmp;
                
            index = swap;
            
        }            
    }
    
    void heapSort(int* start, int* end){
        
        makeHeap(start, end);
        
        for(int* index = end; index != start; --index){
            
            int tmp = *start;
            *start = *index;
            *index = tmp;
            
            ressHeap(start, index - 1);
            
        }
    }
    
    void quickSort(int* start, int* end, Pred pred = less){
        
        if(start == end) return;
        
        int* index = start;
        int* startIndex = start + 1;
        int* endIndex = end;
        
        while(startIndex != endIndex + 1){

            if (startIndex > endIndex) break;
            
            if(pred(*index, *startIndex)) {
                
                while(startIndex != endIndex){
                   
                    if (!pred(*index, *endIndex)) break;
                        
                    --endIndex;
                    
                }
                
                if(startIndex == endIndex) break;
                
                int tmp = *startIndex;
                *startIndex = *endIndex;
                *endIndex = tmp;
                
                --endIndex;
                
            }
                
            if(pred(*startIndex, *index)){
                
                int tmp = *index;
                *index = *startIndex;
                *startIndex = tmp;
                
                ++index;
                ++startIndex;
            }
            
        }

        if (start <= index - 1)
            quickSort(start, index - 1);

        if (index + 1 <= end)
            quickSort(index + 1 , end);

    }
    
    void mergeSort(int* start, int* end, int* scratch, Pred pred = less){
        
        if(start == end) return;
        
        int size = end - start + 1;
        
        mergeSort(start, start + (size / 2) - 1, scratch, pred);
        mergeSort(start + (size / 2), end , scratch, pred);
        
        //merge
        int leftIndex = 0;
        int rightIndex = size / 2;
        int devideIndex = (size / 2) - 1;
        
        int index = 0;
        while(leftIndex != devideIndex + 1 && rightIndex != size){
            
            if(pred(start[leftIndex], start[rightIndex])){
                
                scratch[index] = start[leftIndex];
                ++leftIndex;
                ++index;
                
            }else{
                
                scratch[index] = start[rightIndex];
                ++rightIndex;
                ++index;
                
            }  
            
        } 
                                
        for(; leftIndex != devideIndex + 1; ++leftIndex){
            
            scratch[index] = start[leftIndex];
            ++index;
            
        }
        
        for(; rightIndex != size; ++rightIndex){
            
            scratch[index] = start[rightIndex];
            ++index;
            
        }

        for (int i = 0; i < size; ++i) {
        
            start[i] = scratch[i];
        
        }
        
    }
    
};

#endif //_CS_SORT_