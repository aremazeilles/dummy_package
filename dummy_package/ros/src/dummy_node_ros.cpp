/**
* @file dummy_node_ros.cpp
* @author Anthony Remazeilles
*
* Copyright (C) Tecnalia
*
* @brief Dummy node implementation
* @warning This file should not be edited
**/

// ROS includes
#include <ros/ros.h>

#include <actionlib/server/simple_action_server.h>
#include <actionlib/TestAction.h>
#include <dynamic_reconfigure/server.h>
#include <dummy_package/dummy_nodeConfig.h>

// ROS message & services includes
#include <std_msgs/Bool.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_srvs/SetBool.h>

// other includes
#include <dummy_node_common.cpp>

/**
 * @class DummyNodeROS
 * @brief Class handling the connection with the ROS world.
 * It also implement the node life-cycle, and access to object dummy_node-impl when appropriate
 */
class DummyNodeROS
{
public:
    ros::NodeHandle n_;
    ros::NodeHandle np_;

    dynamic_reconfigure::Server<dummy_package::dummy_nodeConfig> server;
    dynamic_reconfigure::Server<dummy_package::dummy_nodeConfig>::CallbackType f;
    ros::Publisher my_pub_;
    ros::Subscriber my_sub_;
    ros::ServiceServer my_service_;
    actionlib::SimpleActionServer<actionlib::TestAction> as_my_action_;

    DummyNodeData component_data_;
    // todo confirm it should be always defined, even if not used.
    DummyNodeConfig component_config_;
    DummyNodeImpl component_implementation_;

    /**
     * @brief object constructor.
     */
    DummyNodeROS() : np_("~")
                     , as_my_action_(n_, "my_action", boost::bind(&DummyNodeImpl::callback_my_action, &component_implementation_, _1, &as_my_action_), false)
    {
        // launching action servers
        as_my_action_.start();
        // preparing dynamic reconfigure mechanism
        f = boost::bind(&DummyNodeROS::configure_callback, this, _1, _2);
        server.setCallback(f);
        my_pub_ = n_.advertise<std_msgs::Bool>("my_pub", 1);
        // Handling direct publisher
        component_implementation_.passthrough.my_direct_pub = n_.advertise<std_msgs::Bool>("my_direct_pub", 1);
        // Handling direct subscriber
        component_implementation_.passthrough.my_direct_sub = n_.subscribe("my_direct_sub", 1, &DummyNodeImpl::directTopicCallback_my_direct_sub, &component_implementation_);
        my_sub_ = n_.subscribe("my_sub", 1, &DummyNodeROS::topicCallback_my_sub, this);
        // handling parameters from the parameter server
        np_.param("my_static_param", component_config_.my_static_param, (std::string)"staticvalue");
        // handling dynamic parameters
        np_.param("my_dyn_param", component_config_.my_dyn_param, (std::string)"SuperString");
        // handling Service servers
        my_service_ = n_.advertiseService<std_srvs::SetBool::Request , std_srvs::SetBool::Response>("my_service", boost::bind(&DummyNodeImpl::callback_my_service, &component_implementation_, _1, _2, &component_config_));
    }

    /**
     * @brief callback of a topic subscription handled through the update mechanism.
     * @param msg message received from ROS world
     */
    void topicCallback_my_sub(const std_msgs::Float32::ConstPtr& msg)
    {
        component_data_.in_my_sub = *msg;
        component_data_.in_my_sub_updated = true;
    }

    /**
     * @brief callback called when a dynamically reconfigurable parameter is changed
     * @param config the parameter structure to be updated
     * @param level level of parameters changed
     */
    void configure_callback(dummy_package::dummy_nodeConfig &config, uint32_t level)
    {
        component_config_.my_dyn_param = config.my_dyn_param;
    }

    /**
     * @brief configure function called after node creation.
     */
    void configure()
    {
        component_implementation_.configure(component_config_);
    }
    /**
     * @brief Activate all publishers handled through the update mechanism
     */
    void activate_all_output()
    {
        component_data_.out_my_pub_active = true;
    }
    /**
     * @brief State that all input has been read
     */
    void all_input_read()
    {
        component_data_.in_my_sub_updated = false;
     }
    /**
     * @brief core function periodically called.
     * calls implementation update, and handles potential publications
     * @param event access to the timer used for the looping
     */
    void update(const ros::TimerEvent& event)
    {
        activate_all_output();
        component_implementation_.update(component_data_, component_config_);
        all_input_read();
        if (component_data_.out_my_pub_active)
            my_pub_.publish(component_data_.out_my_pub);
    }
    /**
     * @brief object destructor
     */
    ~DummyNodeROS()
    {
    }
};

/**
 * @brief Main of the component. Create the object and launches the periodical call to upde method.
 */
int main(int argc, char** argv)
{

    ros::init(argc, argv, "dummy_node");

    ros::AsyncSpinner spinner(1);

    DummyNodeROS node;
    node.configure();

    ros::Timer timer = node.n_.createTimer(ros::Duration(1.0 / 20), &DummyNodeROS::update, &node);

    spinner.start();

    ros::waitForShutdown();

    return 0;
}
