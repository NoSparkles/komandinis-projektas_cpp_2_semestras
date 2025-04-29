#pragma once

#include "Filter.h"

class BaseFilter : public Filter {
public:
    std::vector<Entry*> apply(const std::vector<Entry*>& entries) const override;
};