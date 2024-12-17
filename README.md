# Rotating Rectangles with SAT Collision Detection

This project demonstrates how to implement collision detection for rotating rectangles using the Separating Axis Theorem (SAT) with the **SFML** library. The code features real-time collision detection and visualization for two independently rotating rectangles.

## Features

- Rotating rectangles with adjustable rotation speeds.
- Collision detection using the SAT algorithm.
- Dynamic visual feedback: rectangles turn **red** on collision and **green** otherwise.

## Requirements

- C++17 or later.
- [SFML](https://www.sfml-dev.org/) library (version 2.5 or newer).

## How It Works

1. **Vertices and Edges**:

   - The vertices of each rectangle are computed using SFML's transformation matrix.
   - Edges are derived by connecting consecutive vertices.

2. **Projection on Axes**:

   - Each edge's perpendicular axis is calculated and used to project both rectangles.
   - Overlapping projections indicate possible collisions.

3. **Collision Detection**:

   - If a gap exists on any axis, the rectangles are not colliding.
   - If no gaps are found, a collision is detected.

## Code Overview

- `dotProduct`: Calculates the dot product of two vectors.
- `normalize`: Normalizes a vector.
- `getVertices`: Returns the vertices of a rectangle after applying transformations.
- `getEdges`: Returns edges of a polygon by connecting its vertices.
- `projectOntoAxis`: Projects vertices onto an axis and calculates the min/max values.
- `checkSATCollision`: Implements the SAT algorithm to check for collisions.

## Preview

- The application opens a window where two rectangles rotate around their centers.
- If they collide, their outlines change to **red**; otherwise, they remain **green**.

## Customization

- **Rectangle Dimensions**: Modify the `sf::RectangleShape` constructors in the `main()` function.
- **Rotation Speeds**: Adjust the `rotationSpeedA` and `rotationSpeedB` variables.
- **Window Properties**: Change the resolution and title in `sf::RenderWindow`.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgments

- [SFML Library](https://www.sfml-dev.org/): Simple and Fast Multimedia Library.
- Conceptual inspiration from SAT tutorials and game physics principles.
