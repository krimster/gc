/*
 * A single-threaded garbage collector
 */

#ifndef GARBAGECOLLECTOR_GC_H
#define GARBAGECOLLECTOR_GC_H

#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>

using namespace std;

// To watch the action of the garbage collector, define DISPLAY.
//#define DISPLAY

// Exception thrown when an attempt is made to use an Iter that
// exceeds the range if the underlying object
class OutOfRangeExc {
    // Add functionality if needed by your application
};

// An iterator-like class for cycling through arrays
// that are pointed to by GCPtrs. Iter pointers
// ** do not ** participate in or affect garbage collection.
// Thus, an Iter pointing to some object does not prevent that
// object from being recycled
//
template <class T> class Iter {

    T *ptr; // current pointer value
    T *end; // points to element one past end
    T *begin; // points to start of allocated array
    unsigned length; // length of sequence

public:
    Iter() {
        ptr = end = begin = NULL;
        length = 0;
    }

    Iter(T *p, T *first, T *last) {

        ptr = p;
        end = last;
        begin = first;
        length = last - first;
    }

    // Return length of sequence to which this Iter points
    unsigned size() { return length; }

    // Return value pointed to by ptr
    // Do not allow out of bounds access
    T &operator* () {
        if ( (ptr >= end) || (ptr < begin)) {
            throw OutOfRangeExc();
        }
        return *ptr;
    }

    // Return address contained in ptr
    // Do not allow out-of-bounds access
    T *operator->() {
        if ((ptr >= end) || (ptr < begin)) {
            throw OutOfRangeExc();
        }
        return ptr;
    }

    // Prefix ++
    Iter operator++() {
        ptr++;
        return *this;
    }

    // Prefix --
    Iter operator--() {
        ptr--;
        return *this;
    }

    // Postfix ++
    Iter operator++(int notUsed) {

        T *tmp = ptr;

        ptr++;
        return Iter<T>(tmp, begin, end);
    }

    // Postfix --
    Iter operator--(int notUsed) {

        T *tmp = ptr;

        ptr--;
        return Iter<T>(tmp, begin, end);
    }

    // Return a reference to the object at the specified index
    // Do not allow out-of-bounds access
    T &operator [] (int i) {
        if ( (i < 0) || (i >= (end - begin))) {
            throw OutOfRangeExc();
        }
        return ptr[i];
    }

    // Define relational operators.
    bool operator == (Iter op2) {
        return ptr == op2.ptr;
    }

    bool operator != (Iter op2) {
        return ptr != op2.ptr;
    }

    bool operator < (Iter op2) {
        return ptr < op2.ptr;
    }

    bool operator <= (Iter op2) {
        return ptr <= op2.ptr;
    }

    bool operator > (Iter op2) {
        return ptr > op2.ptr;
    }

    bool operator >= (Iter op2) {
        return ptr >= op2.ptr;
    }

    // Subtract an integer from an Iter
    Iter operator - (int n) {

        ptr -= n;
        return *this;
    }

    // Add an integer to Iter
    Iter operator + (int n) {

        ptr += n;
        return *this;
    }

    // Return number of elements between 2 Iters
    int operator - (Iter<T> &itr2) {
        return ptr - itr2.ptr;
    }
};

// This class defines an element that is stored in the
// garbage collection information list
template <class T> class GCInfo {

public:

    unsigned refCount; // current reference count

    T *memPtr; // Pointer to the allocated memory

    /* isArray is true if memPtr points to an allocated array.
     * It is false otherwise. */
    bool isArray; // true if pointing to an array

    /* if memPtr is pointing to an allocated array,
     * then arraySize contains its size */
    unsigned arraySize; // size of array

    // Here, mPtr points to the allocated memory.
    // Of this is an array, then size specifies
    // the size of the array
    GCInfo(T *mPtr, unsigned size = 0) {
        refCount = 1;
        memPtr = mPtr;
        isArray = size != 0;
        arraySize = size;
    }
};

// Overloading operator== allows GCInfos to be compared
// This is needed by the STL list class
template <class T> bool operator== (const GCInfo<T> &ob1, const GCInfo<T> &ob2) {
    return (ob1.memPtr == ob2.memPtr);
}

