#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Book structure
struct Book {
    int id;
    char title[100];
    char author[100];
    float price;
    struct Book* next;
};

// Customer structure
struct Customer {
    int id;
    char name[100];
    struct Book* purchased_books;
    struct Customer* next;
};

// Function to create a new book
struct Book* createBook(int id, char* title, char* author, float price) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->price = price;
    newBook->next = NULL;
    return newBook;
}

// Function to add a book to the inventory
void addBook(struct Book** inventory, int id, char* title, char* author, float price) {
    struct Book* newBook = createBook(id, title, author, price);
    newBook->next = *inventory;
    *inventory = newBook;
}

// Function to display books in the inventory
void displayBooks(struct Book* inventory) {
    struct Book* temp = inventory;
    printf("Book Inventory:\n");
    while (temp != NULL) {
        printf("ID: %d, Title: %s, Author: %s, Price: %.2f\n", temp->id, temp->title, temp->author, temp->price);
        temp = temp->next;
    }
}

// Function to create a new customer
struct Customer* createCustomer(int id, char* name) {
    struct Customer* newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
    newCustomer->id = id;
    strcpy(newCustomer->name, name);
    newCustomer->purchased_books = NULL;
    newCustomer->next = NULL;
    return newCustomer;
}

// Function to add a customer
void addCustomer(struct Customer** customerList, int id, char* name) {
    struct Customer* newCustomer = createCustomer(id, name);
    newCustomer->next = *customerList;
    *customerList = newCustomer;
}

// Function for a customer to purchase a book
void purchaseBook(struct Customer* customer, struct Book* inventory, int bookID) {
    struct Book* temp = inventory;
    while (temp != NULL && temp->id != bookID) {
        temp = temp->next;
    }
    
    if (temp != NULL) {
        struct Book* purchasedBook = createBook(temp->id, temp->title, temp->author, temp->price);
        purchasedBook->next = customer->purchased_books;
        customer->purchased_books = purchasedBook;
        printf("%s purchased '%s'\n", customer->name, temp->title);
    } else {
        printf("Book with ID %d not found in inventory.\n", bookID);
    }
}

// Function to display customer's purchased books
void displayPurchasedBooks(struct Customer* customer) {
    printf("%s's Purchased Books:\n", customer->name);
    struct Book* temp = customer->purchased_books;
    while (temp != NULL) {
        printf("Title: %s, Author: %s, Price: %.2f\n", temp->title, temp->author, temp->price);
        temp = temp->next;
    }
}

int main() {
    struct Book* inventory = NULL;
    struct Customer* customerList = NULL;

    // Adding books to inventory
    addBook(&inventory, 1, "The C Programming Language", "Kernighan & Ritchie", 29.99);
    addBook(&inventory, 2, "Clean Code", "Robert C. Martin", 32.50);
    addBook(&inventory, 3, "The Pragmatic Programmer", "Andy Hunt", 40.00);

    // Display the inventory
    displayBooks(inventory);

    // Adding customers
    addCustomer(&customerList, 1, "Alice");
    addCustomer(&customerList, 2, "Bob");

    // Purchase books
    purchaseBook(customerList, inventory, 2); // Bob purchases Clean Code
    purchaseBook(customerList->next, inventory, 1); // Alice purchases The C Programming Language

    // Display purchased books
    displayPurchasedBooks(customerList);       // Bob's purchases
    displayPurchasedBooks(customerList->next); // Alice's purchases

    return 0;
}
