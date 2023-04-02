#ifndef SKATER_TOTALS_H
#define SKATER_TOTALS_H

// Application headers
#include "../ice_time.h"
#include "../skater.h"

namespace stats {
/*! The SkaterTotals class tracks total and average stats for a club */
class SkaterTotals : public Skater
{
public:
    SkaterTotals();

    //! Add stats */
    /*! Add skater stats to the totals and averages */
    void add(const Skater *player);
    using Skater::add;

    //! Get stats */
    double average(const qint32 column) const;
    double averagePerMinute(const qint32 column) const;
    inline qint32 count() const { return skater_count_; }
    QVariant total(const qint32 column) const;
    IceTime ttoi() const override { return ttoi_; }

private:
    qint32 skater_count_{0};
    IceTime ttoi_;
};
} // namespace stats

#endif // SKATER_TOTALS_H
