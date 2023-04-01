#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H

// Qt headers
#include <QString>
#include <memory>

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
    StatsManager(const QString &club_stats_input_path,
                 const QString &player_stats_input_path,
                 const QString &output_file_path);
    ~StatsManager();

    /*!
     * \brief Generate the statistics
     * \return whether operation was successful
     */
    bool generate();

private:
    // Club and player data
    std::unique_ptr<ClubContainer> clubs_;
    std::unique_ptr<SkaterContainer> skaters_;

    // File paths
    QString club_stats_input_path_;
    QString player_stats_input_path_;
    QString output_file_path_;

    /*!
     * \brief Parse the stats input files
     * \return whether operation was successful
     */
    bool parse();
    /*!
     * \brief Save the nice stats to the output spreadsheet
     * \return whether operation was successful
     */
    bool saveSpreadsheet();
};
} // namespace stats

#endif // STATS_MANAGER_H
