//
// Created by Andrew on 12/17/2024.
//

#include "Redactor.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

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

// Redact sensitive data
void Redactor::redactContent(std::string &content) {
    size_t pos;
    while ((pos = content.find(nameToRedact)) != std::string::npos) {
        content.replace(pos, nameToRedact.length(), "REDACTED");
    }
    while ((pos = content.find(dobToRedact)) != std::string::npos) {
        content.replace(pos, dobToRedact.length(), "REDACTED");
    }
}

// Write redacted content to the new output folder
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
    // Get parent directory of the input directory
    fs::path inputDir = directory;
    fs::path outputFolder = inputDir.parent_path() / "redacted_files";

    fs::create_directory(outputFolder); // Create output folder if it doesn't exist

    for (const auto &entry : fs::directory_iterator(inputDir)) {
        if (entry.path().extension() == ".txt") { // Only process .txt files
            std::string content = readFile(entry.path().string());
            redactContent(content);

            // Save file to the output folder
            std::string newFile = outputFolder.string() + "/" + entry.path().stem().string() + "_redacted.txt";
            writeFile(newFile, content);
            std::cout << "Redacted file saved: " << newFile << "\n";
        }
    }

    // Open the output folder
#ifdef _WIN32
    system(("explorer " + outputFolder.string()).c_str()); // Windows
#elif __APPLE__
    system(("open " + outputFolder.string()).c_str());     // macOS
#else
    system(("xdg-open " + outputFolder.string()).c_str()); // Linux
#endif
}