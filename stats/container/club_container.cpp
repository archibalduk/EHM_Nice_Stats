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

ClubContainer::~ClubContainer() {}

/* ================== */
/*      File i/o      */
/* ================== */

void ClubContainer::writeToSpreadsheet(QXlsx::Document &xlsx)
{
    xlsx.addSheet(QStringLiteral("Club stats"));

    auto row{writeHeaderRow(xlsx)};

    for (const auto &itr : data_)
        itr->write(xlsx, row++);
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

/* =========================== */
/*      Get Data: Columns      */
/* =========================== */

qint32 ClubContainer::columnEndPos() const
{
    return Club::DATA_COLUMNS_END_POS;
}

QString ClubContainer::columnDescription(const qint32 column) const
{
    switch (column) {
    // Club stats
    case Club::NAME:
        return QStringLiteral("Club name");
    case Club::GP:
        return QStringLiteral("Games played");
    case Club::W:
        return QStringLiteral("Won");
    case Club::L:
        return QStringLiteral("Lost");
    case Club::T:
        return QStringLiteral("Tied");
    case Club::O_SL:
        return QStringLiteral("Overtime / Shoot-out losses");
    case Club::PCT:
        return QStringLiteral("Win percentage");
    case Club::GF:
        return QStringLiteral("Goals for/scored");
    case Club::GA:
        return QStringLiteral("Goals against");
    case Club::PTS:
        return QStringLiteral("Points");
    // Defencemen
    case Club::DEF_TTOI:
        return QStringLiteral("Defenceman total time on ice");
    case Club::DEF_AVERAGE_GOALS_PER_MINUTE:
        return QStringLiteral("Defenceman average goals per minute");
    case Club::DEF_AVERAGE_ASSISTS_PER_MINUTE:
        return QStringLiteral("Defenceman average assists per minute");
    case Club::DEF_AVERAGE_PIM_PER_MINUTE:
        return QStringLiteral("Defenceman average PIM per minute");
    case Club::DEF_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE:
        return QStringLiteral("Defenceman average shots on goal per minute");
    case Club::DEF_AVERAGE_SHOTS_BLOCKED_PER_MINUTE:
        return QStringLiteral("Defenceman average shots blocked per minute");
    // Forwards
    case Club::FWD_TTOI:
        return QStringLiteral("Forward total time on ice");
    case Club::FWD_AVERAGE_GOALS_PER_MINUTE:
        return QStringLiteral("Forward average goals per minute");
    case Club::FWD_AVERAGE_ASSISTS_PER_MINUTE:
        return QStringLiteral("Forward average assists per minute");
    case Club::FWD_AVERAGE_PIM_PER_MINUTE:
        return QStringLiteral("Forward average PIM per minute");
    case Club::FWD_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE:
        return QStringLiteral("Forward average shots on goal per minute");
    case Club::FWD_AVERAGE_SHOTS_BLOCKED_PER_MINUTE:
        return QStringLiteral("Forward average shots blocked per minute");
    // Default
    default:
        return QStringLiteral("*NO NAME*");
    }
}

QString ClubContainer::columnName(const qint32 column) const
{
    switch (column) {
    // Club stats
    case Club::NAME:
        return QStringLiteral("Name");
    case Club::GP:
        return QStringLiteral("GP");
    case Club::W:
        return QStringLiteral("W");
    case Club::L:
        return QStringLiteral("L");
    case Club::T:
        return QStringLiteral("T");
    case Club::O_SL:
        return QStringLiteral("OT/SO L");
    case Club::PCT:
        return QStringLiteral("PCT");
    case Club::GF:
        return QStringLiteral("GF");
    case Club::GA:
        return QStringLiteral("GA");
    case Club::PTS:
        return QStringLiteral("Pts");
    // Defencemen
    case Club::DEF_TTOI:
        return QStringLiteral("Def TTOI");
    case Club::DEF_AVERAGE_GOALS_PER_MINUTE:
        return QStringLiteral("Def avg G/min");
    case Club::DEF_AVERAGE_ASSISTS_PER_MINUTE:
        return QStringLiteral("Def avg A/min");
    case Club::DEF_AVERAGE_PIM_PER_MINUTE:
        return QStringLiteral("Def avg PIM/min");
    case Club::DEF_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE:
        return QStringLiteral("Def avg SOG/min");
    case Club::DEF_AVERAGE_SHOTS_BLOCKED_PER_MINUTE:
        return QStringLiteral("Def avg SB/min");
    // Forwards
    case Club::FWD_TTOI:
        return QStringLiteral("Fwd TTOI");
    case Club::FWD_AVERAGE_GOALS_PER_MINUTE:
        return QStringLiteral("Fwd avg G/min");
    case Club::FWD_AVERAGE_ASSISTS_PER_MINUTE:
        return QStringLiteral("Fwd avg A/min");
    case Club::FWD_AVERAGE_PIM_PER_MINUTE:
        return QStringLiteral("Fwd avg PIM/min");
    case Club::FWD_AVERAGE_SHOTS_ON_GOAL_PER_MINUTE:
        return QStringLiteral("Fwd avg SOG/min");
    case Club::FWD_AVERAGE_SHOTS_BLOCKED_PER_MINUTE:
        return QStringLiteral("Fwd avg SB/min");
    // Default
    default:
        return QStringLiteral("*NO NAME*");
    }
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
