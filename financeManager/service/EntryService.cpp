#include "EntryService.h"

// Constructor - Initializes DAO
EntryService::EntryService(const std::string& incomePath, const std::string& expensePath)
    : entryDAO(incomePath, expensePath) {}

// Retrieve all incomes
const std::vector<Income>&  EntryService::getAllIncomes()  {
    return entryDAO.getAllIncomes();
}

const std::vector<Expense>& EntryService::getAllExpenses() {
    return entryDAO.getAllExpenses();
}

// Add an income entry
void EntryService::addIncome(const Income& income) {
    entryDAO.addIncome(income);
}

// Add an expense entry
void EntryService::addExpense(const Expense& expense) {
    entryDAO.addExpense(expense);
}

// Update an existing income entry
void EntryService::updateIncome(const Income& oldIncome, const Income& newIncome) {
    entryDAO.updateIncome(oldIncome, newIncome);
}

// Update an existing expense entry
void EntryService::updateExpense(const Expense& oldExpense, const Expense& newExpense) {
    entryDAO.updateExpense(oldExpense, newExpense);
}

// Remove an income entry
void EntryService::removeIncome(const Income& income) {
    entryDAO.removeIncome(income);
}

// Remove an expense entry
void EntryService::removeExpense(const Expense& expense) {
    entryDAO.removeExpense(expense);
}

// Get file paths
std::string EntryService::getIncomePath() const {
    return entryDAO.getIncomePath();
}

std::string EntryService::getExpensePath() const {
    return entryDAO.getExpensePath();
}

// Set file paths
void EntryService::setIncomePath(const std::string& path) {
    entryDAO.setIncomePath(path);
}

void EntryService::setExpensePath(const std::string& path) {
    entryDAO.setExpensePath(path);
}

// Save all entries to files
void EntryService::saveEntriesToFile() {
    entryDAO.saveToFile();
}

// Load all entries from files
void EntryService::loadEntriesFromFile() {
    entryDAO.loadFromFile();
}
