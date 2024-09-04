#ifndef _CS_COMMON_
#define _CS_COMMON_

namespace CS {
    
    typedef bool (*Pred)(int, int);
    Pred less = [](int left, int right) { return left < right ? true : false; };
    
    
};

#endif //_CS_COMMON_