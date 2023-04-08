#include "skater_container.h"

// Application headers
#include "../club.h"
#include "club_container.h"

// Xlsx headers
#include "stats/container/club_container.h"
#include "xlsxdocument.h"

// Qt headers
#include <QDebug>
#include <QFile>
#include <QTextStream>

using namespace stats;

/* ========================== */
/*      Skater Container      */
/* ========================== */

SkaterContainer::SkaterContainer()
{
    initColumnData();
}

SkaterContainer::~SkaterContainer() {}

/* ===================== */
/*      Column Data      */
/* ===================== */

qint32 SkaterContainer::columnEndPos() const
{
    return Skater::DATA_COLUMNS_END_POS;
}

void SkaterContainer::initColumnData()
{
    // Bio
    addColumn(ColumnData(Skater::NAME, QStringLiteral("Name")));
    addColumn(ColumnData(Skater::CLUB, QStringLiteral("Club"), QStringLiteral("Club")));
    addColumn(ColumnData(Skater::POS, QStringLiteral("Pos"), QStringLiteral("Position")));
    // Basic stats
    addColumn(ColumnData(Skater::GP, QStringLiteral("GP"), QStringLiteral("Games played")));
    addColumn(ColumnData(Skater::G, QStringLiteral("G"), QStringLiteral("Goals")));
    addColumn(ColumnData(Skater::A, QStringLiteral("A"), QStringLiteral("Assists")));
    addColumn(ColumnData(Skater::PTS, QStringLiteral("Pts"), QStringLiteral("Points")));
    addColumn(ColumnData(Skater::PLUS_MINUS, QStringLiteral("'+/-"), QStringLiteral("Plus/minus")));
    addColumn(
        ColumnData(Skater::PIM, QStringLiteral("PIM"), QStringLiteral("Penalties in minutes")));
    // Powerplay
    addColumn(ColumnData(Skater::PPG, QStringLiteral("PP G"), QStringLiteral("Powerplay goals")));
    addColumn(ColumnData(Skater::PPA, QStringLiteral("PP A"), QStringLiteral("Powerplay assists")));
    addColumn(ColumnData(Skater::PPP, QStringLiteral("PP Pts"), QStringLiteral("Powerplay points")));
    // Penalty kill
    addColumn(ColumnData(Skater::SHG, QStringLiteral("SH G"), QStringLiteral("Shorthanded goals")));
    addColumn(
        ColumnData(Skater::SHA, QStringLiteral("SH A"), QStringLiteral("Shorthanded assists")));
    addColumn(
        ColumnData(Skater::SHP, QStringLiteral("SH Pts"), QStringLiteral("Shorthanded points")));
    // Goals/shooting
    addColumn(ColumnData(Skater::GWG, QStringLiteral("GWG"), QStringLiteral("Game winning goals")));
    addColumn(ColumnData(Skater::GT, QStringLiteral("GT"), QStringLiteral("Game tying goals")));
    addColumn(ColumnData(Skater::FG, QStringLiteral("FG"), QStringLiteral("First goals")));
    addColumn(ColumnData(Skater::EN, QStringLiteral("EN"), QStringLiteral("Empty net goals")));
    addColumn(ColumnData(Skater::SOG, QStringLiteral("SOG"), QStringLiteral("Shots on goal")));
    addColumn(ColumnData(Skater::SH, QStringLiteral("Sh%"), QStringLiteral("Shooting percentage")));
    // Defence
    addColumn(ColumnData(Skater::HT, QStringLiteral("HT"), QStringLiteral("Hits given")));
    addColumn(ColumnData(Skater::GA, QStringLiteral("GA"), QStringLiteral("Giveaways")));
    addColumn(ColumnData(Skater::TA, QStringLiteral("TA"), QStringLiteral("Takeaways")));
    addColumn(ColumnData(Skater::FO, QStringLiteral("FO%"), QStringLiteral("Faceoff percentage")));
    addColumn(ColumnData(Skater::SB, QStringLiteral("SB"), QStringLiteral("Shots blocked")));
    // Penalties
    addColumn(
        ColumnData(Skater::TWO_MIN_PEN, QStringLiteral("2 MIN"), QStringLiteral("Minor penalties")));
    addColumn(ColumnData(Skater::FIVE_MIN_PEN,
                         QStringLiteral("5 MIN"),
                         QStringLiteral("Major penalties")));
    addColumn(ColumnData(Skater::MI, QStringLiteral("Mi"), QStringLiteral("Misconduct penalties")));
    addColumn(ColumnData(Skater::MA, QStringLiteral("Ma"), QStringLiteral("Match penalties")));
    addColumn(
        ColumnData(Skater::GM, QStringLiteral("GM"), QStringLiteral("Game misconduct penalties")));
    // Fights
    addColumn(ColumnData(Skater::FI, QStringLiteral("FI"), QStringLiteral("Fights")));
    addColumn(ColumnData(Skater::FW, QStringLiteral("FW"), QStringLiteral("Fights won")));
    // Ice time
    addColumn(ColumnData(Skater::TTOI, QStringLiteral("TTOI"), QStringLiteral("Total time on ice")));
    addColumn(
        ColumnData(Skater::ATOI, QStringLiteral("ATOI"), QStringLiteral("Average time on ice")));
    addColumn(ColumnData(Skater::APPT,
                         QStringLiteral("APPT"),
                         QStringLiteral("Average powerplay time on ice")));
    addColumn(ColumnData(Skater::APKT,
                         QStringLiteral("APKT"),
                         QStringLiteral("Average penalty kill time on ice")));
    // Plus/minus breakdown
    addColumn(
        ColumnData(Skater::PLUS, QStringLiteral("'+"), QStringLiteral("Plus (on ice goals for)")));
    addColumn(ColumnData(Skater::MINUS,
                         QStringLiteral("'-"),
                         QStringLiteral("Minus (on ice goals against)")));
    // Performance
    addColumn(ColumnData(Skater::FS, QStringLiteral("FS"), QStringLiteral("First star")));
    addColumn(
        ColumnData(Skater::AVG_RATING, QStringLiteral("Av R"), QStringLiteral("Average rating")));
    // Per minute stats
    addColumn(ColumnData(Skater::GOALS_PER_MINUTE,
                         QStringLiteral("G/min"),
                         QStringLiteral("Goals per minute")));
    addColumn(ColumnData(Skater::ASSISTS_PER_MINUTE,
                         QStringLiteral("A/min"),
                         QStringLiteral("Assists per minute")));
    addColumn(ColumnData(Skater::PIM_PER_MINUTE,
                         QStringLiteral("PIM/min"),
                         QStringLiteral("PIM per minute")));
    addColumn(ColumnData(Skater::SHOTS_ON_GOAL_PER_MINUTE,
                         QStringLiteral("SOG/min"),
                         QStringLiteral("Shots on goal per minute")));
    addColumn(ColumnData(Skater::SHOTS_BLOCKED_PER_MINUTE,
                         QStringLiteral("SB/min"),
                         QStringLiteral("Shots blocked per minute")));
    // Per minute vs club average
    addColumn(ColumnData(Skater::GOALS_PER_MINUTE_VS_CLUB_AVERAGE,
                         QStringLiteral("G/min vs club avg"),
                         QStringLiteral("Goals per minute vs club average")));
    addColumn(ColumnData(Skater::ASSISTS_PER_MINUTE_VS_CLUB_AVERAGE,
                         QStringLiteral("A/min vs club avg"),
                         QStringLiteral("Assists per minute vs club average")));
    addColumn(ColumnData(Skater::PIM_PER_MINUTE_VS_CLUB_AVERAGE,
                         QStringLiteral("PIM/min vs club avg"),
                         QStringLiteral("PIM per minute vs club avg vs club average")));
    addColumn(ColumnData(Skater::SHOTS_ON_GOAL_PER_MINUTE_VS_CLUB_AVERAGE,
                         QStringLiteral("SOG/min vs club avg"),
                         QStringLiteral("Shots on goal per minute vs club average")));
    addColumn(ColumnData(Skater::SHOTS_BLOCKED_PER_MINUTE_VS_CLUB_AVERAGE,
                         QStringLiteral("SB/min vs club avg"),
                         QStringLiteral("Shots blocked per minute vs club average")));
}

