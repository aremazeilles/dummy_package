# dummy_package

## General description of the package

<!--- protected region package description begin -->
Dummy node implementation
<!--- protected region package description end -->

<!--- todo How to handle the image generation -->
<!--- <img src="./model/dummy_node.png" width="300px" />-->

## Node: dummy_node

Update frequency: 20 Hz.

This node is using `\tf` to broadcast transforms.

<!--- protected region dummy_node begin -->
<!--- protected region dummy_node end -->

### Static Parameters

All static parameters can be set through the command line:

```shell
rosrun dummy_package dummy_node [param_name]:=[new_value]
```

`my_static_param` *(std::string, default: "staticvalue")*
<!--- protected region param my_static_param begin -->
my_static_param
<!--- protected region param my_static_param end -->

### Dynamic Parameters

All dynamic parameters can be set through the command line:

```shell
rosrun dummy_package dummy_node _[param_name]:=[new_value]
```

`my_dyn_param` *(std::string, default: "SuperString")*
<!--- protected region param my_dyn_param begin -->
my_dyn_param
<!--- protected region param my_dyn_param end -->

### Published Topics

A topic can be remapped from the command line:

```shell
rosrun dummy_package dummy_node [old_name]:=[new_name]
```

`my_pub` *(std_msgs::Bool)*
<!--- protected region publisher my_pub begin -->
my_pub
<!--- protected region publisher my_pub end -->

### Subscribed Topics

A topic can be remapped from the command line:

```shell
rosrun dummy_package dummy_node [old_name]:=[new_name]
```

`my_sub` *(std_msgs::Float32)*
<!--- protected region my_sub begin -->
<!--- protected region my_sub end -->

### Services proposed

Any service name can be adjusted using the ROS remapping functionality:

```shell
rosrun dummy_package dummy_node [old_name]:=[new_name]
```

`my_service` *(std_srvs::SetBool)*
<!--- protected region service server my_service begin -->
my_service
<!--- protected region service server my_service end -->

### Action proposed

A simple action launched can be obtained with:

```shell
rosrun actionlib axclient.py /do_action
```

`my_action` *(actionlib::Test)*
<!--- protected region action server my_action begin -->
complexaction
<!--- protected region action server my_action end -->

### Direct Publishers

These publishers are not handled through the update loop.
Their publication frequency is thus unknown

`my_direct_pub` *(std_msgs::Bool)*
<!--- protected region direct publisher my_direct_pub begin -->
my_direct_pub
<!--- protected region direct publisher my_direct_pub end -->

### Direct Subscribers

These subscribers are not handled through the update loop.
The subscription handler is triggered as soon as a message arrives.

`my_direct_sub` *(std_msgs::String)*
<!--- protected region direct subscriber my_direct_sub begin -->
my_direct_sub
<!--- protected region direct subscriber my_direct_sub end -->

---

*Package generated with the [ROS Package Generator](https://github.com/tecnalia-advancedmanufacturing-robotics/ros_pkg_gen).*
