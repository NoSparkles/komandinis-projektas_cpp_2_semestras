#include "Income.h"
#include <algorithm>
#include <stdexcept>

const std::vector<std::string> Income::incomeTypes = {"Salary", "Business", "Investments", "Freelancing", "Other"};

Income::Income(const std::string& type, const std::string& date, const std::string& name, double amount) 
: Income(0, type, date, name, amount) {}

Income::Income(int id, const std::string& type, const std::string& date, const std::string& name, double amount)
    : Entry(id, type, date, name, amount) {
    if (!checkType()) {
        throw std::invalid_argument("Invalid income type: " + type);
    }
}

const std::vector<std::string>& Income::getTypes() {
    return incomeTypes;
}

bool Income::checkType() {
    return std::find(incomeTypes.begin(), incomeTypes.end(), type) != incomeTypes.end();
}
    