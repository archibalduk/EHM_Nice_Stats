#ifndef SKATER_CONTAINER_H
#define SKATER_CONTAINER_H

// Application headers
#include "../skater.h"
#include "container_base_class.h"

// Qt headers
class QTextStream;

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {
class ClubContainer;
/*! 
 *  \brief The SkaterContainer class is a container for skater stats and provides 
 *  overall file i/o functions for importing/exporting all skater data.
*/
class SkaterContainer : public ContainerBaseClass
{
public:
    SkaterContainer();
    virtual ~SkaterContainer();

    // File i/o
    /*!
     * \brief Writes the skater stats for the selected club roster to the spreadsheet
     * \param xlsx Ouput xlsx file
     * \param club Club whose skaters are to be output
     */
    void writeToSpreadsheet(QXlsx::Document &xlsx, const std::shared_ptr<Club> &club);

    // Get data
    size_t count() const override { return data_.size(); }

    // Parse data
    /*!
     * \brief Opens and parses a skater stats file
     * \param file_path Input file path
     * \param clubs Club data for linking against skater club details
     * \return whether successful
     */
    bool parseFile(const QString &file_path, const ClubContainer *clubs);

private:
    // Data
    /*!
     * \brief data_ Skater data
     */
    std::vector<Skater> data_;

    // Column data
    qint32 columnEndPos() const override;
    /*!
     * \brief Initialises the column data
     */
    void initColumnData();

    // Parse data
    qint64 findPositionInFile(QTextStream &in) override;
};
} // namespace stats
#endif // SKATER_CONTAINER_H
