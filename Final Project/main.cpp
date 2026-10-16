#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <ctime>
#include <unordered_set>

class Book {
protected:
    std::string title;
    std::string author;
    std::string genre;
    std::string status;
public:
    Book(std::string t, std::string a, std::string g)
        : title(std::move(t)), author(std::move(a)), genre(std::move(g)) {}
    virtual ~Book() = default;
    virtual void writeTo(std::ostream& output) const {
        output << genre << ',' << title << ',' << author << ",Book,0";
    }
};
class EBook : public Book {
    double fileSizeMB;
public:
    EBook(std::string t, std::string a, std::string g, double size)
        : Book(std::move(t), std::move(a), std::move(g)), fileSizeMB(size) {}
    void writeTo(std::ostream& output) const override {
        output << genre << ',' << title << ',' << author << ",EBook," << fileSizeMB;
    }
};

class PrintedBook : public Book {
    int pageCount;
public:
    PrintedBook(std::string t, std::string a, std::string g, int pages)
        : Book(std::move(t), std::move(a), std::move(g)), pageCount(pages) {}
    void writeTo(std::ostream& output) const override {
        output << genre << ',' << title << ',' << author << ",Printed," << pageCount;
    }
};
class Patron {
    std::string name;
    int id;
public:
    Patron(std::string n, int i) : name(std::move(n)), id(i) {}
    int getId() const { return id; }
    const std::string& getName() const { return name; }
};
class Transaction {
    int patronId;
    std::string bookTitle;
public:
    Transaction(int pid, std::string bt)
        : patronId(pid), bookTitle(std::move(bt)) {}
    void displayTransaction() const;
};
class Library {
    std::vector<Book*> books;
    std::vector<Patron> patrons;
    std::vector<Transaction> transactions;
    std::string booksFile;
    std::string patronsFile;
    std::string transactionsFile;
public:
    Library();
    ~Library();
    void loadData();
    void addBook(Book* book);
    void addPatron(const Patron& p);
    void checkoutBook(int patronId, std::string title);
    void returnBook(int patronId, std::string title);
    void displayBooks() const;
    void displayPatrons() const;
};



Library::Library() : booksFile("books.txt"), patronsFile("patrons.txt"), transactionsFile("transactions.txt")  {
    std::ifstream booksIn(booksFile);
    if (!booksIn) {
        booksFile = "Final Project\\books.txt";
        patronsFile = "Final Project\\patrons.txt";
        transactionsFile = "Final Project\\transactions.txt";
    }
}
Library::~Library() {
    for (Book* book : books) {
        delete book;
    }
}
void Library::loadData() {
    std::ifstream bookInput(booksFile);
    if (!bookInput) {
        throw std::runtime_error("Failed to open books file: " + booksFile);
    }
    std::ifstream patronInput(patronsFile);
    if (!patronInput) {
        throw std::runtime_error("Failed to open patrons file: " + patronsFile);
    }
    std::ifstream transactionsInput(transactionsFile);
    if (!transactionsInput) {
        throw std::runtime_error("Failed to open transactions file: " + transactionsFile);
    }
}
void Library::displayBooks() const{
    std::ifstream booksFile("books.txt");
    std::cout << booksFile.rdbuf();
    booksFile.close();
}
void Library::displayPatrons() const{
    std::ifstream patronsFile("patrons.txt");
    std::cout << patronsFile.rdbuf();
    patronsFile.close();
}
void Library::checkoutBook(int patronID, std::string title){
    std::ofstream transactionsFile("transactions.txt", std::ios::app);
    transactionsFile << "Patron ID: " << patronID << "  Checked Out: " << title << std::endl; 
    transactionsFile.close();
}
void Library::returnBook(int patronID, std::string title){
    std::ofstream transactionsFile("transactions.txt", std::ios::app);
    transactionsFile << "Patron ID: " << patronID << "  Returned Out: " << title << std::endl; 
    transactionsFile.close();
}
void Library::addBook(Book* book) {
    if (!book) {
        throw std::invalid_argument("Cannot add an empty book.");
    }

    std::ofstream bookOutput(booksFile, std::ios::app);
    if (!bookOutput) {
        delete book;
        throw std::runtime_error("Failed to open books file: " + booksFile);
    }

    book->writeTo(bookOutput);
    bookOutput << std::endl;
    if (!bookOutput) {
        delete book;
        throw std::runtime_error("Failed to write to books file: " + booksFile);
    }
    books.push_back(book);
    std::ofstream transactionsFile("transactions.txt", std::ios::app);
    transactionsFile << "Patron Added File" << std::endl;
    transactionsFile.close();
}
void Library::addPatron(const Patron& p) {
    std::ofstream patronOutput(patronsFile, std::ios::app);
    if (!patronOutput) {
        throw std::runtime_error("Failed to open patrons file: " + patronsFile);
    }
    patronOutput << p.getId() << ',' << p.getName() << std::endl;
    if (!patronOutput) {
        throw std::runtime_error("Failed to write to patrons file: " + patronsFile);
    }
    patrons.push_back(p);
    std::ofstream transactionsFile("transactions.txt", std::ios::app);
    transactionsFile << "Patron Added" << std::endl;
    transactionsFile.close();
}

