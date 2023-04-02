#ifndef CLUB_H
#define CLUB_H

// Application headers
#include "base_class/schema_base_class.h"
#include "totals/skater_totals.h"

// Qt headers
#include <memory>
class QVariant;

namespace stats {
class Skater;

/*! The Club class contains statistics for a club */
class Club : public SchemaBaseClass
{
public:
    /*! Constructor */
    Club();

    //! Add stats */
    /*! Add skater stats to the club totals and averages */
    void add(const Skater *player);

    //! Get data
    /*! Get column end position */
    inline qint32 columnEndPos() const override { return DATA_COLUMNS_END_POS; }

    //! Get stats */
    QVariant get(const qint32 column) const override;
    inline qint16 goalDifference() const { return goals_for_ - goals_against_; }
    qint16 overtimeAndShootoutLosses() const;

    //! Parse data */
    /*! Parse club stats from a line of a text file */
    bool parse(QString &line);

    //! Sort data */
    /*! Sort two Club items */
    static bool sortByName(const std::shared_ptr<Club> &lhs, const std::shared_ptr<Club> &rhs);
    static bool sortByPerformance(const std::shared_ptr<Club> &lhs,
                                  const std::shared_ptr<Club> &rhs);

    enum ENUM_STATS_COLUMNS {
        // Club stats
        NAME = first_column_id_,
        GP,
        W,
        L,
        T,
        O_SL,
        PCT,
        GF,
        GA,
        PTS,
        // Defencemen
        DEF_TTOI,
        DEF_AVERAGE_GOALS_PER_MINUTE,
        DEF_AVERAGE_ASSISTS_PER_MINUTE,
        DEF_AVERAGE_PIM_PER_MINUTE,
        DEF_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE,
        DEF_AVERAGE_SHOTS_BLOCKED_PER_MINUTE,
        // Forwards
        FWD_TTOI,
        FWD_AVERAGE_GOALS_PER_MINUTE,
        FWD_AVERAGE_ASSISTS_PER_MINUTE,
        FWD_AVERAGE_PIM_PER_MINUTE,
        FWD_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE,
        FWD_AVERAGE_SHOTS_BLOCKED_PER_MINUTE,
        // End position
        DATA_COLUMNS_END_POS
    };

private:
    // Data
    quint16 games_played_{0};
    quint16 won_{0};
    quint16 lost_{0};
    quint16 tied_{0};
    double win_pct_{0.0};
    quint16 goals_for_{0};
    quint16 goals_against_{0};
    quint16 points_{0};

    // Totals
    std::unique_ptr<SkaterTotals> defencemen_totals_;
    std::unique_ptr<SkaterTotals> forward_totals_;

    enum ENUM_TEXT_INPUT_LINE_FLAGS {
        CLUB_NAME_POSITION = 8,
        CLUB_NAME_SIZE = 25,
    };

    enum ENUM_STATS_INPUT_COLUMNS {
        IN_GP,
        IN_W,
        IN_L,
        IN_T,
        IN_PCT,
        IN_GF,
        IN_GA,
        IN_PTS,
        INPUT_COLUMNS_COUNT,
        INPUT_OT_SL_COLUMNS_COUNT,
        INPUT_OT_SL_MODIFIER = INPUT_OT_SL_COLUMNS_COUNT - INPUT_COLUMNS_COUNT,
    };
};
} // namespace stats

#endif //!CLUB_H
