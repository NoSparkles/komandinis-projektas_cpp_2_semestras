#pragma once

#include "Filter.h"
#include <string>

class TypeFilter : public Filter {
private:
    std::shared_ptr<Filter> innerFilter;
    std::string type;
public:
    TypeFilter(std::shared_ptr<Filter> filter, const std::string& type);
    std::vector<Entry*> apply(const std::vector<Entry*>& entries) const override;
};