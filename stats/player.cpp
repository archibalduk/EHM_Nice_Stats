#include "player.h"

// Xlsx headers
#include "club.h"
#include "xlsxdocument.h"

// Qt headers
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <execution>

using namespace stats;

/* ====================== */
/*      Player Stats      */
/* ====================== */

Player::Player()
{
    
}

/* ================== */
/*      File i/o      */
/* ================== */

void Player::write(QXlsx::Document &xlsx, const qint32 row) const
{
    xlsx.write(row, OUT_NAME, name_);

    const auto club{club_.lock()};
    if (club)
        xlsx.write(row, OUT_CLUB, club->name());
    else
        xlsx.write(row, OUT_CLUB, QStringLiteral("[none]"));

    xlsx.write(row, OUT_POS, pos_);
    xlsx.write(row, OUT_GP, gp_);
    xlsx.write(row, OUT_G, skater_stats_.g_);
    xlsx.write(row, OUT_A, skater_stats_.a_);
    xlsx.write(row, OUT_PTS, skater_stats_.pts_);
    xlsx.write(row, OUT_PLUS_MINUS, skater_stats_.plus_minus_);
    xlsx.write(row, OUT_PIM, skater_stats_.pim_);
    xlsx.write(row, OUT_PPG, skater_stats_.ppg_);
    xlsx.write(row, OUT_PPA, skater_stats_.ppa_);
    xlsx.write(row, OUT_PPP, skater_stats_.ppp_);
    xlsx.write(row, OUT_SHG, skater_stats_.shg_);
    xlsx.write(row, OUT_SHA, skater_stats_.sha_);
    xlsx.write(row, OUT_SHP, skater_stats_.shp_);
    xlsx.write(row, OUT_GWG, skater_stats_.gwg_);
    xlsx.write(row, OUT_GT, skater_stats_.gt_);
    xlsx.write(row, OUT_FG, skater_stats_.fg_);
    xlsx.write(row, OUT_EN, skater_stats_.en_);
    xlsx.write(row, OUT_SOG, skater_stats_.sog_);
    xlsx.write(row, OUT_SH, skater_stats_.sh_);
    xlsx.write(row, OUT_HT, skater_stats_.ht_);
    xlsx.write(row, OUT_GA, skater_stats_.ga_);
    xlsx.write(row, OUT_TA, skater_stats_.ta_);
    xlsx.write(row, OUT_FO, skater_stats_.fo_);
    xlsx.write(row, OUT_SB, skater_stats_.sb_);
    xlsx.write(row, OUT_TWO_MIN_PEN, skater_stats_.two_min_pen_);
    xlsx.write(row, OUT_FIVE_MIN_PEN, skater_stats_.five_min_pen_);
    xlsx.write(row, OUT_MI, skater_stats_.mi_);
    xlsx.write(row, OUT_MA, skater_stats_.ma_);
    xlsx.write(row, OUT_GM, skater_stats_.gm_);
    xlsx.write(row, OUT_FI, skater_stats_.fi_);
    xlsx.write(row, OUT_FW, skater_stats_.fw_);
    xlsx.write(row, OUT_ATOI, skater_stats_.atoi_.toTime());
    xlsx.write(row, OUT_APPT, skater_stats_.appt_.toTime());
    xlsx.write(row, OUT_APKT, skater_stats_.apkt_.toTime());
    xlsx.write(row, OUT_PLUS, skater_stats_.plus_);
    xlsx.write(row, OUT_MINUS, skater_stats_.minus_);
    xlsx.write(row, OUT_FS, skater_stats_.fs_);
    xlsx.write(row, OUT_AVG_RATING, skater_stats_.average_rating_);
}

void Player::writeToSpreadsheet(QXlsx::Document &xlsx,
                                std::vector<Player> &data,
                                const std::shared_ptr<Club> &club)
{
    if (club)
        xlsx.addSheet(club->name());
    else
        xlsx.addSheet(QStringLiteral("Unassigned"));

    auto row{1};

    for (auto column = 1; column < OUTPUT_COLUMNS_END_POS; ++column)
        xlsx.write(row, column, columnName(column));

    for (const auto &itr : data)
        if (itr.club_.lock() == club)
            itr.write(xlsx, ++row);
}

