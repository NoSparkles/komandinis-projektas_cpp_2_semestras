#pragma once

#include "../model/Entry.h"
#include <vector>
#include <memory>

class Filter {
public:
    virtual ~Filter() = default;
    virtual std::vector<Entry*> apply(const std::vector<Entry*>& entries) const = 0;
};