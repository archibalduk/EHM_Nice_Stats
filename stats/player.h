#ifndef PLAYER_H
#define PLAYER_H

// Application headers
#include "base_class/schema_base_class.h"
#include "player/skater_stats.h"

// Xlsx headers
namespace QXlsx {
class Document;
}

// Qt headers
#include <QString>
#include <memory>
#include <vector>
class QTextStream;

namespace stats {

class Club;

/*! The Player class contains statistics for a player */
class Player : public SchemaBaseClass
{
public:
    Player();

    //! File i/o */
    /*! Write the player stats to the spreadsheet */
    static void writeToSpreadsheet(QXlsx::Document &xlsx,
                                   std::vector<Player> &data,
                                   const std::shared_ptr<Club> &club);

    //! Get data
    /*! Get column heading description */
    static QString columnDescription(const qint32 xlsx_column);

    //! Parse data */
    /*! Open and parse a player stats file */
    static bool parseFile(const QString &file_path,
                          std::vector<Player> &data,
                          const std::vector<std::shared_ptr<Club>> &clubs);

private:
    // Data
    quint16 gp_{0};
    std::weak_ptr<Club> club_;
    QString pos_;
    SkaterStats skater_stats_;

    //! Get data
    /*! Get column heading name */
    static QString columnName(const qint32 xlsx_column);

    //! File i/o */
    /*! Write the players stats row to the spreadsheet */
    void write(QXlsx::Document &xlsx, const qint32 row) const override;

    //! Parse data */
    /*! Find the file position of the player stats section of a file */
    static qint64 findPlayerStats(QTextStream &in);
    /*! Parse player stats from a line of a text filee */
    bool parse(QString &line,
               const std::vector<std::shared_ptr<Club>> &clubs,
               const QHash<QString, qint32> &club_hash_table);

    enum ENUM_STATS_OUTPUT_COLUMNS {
        OUT_NAME = 1, // Xlsx indexes start at 1
        OUT_CLUB,
        OUT_POS,
        OUT_GP,
        OUT_G,
        OUT_A,
        OUT_PTS,
        OUT_PLUS_MINUS,
        OUT_PIM,
        OUT_PPG,
        OUT_PPA,
        OUT_PPP,
        OUT_SHG,
        OUT_SHA,
        OUT_SHP,
        OUT_GWG,
        OUT_GT,
        OUT_FG,
        OUT_EN,
        OUT_SOG,
        OUT_SH,
        OUT_HT,
        OUT_GA,
        OUT_TA,
        OUT_FO,
        OUT_SB,
        OUT_TWO_MIN_PEN,
        OUT_FIVE_MIN_PEN,
        OUT_MI,
        OUT_MA,
        OUT_GM,
        OUT_FI,
        OUT_FW,
        OUT_ATOI,
        OUT_APPT,
        OUT_APKT,
        OUT_PLUS,
        OUT_MINUS,
        OUT_FS,
        OUT_AVG_RATING,
        OUTPUT_COLUMNS_END_POS
    };
};
} // namespace stats

#endif // PLAYER_H
