#pragma once

#include "Filter.h"

class AmountFilter : public Filter {
private:
    std::shared_ptr<Filter> innerFilter;
    double minAmount;
    double maxAmount;
public:
    AmountFilter(std::shared_ptr<Filter> filter, double minAmount, double maxAmount);
    std::vector<Entry*> apply(const std::vector<Entry*>& entries) const override;
};