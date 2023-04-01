#ifndef CLUB_H
#define CLUB_H

// Application headers
#include "base_class/schema_base_class.h"

// Xlsx headers
namespace QXlsx {
class Document;
}

// Qt headers
#include <memory>

namespace stats {
/*! The Club class contains statistics for a club */
class Club : public SchemaBaseClass
{
public:
    /*! Constructor */
    Club();

    //! File i/o */
    /*! Write the club stats row to the spreadsheet */
    void write(QXlsx::Document &xlsx, const qint32 row) const override;

    //! Get data
    /*! Get column heading name */
    static QString columnName(const qint32 xlsx_column);

    //! Get stats data */
    inline qint16 goalDifference() const { return goals_for_ - goals_against_; }

    //! Parse data */
    /*! Parse club stats from a line of a text file */
    bool parse(QString &line);

    //! Sort data */
    /*! Sort two Club items */
    static bool sortByName(const std::shared_ptr<Club> &lhs, const std::shared_ptr<Club> &rhs);
    static bool sortByPerformance(const std::shared_ptr<Club> &lhs,
                                  const std::shared_ptr<Club> &rhs);

    enum ENUM_STATS_OUTPUT_COLUMNS {
        OUT_NAME = 1, // Xlsx indexes start at 1
        OUT_GP,
        OUT_W,
        OUT_L,
        OUT_T,
        OUT_PCT,
        OUT_GF,
        OUT_GA,
        OUT_PTS,
        OUTPUT_COLUMNS_END_POS
    };

private:
    // Data
    quint16 games_played_{0};
    quint16 won_{0};
    quint16 lost_{0};
    quint16 tied_{0};
    double win_pct_{0.0};
    quint16 goals_for_{0};
    quint16 goals_against_{0};
    quint16 points_{0};

    enum ENUM_TEXT_INPUT_LINE_FLAGS {
        CLUB_NAME_POSITION = 8,
        CLUB_NAME_SIZE = 25,
    };

    enum ENUM_STATS_INPUT_COLUMNS {
        IN_GP,
        IN_W,
        IN_L,
        IN_T,
        IN_PCT,
        IN_GF,
        IN_GA,
        IN_PTS,
        INPUT_COLUMNS_COUNT
    };
};
} // namespace stats

#endif //!CLUB_H
