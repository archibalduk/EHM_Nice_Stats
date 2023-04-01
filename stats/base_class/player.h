#ifndef PLAYER_H
#define PLAYER_H

// Application headers
#include "schema_base_class.h"

namespace stats {
class Club;

/*! The Player class is the base class for skater/goalie statistics */
class Player : public SchemaBaseClass
{
public:
    Player();

    //! Get data */
    /*! Get club pointer */
    std::shared_ptr<Club> club() const;

protected:
    // Data
    quint16 gp_{0};
    std::weak_ptr<Club> club_;
    QString pos_;

    enum ENUM_BASE_CLASS_STATS_INPUT_COLUMNS {
        IN_NAME,
        IN_CLUB,
        IN_POS,
        IN_GP,
        FIRST_BASE_CLASS_INPUT_COLUMN
    };
};
} // namespace stats
#endif // PLAYER_H
