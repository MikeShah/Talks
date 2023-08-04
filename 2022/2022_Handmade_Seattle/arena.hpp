// @file arena.hpp
class LocalArena{
    private:
        // Choose a data structure to manage your data
        //  - ImplicitList* myImplicitList;
        //  - ExplicitList* myExplicitList;
        //  - ListOfLists*  myPoolAllocator

        // *Maybe* one std::mutex if your Local Arena is shared.
        
    public:
        /* Create a region or 'arena' of memory */
        LocalArena(void* startOfRegion, void* endOfRegion){ /* .. */ }

        /* Find space in your arena for the # of bytes requested 
        */
        void* Allocate(std::size_t bytes);

        // Very simple allocation functions as an example for pool allocator
        // void* Allocate8Bytes();        
        // void* Allocate16Bytes();        
        // void* Allocate32Bytes();        
 
        /* Pass in an address, and mark free in Local Arena 
           Note: Optionally 'zero' out memory or do other bookkeeping.
        */
        void DeAllocate(void* address){ }
        
        /* reclaim all memory in just this arena */ 
        void Release(){ }
};


