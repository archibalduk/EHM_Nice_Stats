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
/*! 
 *  \brief The ClubContainer class is a container for club stats and provides 
 *  overall file i/o functions for importing/exporting all club data.
*/
class ClubContainer : public ContainerBaseClass
{
public:
    ClubContainer();
    virtual ~ClubContainer();

    // File i/o
    /*!
     * \brief Writes the club stats to the spreadsheet
     * \param xlsx Ouput xlsx file
     */
    void writeToSpreadsheet(QXlsx::Document &xlsx);

    // Get data
    /*!
     * \brief Returns a copy of the vector sorted alphabetically by name
     * \return alphabetical club list
     */
    std::vector<std::shared_ptr<Club>> alphabeticalList() const;
    size_t count() const override { return data_.size(); }
    /*!
     * \brief Returns a weak pointer to the selected club
     * \param id Club id
     * \return weak_ptr to the selected club
     */
    std::weak_ptr<Club> get(const qint32 id) const;
    /*!
     * \brief Returns a hash table of club names and positions within a vector
     * \return hash table of club names and positions within a vector
     */
    QHash<QString, qint32> hash() const;
    /*!
     * \brief Returns the league name and in-game date
     * \return the league name and in-game date
     */
    inline QString leagueDetails() const { return league_name_and_date_; }
    /*!
     * \brief Returns the in-game season
     * \return the in-game season
     */
    inline QString season() const { return season_; }

    // Graphs/charts
    /*!
     * \brief Adds a scatter chart showing club quality
     * \param xlsx Ouput xlsx file
     */
    void addQualityScatterChart(QXlsx::Document &xlsx);

    // Parse data
    /*!
     * \brief Opens and parses a club stats file
     * \param file_path Input file path
     * \return whether successful
     */
    bool parseFile(const QString &file_path);

private:
    // Data
    /*!
     * \brief data_ Club data
     */
    std::vector<std::shared_ptr<Club>> data_;
    QString league_name_and_date_{QStringLiteral("[NO DATA]")};
    QString season_{QStringLiteral("[NO DATA]")};

    // Column data
    qint32 columnEndPos() const override;
    /*!
     * \brief Initialises the column data
     */
    void initColumnData();

    // Parse data
    qint64 findPositionInFile(QTextStream &in) override;
    /*!
     * \brief Parses the league name, season and in-game date
     * \param in Input QTextStream
     */
    void parseLeagueDetails(QTextStream &in);
    /*!
     * \brief Parses the league standings
     * \param in Input QTextStream
     */
    void parseLeagueStandings(QTextStream &in);
};
} // namespace stats
#endif // CLUB_CONTAINER_H
