#include "EntryDAO.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iostream>

// Constructor - Initialize IDs and load data from files
EntryDAO::EntryDAO(std::string incomePath, std::string expensePath)
    : nextIncomeId(0), nextExpenseId(0) {
    setIncomePath(incomePath);
    setExpensePath(expensePath);
    loadFromFile();
}

// Destructor - Clear stored entries
EntryDAO::~EntryDAO() {
    incomes.clear();
    expenses.clear();
}

int EntryDAO::getNextIncomeId() {
    return this->nextIncomeId;
}
int EntryDAO::getNextExpenseId() {
    return this->nextExpenseId;
}
void EntryDAO::IncrementNextIncomeId() {
    ++this->nextIncomeId;
}
void EntryDAO::IncrementNextExpenseId() {
    ++this->nextExpenseId;
}

// Retrieve all incomes
const std::vector<Income>&  EntryDAO::getAllIncomes() {
    return incomes;
}

// Retrieve all expenses
const std::vector<Expense>& EntryDAO::getAllExpenses() {
    return expenses;
}


// Add new income entry
void EntryDAO::addIncome(const Income& income) {
    incomes.push_back(income);
}

// Add new expense entry
void EntryDAO::addExpense(const Expense& expense) {
    expenses.push_back(expense);
}

// Update an existing income entry
void EntryDAO::updateIncome(const Income& oldIncome, const Income& newIncome) {
    for (Income& entry : incomes) {
        if (entry.getId() == oldIncome.getId()) {
            entry = newIncome;
            return;
        }
    }
}

// Update an existing expense entry
void EntryDAO::updateExpense(const Expense& oldExpense, const Expense& newExpense) {
    for (Expense& entry : expenses) {
        if (entry.getId() == oldExpense.getId()) {
            entry = newExpense;
            return;
        }
    }
}

// Remove an income entry
void EntryDAO::removeIncome(const Income& income) {
    for (auto it = incomes.begin(); it != incomes.end();) {
        if (it->getId() == income.getId()) {
            it = incomes.erase(it);
        } else {
            ++it;
        }
    }
}

// Remove an expense entry
void EntryDAO::removeExpense(const Expense& expense) {
    for (auto it = expenses.begin(); it != expenses.end();) {
        if (it->getId() == expense.getId()) {
            it = expenses.erase(it);
        } else {
            ++it;
        }
    }
}

std::string EntryDAO::getIncomePath() const { return incomePath; }
std::string EntryDAO::getExpensePath() const { return expensePath; }
void EntryDAO::setIncomePath(const std::string& path) { incomePath = path; }
void EntryDAO::setExpensePath(const std::string& path) { expensePath = path; }

// Save entries separately to income and expense files
void EntryDAO::saveToFile() {
    std::ofstream incomeFile(incomePath), expenseFile(expensePath);

    if (!incomeFile.is_open() || !expenseFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    incomeFile << "ID,Type,Date,Name,Amount\n";
    for (const auto& entry : incomes) {
        incomeFile << entry.getId() << "," << entry.getType() << "," << entry.getDate() << ","
                   << entry.getName() << "," << entry.getAmount() << "\n";
    }
    incomeFile.close();

    expenseFile << "ID,Type,Date,Name,Amount\n";
    for (const auto& entry : expenses) {
        expenseFile << entry.getId() << "," << entry.getType() << "," << entry.getDate() << ","
                    << entry.getName() << "," << entry.getAmount() << "\n";
    }
    expenseFile.close();
}

// Load entries separately from income and expense files
void EntryDAO::loadFromFile() {
    std::ifstream inIncome(incomePath), inExpense(expensePath);
    std::string line;

    // Load Income Data
    if (inIncome.is_open()) {
        std::getline(inIncome, line); // Skip header
        while (std::getline(inIncome, line)) {
            std::stringstream ss(line);
            std::string id, type, date, name, amount;
            
            std::getline(ss, id, ',');
            std::getline(ss, type, ',');
            std::getline(ss, date, ',');
            std::getline(ss, name, ',');
            std::getline(ss, amount, ',');

            int entryId = std::stoi(id);
            incomes.emplace_back(entryId, type, date, name, std::stod(amount));
            nextIncomeId = std::max(nextIncomeId, entryId); 
        }
        inIncome.close();
    }
    // Load Expense Data
    if (inExpense.is_open()) {
        std::getline(inExpense, line); // Skip header
        while (std::getline(inExpense, line)) {
            std::stringstream ss(line);
            std::string id, type, date, name, amount;

            std::getline(ss, id, ',');
            std::getline(ss, type, ',');
            std::getline(ss, date, ',');
            std::getline(ss, name, ',');
            std::getline(ss, amount, ',');

            int entryId = std::stoi(id);
            expenses.emplace_back(entryId, type, date, name, std::stod(amount));
            nextExpenseId = std::max(nextExpenseId, entryId);
        }
        inExpense.close();
    }
}
