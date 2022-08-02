# Biconnected_Components

###To run this package 
1. Create a new workspace (or you can the one you already have)
    ```
    mkdir -p ~/dev_ws/src
    ```
2. Clone the two packages to the src file in your workspace
3. Build the workspace and source it as usual
    ```
    colcon build
    ```
4. Run server node
    ```
    ros2 run biconnected_components server
    ```
5. Run client node
    ```
    ros2 run biconnected_components client "A-B A-C B-E E-C E-D E-H D-F D-G G-H"
    ```
