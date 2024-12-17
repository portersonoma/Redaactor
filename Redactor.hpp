//
// Created by Andrew on 12/17/2024.
//
#ifndef REDACTOR_HPP
#define REDACTOR_HPP

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Redactor {
private:
    std::string nameToRedact;
    std::string dobToRedact;

    std::string readFile(const std::string &filePath);
    void redactContent(std::string &content);
    void writeFile(const std::string &filePath, const std::string &content);

public:
    Redactor(const std::string &name, const std::string &dob);
    void processDirectory(const std::string &directory);
};

#endif // REDACTOR_HPP