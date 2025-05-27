#include "Income.h"
#include <algorithm>
#include <stdexcept>

int Income::nextId = 0;
const std::vector<std::string> Income::incomeTypes = {"Salary", "Business", "Investments", "Freelancing", "Other"};

Income::Income(const std::string& type, const std::string& date, const std::string& name, double amount)
    : Entry(type, date, name, amount) {
    if (!checkType()) {
        throw std::invalid_argument("Invalid income type: " + type);
    }
    this->id = ++Income::nextId;
}

Income::Income(int id, const std::string& type, const std::string& date, const std::string& name, double amount)
    : Entry(type, date, name, amount) {
    if (!checkType()) {
        throw std::invalid_argument("Invalid income type: " + type);
    }
    this->id = id;
}

int Income::getNextIncomeId() {
    return Income::nextId;
}

void Income::IncrementNextIncomeId() {
    ++Income::nextId;
}

void Income::setNextIncomeId(int value) {
    Income::nextId = value;
}

const std::vector<std::string>& Income::getTypes() {
    return incomeTypes;
}

bool Income::checkType() {
    return std::find(incomeTypes.begin(), incomeTypes.end(), type) != incomeTypes.end();
}
    
