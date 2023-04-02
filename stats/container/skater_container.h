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

/*! The SkaterContainer class is a container for skater stats */
class SkaterContainer : public ContainerBaseClass
{
public:
    SkaterContainer();
    virtual ~SkaterContainer();

    //! File i/o */
    /*! Write the player stats to the spreadsheet */
    void writeToSpreadsheet(QXlsx::Document &xlsx, const std::shared_ptr<Club> &club);

    //! Parse data */
    /*! Open and parse a player stats file */
    bool parseFile(const QString &file_path, const ClubContainer *clubs);

private:
    // Data
    std::vector<Skater> data_;

    //! Get data: columns */
    /*! Get column end position */
    qint32 columnEndPos() const override;
    /*! Get column heading description */
    QString columnDescription(const qint32 column) const override;
    /*! Get column heading name */
    QString columnName(const qint32 column) const override;

    //! Parse data */
    /*! Find the file position of the player stats section of a file */
    qint64 findPositionInFile(QTextStream &in) override;
};
} // namespace stats
#endif // SKATER_CONTAINER_H
