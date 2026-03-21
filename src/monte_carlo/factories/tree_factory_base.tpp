#include <monte_carlo/factories/tree_factory_base.h>
#include <monte_carlo/common_aliases.h> // Centralized aliases

#include <utility>

namespace sophia::monte_carlo::factories
{

template<typename TState, typename TChange>
TreeFactoryBase<TState, TChange>::TreeFactoryBase(logger_ptr logger)
: m_logger_(std::move(logger))
{
}

} // namespace sophia::monte_carlo::models
