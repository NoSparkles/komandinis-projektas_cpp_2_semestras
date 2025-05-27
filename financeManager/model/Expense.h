#pragma once

#include "Entry.h"

class Expense : public Entry {
private:
    static int nextId;
    static const std::vector<std::string> expenseTypes;
public:
    // Constructors
    Expense(const std::string& type, const std::string& date, const std::string& name, double amount);
    Expense(int id, const std::string& type, const std::string& date, const std::string& name, double amount);

    static int getNextExpenseId();
    static void IncrementNextExpenseId();
    static void setNextExpenseId(int value);
    static const std::vector<std::string>& getTypes();
private:
    bool checkType();
};
