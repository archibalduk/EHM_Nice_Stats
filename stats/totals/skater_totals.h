#ifndef SKATER_TOTALS_H
#define SKATER_TOTALS_H

// Application headers
#include "../ice_time.h"
#include "../skater.h"

namespace stats {
/*!
 * \brief The SkaterTotals class tracks total and average stats for a club
 */
class SkaterTotals : public Skater
{
public:
    SkaterTotals();

    // Add stats
    /*!
     * \brief Add a player's statistics to the club's totals and averages
     * \param player Player to be added
     */
    void add(const Skater *player);
    using Skater::add;

    // Get stats
    /*!
     * \brief Returns the average for the chosen statistic
     * \param column Column id
     * \return average
     */
    double average(const qint32 column) const;
    /*!
     * \brief Returns the average per minute for the chosen statistic (based on total time on ice)
     * \param column Column id
     * \return average per minute
     */
    double averagePerMinute(const qint32 column) const;
    /*!
     * \brief Returns the number of skaters whose statistics are included in the totals
     * \return 
     */
    inline qint32 count() const { return skater_count_; }
    /*!
     * \brief Returns the total figure for the chosen statistic
     * \param column Column id
     * \return total
     */
    QVariant total(const qint32 column) const;
    /*!
     * \brief Returns the total time on ice played by all skaters
     * \return total time on ice
     */
    IceTime ttoi() const override { return ttoi_; }

private:
    qint32 skater_count_{0};
    IceTime ttoi_;
};
} // namespace stats

#endif // SKATER_TOTALS_H
