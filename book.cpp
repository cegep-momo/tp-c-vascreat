#include <sstream>
#include <iostream>
#include "book.h"

using namespace std;

Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerName("") {}

Book::Book(const string& title, const string& author, const string& isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerName("") {}

string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
bool Book::getAvailability() const { return isAvailable; }
string Book::getBorrowerName() const { return borrowerName; }

void Book::setTitle(const string& t) { title = t; }
void Book::setAuthor(const string& a) { author = a; }
void Book::setISBN(const string& i) { isbn = i; }
void Book::setAvailability(bool available) { isAvailable = available; }
void Book::setBorrowerName(const string& name) { borrowerName = name; }

void Book::checkOut(const string& borrower) {
    isAvailable = false;
    borrowerName = borrower;
}

void Book::returnBook() {
    isAvailable = true;
    borrowerName.clear();
}

string Book::toString() const {
    string status = isAvailable ? "Disponible" : ("Emprunté par " + borrowerName);
    string result = "Titre: " + title + "\n";
    result += "Auteur: " + author + "\n";
    result += "ISBN: " + isbn + "\n";
    result += "Statut: " + status;
    return result;
}

string Book::toFileFormat() const {
    // Format: Title|Author|ISBN|<1=available|0=borrowed>|BorrowerName
    string avail = isAvailable ? "1" : "0";
    return title + "|" + author + "|" + isbn + "|" + avail + "|" + borrowerName;
}

void Book::fromFileFormat(const string& line) {
    stringstream ss(line);
    string avail;
    // Parse fields separated by '|'
    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');
    getline(ss, avail, '|');
    isAvailable = (avail != "0");
    string borrower;
    // borrower may be empty
    getline(ss, borrower, '|');
    borrowerName = borrower;
}