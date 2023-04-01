#include "club_container.h"

// Xlsx headers
#include "xlsxdocument.h"

// Qt headers
#include <QDebug>
//#include <execution>
#include <QFile>
#include <QHash>
#include <QTextStream>

using namespace stats;

ClubContainer::ClubContainer() {}

/* ================== */
/*      File i/o      */
/* ================== */

void ClubContainer::writeToSpreadsheet(QXlsx::Document &xlsx)
{
    xlsx.addSheet(QStringLiteral("Club stats"));

    auto row{1};

    for (auto column = 1; column < Club::OUTPUT_COLUMNS_END_POS; ++column)
        xlsx.write(row, column, Club::columnName(column));

    for (const auto &itr : data_)
        itr->write(xlsx, ++row);
}

/* ================== */
/*      Get Data      */
/* ================== */

std::vector<std::shared_ptr<stats::Club>> stats::ClubContainer::alphabeticalList() const
{
    auto list{data_};
    std::sort(/*std::execution::par,*/ list.begin(), list.end(), Club::sortByName);

    return list;
}

std::weak_ptr<Club> ClubContainer::get(const qint32 id) const
{
    if (id >= 0 && id < static_cast<qint32>(data_.size()))
        return std::weak_ptr<Club>(data_[id]);

    return std::weak_ptr<Club>();
}

QHash<QString, qint32> stats::ClubContainer::hash() const
{
    QHash<QString, qint32> h;

    const auto size{static_cast<qint32>(data_.size())};
    for (auto i = 0; i < size; ++i)
        h.insert(data_[i]->name(), i);

    return h;
}

/* ==================== */
/*      Parse Data      */
/* ==================== */

qint64 ClubContainer::findPositionInFile(QTextStream &in)
{
    QString line;
    while (in.readLineInto(&line)) { // The standings table begins with "Pos     Team"
        if (line.startsWith(QStringLiteral("Pos     Team"), Qt::CaseInsensitive))
            return in.pos();
    }

    return no_result_;
}
bool stats::ClubContainer::parseFile(const QString &file_path)
{
    QFile f(file_path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical().noquote() << QStringLiteral("Unable to open club stats file: ") << file_path;
        return false;
    }

    QTextStream in(&f);

    // Locate the league standings/stats and parse each row
    while (findPositionInFile(in) != no_result_)
        parseLeagueStandings(in);

    // Sort the data
    std::sort(/*std::execution::par,*/ data_.begin(), data_.end(), Club::sortByPerformance);

    qInfo().noquote() << QStringLiteral("Total clubs parsed: %L1").arg(data_.size());
    return true;
}

void ClubContainer::parseLeagueStandings(QTextStream &in)
{
    QString line;
    while (in.readLineInto(&line)) {
        if (line.startsWith(QStringLiteral("---"), Qt::CaseInsensitive))
            continue; // Ignore end place separators
        else if (line.isEmpty())
            return; // A blank line denotes the end of the standings

        auto club{std::make_shared<Club>()};

        if (club->parse(line))
            data_.push_back(std::move(club));
    }
}
