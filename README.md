# tfg_ros_simulation
Este repositorio contiene una configuración de pkgs ROS diseñado para trabajar desde casa con un robot autónomo en Simulación. Es ideal para trabajos TFG/TFM que deben desarrollar su código en casa y posteriormente probarlo en un robot real. Se incluye el simulador (Stage), pkgs de navegación autónoma y los archivos de configuración necesario para comenzar.

## Navegación Autónoma (Move Base)
Para poder disponer de un robot autónomo, capaz de navegar sin chocarse dentro de un entorno simulado, contamos con el pkg ROS "MoveBase". Este pkg fundamental de ROS, require a su vez de otros pkgs adicionales. Para su instlación, ejecuta los siguientes comandos (Nota, estos comandos están esritos para la versión "noetic" de ROS, actualizalos a la versión que estés usando):

> sudo apt install ros-noetic-fake-localization  
  sudo apt install ros-noetic-map-server  
  sudo apt install ros-noetic-dwa-local-planner  
  sudo apt install ros-noetic-move-base  
  sudo apt install ros-noetic-gmapping  
  sudo apt install ros-noetic-robot-state-publisher

## Descarga de este Repositorio
Una vez instalados los pkgs ROS del punto anterior, es necesario descargar este repositorio en nuestro "workspace/src". Lo colocaremos junto con nuestros pkgs ROS que tengamos que desarrollar para nuestro trabajo TFG/TFM. Una vez descargado, debemos compilar su contenido empleando "catkin_make" (o con el IDE de preferencia, eg Kdevelop)

Este repositorio contiene a su vez una serie de *launch-files* preconfigurados para lanzar un setup en el que se dispone de un robot 100% autónomo en un entorno simulado con el simulador STAGE-ROS. Para "lanzar" dicho entorno tan solo tenemos que ejecutar:
> roslaunch missions_pkg main.launch

Si todo está bien configurado, deberán ejecutarse una serie de nodos que habilitan la navegación, así como Stage para la simulación y RVIZ para poder visualizar topics y el entorno como tal. Por ejemplo, puedes probar el botón que tiene RVIZ llamado "2D Nav Goal" con el que puedes mandar al robot a moverse a un punto del mapa con el ratón y de forma autónoma buscará el camino hasta ese punto y lo ejecutará.

## Comandos Navegación por Código
Una vez que ya tengas listo la instalación de este repositorio y compruebes que el robot ya navega de forma autónoma, nos queda ver como hacer estas peticiones de navegación desde nuestro código, es decir, desde nuestro nodo ROS. Para ello tendremos que usar un cliente de Acciones, haciendo peticiones al pkg MoveBase que hemos visto anteriormente. Se facilita un enlace a modo de ejemplo, recordando que la comunidad ROS es muy grande y hay muchos foros y ejemplos con soluciones similares:
[http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals)

