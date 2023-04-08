#ifndef CONTAINER_BASE_CLASS_H
#define CONTAINER_BASE_CLASS_H

// Application headers
#include "column_data.h"

// Qt headers
#include <QtGlobal>
class QString;
class QTextStream;

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {

/*!
 * \brief The ContainerBaseClass is a base class for stats containers
 */
class ContainerBaseClass
{
public:
    ContainerBaseClass();

protected:
    static constexpr qint64 no_result_{-1};

    // Column data
    /*!
     * \brief Add column data to the container
     * \param column Column data to be added
     */
    void addColumn(const ColumnData &column);
    /*!
     * \brief Returns the column data with the selected column id. 
     * A null point is returned if no match is found.
     * \param column_id Column id of the target column
     * \return 
     */
    const ColumnData *column(const qint32 column_id) const;

    // File i/o
    /*!
     * \brief Write header row to spreadsheet
     * \param xlsx Ouput xlsx file
     * \return next row id
     */
    qint32 writeHeaderRow(QXlsx::Document &xlsx);

    // Get data
    /*!
     * \brief Returns the number of items within the container
     * \return item count
     */
    virtual size_t count() const = 0;

private:
    // Column data
    /*!
     * \brief Column data
     */
    std::vector<ColumnData> columns_;

    // Get data: columns
    /*!
     * \brief Returns the end position for iterating column numbers
     * \return column end position
     */
    virtual qint32 columnEndPos() const = 0;
    /*!
     * \brief Returns the start position for iterating column numbers
     * \return column start position
     */
    qint32 columnStartPos() const { return 1; } // Xlsx uses 1 as the first column index

    // Get data
    /*!
     * \brief Find the file position of the next section of a file containing the relevant stats
     * \param in Input QTextStream
     * \return file position
     */
    virtual qint64 findPositionInFile(QTextStream &in) = 0;
};
} // namespace stats

#endif // CONTAINER_BASE_CLASS_H
