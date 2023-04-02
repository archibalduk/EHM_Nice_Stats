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
    
}

SkaterContainer::~SkaterContainer() {}

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

/* =========================== */
/*      Get Data: Columns      */
/* =========================== */

qint32 SkaterContainer::columnEndPos() const
{
    return Skater::DATA_COLUMNS_END_POS;
}

QString SkaterContainer::columnDescription(const qint32 column) const
{
    switch (column) {
    case Skater::NAME:
        return QStringLiteral("Player name");
    case Skater::CLUB:
        return QStringLiteral("Club");
    case Skater::POS:
        return QStringLiteral("Position");
    case Skater::GP:
        return QStringLiteral("Games played");
    case Skater::G:
        return QStringLiteral("Goals");
    case Skater::A:
        return QStringLiteral("Assists");
    case Skater::PTS:
        return QStringLiteral("Points");
    case Skater::PLUS_MINUS:
        return QStringLiteral("Plus/minus");
    case Skater::PIM:
        return QStringLiteral("Penalties in minutes");
    case Skater::PPG:
        return QStringLiteral("Powerplay goals");
    case Skater::PPA:
        return QStringLiteral("Powerplay assists");
    case Skater::PPP:
        return QStringLiteral("Powerplay points");
    case Skater::SHG:
        return QStringLiteral("Shorthanded goals");
    case Skater::SHA:
        return QStringLiteral("Shorthanded assists");
    case Skater::SHP:
        return QStringLiteral("Shorthanded points");
    case Skater::GWG:
        return QStringLiteral("Game winning goals");
    case Skater::GT:
        return QStringLiteral("Game tying goals");
    case Skater::FG:
        return QStringLiteral("First goals");
    case Skater::EN:
        return QStringLiteral("Empty net goals");
    case Skater::SOG:
        return QStringLiteral("Shots on goal");
    case Skater::SH:
        return QStringLiteral("Shooting percentage");
    case Skater::HT:
        return QStringLiteral("Hits given");
    case Skater::GA:
        return QStringLiteral("Giveaways");
    case Skater::TA:
        return QStringLiteral("Takeaways");
    case Skater::FO:
        return QStringLiteral("Faceoff percentage");
    case Skater::SB:
        return QStringLiteral("Shots blocked");
    case Skater::TWO_MIN_PEN:
        return QStringLiteral("Minor penalties");
    case Skater::FIVE_MIN_PEN:
        return QStringLiteral("Major penalties");
    case Skater::MI:
        return QStringLiteral("Misconduct penalties");
    case Skater::MA:
        return QStringLiteral("Match penalties");
    case Skater::GM:
        return QStringLiteral("Game misconduct penalties");
    case Skater::FI:
        return QStringLiteral("Fights");
    case Skater::FW:
        return QStringLiteral("Fights won");
    case Skater::TTOI:
        return QStringLiteral("Total time on ice");
    case Skater::ATOI:
        return QStringLiteral("Average time on ice");
    case Skater::APPT:
        return QStringLiteral("Average powerplay time on ice");
    case Skater::APKT:
        return QStringLiteral("Average penalty kill time on ice");
    case Skater::PLUS:
        return QStringLiteral("Plus (on ice goals for)");
    case Skater::MINUS:
        return QStringLiteral("Minus (on ice goals against)");
    case Skater::FS:
        return QStringLiteral("First star");
    case Skater::GOALS_PER_MINUTE:
        return QStringLiteral("Goals per minute");
    case Skater::ASSISTS_PER_MINUTE:
        return QStringLiteral("Assists per minute");
    case Skater::PIM_PER_MINUTE:
        return QStringLiteral("PIM per minute");
    case Skater::SHOTS_ON_GOAL_PER_MINUTE:
        return QStringLiteral("Shots on goal per minute");
    case Skater::SHOTS_BLOCKED_PER_MINUTE:
        return QStringLiteral("Shots blocked per minute");
    default:
        return QStringLiteral("*NO NAME*");
    }
}

QString SkaterContainer::columnName(const qint32 column) const
{
    switch (column) {
    case Skater::NAME:
        return QStringLiteral("Name");
    case Skater::CLUB:
        return QStringLiteral("Club");
    case Skater::POS:
        return QStringLiteral("Pos");
    case Skater::GP:
        return QStringLiteral("GP");
    case Skater::G:
        return QStringLiteral("G");
    case Skater::A:
        return QStringLiteral("A");
    case Skater::PTS:
        return QStringLiteral("Pts");
    case Skater::PLUS_MINUS:
        return QStringLiteral("'+/-");
    case Skater::PIM:
        return QStringLiteral("PIM");
    case Skater::PPG:
        return QStringLiteral("PP G");
    case Skater::PPA:
        return QStringLiteral("PP A");
    case Skater::PPP:
        return QStringLiteral("PP Pts");
    case Skater::SHG:
        return QStringLiteral("SH G");
    case Skater::SHA:
        return QStringLiteral("SH A");
    case Skater::SHP:
        return QStringLiteral("SH Pts");
    case Skater::GWG:
        return QStringLiteral("GWG");
    case Skater::GT:
        return QStringLiteral("GT");
    case Skater::FG:
        return QStringLiteral("FG");
    case Skater::EN:
        return QStringLiteral("EN");
    case Skater::SOG:
        return QStringLiteral("SOG");
    case Skater::SH:
        return QStringLiteral("Sh%");
    case Skater::HT:
        return QStringLiteral("HT");
    case Skater::GA:
        return QStringLiteral("GA");
    case Skater::TA:
        return QStringLiteral("TA");
    case Skater::FO:
        return QStringLiteral("FO%");
    case Skater::SB:
        return QStringLiteral("SB");
    case Skater::TWO_MIN_PEN:
        return QStringLiteral("2 MIN");
    case Skater::FIVE_MIN_PEN:
        return QStringLiteral("5 MIN");
    case Skater::MI:
        return QStringLiteral("Mi");
    case Skater::MA:
        return QStringLiteral("Ma");
    case Skater::GM:
        return QStringLiteral("GM");
    case Skater::FI:
        return QStringLiteral("FI");
    case Skater::FW:
        return QStringLiteral("FW");
    case Skater::TTOI:
        return QStringLiteral("TTOI");
    case Skater::ATOI:
        return QStringLiteral("ATOI");
    case Skater::APPT:
        return QStringLiteral("APPT");
    case Skater::APKT:
        return QStringLiteral("APKT");
    case Skater::PLUS:
        return QStringLiteral("'+");
    case Skater::MINUS:
        return QStringLiteral("'-");
    case Skater::FS:
        return QStringLiteral("FS");
    case Skater::AVG_RATING:
        return QStringLiteral("Av R");
    case Skater::GOALS_PER_MINUTE:
        return QStringLiteral("G/min");
    case Skater::ASSISTS_PER_MINUTE:
        return QStringLiteral("A/min");
    case Skater::PIM_PER_MINUTE:
        return QStringLiteral("PIM/min");
    case Skater::SHOTS_ON_GOAL_PER_MINUTE:
        return QStringLiteral("SOG/min");
    case Skater::SHOTS_BLOCKED_PER_MINUTE:
        return QStringLiteral("SB/min");
    default:
        return QStringLiteral("*NO NAME*");
    }
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
