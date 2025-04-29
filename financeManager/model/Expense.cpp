#include "Expense.h"
#include <algorithm>
#include <stdexcept>

const std::vector<std::string> Expense::expenseTypes = {"Transport", "Food", "Rent", "Entertainment", "Healthcare", "Other"};

Expense::Expense(const std::string& type, const std::string& date, const std::string& name, double amount)
    : Expense(0, type, date, name, amount) {}
Expense::Expense(int id, const std::string& type, const std::string& date, const std::string& name, double amount)
    : Entry(id, type, date, name, amount) {
    if (!checkType()) {
        throw std::invalid_argument("Invalid expense type: " + type);
    }
}

const std::vector<std::string>& Expense::getTypes() {
    return expenseTypes;
}

bool Expense::checkType() {
    return std::find(expenseTypes.begin(), expenseTypes.end(), type) != expenseTypes.end();
}
    
