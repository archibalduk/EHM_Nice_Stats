#include "stats_manager.h"

// Application headers
#include "container/club_container.h"
#include "container/skater_container.h"

// Xlsx headers
#include "xlsxdocument.h"

using namespace stats;

StatsManager::StatsManager(const QString &club_stats_input_path,
                           const QString &player_stats_input_path,
                           const QString &output_file_path)
    : clubs_(std::make_unique<ClubContainer>())
    , skaters_(std::make_unique<SkaterContainer>())
    , club_stats_input_path_(club_stats_input_path)
    , player_stats_input_path_(player_stats_input_path)
    , output_file_path_(output_file_path)
{
    
}

StatsManager::~StatsManager() {}

bool StatsManager::generate()
{
    if (!parse())
        return false;

    if (!saveSpreadsheet())
        return false;

    return true;
}

size_t StatsManager::clubCount() const
{
    return clubs_->count();
}

size_t StatsManager::skaterCount() const
{
    return skaters_->count();
}

bool StatsManager::parse()
{
    if (!clubs_->parseFile(club_stats_input_path_))
        return false;

    if (!skaters_->parseFile(player_stats_input_path_, clubs_.get()))
        return false;

    return true;
}

bool StatsManager::saveSpreadsheet()
{
    QXlsx::Document xlsx;

    writeCoverSheet(xlsx);

    clubs_->writeToSpreadsheet(xlsx);

    // Get a list of the clubs sorted by name so that the player stats worksheets are sorted alphabetically.
    // Add a nullptr to the list for unassigned players
    auto sorted_club_list{clubs_->alphabeticalList()};
    sorted_club_list.push_back(nullptr);

    for (const auto &itr : sorted_club_list)
        skaters_->writeToSpreadsheet(xlsx, itr);

    // Navigate back to the first worksheet ready for when the user next opens the file
    xlsx.selectSheet(0);

    return xlsx.saveAs(output_file_path_);
}

void StatsManager::writeCoverSheet(QXlsx::Document &xlsx)
{
    xlsx.addSheet(QStringLiteral("Overview"));

    // Auto-size column widths
    xlsx.autosizeColumnWidth();

    auto row{1};
    const auto left_column{1};
    const auto right_column{2};

    // League details
    xlsx.write(row, left_column, QStringLiteral("League / in-game date:"));
    xlsx.write(row++, right_column, clubs_->leagueDetails());

    // Season
    xlsx.write(row, left_column, QStringLiteral("Season:"));
    xlsx.write(row++, right_column, clubs_->season());

    // Club count
    xlsx.write(row, left_column, QStringLiteral("Clubs:"));
    xlsx.write(row++, right_column, clubs_->count());

    // Skater count
    xlsx.write(row, left_column, QStringLiteral("Skaters:"));
    xlsx.write(row++, right_column, skaters_->count());
}
