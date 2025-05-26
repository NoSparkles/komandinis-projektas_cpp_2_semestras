#include "DateFilter.h"

DateFilter::DateFilter(std::shared_ptr<Filter> filter,
                       const std::string& from, const std::string& to)
    : innerFilter(std::move(filter)),
      fromDate(from), toDate(to) {}

std::vector<Entry*> DateFilter::apply(const std::vector<Entry*>& entries) const {
    const std::vector<Entry*>& base = innerFilter ? innerFilter->apply(entries) : entries;

    std::vector<Entry*> out;
    out.reserve(base.size());
    for (Entry* e : base) {
        const std::string& d = e->getDate();
        if ( (fromDate.empty() || d >= fromDate) &&
             (toDate.empty()   || d <= toDate) )
            out.push_back(e);
    }
    return out;
}