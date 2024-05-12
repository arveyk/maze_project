<h1><-- The Maze Project --></h1>

In this project I am implementing Raycasting semi-3D rendering technique to make a sample game or program.
The implementation is in C and a special library SDL2 will be used as well.

<h3>Why Implement in C?</h3>
C is a simple language to study but difficult to program with. It requires a certain kind of discipline, especially with pointers (Those pointy things can be dangerouse!). So it is difficult to implement at many levels but the encouter is worth it since I've learned a lot. Using it helps in understanding program flow and logic

<h3>Raycasting</h3>
It utilizes a library called SDL (simple Multimedia Library) version 2

The technique being used to create 3D images is raycasting. It is not a true 3D renderer thus but is a very fast technique
and require little resource to render since calculations are only done for vertical lines.

The most well known game that applied this technique is Wolfenstein 3D.
Raycasting is different from raytracing is a true 3D rendering technique.

<b><h3>The Basic Idea </h3></b>
<br>
The basic idea of raycasting is as follows: the map is a 2D square grid, and each square can either be 0 (= no wall), or a positive value (= a wall with a certain color or texture).

For every x of the screen (i.e. for every vertical stripe of the screen), send out a ray that starts at the player location and with a direction that depends on both the player's looking direction, and the x-coordinate of the screen. Then, let this ray move forward on the 2D map, until it hits a map square that is a wall. 
If it hit a wall, calculate the distance of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen: the further away the wall, the smaller it's on screen, and the closer, the higher it appears to be. These are all 2D calculations. 

<h3>Algorithm Used</h3>
Getting the distance from the player to the wall is the most important calculation since it determines how high the wall is to
be projected and the ceiling and floor ought to be drawn. One fast algorithm used is based on DDA (Digital Differential Analysis). After a wall that is hit is found calculations are stopped and the wall projected.

The angle of the viewer is also an important consideration. Euclidean angles can be used to represent the players direction. Another method employed is using vectors and a camera.

<img src="images/raycastingcamera.gif" alt="Raycasting">Raycasting</img>

<h3><i>Inspiration</i></h3>
This raycasting project is a good challenge since it incorporates mathematics and programming. Also creating a 3D rendering program is a step toward creating fully functioning full scale programs.

<h3>Challenges</h3>
So far I have managed to project an image on the SDL window.

<h3> Technologies Used</h3>
<ul>
<li>C Programming Language</li>
<li>SDL version2</li>
</ul>

