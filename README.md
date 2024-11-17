# Pixl - A Low-Level Pixel Graphics Library

Pixl is a minimalist graphics library built on SDL2, focusing exclusively on pixel-level rendering operations. Unlike higher-level graphics libraries, Pixl provides direct pixel manipulation capabilities while abstracting away SDL2's complexity.

## Core Concept

The library's fundamental approach is to work directly with pixels, providing:
- Raw pixel buffer management
- Multiple layer compositing
- Pixel-by-pixel shape rendering
- No texture or sprite operations - everything is rendered pixel by pixel

## Features

- **Pure Pixel Operations**: All rendering is done at the pixel level
- **Multi-Layer System**: Up to 5 independent pixel layers with alpha compositing
- **Shape Primitives**: Basic shapes (like lines and circles) implemented through pixel-perfect algorithms
- **Custom Framebuffer**: Direct pixel buffer manipulation separate from SDL's renderer
- **Vector Math**: Basic 2D vector operations for pixel calculations

## Dependencies

- SDL2 (only used for window management and final buffer presentation)

## Example Usage

The library handles all rendering through pixel operations. For instance, a line is drawn by calculating and setting individual pixels rather than using SDL's line drawing functions.