/* ================== */
/*      Get Data      */
/* ================== */

QString Player::columnDescription(const qint32 xlsx_column)
{
    switch (xlsx_column) {
    case OUT_NAME:
        return QStringLiteral("Player name");
    case OUT_CLUB:
        return QStringLiteral("Club");
    case OUT_POS:
        return QStringLiteral("Position");
    case OUT_GP:
        return QStringLiteral("Games played");
    case OUT_G:
        return QStringLiteral("Goals");
    case OUT_A:
        return QStringLiteral("Assists");
    case OUT_PTS:
        return QStringLiteral("Points");
    case OUT_PLUS_MINUS:
        return QStringLiteral("Plus/minus");
    case OUT_PIM:
        return QStringLiteral("Penalties in minutes");
    case OUT_PPG:
        return QStringLiteral("Powerplay goals");
    case OUT_PPA:
        return QStringLiteral("Powerplay assists");
    case OUT_PPP:
        return QStringLiteral("Powerplay points");
    case OUT_SHG:
        return QStringLiteral("Shorthanded goals");
    case OUT_SHA:
        return QStringLiteral("Shorthanded assists");
    case OUT_SHP:
        return QStringLiteral("Shorthanded points");
    case OUT_GWG:
        return QStringLiteral("Game winning goals");
    case OUT_GT:
        return QStringLiteral("Game tying goals");
    case OUT_FG:
        return QStringLiteral("First goals");
    case OUT_EN:
        return QStringLiteral("Empty net goals");
    case OUT_SOG:
        return QStringLiteral("Shots on goal");
    case OUT_SH:
        return QStringLiteral("Shooting percentage");
    case OUT_HT:
        return QStringLiteral("Hits given");
    case OUT_GA:
        return QStringLiteral("Giveaways");
    case OUT_TA:
        return QStringLiteral("Takeaways");
    case OUT_FO:
        return QStringLiteral("Faceoff percentage");
    case OUT_SB:
        return QStringLiteral("Shots blocked");
    case OUT_TWO_MIN_PEN:
        return QStringLiteral("Minor penalties");
    case OUT_FIVE_MIN_PEN:
        return QStringLiteral("Major penalties");
    case OUT_MI:
        return QStringLiteral("Misconduct penalties");
    case OUT_MA:
        return QStringLiteral("Match penalties");
    case OUT_GM:
        return QStringLiteral("Game misconduct penalties");
    case OUT_FI:
        return QStringLiteral("Fights");
    case OUT_FW:
        return QStringLiteral("Fights won");
    case OUT_ATOI:
        return QStringLiteral("Average time on ice");
    case OUT_APPT:
        return QStringLiteral("Average powerplay time on ice");
    case OUT_APKT:
        return QStringLiteral("Average penalty kill time on ice");
    case OUT_PLUS:
        return QStringLiteral("Plus (on ice goals for)");
    case OUT_MINUS:
        return QStringLiteral("Minus (on ice goals against)");
    case OUT_FS:
        return QStringLiteral("First star");
    case OUT_AVG_RATING:
        return QStringLiteral("EHM average rating");
    default:
        return QStringLiteral("*NO NAME*");
    }
}

