#ifndef MANAGER_H
#define MANAGER_H

// Qt headers
#include <QString>
#include <memory>

namespace stats {

/*!
 * \brief The Manager class is the statistics manager/database. 
 * It manages file i/o and stats generation.
 */
class Manager
{
public:
    Manager(const QString &club_stats_input_path,
            const QString &player_stats_input_path,
            const QString &output_file_path);
    ~Manager();

    /*!
     * \brief Generate the statistics
     * \return whether operation was successful
     */
    bool generate();

private:
    // Club and player data
    struct Data;
    std::unique_ptr<Data> data_;

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

#endif // MANAGER_H
