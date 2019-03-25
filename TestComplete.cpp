#include <iostream>
#include <new>
#include "gc.h"


// A simole class for testing GCPtr with class types
class MyClass {

    int a;
    int b;

public:

    double val;

    MyClass() {
        a = b = 0;
    }

    MyClass(int x, int y) {
        a = x;
        b = y;
        val = 0.0;
    }

    ~MyClass() {
        std::cout << "Destructing MyClass (" <<
        a << ", " << b << ")\n";
    }

    int sum() {
        return a + b;
    }

    friend std::ostream &operator<< (std::ostream &strm, MyClass &obj);
};

// Create an inserter for MyClass.
std::ostream &operator<< (std::ostream &strm, MyClass &obj) {
    strm << "(" << obj.a << " " << obj.b << ")";
    return strm;
}

// Pass a normal pointer to a function
void passPtr(int *p) {
    std::cout << "Inside passPtr(): "
    << *p << endl;
}

// Pass a GCPtr pointer to a function
void passGCPtr(GCPtr<int, 0> p) {
    std::cout << "Inside passGCPtr(): "
    << *p << endl;
}

int main() {

    try {

        // Declare an int GCPtr.
        GCPtr<int> ip;

        // Allocate an int and assign its address to ip
        ip = new int(22);

        // Display its value
        std::cout << "Value at *ip: " << *ip << "\n\n";

        // Pass ip to a function
        passGCPtr(ip);

        // ip2 is created and then goes out of scope
        {
            GCPtr<int> ip2 = ip;
        }

        int *p = ip; // convert to int * pointer

        passPtr(p); // Pass int * to passPtr()

        *ip = 100; // assign a new value to ip

        // Now use implicit conversion to int *
        passPtr(ip);

        std::cout << endl;

        // Create a GCPTr to an array of ints
        GCPtr<int, 5> iap = new int[5];

        // Initialise dynamic array
        for (int i = 0; i < 5; ++i) {
            iap[i] = i;
        }

        // Display content of array
        std::cout << "Content of iap via array indexing.\n";
        for (int j = 0; j < 5; ++j) {
            std::cout << iap[j] << " ";
        }
        std::cout << "\n\n";

        // Create a GCiterator
        GCPtr<int>::GCIterator itr;

        // Now use the iterator to access dynamic array
        std::cout << "Contents of iap via iterator.\n";
        for(itr = iap.begin(); itr != iap.end(); itr++) {
            std::cout << *itr << " ";
        }
        std::cout << "\n\n";

        // Generate and discard many objects
        for (int k = 0; k < 10; ++k) {
            ip = new int(k+10);
        }

        // Now manually garbage collect GCPTtr<int> list
        // Keep in mind that GCPtr<int, 5> pointers will not be collected
        // by this call
        GCPtr<int>::collect();

        // Now use GCPtr with class type
        GCPtr<MyClass> ob = new MyClass(10, 20);

        // show value via overloaded inserter
        std::cout << "ob points to " << *ob << endl;

        // Change object pointed to ob
        ob = new MyClass(11, 21);
        std::cout << "ob now points to " << *ob << endl;

        // Call a member function through a GCPtr
        std::cout << "Sum is: " << ob->sum() << endl;

        // Assign a value to a class member through a GCPtr
        ob->val = 19.21;
        std::cout << "ob->val : " << ob->val << "\n\n";

        std::cout << "Now work with pointers to class objects.\n";

        // Declare a GCPtr to a 5 elements array
        // of MYClass objects
        GCPtr<MyClass, 5> v;

        // Allocate the array
        v = new MyClass[5];

        // Get a MyClass iterator
        GCPtr<MyClass>::GCIterator mcItr;

        // Initialize the MyClass array
        for (int l = 0; l < 5; ++l) {
            v[l] = MyClass(l, 2*l);
        }

        // Display contents of MyClass array using indexing
        std::cout << "Cycle through array via array indexing.\n";
        for (int m = 0; m < 5; ++m) {
            std::cout << v[m] << " ";
        }
        std::cout << "\n\n";

        // Display contents of MyClass array using iterator
        std::cout << "Cycle through array via iterator.\n";
        for (mcItr = v.begin(); mcItr != v.end(); mcItr++) {
            std::cout << *mcItr << " ";
        }
        std::cout << "\n\n";

        // Here is another way to write the previous loop
        std::cout << "Cycling through array using a while loop.\n";
        mcItr = v.begin();
        while (mcItr != v.end()) {
            std::cout << *mcItr << " ";
            mcItr++;
        }
        std::cout << "\n\n";

        std::cout << "mcItr points to an array that is "
        << mcItr.size() << " objects long\n";

        // Find number of elements between two iterators
        GCPtr<MyClass>::GCIterator mcItr2 = v.end() - 2;
        mcItr = v.begin();
        std::cout << "The difference between mcItr2 and mcItr is "
        << mcItr2 - mcItr;
        std::cout << "\n\n";

        // Can also cycle though loop like this
        std::cout << "Dynamically compute length of array.\n";
        mcItr = v.begin();
        mcItr2 = v.end();

        for (int n = 0; n < mcItr2 - mcItr; ++n) {
            std::cout << v[n] << " ";
        }
        std::cout << "\n\n";

        // Now display the array backwards.
        std::cout << "Cycle through the array backwards.\n";
        for (mcItr = v.end() - 1; mcItr >= v.begin(); mcItr--) {
            std::cout << *mcItr << " ";
        }
        std::cout << "\n\n";

        // Of  course can use "normal" pointer to cycle though the array
        std::cout << "Cycle through the array using a normal pointer.\n";
        MyClass *ptr = v;
        for (int i = 0; i < 5; ++i) {
            std::cout << *ptr++ << " ";
        }
        std::cout << "\n\n";

        // Can access members through a GCIterator.
        std::cout << "Access class members through a iterator.\n";
        for (mcItr = v.begin(); mcItr != v.end(); mcItr++) {
            std::cout << mcItr->sum() << " ";
        }
        std::cout << "\n\n";

        // Can allocate and delete a pointer to a GCPtr
        // normally, just like any other pointer.
        std::cout << "Use a pointer to a GCPtr.\n";
        GCPtr<int> *pp = new GCPtr<int>();
        *pp = new int(100);
        std::cout << "Value at **pp is: " << **pp;
        std::cout << "\n\n";

        // Because pp is not a garbage collected pointer
        // it must be deleted manually
        delete pp;

    } catch (bad_alloc &exc) {
        // A real application could attempt to free
        // memory by collect() when allocation error occurs
        std::cout << "Allocation error.\n";
    }

    return 0;
}


















