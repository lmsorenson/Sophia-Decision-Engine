#ifndef MOCK_ACTION_H
#define MOCK_ACTION_H

#include <gmock/gmock.h>
#include <monte_carlo/models/action_base.h>

// namespace sophia::monte_carlo::models
// {
//     class Node;
// }

namespace sophia::monte_carlo::mocks
{
    using models::ActionBase;
    using models::Node;
    using factories::TreeFactoryBase;
    using std::shared_ptr;
    using std::string;

    class MockAction : public ActionBase<bool, int>
    {
    public:
        explicit MockAction(node_base_ptr<bool, int> source,
        const std::shared_ptr<const TreeFactoryBase<bool, int>> &factory);
        ~MockAction() override = default;

        MOCK_METHOD(string, name, (), (const, override));
        MOCK_METHOD(void, generate, (), (override));
        MOCK_METHOD(shared_ptr<Node>, target, (), (const, override));
        MOCK_METHOD(const_actor_ptr, actor, (), (const, override));

        void Setup( std::string name, const shared_ptr<Node> &node ) const;
    };
}

#endif //MOCK_ACTION_H