/* ================== */
/*      File i/o      */
/* ================== */

void SkaterContainer::writeToSpreadsheet(QXlsx::Document &xlsx, const std::shared_ptr<Club> &club)
{
    if (club)
        xlsx.addSheet(club->name());
    else
        xlsx.addSheet(QStringLiteral("Unassigned"));

    auto row{writeHeaderRow(xlsx)};

    for (const auto &itr : data_)
        if (itr.club() == club)
            itr.write(xlsx, row++);
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

bool stats::SkaterContainer::parseFile(const QString &file_path, const ClubContainer *clubs)
{
    QFile f(file_path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical().noquote() << QStringLiteral("Unable to open player stats file: ") << file_path;
        return false;
    }

    QTextStream in(&f);

    // Locate the start of the stats and parse each row
    if (!findPositionInFile(in)) {
        qCritical().noquote() << QStringLiteral("Unable to find any player stats within")
                              << file_path;
        return false;
    }

    const auto club_hash_table{clubs->hash()};

    // Parse each line
    QString line;
    while (in.readLineInto(&line)) {
        if (line.startsWith(QStringLiteral("---"), Qt::CaseInsensitive))
            break; // Stop at the end of the regular season stats

        Skater player;

        if (player.parse(line, clubs, club_hash_table))
            data_.push_back(std::move(player));
    }

    // Sort the data
    //std::sort(/*std::execution::par,*/ data.begin(), data.end(), Player::sort);

    qInfo().noquote() << QStringLiteral("Total players parsed: %L1").arg(data_.size());
    return true;
}

qint64 SkaterContainer::findPositionInFile(QTextStream &in)
{
    QString line;
    while (in.readLineInto(&line)) { // The stats table begins with "Name,Team,Pos"
        if (line.startsWith(QStringLiteral("Name,Team,Pos"), Qt::CaseInsensitive))
            return in.pos();
    }

    return no_result_;
}
