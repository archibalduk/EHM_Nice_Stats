#ifndef CLUB_CONTAINER_H
#define CLUB_CONTAINER_H

// Application headers
#include "../club.h"
#include "container_base_class.h"

// Qt headers
#include <memory>
class QTextStream;

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {
/*! The ClubContainer class is a container for club stats */
class ClubContainer : public ContainerBaseClass
{
public:
    ClubContainer();
    virtual ~ClubContainer();

    //! File i/o */
    /*! Write the club stats to the spreadsheet */
    void writeToSpreadsheet(QXlsx::Document &xlsx);

    //! Get data
    /*! Get a copy of the vector sorted alphabetically by name */
    std::vector<std::shared_ptr<Club>> alphabeticalList() const;
    /*! Get a weak pointer to the selected club */
    std::weak_ptr<Club> get(const qint32 id) const;
    /*! Get a hash table of club names and positions within a vector */
    QHash<QString, qint32> hash() const;

    //! Parse data */
    /*! Open and parse a club stats file */
    bool parseFile(const QString &file_path);

private:
    // Data
    std::vector<std::shared_ptr<Club>> data_;

    //! Get data: columns */
    /*! Get column end position */
    qint32 columnEndPos() const override;
    /*! Get column heading description */
    QString columnDescription(const qint32 column) const override;
    /*! Get column heading name */
    QString columnName(const qint32 column) const override;

    //! Parse data */
    /*! Find the file position of the next league standings section of a file */
    qint64 findPositionInFile(QTextStream &in) override;
    /*! Parse the league standings */
    void parseLeagueStandings(QTextStream &in);
};
} // namespace stats
#endif // CLUB_CONTAINER_H
