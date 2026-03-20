#include <monte_carlo/models/action.h>
#include <monte_carlo/models/node.h>
#include <utility>

using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::models::Action;

double Action::upper_confidence_bound(const int c) const
{
    if (const auto sp = target())
    {
        return sp->upper_confidence_bound(c);
    }

    return 0.0;
}





