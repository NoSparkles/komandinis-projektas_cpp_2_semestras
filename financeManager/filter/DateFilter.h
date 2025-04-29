#pragma once

#include "Filter.h"
#include <string>

class DateFilter : public Filter {
private:
    std::shared_ptr<Filter> innerFilter;
    std::string fromDate;
    std::string toDate;
public:
    DateFilter(std::shared_ptr<Filter> filter, const std::string& from, const std::string& to);
    std::vector<Entry*> apply(const std::vector<Entry*>& entries) const override;
};