## Punchbak Simulation with OpenGL
In this project a basic punchbag simulation is created with OpenGL.

![](https://raw.githubusercontent.com/cornetto/PunchbagOpenGL/master/wiki/punchbag-simulator.jpg)


### Specifications
* In the environment, there is a punchbag and two arms that moves with the camera on a large rectangular ground.

* The punchbag hangs on a vertical support that consist of a vertical cylinder pole and a horizontal cylinder pole on top of the vertical one. The punchbag consists of a vertical cone and a sphere that resides at the bottom of the cone.

* Arms of the boxer consists of a cylinder and a red sphere (boxing glove) on the edge of the cylinder. There are 2 arms which reside in the bottom right and bottom left of the camera. Arms move with the camera so that arm positions with respect to the camera do not change. Arm direction is always same with the viewing direction.

* Camera travels in the environment with keyboard keys with a constant height over the rectangular ground. That means camera will move with respect to the projection of the viewing direction on the ground. **"w"** key moves the camera to the projection of viewing direction. **"a"** key moves the camera to the left of the projection of viewing direction. **"d"** key moves the camera to the right of the projection of viewing direction. **"s"** key moves the camera to the back of the projection of viewing direction. Camera movement continues as long as the keys are pressed. Up and viewing vector of the camera do not change by pressing these traveling buttons.

* Camera viewing direction changes with the mouse movement. Moving mouse forward turns the viewing vector up. Moving mouse backward turns the viewing vector down. Moving mouse left turns the viewing vector left. Moving mouse right turns the viewing vector right. Camera position does not change with mouse movement.


* Arms move with the viewing direction with mouse keys. Pressing left mouse button moves the left arm forward and backward once with constant speed in viewing direction. Pressing right mouse button moves the right arm forward and backward once with constant speed in viewing direction.

* Punchbag swings in the punch direction if the punch button is pressed and the moving glove touches to the punchbag. Punchbag swings forward and backward once with respect to punch direction.

* Punchbag height changes with keys if the camera near to the punchbag vertical pole. You can arrange the maximum distance that punchbag height can be changed. Near the punchbag, pressing **"z"** button reduces the vertical pole size in a constant speed while pressing **"x"** button extends the height of vertical pole. The pole shrinks or extends as long as **"z"** or **"x"** button pressed respectively

* The program handles multiple keys at the same time. The program exits with Esc key.

### Compile and Run
With the help of makefile, you can build and run code with the following lines:
```
make
./punchbag
```
