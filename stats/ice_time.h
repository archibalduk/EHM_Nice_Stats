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
    IceTime();

    //! Get data */
    /*! Get mm:ss as decimal */
    double toDecimal() const;
    /*! Get mm:ss as time */
    QTime toTime() const;

    //! Parse data */
    /*! Parse from a QString containing mm:ss */
    void parse(const QString &mm_ss_string);

private:
    // Data
    quint16 minutes_{0};
    quint16 seconds_{0};

    enum ENUM_SUB_STRING_POSITIONS { MINUTES, SECONDS, SUB_STRING_COUNT };

    static constexpr quint16 seconds_in_one_minute_{60};
};

#endif // ICETIME_H