// GCInfo implements a pointer type that uses garbage collection to release unused memory.
// A GCPtr must only be used to point to memory that was dynamically allocated using new.
// When used to refer to an allocated array, specify the array size.
template <class T, int size = 0> class GCPtr {

        // gclist maintains the garbage collection list.
        static list<GCInfo<T>> gclist;

        // addr points to the allocated memory to which this GCPtr pointer currently points
        T *addr;

        /* isArray is true if this GCPtr points to an allocated array.
         * It is false otherwise */
        bool isArray; // true if pointing to an array

        // If this GCPtr is pointing to an allocated array, then arraySize contains its size.
        unsigned arraySize; // the size of the array

        static bool first; // true when first GCPtr is created

        // Return an iterator to pointer info in gclist
        typename list<GCInfo<T>>::iterator findPtrInfo(T *ptr);

public:
    // Define an iterator type for GCPtr<T>
    typedef Iter<T> GCIterator;

    // Construct both initialized and uninitialized objects
    GCPtr(T *t=NULL) {

        // Register shutdown() as an exit function.
        if (first) std::atexit(shutdown);
        first = false;

        typename list<GCInfo<T>>::iterator p;

        p = findPtrInfo(t);

        // if t is already i gclist, then increment its reference count.
        // Otherwise, add it to the list
        if (p != gclist.end()) {
            p->refCount++; // increment ref count
        } else {
            // Create and store this entry
            GCInfo<T> gcObj(t, size);
            gclist.push_front(gcObj);
        }

        addr = t;
        arraySize = size;
        isArray = size > 0;

        #ifdef DISPLAY
        cout << "Constructing GCPtr. ";
        if (isArray) {
            cout << "size is : " << arraySize << endl;
        } else {
            cout << endl;
        }

        #endif
    }

    // Copy constructor
    GCPtr(const GCPtr &ob) {

        typename list<GCPtr<T>>::iterator p;

        p = findPtrInfo(ob.addr);
        p->refcount++; // increment ref count

        addr = ob.addr;
        arraySize = ob.arraySize;
        isArray = arraySize > 0;
        #ifdef DISPLAY
            cout << "Constructing copy";
            if (isArray) {
                cout << "Size is " << arraySize << endl;
            } else {
                cout << endl;
            }
        #endif
    }

    // Destructor for GCPtr
    ~GCPtr();

    // Collect garbage. Returns true if at least one object was freed
    static bool collect();

    // overload assignment of pointer to GCPtr
    T *operator=(T *t);

    // Overload asssignment of GCPtr to GCPtr
    GCPtr &operator=(GCPtr &rv);

    // Return reference to the object pointed to by this GCPtr
    T &operator*() {
        return *addr;
    }

    // Return address being pointer to
    T *operator->() {
        return addr;
    }

    // Return a reference to the object at the index specified by i
    T &operator[](int i) {
        return addr[i];
    }

    // Conversion to T *
    operator T *() {
        return addr;
    }

    // Return an Iter to the start of the allocated memory
    Iter<T> begin() {

        int sz;

        if (isArray) sz = arraySize;
        else sz=1;

        return Iter<T>(addr, addr, addr + sz);
    }

    // Return an Iter to one past the end of an allocated array
    Iter<T> end() {

        int sz;

        if (isArray) sz = arraySize;
        else sz = 1;

        return Iter<T>(addr + sz, addr, addr + sz);
    }

    // Return the size of gclist for this type of GCPtr
    static int gclistSize() {
        return gclist.size();
    }

    // A utility function that displays gclist
    static void showlist();

    // Clear gclist when program exits
    static void shutdown();

    };

    // Create a storage for the static variables
    template <class T, int size>
    list<GCInfo<T>> GCPtr<T, size>::gclist;

    template <class T, int size>
    bool GCPtr<T, size>::first = true;

    // Destructor for GCPtr
    template <class T, int size>
    GCPtr<T, size>::~GCPtr() {

        typename list<GCInfo<T>>::iterator p;

        p = findPtrInfo(addr);
        if (p->refcount) p->recount--; // decrement red count

        #ifdef DISPLAY
            cout << "GCPtr pointer out of scope.\n";
        #endif

        // Collect garbage when a pointer is out of scope
        collect();


        // For real use, you might want to collect unused memory less frequently
        // such as after gclist has reached a certain size, after a certain number
        // of GCPtrs have gone out of scope, or when memory is low.
    }

    // Collect garbage. Return true if at least one object was freed
    template <class T, int size>
    bool GCPtr<T, size>::collect() {
        bool memFreed = false;

        #ifdef DISPLAY
            cout << "Before garbage collection for ";
            showlist();
        #endif

        typename list<GCInfo<T>>::iterator p;

        do {
            // Scan gclist looking for unreferenced pointers.
            for (p = gclist.begin(); p != gclist.end(); p++) {
                // if in-use skip
                if (p->refcount > 0) continue;

                memFreed = true;

                // Remove unused entry from gclist
                gclist.remove(*p);

                // Free memory unless the GCPtr is null
                if (p->memPtr) {

                    if (p->isArray) {

                    #ifdef DISPLAY
                        cout << "Deleting array of size "
                        << p->arraySize << endl;
                    #endif

                        delete[] p->memPtr; // delete array

                    } else {
                        #ifdef DISPLAY
                            cout << "Deleting: "
                            << *(T *) p->memPtr << "\n";
                        #endif
                        delete p->memPtr; // delete single element
                    }
                }
                // Restart the search
                break;
            }
        } while(p != gclist.end());

        #ifdef DISPLAY
            cout << "After garbage collection for ";
            showlist();
        #endif

        return memFreed;
    }

    // Overload assignment of pointer to GCPtr.
    template <class T, int size>
    T * GCPtr<T, size>::operator=(T *t) {

        typename list<GCInfo<T>>::iterator p;

        // First, decrement the reference count
        // for the memory currently being pointed to
        p = findPtrInfo(addr);
        p->recount--;

        // Next, if te new address is already existent in the system,
        // increment its count. Otherwise, create a new entry for gclist
        p = findPtrInfo(t);
        if (p != gclist.end()) {

            p->recount++;
        } else {

            // Create and store this entry
            GCInfo<T> gcObj(t, size);
            gclist.push_front(gcObj);
        }

        addr = t; // store the address

        return t;
    }

    // Overload assignment of GCPtr to GCPtr.
    template <class T, int size>
    GCPtr<T, size> & GCPtr<T, size>::operator=(GCPtr &rv) {

        typename list<GCInfo<T>>::iterator p;

        // First decrement the reference count
        // for the memory currently being pointed to.
        p = findPtrInfo(addr);
        p->refcount--;

        // Next, increment the reference count of the new address
        p = findPtrInfo(rv.addr);
        p->recount++; // increment the count

        addr = rv.addr; // store the address.

        return rv;
    }

    // A utility function that displays gclist
    template <class T, int size>
    void GCPtr<T, size>::showlist() {

        typename list<GCInfo<T>>::iterator p;

        cout << "gclist<" << typeid(T).name() << ", "
        << size << ">: \n";
        cout << "memPtr     recount         value\n";

        if (gclist.begin() == gclist.end()) {
            cout << "      -- Empty --\n\n";
            return;
        }

        for (p = gclist.beging(); p != gclist.end(); p++) {

            cout << " [" << (void *)p->memPtr << "]"
            << "        " << p->refcount << "       ";

            if (p->memPtr) cout << "    " << *p->memPtr;
            else cout << "   ---";
            cout << endl;
        }
        cout << endl;
    }

    // Find a pointer in gclist.
    template <class T, int size>
    typename list<GCInfo<T>>::iterator
    GCPtr<T, size>::findPtrInfo(T *ptr) {

        typename list<GCInfo<T>>::iterator p;

        // Find pointer in gclist
        for (p = gclist.begin(); p != gclist.end(); p++) {
            if (p->memPtr == ptr) {
                return p;
            }
        }
        return p;
    }

    // Clear gclist when program exits
    template <class T, int size>
    void GCPtr<T, size>::shutdown() {

        if (gclistSize() == 0) return; // list is empty

        typename list<GCInfo<T>>::iterator p;

        for (p == gclist.begin(); p != gclist.end(); p++) {

            // Set all ref counts to zero
            p->refcount = 0;
        }

        #ifdef DISPLAY
            cout << "Before collecting for shutdown() for "
            << typeid(T).name() << "\n";
        #endif

        collect();

        #ifdef DISPLAY
            cout << "After collecting for shutdown() for "
            << typeid(T).name() << "\n";
        #endif
    }































#endif //GARBAGECOLLECTOR_GC_H