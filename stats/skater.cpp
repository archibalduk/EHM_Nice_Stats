#include "skater.h"

// Application headers
#include "club.h"
#include "container/club_container.h"

// Qt headers
#include <QDebug>
#include <QFile>
#include <QVariant>

using namespace stats;

/* ====================== */
/*      Skater Stats      */
/* ====================== */

Skater::Skater()
{
    
}

/* =================== */
/*      Add stats      */
/* =================== */

void Skater::add(const qint32 column, const QVariant &value)
{
    switch (column) {
    case GP:
        gp_ += static_cast<quint16>(value.toInt());
        break;
    case G:
        g_ += static_cast<quint16>(value.toInt());
        break;
    case A:
        a_ += static_cast<quint16>(value.toInt());
        break;
    case PTS:
        pts_ += static_cast<quint16>(value.toInt());
        break;
    case PLUS_MINUS:
        plus_minus_ += static_cast<qint16>(value.toInt());
        break;
    case PIM:
        pim_ += static_cast<quint16>(value.toInt());
        break;
    case PPG:
        ppg_ += static_cast<quint16>(value.toInt());
        break;
    case PPA:
        ppa_ += static_cast<quint16>(value.toInt());
        break;
    case PPP:
        ppp_ += static_cast<quint16>(value.toInt());
        break;
    case SHG:
        shg_ += static_cast<quint16>(value.toInt());
        break;
    case SHA:
        sha_ += static_cast<quint16>(value.toInt());
        break;
    case SHP:
        shp_ += static_cast<quint16>(value.toInt());
        break;
    case GWG:
        gwg_ += static_cast<quint16>(value.toInt());
        break;
    case GT:
        gt_ += static_cast<quint16>(value.toInt());
        break;
    case FG:
        fg_ += static_cast<quint16>(value.toInt());
        break;
    case EN:
        en_ += static_cast<quint16>(value.toInt());
        break;
    case SOG:
        sog_ += static_cast<quint16>(value.toInt());
        break;
    case SH:
        sh_ += value.toDouble();
        break;
    case HT:
        ht_ += static_cast<quint16>(value.toInt());
        break;
    case GA:
        ga_ += static_cast<quint16>(value.toInt());
        break;
    case TA:
        ta_ += static_cast<quint16>(value.toInt());
        break;
    case FO:
        fo_ += value.toDouble();
        break;
    case SB:
        sb_ += static_cast<quint16>(value.toInt());
        break;
    case TWO_MIN_PEN:
        two_min_pen_ += static_cast<quint16>(value.toInt());
        break;
    case FIVE_MIN_PEN:
        five_min_pen_ += static_cast<quint16>(value.toInt());
        break;
    case MI:
        mi_ += static_cast<quint16>(value.toInt());
        break;
    case MA:
        ma_ += static_cast<quint16>(value.toInt());
        break;
    case GM:
        gm_ += static_cast<quint16>(value.toInt());
        break;
    case FI:
        fi_ += static_cast<quint16>(value.toInt());
        break;
    case FW:
        fw_ += static_cast<quint16>(value.toInt());
        break;
    case ATOI:
        atoi_.add(value);
        break;
    case APPT:
        appt_.add(value);
        break;
    case APKT:
        apkt_.add(value);
        break;
    case PLUS:
        plus_ += static_cast<quint16>(value.toInt());
        break;
    case MINUS:
        minus_ += static_cast<quint16>(value.toInt());
        break;
    case FS:
        fs_ += static_cast<quint16>(value.toInt());
        break;
    case AVG_RATING:
        average_rating_ += value.toDouble();
        break;
    default:
        return;
    };
}

/* =================== */
/*      Get Stats      */
/* =================== */

QVariant Skater::get(const qint32 column) const
{
    switch (column) {
    case NAME:
        return name();
    case CLUB:
        return clubName();
    case POS:
        return pos_;
    case GP:
        return gp_;
    case G:
        return g_;
    case A:
        return a_;
    case PTS:
        return pts_;
    case PLUS_MINUS:
        return plus_minus_;
    case PIM:
        return pim_;
    case PPG:
        return ppg_;
    case PPA:
        return ppa_;
    case PPP:
        return ppp_;
    case SHG:
        return shg_;
    case SHA:
        return sha_;
    case SHP:
        return shp_;
    case GWG:
        return gwg_;
    case GT:
        return gt_;
    case FG:
        return fg_;
    case EN:
        return en_;
    case SOG:
        return sog_;
    case SH:
        return sh_;
    case HT:
        return ht_;
    case GA:
        return ga_;
    case TA:
        return ta_;
    case FO:
        return fo_;
    case SB:
        return sb_;
    case TWO_MIN_PEN:
        return two_min_pen_;
    case FIVE_MIN_PEN:
        return five_min_pen_;
    case MI:
        return mi_;
    case MA:
        return ma_;
    case GM:
        return gm_;
    case FI:
        return fi_;
    case FW:
        return fw_;
    case TTOI: // NOTE: Decimal as QTime doesn't work with hh > 23; mm > 59; or ss > 59
        return ttoi().toDecimal();
    case ATOI:
        return atoi_.get();
    case APPT:
        return appt_.get();
    case APKT:
        return apkt_.get();
    case PLUS:
        return plus_;
    case MINUS:
        return minus_;
    case FS:
        return fs_;
    case AVG_RATING:
        return average_rating_;
    case GOALS_PER_MINUTE:
        return getPerMinute(G);
    case ASSISTS_PER_MINUTE:
        return getPerMinute(A);
    case PIM_PER_MINUTE:
        return getPerMinute(PIM);
    case SHOTS_ON_GOAL_PER_MINUTE:
        return getPerMinute(SOG);
    case SHOTS_BLOCKED_PER_MINUTE:
        return getPerMinute(SB);
    case GOALS_PER_MINUTE_VS_CLUB_AVERAGE:
        return getPerMinuteAgainstClubAverage(G);
    case ASSISTS_PER_MINUTE_VS_CLUB_AVERAGE:
        return getPerMinuteAgainstClubAverage(A);
    case PIM_PER_MINUTE_VS_CLUB_AVERAGE:
        return getPerMinuteAgainstClubAverage(PIM);
    case SHOTS_ON_GOAL_PER_MINUTE_VS_CLUB_AVERAGE:
        return getPerMinuteAgainstClubAverage(SOG);
    case SHOTS_BLOCKED_PER_MINUTE_VS_CLUB_AVERAGE:
        return getPerMinuteAgainstClubAverage(SB);
    default:
        return 0;
    };
}

