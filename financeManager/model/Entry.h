#pragma once

#include <string>
#include <vector>

class Entry {
protected:
    int id;
    std::string date;
    std::string type;
    std::string name;
    double amount;
public:
    Entry(const std::string& type, const std::string& date, const std::string& name, double amount);
    virtual ~Entry() = default;

    int getId() const;
    std::string getType() const;
    std::string getDate() const;
    std::string getName() const;
    double getAmount() const;
    std::string toString() const;

    void setId(int id);
    void setType(const std::string& type);
    void setDate(const std::string& date);
    void setName(const std::string& name);
    void setAmount(double amount);
};
