#ifndef SKATER_H
#define SKATER_H

// Application headers
#include "base_class/player.h"
#include "ice_time.h"

// Xlsx headers
namespace QXlsx {
class Document;
}

// Qt headers
#include <memory>

namespace stats {

class ClubContainer;

/*! The Skater class contains statistics for a skater */
class Skater : public Player
{
public:
    Skater();

    //! File i/o */
    /*! Write the skater stats row to the spreadsheet */
    void write(QXlsx::Document &xlsx, const qint32 row) const override;

    //! Get data */
    /*! Get club pointer */
    /*! Get column heading description */
    static QString columnDescription(const qint32 xlsx_column);
    /*! Get column heading name */
    static QString columnName(const qint32 xlsx_column);

    //! Parse data */
    /*! Parse skater stats from a line of a text file */
    bool parse(QString &line,
               const ClubContainer *clubs,
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

private:
    // Data
    quint16 g_{0};
    quint16 a_{0};
    quint16 pts_{0};
    qint16 plus_minus_{0};
    quint16 pim_{0};
    quint16 ppg_{0};
    quint16 ppa_{0};
    quint16 ppp_{0};
    quint16 shg_{0};
    quint16 sha_{0};
    quint16 shp_{0};
    quint16 gwg_{0};
    quint16 gt_{0};
    quint16 fg_{0};
    quint16 en_{0};
    quint16 sog_{0};
    double sh_{0.0};
    quint16 ht_{0};
    quint16 ga_{0};
    quint16 ta_{0};
    double fo_{0.0};
    quint16 sb_{0};
    quint16 two_min_pen_{0};
    quint16 five_min_pen_{0};
    quint16 mi_{0};
    quint16 ma_{0};
    quint16 gm_{0};
    quint16 fi_{0};
    quint16 fw_{0};
    IceTime atoi_;
    IceTime appt_;
    IceTime apkt_;
    quint16 plus_{0};
    quint16 minus_{0};
    quint16 fs_{0};
    double average_rating_{0.0};

    enum ENUM_SKATER_STATS_INPUT_COLUMNS {
        IN_G = FIRST_BASE_CLASS_INPUT_COLUMN,
        IN_A,
        IN_PTS,
        IN_PLUS_MINUS,
        IN_PIM,
        IN_PPG,
        IN_PPA,
        IN_PPP,
        IN_SHG,
        IN_SHA,
        IN_SHP,
        IN_GWG,
        IN_GT,
        IN_FG,
        IN_EN,
        IN_SOG,
        IN_SH,
        IN_HT,
        IN_GA,
        IN_TA,
        IN_FO,
        IN_SB,
        IN_TWO_MIN_PEN,
        IN_FIVE_MIN_PEN,
        IN_MI,
        IN_MA,
        IN_GM,
        IN_FI,
        IN_FW,
        IN_ATOI,
        IN_APPT,
        IN_APKT,
        IN_PLUS,
        IN_MINUS,
        IN_FS,
        IN_AVG_RATING,
        INPUT_COLUMNS_COUNT
    };
};
} // namespace stats

#endif // SKATER_H