//! Stat item divided by TTOI */
double Skater::getPerMinute(const qint32 column) const
{
    const auto value{get(column).toDouble()};

    if (value == 0.0)
        return value;

    return value / ttoi().toDecimal();
}

//! Skater's statistic plus or minus the club average */
double Skater::getPerMinuteAgainstClubAverage(const qint32 column) const
{
    const auto c{club()};
    if (!c)
        return 0;

    return getPerMinute(column) - c->skaterAveragePerMinute(column, isDefenceman());
}

//! Total time on ice */
IceTime Skater::ttoi() const
{
    return atoi_.multiplied(gp_);
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

bool Skater::parse(QString &line,
                   const ClubContainer *clubs,
                   const QHash<QString, qint32> &club_hash_table)
{
    const auto stats_list{line.split(",", Qt::SkipEmptyParts, Qt::CaseInsensitive)};

    if (stats_list.size() != INPUT_COLUMNS_COUNT) {
        qWarning().noquote()
            << QStringLiteral(
                   "Unexpected number of player stats columns found (%L1 found | %L2 expected)")
                   .arg(stats_list.size())
                   .arg(INPUT_COLUMNS_COUNT);
        return false;
    }

    // Basic details
    name_ = stats_list[IN_NAME];
    pos_ = stats_list[IN_POS];

    // Club
    const auto club_id = club_hash_table.value(stats_list[IN_CLUB], static_cast<qint32>(no_result_));
    if (club_id != static_cast<qint32>(no_result_))
        club_ = clubs->get(club_id);

    // Stats
    gp_ = stats_list[IN_GP].toUShort();
    g_ = stats_list[IN_G].toUShort();
    a_ = stats_list[IN_A].toUShort();
    pts_ = stats_list[IN_PTS].toUShort();
    plus_minus_ = stats_list[IN_PLUS_MINUS].toShort();
    pim_ = stats_list[IN_PIM].toUShort();
    ppg_ = stats_list[IN_PPG].toUShort();
    ppa_ = stats_list[IN_PPA].toUShort();
    ppp_ = stats_list[IN_PPP].toUShort();
    shg_ = stats_list[IN_SHG].toUShort();
    sha_ = stats_list[IN_SHA].toUShort();
    shp_ = stats_list[IN_SHP].toUShort();
    gwg_ = stats_list[IN_GWG].toUShort();
    gt_ = stats_list[IN_GT].toUShort();
    fg_ = stats_list[IN_FG].toUShort();
    en_ = stats_list[IN_EN].toUShort();
    sog_ = stats_list[IN_SOG].toUShort();
    sh_ = stats_list[IN_SH].toDouble();
    ht_ = stats_list[IN_HT].toUShort();
    ga_ = stats_list[IN_GA].toUShort();
    ta_ = stats_list[IN_TA].toUShort();
    fo_ = stats_list[IN_FO].toDouble();
    sb_ = stats_list[IN_SB].toUShort();
    two_min_pen_ = stats_list[IN_TWO_MIN_PEN].toUShort();
    five_min_pen_ = stats_list[IN_FIVE_MIN_PEN].toUShort();
    mi_ = stats_list[IN_MI].toUShort();
    ma_ = stats_list[IN_MA].toUShort();
    gm_ = stats_list[IN_GM].toUShort();
    fi_ = stats_list[IN_FI].toUShort();
    fw_ = stats_list[IN_FW].toUShort();
    atoi_.parse(stats_list[IN_ATOI]);
    appt_.parse(stats_list[IN_APPT]);
    apkt_.parse(stats_list[IN_APKT]);
    plus_ = stats_list[IN_PLUS].toUShort();
    minus_ = stats_list[IN_MINUS].toUShort();
    fs_ = stats_list[IN_FS].toUShort();
    average_rating_ = stats_list[IN_AVG_RATING].toDouble();

    // Add to club totals
    const auto club{club_.lock()};
    if (club)
        club->add(this);

    return true;
}
