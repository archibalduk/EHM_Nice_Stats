#ifndef COLUMNDATA_H
#define COLUMNDATA_H

// Qt headers
#include <QString>

namespace stats {
/*!
 * \brief The ColumnData class stores properties of a statistics column
 */
class ColumnData
{
public:
    ColumnData();
    /*!
     * \brief Constructor
     * \param column_id Unique id to be assigned to this column
     * \param column_name Column name
     * \param column_description Column description
     * \param maintain_a_totals_count Whether club totals should be calculated for this column
     */
    ColumnData(const qint16 column_id,
               const QString &column_name,
               const QString &column_description = QStringLiteral(""),
               const bool maintain_a_totals_count = true);

    // Get data
    /*!
     * \brief Returns the column description (if any)
     * \return description
     */
    inline QString description() const { return description_; }
    /*!
     * \brief Returns the column name
     * \return name
     */
    inline QString name() const { return name_; }
    /*!
     * \brief Returns the column id
     * \return id
     */
    inline qint16 id() const { return id_; }
    /*!
     * \brief Returns whether the stats within the column are countable when calculating club totals
     * \details Certain columns shouldn't be countable in order to avoid irrelevant or circular numbers. 
     * E.g. Total club ATOI is irrelevant and therefore shouldn't be counted.
     * \return whether the column is countable
     */
    inline bool isCountable() const { return maintain_a_totals_count_; }

private:
    qint16 id_{-1};
    QString name_{QStringLiteral("[No name]")};
    QString description_{QStringLiteral("[No description]")};
    bool maintain_a_totals_count_{true}; // False = stats not counted for skater/club totals
};
} // namespace stats

#endif // COLUMNDATA_H