int main() {
    try {
        Library library;
        library.loadData();
    } catch (const std::exception& e) {
        std::cerr << "Application Error: " << e.what() << std::endl;
    }
    int userinput = 0;
    int pnum;
    std:: cout << "Please input your patron number: ";
    std:: cin >> pnum;
    while (userinput != 8){
    std:: cout << "Type 1 to view all books, 2 to view all patrons, 3 to checkout books, 4 to return books, 5 to add a new book, 6 to add a new patron, 7 to change your patron number, or 8 to end the program." << std::endl;
    std:: cin >> userinput;
        if (userinput == 1){
        Library library;
        library.displayBooks();
        }
        else if (userinput == 2){
        Library library;
        library.displayPatrons();
        }
        else if (userinput == 3){
        std::string cbook;
        Library library;
        std::cout << "Input book title" << std::endl;
        std::cin >> cbook;
        library.checkoutBook(pnum,cbook);
        }
        else if (userinput == 4){
        std::string rbook;
        Library library;
        std::cout << "Input book title" << std::endl;
        std::cin >> rbook;
        library.returnBook(pnum, rbook);
        }
        else if (userinput == 5){
        Library library;
        std::string title;
        std::string author;
        std::string genre;
        std::string validity = "no";
        std::string formatvalid = "no";
        std::string format;
        std::cout << " " << std::endl <<"Please input new book's title: ";
        std::cin.ignore();
        std::getline(std::cin, title); 
        std::cout << "Inputted Title: " <<  title << std::endl;
        std::cout << "Please input new book's author: ";
        std::getline(std::cin, author); 
        std::cout << "Inputted Author: " <<  author << std::endl;
        std::cout << "Is the book's genre Fiction, NonFiction, Mystery, Science, or Biography: " << std::endl;
        std::cin >> genre;
        while (validity == "no"){
            if ((std::unordered_set<std::string>{"Fiction","NonFiction","Mystery","Science","Biography"}.count(genre)) == 0){
                std::cout << "Wrong Genre" << std::endl;
                std::cout << "Is the book's genre Fiction, NonFiction, Mystery, Science, or Biography: " << std::endl;
                std::cin >> genre;
            }
            else {
                validity = "yes";
            }
        }
        std::cout << "Is the book's format Printed or EBook: " << std::endl;
        std::cin >> format;
        while (formatvalid == "no"){
            if(format == "Printed"){
                int pages;
                std::cout << "Input number of pages: " << std::endl;
                std::cin >> pages;
                formatvalid = "yes";
                library.addBook(new PrintedBook(title, author, genre, pages));
            }
            else if(format == "EBook"){
                double size;
                std::cout << "Input file size as a number of MB: " << std::endl;
                std::cin >> size;
                formatvalid = "yes";
                library.addBook(new EBook(title, author, genre, size));
            }
            else {
                std::cout << "Wrong format" << std::endl;
                std::cout << "Is the book's format Printed or EBook: " << std::endl;
                std::cin >> format;
            }
        }
        }
        else if (userinput == 6){
        Library library;
        int ID;
        std::string Name;
        std::cout << "Please input new patron's ID: " << std::endl;
        std::cin >> ID;
        std::cout << "Please input new patron's name: " << std::endl;
        std::cin >> Name;
        library.addPatron(Patron(Name,ID));
        }
        else if (userinput == 7){
        std:: cout << "Please input your patron number" << std::endl;
        std:: cin >> pnum;
        }
        else if (userinput == 8){
            return 0;
        }
        else {
            std:: cout << "Please input number between 1 and 8" << std::endl;
        }

    }
    
    return 0;
}