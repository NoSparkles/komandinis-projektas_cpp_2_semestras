#include "Expense.h"
#include <algorithm>
#include <stdexcept>

int Expense::nextId = 0;
const std::vector<std::string> Expense::expenseTypes = {"Transport", "Food", "Rent", "Entertainment", "Healthcare", "Other"};

Expense::Expense(const std::string& type, const std::string& date, const std::string& name, double amount)
    : Entry(type, date, name, amount) {
    if (!checkType()) {
        throw std::invalid_argument("Invalid expense type: " + type);
    }
    this->id = ++Expense::nextId;
}

Expense::Expense(int id, const std::string& type, const std::string& date, const std::string& name, double amount)
    : Entry(type, date, name, amount) {
    if (!checkType()) {
        throw std::invalid_argument("Invalid expense type: " + type);
    }
    this->id = id;
}

int Expense::getNextExpenseId() {
    return Expense::nextId;
}

void Expense::IncrementNextExpenseId() {
    ++Expense::nextId;
}

void Expense::setNextExpenseId(int value) {
    Expense::nextId = value;
}

const std::vector<std::string>& Expense::getTypes() {
    return expenseTypes;
}

bool Expense::checkType() {
    return std::find(expenseTypes.begin(), expenseTypes.end(), type) != expenseTypes.end();
}
    
