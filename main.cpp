#include <iostream>
#include "Redactor.hpp"

int main() {
    std::string name, dob, directory;

    std::cout << "== Patient Data Redactor ==" << std::endl;
    std::cout << "Enter name to redact: ";
    std::getline(std::cin, name);

    std::cout << "Enter date of birth to redact (YYYY-MM-DD): ";
    std::getline(std::cin, dob);

    std::cout << "Enter directory path containing text files: ";
    std::getline(std::cin, directory);

    // Create a Redactor object and process files
    Redactor redactor(name, dob);
    std::cout << "Redaction complete" << std::endl;
    redactor.processDirectory(directory);
    std::cout << "Directory created" << std::endl;

    return 0;
}

