#include "NameFilter.h"
#include <algorithm>

static bool icompare(std::string a, std::string b) {
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a == b;
}

NameFilter::NameFilter(std::shared_ptr<Filter> filter, const std::string& name)
    : innerFilter(std::move(filter)), name(name) {}

std::vector<Entry*> NameFilter::apply(const std::vector<Entry*>& entries) const {
    const std::vector<Entry*>& base = innerFilter ? innerFilter->apply(entries) : entries;

    std::vector<Entry*> out;
    out.reserve(base.size());
    for (Entry* e : base) {
        if (icompare(e->getName(), name))
            out.push_back(e);
    }
    return out;
}