#include "ice_time.h"

// Qt headers
#include <QList>
#include <QString>
#include <QTime>

/* ================== */
/*      Ice Time      */
/* ================== */

IceTime::IceTime(const double mm_ss)
    : mm_ss_(mm_ss)
{}

IceTime::IceTime(const quint16 minutes, const quint16 seconds)
{
    add(minutes, seconds);
}

/* ================== */
/*      Get Data      */
/* ================== */

QVariant IceTime::get() const
{
    return toDecimal();
    //return toTime();
}

double IceTime::toDecimal() const
{
    return mm_ss_;
}

QTime IceTime::toTime() const
{
    double mins{0};
    double secs{modf(mm_ss_, &mins) * seconds_in_one_minute_};

    return QTime(0, std::floor(mins), std::round(secs));
}

/* ==================== */
/*      Operations      */
/* ==================== */

void IceTime::add(const double time_to_add)
{
    mm_ss_ += time_to_add;
}

void IceTime::add(const qint32 mins_to_add, const qint32 secs_to_add)
{
    add(static_cast<double>(mins_to_add)
        + (static_cast<double>(secs_to_add) / seconds_in_one_minute_));
}

void IceTime::add(const IceTime &time_to_add)
{
    add(time_to_add.toDecimal());
}

void IceTime::add(const QTime &time_to_add)
{
    add(time_to_add.minute(), time_to_add.second());
}

void IceTime::add(const QVariant &time_to_add)
{
    //const auto b{toDecimal()};

    if (time_to_add.userType() == QMetaType::QTime)
        add(time_to_add.toTime());
    else
        add(time_to_add.toDouble());

    //qInfo() << b << "+" << time_to_add << "=" << toDecimal() << "\n";
}

IceTime IceTime::multiplied(const qint32 multiple) const
{
    IceTime tmp(mm_ss_ * multiple);
    return tmp;
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

void IceTime::parse(const QString &mm_ss_string)
{
    const auto time{mm_ss_string.split(":", Qt::KeepEmptyParts, Qt::CaseInsensitive)};

    if (time.size() < SUB_STRING_COUNT)
        return;

    add(time[MINUTES].toUInt(), time[SECONDS].toUInt());
}
