#include "club.h"

// Xlsx headers
#include "xlsxdocument.h"

using namespace stats;

/* ==================== */
/*      Club Stats      */
/* ==================== */

Club::Club()
{
    
}

/* ================== */
/*      File i/o      */
/* ================== */

void Club::write(QXlsx::Document &xlsx, const qint32 row) const
{
    xlsx.write(row, OUT_NAME, name_);
    xlsx.write(row, OUT_GP, games_played_);
    xlsx.write(row, OUT_W, won_);
    xlsx.write(row, OUT_L, lost_);
    xlsx.write(row, OUT_T, tied_);
    xlsx.write(row, OUT_PCT, win_pct_);
    xlsx.write(row, OUT_GF, goals_for_);
    xlsx.write(row, OUT_GA, goals_against_);
    xlsx.write(row, OUT_PTS, points_);
}

/* ================== */
/*      Get Data      */
/* ================== */

QString Club::columnName(const qint32 xlsx_column)
{
    switch (xlsx_column) {
    case OUT_NAME:
        return QStringLiteral("Name");
    case OUT_GP:
        return QStringLiteral("GP");
    case OUT_W:
        return QStringLiteral("W");
    case OUT_L:
        return QStringLiteral("L");
    case OUT_T:
        return QStringLiteral("T");
    case OUT_PCT:
        return QStringLiteral("PCT");
    case OUT_GF:
        return QStringLiteral("GF");
    case OUT_GA:
        return QStringLiteral("GA");
    case OUT_PTS:
        return QStringLiteral("Pts");

    default:
        return QStringLiteral("*NO NAME*");
    }
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

    if (stats_list.size() != INPUT_COLUMNS_COUNT) {
        qWarning().noquote()
            << QStringLiteral(
                   "Unexpected number of club stats columns found (%L1 found | %L2 expected)")
                   .arg(stats_list.size())
                   .arg(INPUT_COLUMNS_COUNT);
        return false;
    }

    games_played_ = stats_list[IN_GP].toUShort();
    won_ = stats_list[IN_W].toUShort();
    lost_ = stats_list[IN_L].toUShort();
    tied_ = stats_list[IN_T].toUShort();
    win_pct_ = stats_list[IN_PCT].toDouble();
    goals_for_ = stats_list[IN_GF].toUShort();
    goals_against_ = stats_list[IN_GA].toUShort();
    points_ = stats_list[IN_PTS].toUShort();

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
