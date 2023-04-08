#include "club.h"

// Application headers
#include "skater.h"

// Qt headers
#include <QVariant>

using namespace stats;

/* ==================== */
/*      Club Stats      */
/* ==================== */

Club::Club()
    : defencemen_totals_(std::make_unique<SkaterTotals>())
    , forward_totals_(std::make_unique<SkaterTotals>())
{
    
}

/* =================== */
/*      Add Stats      */
/* =================== */

void Club::add(const Skater *player)
{
    if (player->isDefenceman())
        defencemen_totals_->add(player);
    else
        forward_totals_->add(player);
}

/* =================== */
/*      Get Stats      */
/* =================== */

QVariant Club::get(const qint32 column) const
{
    switch (column) {
    // Club stats
    case NAME:
        return name();
    case GP:
        return games_played_;
    case W:
        return won_;
    case L:
        return lost_;
    case T:
        return tied_;
    case O_SL:
        return overtimeAndShootoutLosses();
    case PCT:
        return win_pct_;
    case GF:
        return goals_for_;
    case GA:
        return goals_against_;
    case PTS:
        return points_;
    // Defencemen
    case DEF_TTOI:
        return defencemen_totals_->ttoi().get();
    case DEF_AVERAGE_GOALS_PER_MINUTE:
        return defencemen_totals_->averagePerMinute(Skater::G);
    case DEF_AVERAGE_ASSISTS_PER_MINUTE:
        return defencemen_totals_->averagePerMinute(Skater::A);
    case DEF_AVERAGE_PIM_PER_MINUTE:
        return defencemen_totals_->averagePerMinute(Skater::PIM);
    case DEF_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE:
        return defencemen_totals_->averagePerMinute(Skater::SOG);
    case DEF_AVERAGE_SHOTS_BLOCKED_PER_MINUTE:
        return defencemen_totals_->averagePerMinute(Skater::SB);
    // Forwards
    case FWD_TTOI:
        return forward_totals_->ttoi().get();
    case FWD_AVERAGE_GOALS_PER_MINUTE:
        return forward_totals_->averagePerMinute(Skater::G);
    case FWD_AVERAGE_ASSISTS_PER_MINUTE:
        return forward_totals_->averagePerMinute(Skater::A);
    case FWD_AVERAGE_PIM_PER_MINUTE:
        return forward_totals_->averagePerMinute(Skater::PIM);
    case FWD_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE:
        return forward_totals_->averagePerMinute(Skater::SOG);
    case FWD_AVERAGE_SHOTS_BLOCKED_PER_MINUTE:
        return forward_totals_->averagePerMinute(Skater::SB);
    // Default
    default:
        return QVariant();
    };
}

qint16 Club::overtimeAndShootoutLosses() const
{
    return games_played_ - won_ - lost_ - tied_;
}

double Club::skaterAverage(const qint32 skater_column, const bool is_defenceman) const
{
    if (is_defenceman)
        return defencemen_totals_->average(skater_column);

    return forward_totals_->average(skater_column);
}

double Club::skaterAveragePerMinute(const qint32 skater_column, const bool is_defenceman) const
{
    if (is_defenceman)
        return defencemen_totals_->averagePerMinute(skater_column);

    return forward_totals_->averagePerMinute(skater_column);
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

bool Club::parse(QString &line)
{
    // Club Name
    line.remove(0, CLUB_NAME_POSITION);
    name_ = line.left(CLUB_NAME_SIZE).simplified();

    // Stats
    line.remove(0, CLUB_NAME_SIZE);
    const auto stats_list{line.split(" ", Qt::SkipEmptyParts, Qt::CaseInsensitive)};

    //qInfo() << stats_list;

    if (stats_list.size() != INPUT_COLUMNS_COUNT && stats_list.size() != INPUT_OT_SL_COLUMNS_COUNT) {
        qWarning().noquote() << QStringLiteral("Unexpected number of club stats columns found (%L1 "
                                               "found | %L2 or %L3 expected)")
                                    .arg(stats_list.size())
                                    .arg(INPUT_COLUMNS_COUNT)
                                    .arg(INPUT_OT_SL_COLUMNS_COUNT);
        return false;
    }

    games_played_ = stats_list[IN_GP].toUShort();
    won_ = stats_list[IN_W].toUShort();
    lost_ = stats_list[IN_L].toUShort();

    // Non-OT/SO Losses tables
    if (stats_list.size() == INPUT_COLUMNS_COUNT) {
        tied_ = stats_list[IN_T].toUShort();
        win_pct_ = stats_list[IN_PCT].toDouble();
        goals_for_ = stats_list[IN_GF].toUShort();
        goals_against_ = stats_list[IN_GA].toUShort();
        points_ = stats_list[IN_PTS].toUShort();
    }
    // OT/SO Losses tables
    else {
        win_pct_ = stats_list[IN_PCT + INPUT_OT_SL_MODIFIER].toDouble();
        goals_for_ = stats_list[IN_GF + INPUT_OT_SL_MODIFIER].toUShort();
        goals_against_ = stats_list[IN_GA + INPUT_OT_SL_MODIFIER].toUShort();
        points_ = stats_list[IN_PTS + INPUT_OT_SL_MODIFIER].toUShort();
    }

    return true;
}

/* =================== */
/*      Sort Data      */
/* =================== */

bool Club::sortByName(const std::shared_ptr<Club> &lhs, const std::shared_ptr<Club> &rhs)
{
    return lhs->name_ < rhs->name_;
}

bool Club::sortByPerformance(const std::shared_ptr<Club> &lhs, const std::shared_ptr<Club> &rhs)
{
    if (lhs->win_pct_ != rhs->win_pct_)
        return lhs->win_pct_ > rhs->win_pct_;

    if (lhs->goalDifference() != rhs->goalDifference())
        return lhs->goalDifference() > rhs->goalDifference();

    if (lhs->goals_for_ != rhs->goals_for_)
        return lhs->goals_for_ > rhs->goals_for_;

    return lhs->name_ < rhs->name_;
}
