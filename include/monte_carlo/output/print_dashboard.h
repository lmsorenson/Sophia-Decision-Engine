#ifndef PRINT_DASHBOARD_H
#define PRINT_DASHBOARD_H

#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::output
{
    /**
     * @class Dashboard
     */
    class Dashboard
    {
    public:
        static void print(
            const node_ptr& node,
            const logger_ptr& logger = nullptr);

    };
}

#endif //PRINT_DASHBOARD_H
