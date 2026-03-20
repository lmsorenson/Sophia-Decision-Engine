#include <tic_tac_toe/models/state.h>
#include <tic_tac_toe/models/tic_tac_toe_simulation_result.h>
#include <monte_carlo/factories/tree_factory_interface.h>

#include <utility>
#include <tic_tac_toe/models/bot.h>
#include <tic_tac_toe/models/human.h>
#include <monte_carlo/models/action.h>
#include <monte_carlo/common_aliases.h>

using sophia::monte_carlo::tic_tac_toe::models::State;
using sophia::monte_carlo::tic_tac_toe::models::TicTacToeSimulationResult;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::const_factory_ptr;
using sophia::monte_carlo::const_simulation_result_ptr;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;

Symbol Alternate(const Symbol last_placed)
{
    switch (last_placed)
    {
        case Symbol::X: return Symbol::O;
        case Symbol::O:
        default:
        case Symbol::None: return Symbol::X;
    }
}

State::State(const string &name, const const_factory_ptr<GameState, Position> &tree_factory, const logger_ptr& logger)
    : NodeBase(name, GameState(nullptr, nullptr, nullptr), tree_factory, logger)
{
}

State::State(const std::string &name, GameState game_state,
    const std::shared_ptr<const TreeFactoryBase<GameState, Position>> &tree_factory, const logger_ptr& logger)
: NodeBase(name, std::move(game_state), tree_factory, logger)
{
}

std::vector<action_ptr> State::get_available_actions()
{
    std::vector<action_ptr> actions;

    const auto open_positions = m_state_.get_open_positions();
    const auto last_placed = m_state_.LastPlaced();
    const auto current_player = m_state_.CurrentPlayer();

    const Symbol new_state = Alternate(last_placed);

    for(const auto& position : open_positions)
    {
        const auto new_position = position->WithState(new_state);

        auto _this_ = std::static_pointer_cast<State>(shared_from_this());
        auto action = m_factory_->CreateAction(_this_, new_position, current_player);
        action->generate();
        actions.push_back(action);
    }

    return actions;
}

bool State::is_terminal_state() const
{
    if (m_state_.get_open_positions().empty())
        return true;

    if (auto winner = m_state_.Winner())
    {
        return true;
    }

    return false;
}

const_simulation_result_ptr State::value() const
{
    Symbol winner_symbol = Symbol::None;

    if (const auto winner = m_state_.Winner())
    {
        winner_symbol = winner->first;
    }

    return make_shared<TicTacToeSimulationResult>(winner_symbol);
}

double State::interpret_result(const const_simulation_result_ptr result) const
{
    if (!result) return 0.0;

    if (m_state_.GetTurnNumber() == 0)
        return 0.0;

    auto ttt_result = std::dynamic_pointer_cast<const TicTacToeSimulationResult>(result);
    if (!ttt_result) return 0.0;

    const Symbol winner = ttt_result->Winner();

    // we want the player who caused this move.
    if (const auto cp = m_state_.LastPlayer())
    {
        if (winner == Symbol::None)
        {
            return 1.0; // Draw
        }

        if (winner == cp->symbol())
        {
            return 2.0; // Win
        }

        return 0.0; // Loss
    }

    throw std::runtime_error("Last player not found!");
}

action_ptr State::select_action(const std::string action_name)
{
    std::string desired_name = action_name;
    for (char &c : desired_name)
    {
        c = static_cast<char>(std::toupper(c));
    }

    // 1. First, check if the action exists in already expanded children (m_child_action_)
    for (const auto& existing_child_action : m_child_action_)
    {
        if (existing_child_action->name() == desired_name)
        {
            if (m_logger_) m_logger_->debug("select_action: Found existing child action '{}'. Reusing.", desired_name);
            return existing_child_action;
        }
    }

    // 2. If not found in existing children, generate all possible actions for the current state.
    //    These will be new action/node pairs.
    const std::vector<sophia::monte_carlo::action_ptr> newly_generated_actions = get_available_actions();

    for (const auto& new_action : newly_generated_actions)
    {
        if (new_action->name() == desired_name)
        {
            if (m_logger_) m_logger_->debug("select_action: Generated new action '{}'. Adding to children and returning.", desired_name);
            // Add this newly generated action to our m_child_action_ list for future reuse
            m_child_action_.push_back(new_action);
            if (new_action->target()) {
                new_action->target()->set_parent(new_action);
            }
            return new_action;
        }
    }

    if (m_logger_) m_logger_->warn("select_action: No matching action found for name '{}'.", desired_name);
    return nullptr;
}

void State::print() const
{
    m_state_.print();
}
