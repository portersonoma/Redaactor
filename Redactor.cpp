//
// Created by Andrew on 12/17/2024.
//

#include "Redactor.hpp"
#include <iostream>
#include <fstream>

// Constructor
Redactor::Redactor(const std::string &name, const std::string &dob)
        : nameToRedact(name), dobToRedact(dob) {}

// Read file content
std::string Redactor::readFile(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string content, line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << "\n";
    }
    return content;
}

// Redact name and DOB from file content
void Redactor::redactContent(std::string &content) {
    size_t pos;
    while ((pos = content.find(nameToRedact)) != std::string::npos) {
        content.replace(pos, nameToRedact.length(), "REDACTED");
    }
    while ((pos = content.find(dobToRedact)) != std::string::npos) {
        content.replace(pos, dobToRedact.length(), "REDACTED");
    }
}

// Write redacted content to a new file
void Redactor::writeFile(const std::string &filePath, const std::string &content) {
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
    } else {
        std::cerr << "Unable to write to file: " << filePath << "\n";
    }
}

// Process all text files in a directory
void Redactor::processDirectory(const std::string &directory) {
    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".txt") {
            std::string content = readFile(entry.path().string());
            redactContent(content);
            std::string newFile = entry.path().parent_path().string() + "/" +
                                  entry.path().stem().string() + "_redacted.txt";
            writeFile(newFile, content);
            std::cout << "Redacted file saved: " << newFile << "\n";
        }
    }
}

