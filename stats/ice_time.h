#ifndef ICETIME_H
#define ICETIME_H

// Qt headers
#include <QtGlobal>
class QTime;

/*! The IceTime class stores and parses ice time in minutes and seconds */
class IceTime
{
public:
    /*! Constructor */
    IceTime(const double mm_ss = 0.0);
    IceTime(const quint16 minutes, const quint16 seconds);

    //! Get data */
    /*! Get data based on decimal/time setting */
    QVariant get() const;
    quint16 minutes() const;
    quint16 seconds() const;
    /*! Get mm:ss as decimal */
    double toDecimal() const;
    /*! Get mm:ss as time */
    QTime toTime() const;

    //! Operations */
    /*! Add time */
    void add(const double time_to_add);
    void add(const qint32 mins_to_add, const qint32 secs_to_add);
    void add(const IceTime &time_to_add);
    void add(const QTime &time_to_add);
    void add(const QVariant &time_to_add);
    /*! Return a copy of the ice time multiplied by the chosen amount */
    IceTime multiplied(const qint32 multiple) const;

    //! Parse data */
    /*! Parse from a QString containing mm:ss */
    void parse(const QString &mm_ss_string);

private:
    // Data
    double mm_ss_{0.0};

    enum ENUM_SUB_STRING_POSITIONS { MINUTES, SECONDS, SUB_STRING_COUNT };

    static constexpr quint16 seconds_in_one_minute_{60};
};

#endif // ICETIME_H
