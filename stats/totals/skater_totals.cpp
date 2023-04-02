#include "skater_totals.h"

// Qt headers
#include <QVariant>

using namespace stats;

/* ======================= */
/*      Skater Totals      */
/* ======================= */

SkaterTotals::SkaterTotals()
{
    
}

/* =================== */
/*      Add stats      */
/* =================== */

void SkaterTotals::add(const Skater *player)
{
    for (auto i = 1; i < DATA_COLUMNS_END_POS; ++i)
        add(i, player->get(i));

    ttoi_.add(player->get(Skater::TTOI));

    ++skater_count_;
}

/* =================== */
/*      Get stats      */
/* =================== */

double SkaterTotals::average(const qint32 column) const
{
    return get(column).toDouble() / skater_count_;
}

double SkaterTotals::averagePerMinute(const qint32 column) const
{
    const auto value{get(column).toDouble()};

    if (value == 0.0)
        return value;

    return value / ttoi().toDecimal();
}

QVariant SkaterTotals::total(const qint32 column) const
{
    return get(column);
}
