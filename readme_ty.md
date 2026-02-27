*This project has been created as part of the 42 curriculum by cbitca and tyamano.*

# cub3D

A simple 3D raycasting engine written in C using the MiniLibX graphics library. Inspired by the classic Wolfenstein 3D, this project renders a first-person view inside a maze using raycasting techniques.

---

## Description

cub3D is a 3D graphics engine that projects a 2D map into a dynamic first-person perspective with raycasting.

The program:
- Parses a `.cub` scene file
- Loads wall textures
- Renders textured walls using raycasting
- Handles player movement and rotation
- Manages memory safely
- Ensures proper error handling

The engine uses the **DDA (Digital Differential Analyzer)** algorithm to efficiently detect wall intersections and compute correct projection distances.

---

## Features

- Raycasting rendering engine
- Textured walls (North, South, East, West)
- Floor and ceiling colors
- WASD movement
- Left / Right arrow rotation
- ESC to exit
- Proper window close handling
- Strict `.cub` parsing and validation
- Memory leak free
- Wall collision detection

---

## Instruction

### Requirements (Linux)

- `cc`
- `make`
- MiniLibX (Linux version)
- Math library (`-lm`)
- X11 development libraries

### Compile

```bash
make
```

### Run

```bash
./cub3D path/to/map.cub
```

---

## Controls

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Move left |
| D | Move right |
| ← / → | Rotate camera |
| M | Toggle debug mode |
| ESC | Exit |

---

## Map File Format (.cub)

The program requires a `.cub` file.

### Texture Identifiers

```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
```

### Colors

```
F 220,100,0
C 225,30,0
```

- RGB values must be in range `[0,255]`.
- format must follow `R,G,B`.

### Map Rules

- Allowed characters:
  - `0` → empty space
  - `1` → wall
  - `N`, `S`, `E`, `W` → player start position
- Exactly one player
- Map must be closed (surrounded by walls)
- Map must be the last element in the file
- Spaces inside the map are handled properly

Any invalid configuration results in:

```
Error
<explicit error message>
```

---

### Debug Mode

Pressing `M` toggles debug mode.

In debug mode:

- 2D top-down map is rendered
- Rays are drawn in real time
- Player direction is visualized

This mode can be used to check raycasting, collision detection and map parsing.

---

## Resources

- https://lodev.org/cgtutor/raycasting.html
- https://www.permadi.com/tutorial/raycast/rayc1.html#google_vignette
- https://harm-smits.github.io/42docs/libs/minilibx
- https://www.geeksforgeeks.org/videos/digital-differential-analyzer-dda/

---

### AI Usage

AI tools were used for:

- Understanding raycasting concept and how it works
- Reviewing DDA logic
- Brainstorming edge-cases for parsing

All generated content was manually reviewed, tested, and fully understood before integration.