#ifndef PLAYER_STATS_BASE_CLASS_H
#define PLAYER_STATS_BASE_CLASS_H

/*! The SkaterStats class is the base class for goalie and skater statistics */
namespace stats {
class PlayerStatsBaseClass
{
public:
    PlayerStatsBaseClass() {}
    enum ENUM_BASE_CLASS_STATS_INPUT_COLUMNS {
        IN_NAME,
        IN_CLUB,
        IN_POS,
        IN_GP,
        FIRST_BASE_CLASS_INPUT_COLUMN
    };
};
} // namespace stats
#endif // PLAYER_STATS_BASE_CLASS_H
