#include "skater_container.h"

// Application headers
#include "../club.h"

// Xlsx headers
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

/* ================== */
/*      File i/o      */
/* ================== */

void SkaterContainer::writeToSpreadsheet(QXlsx::Document &xlsx, const std::shared_ptr<Club> &club)
{
    if (club)
        xlsx.addSheet(club->name());
    else
        xlsx.addSheet(QStringLiteral("Unassigned"));

    auto row{1};

    for (auto column = 1; column < Skater::OUTPUT_COLUMNS_END_POS; ++column)
        xlsx.write(row, column, Skater::columnName(column));

    for (const auto &itr : data_)
        if (itr.club() == club)
            itr.write(xlsx, ++row);
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

bool stats::SkaterContainer::parseFile(const QString &file_path,
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

        Skater player;

        if (player.parse(line, clubs, club_hash_table))
            data_.push_back(std::move(player));
    }

    // Sort the data
    //std::sort(/*std::execution::par,*/ data.begin(), data.end(), Player::sort);

    qInfo().noquote() << QStringLiteral("Total players parsed: %L1").arg(data_.size());
    return true;
}

qint64 SkaterContainer::findPlayerStats(QTextStream &in)
{
    QString line;
    while (in.readLineInto(&line)) { // The stats table begins with "Name,Team,Pos"
        if (line.startsWith(QStringLiteral("Name,Team,Pos"), Qt::CaseInsensitive))
            return in.pos();
    }

    return no_result_;
}
