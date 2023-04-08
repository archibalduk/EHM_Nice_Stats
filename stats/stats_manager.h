#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H

// Qt headers
#include <QString>
#include <memory>

// Xlsx headers
namespace QXlsx {
class Document;
}

namespace stats {

class ClubContainer;
class SkaterContainer;

/*!
 * \brief The StatsManager class is the statistics manager/database. 
 * It manages file i/o and stats generation.
 */
class StatsManager
{
public:
    /*!
     * \brief Constructor
     * \param club_stats_input_path File path to club stats input file
     * \param player_stats_input_path File path to player stats input file
     * \param output_file_path File path to output nice stats xlsx file
     */
    StatsManager(const QString &club_stats_input_path,
                 const QString &player_stats_input_path,
                 const QString &output_file_path);
    ~StatsManager();

    /*!
     * \brief Generates the statistics
     * \return whether operation was successful
     */
    bool generate();

    // Get data
    /*!
     * \brief Returns the number of clubs
     * \return the number of clubs
     */
    size_t clubCount() const;
    /*!
     * \brief Returns the number of skaters
     * \return the number of skaters
     */
    size_t skaterCount() const;

private:
    // Club and player data
    std::unique_ptr<ClubContainer> clubs_;
    std::unique_ptr<SkaterContainer> skaters_;

    // File paths
    QString club_stats_input_path_;
    QString player_stats_input_path_;
    QString output_file_path_;

    /*!
     * \brief Parses the stats input files
     * \return whether operation was successful
     */
    bool parse();
    /*!
     * \brief Saves the nice stats to the output xlsx spreadsheet
     * \return whether operation was successful
     */
    bool saveSpreadsheet();
    /*!
     * \brief Writes the cover sheet to the spreadsheet
     * \param xlsx Ouput xlsx file
     */
    void writeCoverSheet(QXlsx::Document &xlsx);
};
} // namespace stats

#endif // STATS_MANAGER_H
