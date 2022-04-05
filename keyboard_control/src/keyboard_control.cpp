#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71
#define KEYCODE_SPACE 0x20

//global VAR
int kfd = 0;
struct termios cooked, raw;
double linear_v, angular_v;
std::string publish_topic;
ros::Publisher twist_pub_;


void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


void keyLoop()
{
  double linear_, angular_;
  char c;
  bool dirty=false;
  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);
  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the robot.");
  puts("Press the space bar to stop the robot.");
  puts("Press q to stop the program");
  for(;;)
  {
    // get the next event from the keyboard
    if(read(kfd, &c, 1) < 0)
	  {
  	  perror("read():");
  	  exit(-1);
	  }
    linear_=angular_=0;
    ROS_DEBUG("value: 0x%02X\n", c);
    switch(c)
	  {
    	case KEYCODE_L:
    	  ROS_DEBUG("LEFT");
    	  angular_ = angular_v;
    	  linear_ = 0.0;
    	  dirty = true;
    	  break;
    	case KEYCODE_R:
    	  ROS_DEBUG("RIGHT");
    	  angular_ = -angular_v;
    	  linear_ = 0;
    	  dirty = true;
    	  break;
    	case KEYCODE_U:
    	  ROS_DEBUG("UP");
    	  linear_ = linear_v;
    	  angular_ = 0;
    	  dirty = true;
    	  break;
    	case KEYCODE_D:
    	  ROS_DEBUG("DOWN");
    	  linear_ = -linear_v;
    	  angular_ = 0;
    	  dirty = true;
    	  break;
    	case KEYCODE_SPACE:
    	  ROS_DEBUG("STOP");
    	  linear_ = 0;
    	  angular_ = 0;
    	  dirty = true;
    	  break;
      case KEYCODE_Q:
        ROS_DEBUG("QUIT");
        ROS_INFO_STREAM("You quit the teleop successfully");
        return;
        break;
  	}
    geometry_msgs::Twist twist;
    //twist.angular.z = a_scale_*angular_;
    //twist.linear.x = l_scale_*linear_;
    twist.angular.z = angular_;
    twist.linear.x = linear_;
    if(dirty ==true)
  	{
  	  twist_pub_.publish(twist);
  	  dirty=false;
  	}
  }
  return;
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "keyboard_control");
  ros::NodeHandle nh_;  
  ros::NodeHandle private_nh("~");
  

  //Read parameters or set default values
  linear_v = 0.1;	//m/s
  angular_v = 0.1;	//rad/s
  publish_topic ="cmd_vel";

  private_nh.param("linear_v", linear_v, linear_v);
  private_nh.param("angular_v", angular_v, angular_v);
  private_nh.param("publish_topic", publish_topic, publish_topic);

  ROS_INFO("[keyboard_controller] v=%.2f, w=%.2f, topic=%s",linear_v, angular_v, publish_topic.c_str());

  //Set publisher topic
  twist_pub_ = nh_.advertise<geometry_msgs::Twist>(publish_topic, 1);

  //Call main loop
  signal(SIGINT,quit);
  keyLoop();
  return(0);
}




