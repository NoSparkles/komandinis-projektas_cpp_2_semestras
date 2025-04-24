#pragma once

#include "Entry.h"

class Income : public Entry {
private:
    static const std::vector<std::string> incomeTypes;
public:
    // Constructors
    Income(const std::string& type, const std::string& date, const std::string& name, double amount);
    Income(int id, const std::string& type, const std::string& date, const std::string& name, double amount);

    static const std::vector<std::string>& getTypes();
private:
    bool checkType();
};