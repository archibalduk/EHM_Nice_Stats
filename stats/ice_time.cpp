#include "ice_time.h"

// Qt headers
#include <QList>
#include <QString>
#include <QTime>

/* ================== */
/*      Ice Time      */
/* ================== */

IceTime::IceTime()
{
    
}

/* ================== */
/*      Get Data      */
/* ================== */

double IceTime::toDecimal() const
{
    return static_cast<double>(minutes_)
           + (static_cast<double>(seconds_) / static_cast<double>(seconds_in_one_minute_));
}

QTime IceTime::toTime() const
{
    return QTime(0, minutes_, seconds_);
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

void IceTime::parse(const QString &mm_ss_string)
{
    const auto time{mm_ss_string.split(":", Qt::KeepEmptyParts, Qt::CaseInsensitive)};

    if (time.size() < SUB_STRING_COUNT)
        return;

    minutes_ = time[MINUTES].toUShort();
    seconds_ = time[SECONDS].toUShort();
}
