#include <cassert>   // To use the assert function to validate some conditions during execution.
#include <cstdio>    //  To handle C files (such as using std::fopen and std::fclose).
#include <fstream>   // To handle files using C++ (example: Create a file).
#include <iostream>  // To perform input and output operations (such as std::cout).
#include <locale>    // To adjust the output format according to the language or region (e.g., numbers formatting).
#include <memory>    // To use smart pointers such as std::unique_ptr and std::make_unique.
#include <stdexcept> // To handle exceptions (such as throwing or capturing std:runtime_error).

// Base class demonstrating runtime polymorphism.
class Base
{
  public:
    virtual ~Base() = default;
    virtual void doShop() { std::cout << "Base::doShop\n"; }
};

// Derived class that overrides Base's behavior.
class Derived : public Base
{
  public:
    Derived() { std::cout << "Derived::Constructor\n"; }
    ~Derived() { std::cout << "Derived::Destructor\n"; }
    void doShop() override { std::cout << "Derived::doShop\n"; }
};

// Function to transfer ownership of a Derived object.
// Note: Ownership is moved, ensuring unique ownership.
std::unique_ptr<Derived> passThrough(std::unique_ptr<Derived> derivedPtr)
{
    derivedPtr->doShop();
    return derivedPtr;
}

// Custom deleter function for C FILE pointers.
void closeFile(std::FILE *filePtr)
{
    if (filePtr)
    {
        std::fclose(filePtr);
    }
}

// A simple linked list that uses unique_ptr to manage nodes.
// This design avoids recursive destruction by iteratively releasing nodes.
class LinkedList
{
  public:
    // Internal Node structure.
    struct Node
    {
        int data;
        std::unique_ptr<Node> next;
    };

    // Insert a new node at the beginning.
    void push(int value)
    {
        auto newNode = std::make_unique<Node>();
        newNode->data = value;
        newNode->next = std::move(head_);
        head_ = std::move(newNode);
    }

    // Destructor iteratively releases nodes.
    ~LinkedList()
    {
        while (head_)
        {
            head_ = std::move(head_->next);
        }
    }

  private:
    std::unique_ptr<Node> head_;
};

// Demo 1: Unique Ownership Semantics
void demoUniqueOwnership()
{
    std::cout << "1) Unique Ownership Semantics Demo\n";
    auto derivedPtr = std::make_unique<Derived>();
    // Transfer ownership via passThrough.
    auto resultPtr = passThrough(std::move(derivedPtr));
    // After moving, derivedPtr should be null.
    assert(!derivedPtr && "derivedPtr must be null after move.");
}

// Demo 2: Runtime Polymorphism
void demoRuntimePolymorphism()
{
    std::cout << "\n2) Runtime Polymorphism Demo\n";
    auto derivedPtr = std::make_unique<Derived>();
    // Transfer to a unique_ptr of Base to achieve polymorphism.
    std::unique_ptr<Base> basePtr = std::move(derivedPtr);
    basePtr->doShop();
}

// Demo 3: Custom Deleter for FILE pointers
void demoCustomDeleter()
{
    std::cout << "\n3) Custom Deleter Demo\n";
    // Create a file for reading.
    std::ofstream("demo.txt") << 'x';
    using UniqueFilePtr = std::unique_ptr<std::FILE, decltype(&closeFile)>;
    UniqueFilePtr filePtr(std::fopen("demo.txt", "r"), &closeFile);
    if (filePtr)
    {
        std::cout << static_cast<char>(std::fgetc(filePtr.get())) << '\n';
    }
}

// Demo 4: Custom Lambda Deleter and Exception Safety
void demoLambdaCustomDeleter()
{
    std::cout << "\n4) Custom Lambda Deleter and Exception Safety Demo\n";
    try
    {
        // Define a lambda deleter for Derived.
        auto lambdaDeleter = [](Derived *ptr) {
            std::cout << "Custom lambda deleter is destroying the object...\n";
            delete ptr;
        };
        std::unique_ptr<Derived, decltype(lambdaDeleter)> derivedPtr(new Derived, lambdaDeleter);
        // Simulate an exception to show automatic resource cleanup.
        throw std::runtime_error("Simulated error");
    }
    catch (const std::exception &ex)
    {
        std::cout << "Caught exception: " << ex.what() << '\n';
    }
}

// Demo 5: Managing an Array of Objects with unique_ptr
void demoArrayUniquePtr()
{
    std::cout << "\n5) Array Form of unique_ptr Demo\n";
    // Using make_unique for arrays (C++14 and later).
    auto arrayPtr = std::make_unique<Derived[]>(3);
    // The destructors for the 3 elements will be automatically invoked.
}

// Demo 6: Linked List Using unique_ptr
void demoLinkedList()
{
    std::cout << "\n6) Linked List Demo\n";
    LinkedList list;
    const int nodeCount = 1000000;
    for (int i = 0; i < nodeCount; ++i)
    {
        list.push(i);
    }
    // Set locale to format the number according to US standards.
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << nodeCount << " nodes in the linked list (bottles of juice in the shop)...\n";
}

int main()
{
    demoUniqueOwnership();
    demoRuntimePolymorphism();
    demoCustomDeleter();
    demoLambdaCustomDeleter();
    demoArrayUniquePtr();
    demoLinkedList();

    return 0;
}