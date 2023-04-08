#include "club_container.h"

// Xlsx headers
#include "xlsxchart.h"
#include "xlsxdocument.h"

// Qt headers
#include <QDebug>
//#include <execution>
#include <QFile>
#include <QHash>
#include <QTextStream>

using namespace stats;

ClubContainer::ClubContainer()
{
    initColumnData();
}

ClubContainer::~ClubContainer() {}

/* ===================== */
/*      Column Data      */
/* ===================== */

qint32 ClubContainer::columnEndPos() const
{
    return Club::DATA_COLUMNS_END_POS;
}

void ClubContainer::initColumnData()
{
    addColumn(ColumnData(Club::NAME, QStringLiteral("Name")));
    addColumn(ColumnData(Club::GP, QStringLiteral("GP"), QStringLiteral("Games played")));
    addColumn(ColumnData(Club::W, QStringLiteral("W"), QStringLiteral("Won")));
    addColumn(ColumnData(Club::L, QStringLiteral("L"), QStringLiteral("Lost")));
    addColumn(ColumnData(Club::T, QStringLiteral("T"), QStringLiteral("Tied")));
    addColumn(ColumnData(Club::O_SL,
                         QStringLiteral("OT/SO L"),
                         QStringLiteral("Overtime / Shoot-out losses")));
    addColumn(ColumnData(Club::PCT, QStringLiteral("PCT"), QStringLiteral("Win percentage")));
    addColumn(ColumnData(Club::GF, QStringLiteral("GF"), QStringLiteral("Goals for/scored")));
    addColumn(ColumnData(Club::GA, QStringLiteral("GA"), QStringLiteral("Goals against")));
    addColumn(ColumnData(Club::PTS, QStringLiteral("Pts"), QStringLiteral("Points")));
    addColumn(ColumnData(Club::DEF_TTOI,
                         QStringLiteral("Def TTOI"),
                         QStringLiteral("Defenceman total time on ice")));
    addColumn(ColumnData(Club::DEF_AVERAGE_GOALS_PER_MINUTE,
                         QStringLiteral("Def avg G/min"),
                         QStringLiteral("Defenceman average goals per minute")));
    addColumn(ColumnData(Club::DEF_AVERAGE_ASSISTS_PER_MINUTE,
                         QStringLiteral("Def avg A/min"),
                         QStringLiteral("Defenceman average assists per minute")));
    addColumn(ColumnData(Club::DEF_AVERAGE_PIM_PER_MINUTE,
                         QStringLiteral("Def avg PIM/min"),
                         QStringLiteral("Defenceman average PIM per minute")));
    addColumn(ColumnData(Club::DEF_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE,
                         QStringLiteral("Def avg SOG/min"),
                         QStringLiteral("Defenceman average shots on goal per minute")));
    addColumn(ColumnData(Club::DEF_AVERAGE_SHOTS_BLOCKED_PER_MINUTE,
                         QStringLiteral("Def avg SB/min"),
                         QStringLiteral("Defenceman average shots blocked per minute")));
    addColumn(ColumnData(Club::FWD_TTOI,
                         QStringLiteral("Fwd TTOI"),
                         QStringLiteral("Forward total time on ice")));
    addColumn(ColumnData(Club::FWD_AVERAGE_GOALS_PER_MINUTE,
                         QStringLiteral("Fwd avg G/min"),
                         QStringLiteral("Forward average goals per minute")));
    addColumn(ColumnData(Club::FWD_AVERAGE_ASSISTS_PER_MINUTE,
                         QStringLiteral("Fwd avg A/min"),
                         QStringLiteral("Forward average assists per minute")));
    addColumn(ColumnData(Club::FWD_AVERAGE_PIM_PER_MINUTE,
                         QStringLiteral("Fwd avg PIM/min"),
                         QStringLiteral("Forward average PIM per minute")));
    addColumn(ColumnData(Club::FWD_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE,
                         QStringLiteral("Fwd avg SOG/min"),
                         QStringLiteral("Forward average shots on goal per minute")));
    addColumn(ColumnData(Club::FWD_AVERAGE_SHOTS_BLOCKED_PER_MINUTE,
                         QStringLiteral("Fwd avg SB/min"),
                         QStringLiteral("Forward average shots blocked per minute")));
}

/* ================== */
/*      File i/o      */
/* ================== */

void ClubContainer::writeToSpreadsheet(QXlsx::Document &xlsx)
{
    // Club stats
    xlsx.addSheet(QStringLiteral("Club stats"));

    auto row{writeHeaderRow(xlsx)};

    for (const auto &itr : data_)
        itr->write(xlsx, row++);

    //addQualityScatterChart(xlsx);
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

/* ======================= */
/*      Graphs/Charts      */
/* ======================= */

void ClubContainer::addQualityScatterChart(QXlsx::Document &xlsx)
{
    // TODO
    const auto row_buffer{2};
    const auto row{xlsx.currentWorksheet()->dimension().lastRow() + row_buffer};
    const auto column{1};

    auto chart{xlsx.insertChart(row, column, QSize(300, 300))};
    chart->setChartType(QXlsx::Chart::CT_ScatterChart);
    //chart->addSeries(QXlsx::CellRange("G2:G19"));
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

    // Parse the league details
    parseLeagueDetails(in);

    // Locate the league standings/stats and parse each row
    while (findPositionInFile(in) != no_result_)
        parseLeagueStandings(in);

    // Sort the data
    std::sort(/*std::execution::par,*/ data_.begin(), data_.end(), Club::sortByPerformance);

    qInfo().noquote() << QStringLiteral("Total clubs parsed: %L1").arg(data_.size());
    return true;
}

void ClubContainer::parseLeagueDetails(QTextStream &in)
{
    in.seek(0);

    // League name and in-game date are on the second line
    in.readLine(); // Skip first line
    league_name_and_date_ = in.readLine().simplified();

    // Season can be found immediately prior to the first instance of "xxxx-xx Tables"
    QString line;
    const qint32 season_length = 7; // xxxx-xx = 7 characters long
    while (in.readLineInto(&line)) {
        if (line.contains("Tables") && line.size() > season_length) {
            season_ = line.simplified().chopped(season_length);
        }
    }

    in.seek(0); // Reset to the front of the file
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
