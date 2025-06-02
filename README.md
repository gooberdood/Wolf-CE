# Wolf-CE
Wolfenstein 3D for the TI-84+ CE graphing calculator. Made by ID-Software, rewritten by gooberdev

Currently just a crappy unfinished raycasting engine that doesn't render properly, made it in a few hours for a school project.

I plan on developing this further eventually but for now it will stand as a testament to how bad I am at finishing projects.

To compile, use the CE C Toolchain and navigate to src/gfx. Type in "convimg" (sans quotes) to convert the sprites and palettes into an appvar, and then back out to the makefile and type "make".

All it does is render the floor, ceiling, and sometimes a wall if you try hard enough. You can turn in full 360 degrees and move on the 2d plane in any direction. If you would like it to run faster and get rid of the walls you can comment parts of the rayMath() function out. The target was 30 frames per second but as of now it runs at about 3-4 seconds per frame, sometimes more. It's rather tragic.

Generally speaking there isn't really a reason you would actually want to run this as it's nothing impressive, as of now I am moreso uploading this for the sake of having my source code open and for people to help out.
