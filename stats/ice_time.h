#ifndef ICETIME_H
#define ICETIME_H

// Qt headers
#include <QtGlobal>
class QTime;

namespace stats {
/*!
 * \brief The IceTime class stores and parses ice time in minutes and seconds
 */
class IceTime
{
public:
    /*!
     * \brief Constructor
     * \param mm_ss minutes and seconds as a decimal (e.g. 2.5 = 2 minutes 30 seconds)
     */
    IceTime(const double mm_ss = 0.0);
    /*!
     * \brief Contstructor
     * \param minutes Minutes
     * \param seconds Seconds
     */
    IceTime(const quint16 minutes, const quint16 seconds);

    // Get data
    /*!
     * \brief Returns the ice time in a format determined by the `time_format` Settings
     * \return ice time
     */
    QVariant get() const;
    /*!
     * \brief Returns the number of minutes
     * \return minutes
     */
    quint16 minutes() const;
    /*!
     * \brief Returns the number of seconds
     * \return seconds
     */
    quint16 seconds() const;
    /*! Get mm:ss as decimal */
    /*!
     * \brief Returns ice time in decimal format (e.g. 2.5 = 2 minutes 30 seconds)
     * \return ice time in decimal format
     */
    double toDecimal() const;
    /*!
     * \brief Returns ice time in time format (e.g. 2:30 = 2 minutes 30 seconds)
     * \details Note that this function has a limit of 23 hours, 59 minutes and 59 seconds
     * \return ice time in mm:ss format
     */
    QTime toTime() const;

    // Operations
    /*!
     * \brief Adds time to the existing ice time
     * \param time_to_add Time in decimal format (e.g. 2.5 = 2 minutes 30 seconds)
     */
    void add(const double time_to_add);
    /*!
     * \brief Adds time to the existing ice time
     * \param mins_to_add Minutes
     * \param secs_to_add Seconds
     */
    void add(const qint32 mins_to_add, const qint32 secs_to_add);
    /*!
     * \brief Adds time to the existing ice time
     * \param time_to_add IceTime to add
     */
    void add(const IceTime &time_to_add);
    /*!
     * \brief Adds time to the existing ice time
     * \param time_to_add QTime to add
     */
    void add(const QTime &time_to_add);
    /*!
     * \brief Adds time to the existing ice time
     * \param time_to_add QVariant to add (this could be wrapping a QTime or double)
     */
    void add(const QVariant &time_to_add);
    /*!
     * \brief Returns a copy of the ice time multiplied by the chosen amount
     * \param multiple Amount by which to multiply the ice time
     * \return 
     */
    IceTime multiplied(const qint32 multiple) const;

    // Parse data
    /*!
     * \brief Parses a QString containing mm:ss time format
     * \param mm_ss_string QString to parse
     */
    void parse(const QString &mm_ss_string);

    // Settings
    /*!
     * \brief Set the time format for when exporting (either hh:mm:ss or decimal)
     * \param format Settings::ENUM_SETTINGS_IDS
     */
    static void setTimeFormat(const qint8 format);

private:
    // Data
    double mm_ss_{0.0};

    enum ENUM_SUB_STRING_POSITIONS { MINUTES, SECONDS, SUB_STRING_COUNT };

    static constexpr quint16 seconds_in_one_minute_{60};

    // Time format setting
    static qint8 time_format_setting_;
};
} // namespace stats

#endif // ICETIME_H
