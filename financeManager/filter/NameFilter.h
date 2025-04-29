#pragma once

#include "Filter.h"
#include <string>

class NameFilter : public Filter {
private:
    std::shared_ptr<Filter> innerFilter;
    std::string name;
public:
    NameFilter(std::shared_ptr<Filter> filter, const std::string& name);
    std::vector<Entry*> apply(const std::vector<Entry*>& entries) const override;
};