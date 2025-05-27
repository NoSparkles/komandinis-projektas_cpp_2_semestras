#pragma once

#include <vector>
#include <string>

#include "../model/Entry.h"
#include "../model/Income.h"
#include "../model/Expense.h"

class EntryDAO {
private:
    int nextIncomeId; // Tracks highest income ID
    int nextExpenseId; // Tracks highest expense ID
    std::vector<Income> incomes;
    std::vector<Expense> expenses;
    std::string incomePath;
    std::string expensePath;
public:
EntryDAO(std::string incomePath, std::string expensePath);

    ~EntryDAO();

    // CRUD operations
    int getNextIncomeId();
    int getNextExpenseId();
    void IncrementNextIncomeId();
    void IncrementNextExpenseId();

    const std::vector<Income>&  getAllIncomes();
    const std::vector<Expense>& getAllExpenses();
    void addIncome(const Income& income);
    void addExpense(const Expense& expense);
    void updateIncome(const Income& oldIncome, const Income& newIncome);
    void updateExpense(const Expense& oldExpense, const Expense& newExpense);
    void removeIncome(const Income& income);
    void removeExpense(const Expense& expense);

    // File paths
    std::string getIncomePath() const;
    std::string getExpensePath() const;
    void setIncomePath(const std::string& path);
    void setExpensePath(const std::string& path);

    // File operations
    void saveToFile();
    void loadFromFile();
};