QString Player::columnName(const qint32 xlsx_column)
{
    switch (xlsx_column) {
    case OUT_NAME:
        return QStringLiteral("Name");
    case OUT_CLUB:
        return QStringLiteral("Club");
    case OUT_POS:
        return QStringLiteral("Pos");
    case OUT_GP:
        return QStringLiteral("GP");
    case OUT_G:
        return QStringLiteral("G");
    case OUT_A:
        return QStringLiteral("A");
    case OUT_PTS:
        return QStringLiteral("Pts");
    case OUT_PLUS_MINUS:
        return QStringLiteral("'+/-");
    case OUT_PIM:
        return QStringLiteral("PIM");
    case OUT_PPG:
        return QStringLiteral("PP G");
    case OUT_PPA:
        return QStringLiteral("PP A");
    case OUT_PPP:
        return QStringLiteral("PP Pts");
    case OUT_SHG:
        return QStringLiteral("SH G");
    case OUT_SHA:
        return QStringLiteral("SH A");
    case OUT_SHP:
        return QStringLiteral("SH Pts");
    case OUT_GWG:
        return QStringLiteral("GWG");
    case OUT_GT:
        return QStringLiteral("GT");
    case OUT_FG:
        return QStringLiteral("FG");
    case OUT_EN:
        return QStringLiteral("EN");
    case OUT_SOG:
        return QStringLiteral("SOG");
    case OUT_SH:
        return QStringLiteral("Sh%");
    case OUT_HT:
        return QStringLiteral("HT");
    case OUT_GA:
        return QStringLiteral("GA");
    case OUT_TA:
        return QStringLiteral("TA");
    case OUT_FO:
        return QStringLiteral("FO%");
    case OUT_SB:
        return QStringLiteral("SB");
    case OUT_TWO_MIN_PEN:
        return QStringLiteral("2 MIN");
    case OUT_FIVE_MIN_PEN:
        return QStringLiteral("5 MIN");
    case OUT_MI:
        return QStringLiteral("Mi");
    case OUT_MA:
        return QStringLiteral("Ma");
    case OUT_GM:
        return QStringLiteral("GM");
    case OUT_FI:
        return QStringLiteral("FI");
    case OUT_FW:
        return QStringLiteral("FW");
    case OUT_ATOI:
        return QStringLiteral("ATOI");
    case OUT_APPT:
        return QStringLiteral("APPT");
    case OUT_APKT:
        return QStringLiteral("APKT");
    case OUT_PLUS:
        return QStringLiteral("'+");
    case OUT_MINUS:
        return QStringLiteral("'-");
    case OUT_FS:
        return QStringLiteral("FS");
    case OUT_AVG_RATING:
        return QStringLiteral("Av R");
    default:
        return QStringLiteral("*NO NAME*");
    }
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

qint64 Player::findPlayerStats(QTextStream &in)
{
    QString line;
    while (in.readLineInto(&line)) { // The stats table begins with "Name,Team,Pos"
        if (line.startsWith(QStringLiteral("Name,Team,Pos"), Qt::CaseInsensitive))
            return in.pos();
    }

    return no_result_;
}

bool Player::parse(QString &line,
                   const std::vector<std::shared_ptr<Club>> &clubs,
                   const QHash<QString, qint32> &club_hash_table)
{
    const auto stats_list{line.split(",", Qt::SkipEmptyParts, Qt::CaseInsensitive)};

    if (stats_list.size() != SkaterStats::INPUT_COLUMNS_COUNT) {
        qWarning().noquote()
            << QStringLiteral(
                   "Unexpected number of player stats columns found (%L1 found | %L2 expected)")
                   .arg(stats_list.size())
                   .arg(SkaterStats::INPUT_COLUMNS_COUNT);
        return false;
    }

    // Basic details
    name_ = stats_list[SkaterStats::IN_NAME];
    pos_ = stats_list[SkaterStats::IN_POS];

    // Club
    const auto club_id = club_hash_table.value(stats_list[SkaterStats::IN_CLUB],
                                               static_cast<qint32>(no_result_));
    if (club_id != static_cast<qint32>(no_result_))
        club_ = clubs[club_id];

    // Stats
    gp_ = stats_list[SkaterStats::IN_GP].toUShort();
    skater_stats_.g_ = stats_list[SkaterStats::IN_G].toUShort();
    skater_stats_.a_ = stats_list[SkaterStats::IN_A].toUShort();
    skater_stats_.pts_ = stats_list[SkaterStats::IN_PTS].toUShort();
    skater_stats_.plus_minus_ = stats_list[SkaterStats::IN_PLUS_MINUS].toShort();
    skater_stats_.pim_ = stats_list[SkaterStats::IN_PIM].toUShort();
    skater_stats_.ppg_ = stats_list[SkaterStats::IN_PPG].toUShort();
    skater_stats_.ppa_ = stats_list[SkaterStats::IN_PPA].toUShort();
    skater_stats_.ppp_ = stats_list[SkaterStats::IN_PPP].toUShort();
    skater_stats_.shg_ = stats_list[SkaterStats::IN_SHG].toUShort();
    skater_stats_.sha_ = stats_list[SkaterStats::IN_SHA].toUShort();
    skater_stats_.shp_ = stats_list[SkaterStats::IN_SHP].toUShort();
    skater_stats_.gwg_ = stats_list[SkaterStats::IN_GWG].toUShort();
    skater_stats_.gt_ = stats_list[SkaterStats::IN_GT].toUShort();
    skater_stats_.fg_ = stats_list[SkaterStats::IN_FG].toUShort();
    skater_stats_.en_ = stats_list[SkaterStats::IN_EN].toUShort();
    skater_stats_.sog_ = stats_list[SkaterStats::IN_SOG].toUShort();
    skater_stats_.sh_ = stats_list[SkaterStats::IN_SH].toDouble();
    skater_stats_.ht_ = stats_list[SkaterStats::IN_HT].toUShort();
    skater_stats_.ga_ = stats_list[SkaterStats::IN_GA].toUShort();
    skater_stats_.ta_ = stats_list[SkaterStats::IN_TA].toUShort();
    skater_stats_.fo_ = stats_list[SkaterStats::IN_FO].toDouble();
    skater_stats_.sb_ = stats_list[SkaterStats::IN_SB].toUShort();
    skater_stats_.two_min_pen_ = stats_list[SkaterStats::IN_TWO_MIN_PEN].toUShort();
    skater_stats_.five_min_pen_ = stats_list[SkaterStats::IN_FIVE_MIN_PEN].toUShort();
    skater_stats_.mi_ = stats_list[SkaterStats::IN_MI].toUShort();
    skater_stats_.ma_ = stats_list[SkaterStats::IN_MA].toUShort();
    skater_stats_.gm_ = stats_list[SkaterStats::IN_GM].toUShort();
    skater_stats_.fi_ = stats_list[SkaterStats::IN_FI].toUShort();
    skater_stats_.fw_ = stats_list[SkaterStats::IN_FW].toUShort();
    skater_stats_.atoi_.parse(stats_list[SkaterStats::IN_ATOI]);
    skater_stats_.appt_.parse(stats_list[SkaterStats::IN_APPT]);
    skater_stats_.apkt_.parse(stats_list[SkaterStats::IN_APKT]);
    skater_stats_.plus_ = stats_list[SkaterStats::IN_PLUS].toUShort();
    skater_stats_.minus_ = stats_list[SkaterStats::IN_MINUS].toUShort();
    skater_stats_.fs_ = stats_list[SkaterStats::IN_FS].toUShort();
    skater_stats_.average_rating_ = stats_list[SkaterStats::IN_AVG_RATING].toDouble();

    return true;
}

bool Player::parseFile(const QString &file_path,
                       std::vector<Player> &data,
                       const std::vector<std::shared_ptr<Club>> &clubs)
{
    QFile f(file_path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical().noquote() << QStringLiteral("Unable to open player stats file: ") << file_path;
        return false;
    }

    QTextStream in(&f);

    // Locate the start of the stats and parse each row
    if (!findPlayerStats(in)) {
        qCritical().noquote() << QStringLiteral("Unable to find any player stats within")
                              << file_path;
        return false;
    }

    const auto club_hash_table{Club::hash(clubs)};

    // Parse each line
    QString line;
    while (in.readLineInto(&line)) {
        if (line.startsWith(QStringLiteral("---"), Qt::CaseInsensitive))
            break; // Stop at the end of the regular season stats

        Player player;

        if (player.parse(line, clubs, club_hash_table))
            data.push_back(std::move(player));
    }

    // Sort the data
    //std::sort(/*std::execution::par,*/ data.begin(), data.end(), Player::sort);

    qInfo().noquote() << QStringLiteral("Total players parsed: %L1").arg(data.size());
    return true;
}
