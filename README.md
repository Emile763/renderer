# Global Description
This project aims to create from scratch a simple C++ library for rendering objects in 2D, 3D and maybe 4D,5D,6D...  
The rendering is done using OpenGL.

# Current State
2D and 3D models can be scaled, rotated, positioned, and rendered with or without textures.
2D and 3D cameras can be created to move around. 

https://github.com/user-attachments/assets/c0c36733-a0ec-4bae-b521-f67eb7b0c9c1

# Todo
- Render to a texture instead of the screen, which can be useful for post-processing, or mirrors and portals.
- Load animated models with rigs (2D and 3D)

# How To Compile
At the root of the repository:
```console
mkdir build
cd build
cmake ..
cmake --build .
# To launch
./RenderApp
```

# How To Use
The current app draws a cube, Blender’s Suzanne monkey, a jar, and a textured apple in 3D. A 2D apple moves around the screen following an infinite form path.  
The camera can be rotated using the mouse position.  
The camera can be moved using <kbd>z</kbd><kbd>q</kbd><kbd>s</kbd><kbd>d</kbd><kbd>Space</kbd><kbd>LShift</kbd>.
