# cub3D - 3D Maze Renderer

A Wolfenstein 3D-style maze renderer created using raycasting techniques. This project implements a first-person view renderer that creates a 3D perspective from a 2D map using raycasting principles, similar to the technique used in the original Wolfenstein 3D game.

## Overview

cub3D is a 3D maze visualization project that demonstrates fundamental computer graphics concepts through raycasting. The program reads a map configuration file and renders a navigable 3D environment where players can move and look around using keyboard/mouse controls.

## Technical Implementation

### Raycasting Explained

Raycasting is a rendering technique that creates a 3D perspective from a 2D map. Unlike full 3D rendering, raycasting is a simplified approach that:

1. Casts rays from the player's position
2. Calculates distance to walls for each vertical screen slice
3. Renders walls with height inversely proportional to distance

The main principles behind our implementation:

- **Ray Calculation**: For each vertical strip of the screen, a ray is cast from the player's position in the appropriate direction
- **Distance Calculation**: Using DDA (Digital Differential Analysis) algorithm to efficiently find wall intersections
- **Wall Rendering**: Walls are rendered as vertical strips, with height based on the perpendicular distance to avoid fisheye effect
- **Texture Mapping**: Wall textures are mapped based on where the ray hits the wall, creating the illusion of solid surfaces

### Key Features

- First-person perspective rendering
- Textured walls with different textures for each cardinal direction
- Configurable floor and ceiling colors
- Smooth window management
- Collision detection
- Clean exit handling

## Controls

- `W`, `S`: Move forward/backward
- `A`, `D`: Strafe left/right
- `←`, `→`: Rotate camera left/right
- `ESC`: Exit program
- Mouse movement: Rotate camera

## Map Configuration

Maps use `.cub` files with the following format:

```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

Where:

- `NO`, `SO`, `WE`, `EA`: Texture paths for each cardinal direction
- `F`, `C`: RGB colors for floor and ceiling
- Map characters:
  - `0`: Empty space
  - `1`: Wall
  - `N`, `S`, `E`, `W`: Player spawn position and orientation

## Dependencies

- MinilibX (graphics library)
- Math library (-lm)
- C compiler (cc)

## Running the project

```bash
# Clone the repo
git clone https://github.com/ElmehdiBennix/Cub3D_42.git
cd Cub3D_42

# Compile the project
make bonus

# Run with a map file
./cub3D maps/example.cub
```

## Error Handling

The program includes robust error checking for:

- Invalid map configurations
- Missing or invalid textures
- Unclosed maps
- Invalid color values
- Memory management
- File operations

## Technical Challenges and Solutions

During development, several technical challenges were addressed:

1. **Performance Optimization**:
   - Implemented efficient DDA algorithm for ray calculations
   - Optimized texture mapping calculations
   - Minimized floating-point operations where possible

2. **Memory Management**:
   - Careful texture loading and unloading
   - Proper cleanup of allocated resources
   - Prevention of memory leaks

3. **Precision Issues**:
   - Fixed fisheye effect using perpendicular distance calculation
   - Implemented precise collision detection
   - Handled floating-point precision in movement calculations

## Resources and References

For those interested in learning more about raycasting:

- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D's Engine Technology](https://users.atw.hu/wolf3d/)
- [Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
