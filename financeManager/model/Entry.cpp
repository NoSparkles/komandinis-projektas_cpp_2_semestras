#include "Entry.h"

// Constructors
Entry::Entry(int id, const std::string& type, const std::string& date, const std::string& name, double amount){
    this->setId(id);
    this->setType(type);
    this->setDate(date);
    this->setName(name);
    this->setAmount(amount);
}

// Getters
int Entry::getId() const {
    return id;
}

std::string Entry::getType() const {
    return type;
}

std::string Entry::getDate() const {
    return date;
}

std::string Entry::getName() const {
    return name;
}

double Entry::getAmount() const {
    return amount;
}

std::string Entry::toString() const {
    return "ID: " + std::to_string(id) + ", Type: " + type + ", Date: " + date + ", Name: " + name + ", Amount: " + std::to_string(amount);
}

// Setters
void Entry::setId(int id) {
    this->id = id;
}

void Entry::setType(const std::string& type) {
    this->type = type;
}

void Entry::setDate(const std::string& date) {
    this->date = date;
}

void Entry::setName(const std::string& name) {
    this->name = name;
}

void Entry::setAmount(double amount) {
    this->amount = amount;
}