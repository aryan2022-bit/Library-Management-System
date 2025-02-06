#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

// Define the Book structure
struct Book {
    int id;
    char title[100];
    char author[100];
    bool isIssued;

    Book(int id, const char* title, const char* author)
        : id(id), isIssued(false) {
        strcpy(this->title, title);
        strcpy(this->author, author);
    }
};

// Node structure for linked list (Singly Linked List)
struct Node {
    Book book;
    Node* next;
    Node(Book b) : book(b), next(NULL) {}
};

// Class for managing books using Singly Linked List
class BookList {
private:
    Node* head;

public:
    BookList() : head(NULL) {}

    void addBook(int id, const char* title, const char* author) {
        Node* newNode = new Node(Book(id, title, author));
        newNode->next = head;
        head = newNode;
        cout << "Book added successfully!" << endl;
    }

    Node* searchBookByID(int id) {
        Node* current = head;
        while (current != NULL) {
            if (current->book.id == id)
                return current;
            current = current->next;
        }
        return NULL;
    }

    void listBooks() {
        Node* current = head;
        while (current != NULL) {
            cout << "ID: " << current->book.id << ", Title: " << current->book.title
                 << ", Author: " << current->book.author << ", Status: "
                 << (current->book.isIssued ? "Issued" : "Available") << endl;
            current = current->next;
        }
    }
};

// Simulated hash table for fast book ID lookup
const int MAX_BOOKS = 1000;  // Adjust size as needed
Book* bookMap[MAX_BOOKS];

// Stack for undo operations
stack<Book> actionStack;

// Queue for book requests
queue<int> bookQueue;

// Function to add new books
void addBook(BookList &bookList, int id, const char* title, const char* author) {
    bookList.addBook(id, title, author);
    bookMap[id % MAX_BOOKS] = new Book(id, title, author);
    actionStack.push(Book(id, title, author));
}

// Function to search for a book by ID
Book* searchBookByID(int id) {
    if (bookMap[id % MAX_BOOKS] && bookMap[id % MAX_BOOKS]->id == id)
        return bookMap[id % MAX_BOOKS];
    return NULL;
}

// Function to issue a book
bool issueBook(BookList &bookList, int id, const char* student) {
    Node* node = bookList.searchBookByID(id);
    if (node && !node->book.isIssued) {
        node->book.isIssued = true;
        cout << "Book issued to " << student << " successfully!" << endl;
        return true;
    }
    cout << "Book is already issued or not found." << endl;
    return false;
}

// Function to return a book
bool returnBook(BookList &bookList, int id) {
    Node* node = bookList.searchBookByID(id);
    if (node && node->book.isIssued) {
        node->book.isIssued = false;
        cout << "Book returned successfully!" << endl;
        return true;
    }
    cout << "Book is not issued or not found." << endl;
    return false;
}

// Main function to demonstrate usage
int main() {
    BookList bookList;
    int choice, id;
    char title[100], author[100], student[100];

    while (true) {
        cout << "\n----- LIBRARY MANAGEMENT SYSTEM -----\n"<<endl;
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. List All Books\n";
        cout << "6. Exit\n"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();  // To ignore the newline character after entering the ID
                cout << "Enter Book Title: ";
                cin.getline(title, 100);
                cout << "Enter Book Author: ";
                cin.getline(author, 100);
                addBook(bookList, id, title, author);
                break;
            case 2:
                cout << "Enter Book ID: ";
                cin >> id;
                if (Node* node = bookList.searchBookByID(id)) {
                    cout << "Book found: " << node->book.title << " by " << node->book.author << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            case 3:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();  // To ignore the newline character after entering the ID
                cout << "Enter Student Name: ";
                cin.getline(student, 100);
                issueBook(bookList, id, student);
                break;
            case 4:
                cout << "Enter Book ID: ";
                cin >> id;
                returnBook(bookList, id);
                break;
            case 5:
                bookList.listBooks();
                break;
            case 6:
                cout << "Exiting the system." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
