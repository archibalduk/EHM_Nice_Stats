#include "stats_manager.h"

// Application headers
#include "club.h"
#include "container/skater_container.h"

// Xlsx headers
#include "xlsxdocument.h"

// Qt headers
#include <vector>

using namespace stats;

struct StatsManager::Data
{
    std::vector<std::shared_ptr<Club>> clubs_;
};

StatsManager::StatsManager(const QString &club_stats_input_path,
                           const QString &player_stats_input_path,
                           const QString &output_file_path)
    : data_(std::make_unique<Data>())
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

bool StatsManager::parse()
{
    if (!Club::parseFile(club_stats_input_path_, data_->clubs_))
        return false;

    if (!skaters_->parseFile(player_stats_input_path_, data_->clubs_))
        return false;

    return true;
}

bool StatsManager::saveSpreadsheet()
{
    QXlsx::Document xlsx;

    Club::writeToSpreadsheet(xlsx, data_->clubs_);

    // Get a list of the clubs sorted by name so that the player stats worksheets are sorted alphabetically.
    // Add a nullptr to the list for unassigned players
    auto sorted_club_list{Club::alphabeticalCopy(data_->clubs_)};
    sorted_club_list.push_back(nullptr);

    for (const auto &itr : sorted_club_list)
        skaters_->writeToSpreadsheet(xlsx, itr);

    return xlsx.saveAs(output_file_path_);
}
