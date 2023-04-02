#include "player.h"

// Application headers
#include "../club.h"

using namespace stats;

/* ================================= */
/*      Player Stats Base Class      */
/* ================================= */

Player::Player()
{

}

/* ================== */
/*      Get Data      */
/* ================== */

std::shared_ptr<Club> Player::club() const
{
    return club_.lock();
}

QString Player::clubName() const
{
    const auto c{club()};

    if (c)
        return c->name();

    return QStringLiteral("[No club]");
}

/* ============================= */
/*      Get Data: Positions      */
/* ============================= */

bool Player::isGoalie() const
{
    if (pos_.isEmpty())
        return false;

    return pos_.first(1).compare("G", Qt::CaseInsensitive) == 0;
}

bool Player::isDefenceman() const
{
    if (pos_.size() < 2)
        return false;

    return pos_.first(2).contains("D", Qt::CaseInsensitive);
}

bool Player::isForward() const
{
    if (pos_.size() < 2)
        return false;

    const auto pos{pos_.first(2)};

    return pos.contains("W", Qt::CaseInsensitive) || pos.contains("C", Qt::CaseInsensitive);
}
