#ifndef SCHEMA_BASE_CLASS_H
#define SCHEMA_BASE_CLASS_H

// Qt headers
#include <QString>

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {
/*!
 * \brief The SchemaBaseClass is a base class for Club and Skater classes
 */
class SchemaBaseClass
{
public:
    SchemaBaseClass();
    virtual ~SchemaBaseClass();

    // File i/o
    /*!
     * \brief Write the stats row to the spreadsheet
     * \param xlsx Ouput xlsx file
     * \param row Spreadsheet row to be written to
     */
    void write(QXlsx::Document &xlsx, const qint32 row) const;

    //! Get data
    /*!
     * \brief Returns the end position for iterating column numbers
     * \return column end position
     */
    virtual qint32 columnEndPos() const = 0;
    /*!
     * \brief Returns the name of the current item (e.g. club name or player name)
     * \return name
     */
    inline QString name() const { return name_; }

    // Get stats
    /*!
     * \brief Returns the item's statistics for the selected `column`
     * \param column Column id
     * \return statistics
     */
    virtual QVariant get(const qint32 column) const = 0;

protected:
    // Data
    /*!
     * \brief name_ Name of the current item (e.g. club name or player name)
     */
    QString name_;

    static constexpr qint32 first_column_id_{1}; // Xlsx indexes start at 1
    static constexpr qint64 no_result_{-1};
};
} // namespace stats

#endif // SCHEMA_BASE_CLASS_H
