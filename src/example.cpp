#include <iostream>
#include <BTpp/behavior_tree.h>



class MyCondition : public BT::ConditionNode
{
public:
    MyCondition(std::string name);
    ~MyCondition();
    BT::ReturnStatus Tick();
};

MyCondition::MyCondition(std::string name) : BT::ConditionNode::ConditionNode(name)
{

}

BT::ReturnStatus MyCondition::Tick()
{
    std::cout << "The Condition is true" << std::endl;

    return BT::SUCCESS;
}


class MyAction : public BT::ActionNode
{
public:
    MyAction(std::string name);
    ~MyAction();
    BT::ReturnStatus Tick();
    void Halt();
};

MyAction::MyAction(std::string name) : ActionNode::ActionNode(name)
{

}


BT::ReturnStatus MyAction::Tick()
{
    std::cout << "The Action is doing some operations" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (is_halted())
    {
        return BT::HALTED;
    }

    std::cout << "The Action is doing some others operations" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (is_halted())
    {
        return BT::HALTED;
    }

    std::cout << "The Action is doing more operations" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (is_halted())
    {
        return BT::HALTED;
    }

    std::cout << "The Action has succeeded" << std::endl;
    return BT::SUCCESS;
}

void MyAction::Halt()
{

}


int main(int argc, char *argv[])
{

    BT::SequenceNode* seq = new BT::SequenceNode("Sequence");
    MyCondition* my_con_1 = new MyCondition("Condition");
    MyAction* my_act_1 = new MyAction("Action");
    int tick_time_milliseconds = 1000;

    seq->AddChild(my_con_1);
    seq->AddChild(my_act_1);

    Execute(seq, tick_time_milliseconds);

    return 0;
}
