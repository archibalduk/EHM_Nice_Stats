#include "player.h"

// Xlsx headers
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
    //xlsx.write(row, OUT_CLUB, club_);
    xlsx.write(row, OUT_POS, pos_);
    xlsx.write(row, OUT_GP, gp_);
    xlsx.write(row, OUT_G, g_);
    xlsx.write(row, OUT_A, a_);
    xlsx.write(row, OUT_PTS, pts_);
    xlsx.write(row, OUT_PLUS_MINUS, plus_minus_);
    xlsx.write(row, OUT_PIM, pim_);
    xlsx.write(row, OUT_PPG, ppg_);
    xlsx.write(row, OUT_PPA, ppa_);
    xlsx.write(row, OUT_PPP, ppp_);
    xlsx.write(row, OUT_SHG, shg_);
    xlsx.write(row, OUT_SHA, sha_);
    xlsx.write(row, OUT_SHP, shp_);
    xlsx.write(row, OUT_GWG, gwg_);
    xlsx.write(row, OUT_GT, gt_);
    xlsx.write(row, OUT_FG, fg_);
    xlsx.write(row, OUT_EN, en_);
    xlsx.write(row, OUT_SOG, sog_);
    xlsx.write(row, OUT_SH, sh_);
    xlsx.write(row, OUT_HT, ht_);
    xlsx.write(row, OUT_GA, ga_);
    xlsx.write(row, OUT_TA, ta_);
    xlsx.write(row, OUT_FO, fo_);
    xlsx.write(row, OUT_SB, sb_);
    xlsx.write(row, OUT_TWO_MIN_PEN, two_min_pen_);
    xlsx.write(row, OUT_FIVE_MIN_PEN, five_min_pen_);
    xlsx.write(row, OUT_MI, mi_);
    xlsx.write(row, OUT_MA, ma_);
    xlsx.write(row, OUT_GM, gm_);
    xlsx.write(row, OUT_FI, fi_);
    xlsx.write(row, OUT_FW, fw_);
    xlsx.write(row, OUT_ATOI, atoi_.toTime());
    xlsx.write(row, OUT_APPT, appt_.toTime());
    xlsx.write(row, OUT_APKT, apkt_.toTime());
    xlsx.write(row, OUT_PLUS, plus_);
    xlsx.write(row, OUT_MINUS, minus_);
    xlsx.write(row, OUT_FS, fs_);
    xlsx.write(row, OUT_AVG_RATING, average_rating_);
}

void Player::writeToSpreadsheet(QXlsx::Document &xlsx, std::vector<Player> &data)
{
    xlsx.addSheet(QStringLiteral("Players"));

    auto row{1};

    for (auto column = 1; column < OUTPUT_COLUMNS_END_POS; ++column)
        xlsx.write(row, column, columnName(column));

    for (const auto &itr : data)
        itr.write(xlsx, ++row);
}

/* ================== */
/*      Get Data      */
/* ================== */

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
        return QStringLiteral("PP Pta");
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
        return QStringLiteral("Sh");
    case OUT_HT:
        return QStringLiteral("HT");
    case OUT_GA:
        return QStringLiteral("GA");
    case OUT_TA:
        return QStringLiteral("TA");
    case OUT_FO:
        return QStringLiteral("FO");
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

bool Player::parse(QString &line)
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

    name_ = stats_list[IN_NAME];
    pos_ = stats_list[IN_POS];
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
    sh_ = stats_list[IN_SH].toUShort();
    ht_ = stats_list[IN_HT].toUShort();
    ga_ = stats_list[IN_GA].toUShort();
    ta_ = stats_list[IN_TA].toUShort();
    fo_ = stats_list[IN_FO].toUShort();
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

    return true;
}

bool Player::parseFile(const QString &file_path,
                       std::vector<Player> &data,
                       std::vector<std::shared_ptr<Club>> &clubs)
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

    // Parse each line
    QString line;
    while (in.readLineInto(&line)) {
        if (line.startsWith(QStringLiteral("---"), Qt::CaseInsensitive))
            break; // Stop at the end of the regular season stats

        Player player;

        if (player.parse(line))
            data.push_back(std::move(player));
    }

    // Sort the data
    //std::sort(/*std::execution::par,*/ data.begin(), data.end(), Player::sort);

    qInfo().noquote() << QStringLiteral("Total players parsed: %L1").arg(data.size());
    return true;
}
