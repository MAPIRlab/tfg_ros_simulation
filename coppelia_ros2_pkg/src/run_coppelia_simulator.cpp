#include <rclcpp/rclcpp.hpp>
#include <stdlib.h>
#include <string>


class CoppeliaSim: public rclcpp::Node
{
  public:
    CoppeliaSim()
    : Node("coppelia_simulator")
    {
      //Read parameters and set default values
      this->declare_parameter<std::string>("coppelia_root_dir", "");
      this->get_parameter("coppelia_root_dir", coppelia_dir);

      this->declare_parameter<std::string>("coppelia_scene_path", "");
      this->get_parameter("coppelia_scene_path", coppelia_scene);
      
      this->declare_parameter<bool>("coppelia_headless", false);
      this->get_parameter("coppelia_headless", coppelia_headless);
      
    }
    
    void run()
    {
      //system("~/CoppeliaSim_Edu_V4_3_0_rev10_Ubuntu20_04/coppeliaSim.sh -s ~/tfg_ros_simulation_ws/src/Coppelia_scenes/ros2_mobile_robot.ttt");
      if (coppelia_headless)
      {
        system( (coppelia_dir+"/coppeliaSim.sh -h -s "+ coppelia_scene).c_str() );
      }
      else
      {
        system( (coppelia_dir+"/coppeliaSim.sh -s "+ coppelia_scene).c_str() );
      }
    }
    
  private:
    std::string coppelia_dir, coppelia_scene;
    bool coppelia_headless;
};

      
// MAIN
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  
  //create object
  std::shared_ptr<CoppeliaSim> myNode = std::make_shared<CoppeliaSim>();
  myNode->run();

  rclcpp::shutdown();
  return 0;
  
}




