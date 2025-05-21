#pragma once

#include "../model/Entry.h"
#include "../model/Income.h"
#include "../model/Expense.h"
#include "../dao/EntryDAO.h"
#include <vector>
#include <string>

class EntryService {
private:
    EntryDAO entryDAO;
public:
    EntryService(const std::string& incomePath, const std::string& expensePath);

    // CRUD operations for Income
    std::vector<Income> getAllIncomes();
    void addIncome(const Income& income);
    void updateIncome(const Income& oldIncome, const Income& newIncome);
    void removeIncome(const Income& income);

    // CRUD operations for Expense
    std::vector<Expense> getAllExpenses();
    void addExpense(const Expense& expense);
    void updateExpense(const Expense& oldExpense, const Expense& newExpense);
    void removeExpense(const Expense& expense);



    // File paths
    std::string getIncomePath() const;
    std::string getExpensePath() const;
    void setIncomePath(const std::string& path);
    void setExpensePath(const std::string& path);

    // File operations
    void saveEntriesToFile();
    void loadEntriesFromFile();
};
