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
