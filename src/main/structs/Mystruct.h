    /* Mystruct.h */ 
    #ifdef __cplusplus 
     
    struct Mystruct 
    { 
      int x; 
      std:string s; 
      std::vector<int> v; 
      Mystruct( const int& _x) : x(_x) {} 
      Mystruct( const std::string& _s) : s(_s) {} 
      Mystruct(const std::vector<int>& _V) : v{_v} {} 
    }; 
     
    extern "C" { 
     
    char*  MyStruct_getString(const Mystruct* m)  
    { return m->s.c_str(); } 
     
    void   Mystruct_set_Int(const Mystruct* m, int i)  
    { m->x = i;} 
     
    void   MyStruct_setString(const Mystruct* m,const char* cp)  
    { m->s.assign(cp); } 
     
    void   MyStruct_setVector(const Mystruct* m, const int* arr, size_t n) 
            { 
               m->v = std::vector<int>(arr, arr + n); 
            } 
     
    int* MyStruct_getVector(const Mystruct* m) 
    { 
      return m->v.data(); 
    } 
     
    void Mystruct_insert( Mystruct* m, int x) 
    { 
      m->v.push_back(x); 
    } 
     
    size_t Mystruct_vectorsize(const Mystruct* m)  
    { return m->v.size();} 
     
     
    Mystruct* Mystruct_new_int( const int i) 
     { return new Mystruct(i);} 
     
    Mystruct* Mystruct_new_string( const char* str) 
    { return new Mystruct(str);} 
     
    Mystruct* Mystruct_new_array(const int* arr, size_t n )  
    {  
      std::vector<int> ivec(arr, arr+n); 
      return new Mystruct(ivec); 
    }   
     
    void Mystruct_delete(const Mystruct* m)  
    { 
      m->v.clear();  
      m->~Mystruct();  
    } 
     
    } // extern "C" 
     
    };  // struct Mystruct (CPP) 
     
    #else  /* not  __cplusplus 
     
    struct Mystruct; /* This is all C knows about it */ 
     
    /* function prototypes */ 
    char*  MyStruct_getString(const Mystruct* m); 
    void   Mystruct_set_Int(const Mystruct* m, int i); 
    void   MyStruct_setString(const Mystruct* m,const char* cp); 
    void   MyStruct_setVector(const Mystruct* m, const int* arr, size_t n); 
    int* MyStruct_getVector(const Mystruct* m); 
    void Mystruct_insert( Mystruct* m, int x); 
    size_t Mystruct_vectorsize(const Mystruct* m);  
    Mystruct* Mystruct_new_int( const int i); 
    Mystruct* Mystruct_new_string( const char* str); 
    Mystruct* Mystruct_new_array(const int* arr, size_t n ); 
    void Mystruct_delete(const Mystruct* m);  
     
    #endif  // __cplusplus 

/*
Then in your C calling code:

    int a[5] = { 1,2,3,4,5}; 
     
    Mystruct* M = Mystruct_new_array(a, 5); 
     
    Mystruct_set_Int(M, 100); 
     
    Mystruct_set_String(M, "a string"); 
     
    int* x = MyStruct_getVector(M); 
     
    Mystruct_insert(M, 12345);  
     
     
    int j = x[3]; /* this I think will work */ 
/*     
    Mystruct_delete(M); 

Notice that you have to pass a pointer argument to the struct for all C interfaces to it. A bit cumbersome, but simpler than trying to work out a bunch of attached function pointers, plus it forces you to realize what you are working with. My convention is to use the struct or class name as the first word of the C functions.

This example is problematic because it used std::string and std::vector, which have no C equivalents. It would be better to create structs with only C data types, or at least easier. This is called “Mix-In” style in that there is an impermeable barrier between the languages with a bridged translation API.

*/