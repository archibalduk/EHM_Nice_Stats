#ifndef PLAYER_H
#define PLAYER_H

// Application headers
#include "schema_base_class.h"

namespace stats {
class Club;

/*!
 * \brief The Player class is the base class for skater/goalie statistics
 */
class Player : public SchemaBaseClass
{
public:
    Player();

    // Add stats
    /*!
     * \brief Add add statistic as a running total
     * \details I.e. this will add to, and not substitute, the statistic value.
     * \param column Column id
     * \param value Statstic value
     */
    virtual void add(const qint32 column, const QVariant &value) = 0;

    // Get data
    /*!
     * \brief Returns a pointer to the player's club
     * \return shared_ptr to the player's club
     */
    std::shared_ptr<Club> club() const;
    /*!
     * \brief Returns the name of the player's club
     * \return name of the player's club
     */
    QString clubName() const;

    // Get data: positions
    /*!
     * \brief Returns whether the player is a goalie
     * \return whether a goalie
     */
    bool isGoalie() const;
    /*!
     * \brief Returns whether the player is a defenceman
     * \return whether a defenceman
     */
    bool isDefenceman() const;
    /*!
     * \brief Returns whether the player is a forward
     * \return whether a forward
     */
    bool isForward() const;

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
