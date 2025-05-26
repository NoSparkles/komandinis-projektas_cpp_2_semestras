#include "TypeFilter.h"
#include <algorithm>

static bool icompare(std::string a, std::string b) {
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a == b;
}

TypeFilter::TypeFilter(std::shared_ptr<Filter> filter, const std::string& type)
    : innerFilter(std::move(filter)), type(type) {}

std::vector<Entry*> TypeFilter::apply(const std::vector<Entry*>& entries) const {
    const std::vector<Entry*>& base = innerFilter ? innerFilter->apply(entries) : entries;

    std::vector<Entry*> out;
    out.reserve(base.size());
    for (Entry* e : base) {
        if (icompare(e->getType(), type))
            out.push_back(e);
    }
    return out;
}