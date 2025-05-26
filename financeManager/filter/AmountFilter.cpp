#include "AmountFilter.h"

AmountFilter::AmountFilter(std::shared_ptr<Filter> filter,
                           double minAmount, double maxAmount)
    : innerFilter(std::move(filter)),
      minAmount(minAmount), maxAmount(maxAmount) {}

std::vector<Entry*> AmountFilter::apply(const std::vector<Entry*>& entries) const {
    const std::vector<Entry*>& base = innerFilter ? innerFilter->apply(entries) : entries;

    std::vector<Entry*> out;
    out.reserve(base.size());
    for (Entry* e : base) {
        double a = e->getAmount();
        if (a >= minAmount && a <= maxAmount)
            out.push_back(e);
    }
    return out;
}