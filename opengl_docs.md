Here is the Markdown representation of the provided HTML document:

## 2.1 Introduction

OpenGL (Open Graphics Library) is a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics. Developed by the Khronos Group, OpenGL is widely used in video games, simulations, and any application requiring high-performance graphics rendering.

At its core, OpenGL provides a set of functions that allow you to control how graphics are drawn on the screen. These functions can be used to draw simple geometric shapes, manipulate colors and textures, and apply transformations to create complex scenes.

## 2.2 Basic OpenGL Concepts

OpenGL uses a Cartesian coordinate system with units ranging from -1.0 to 1.0 in normalized device coordinates. This system helps define the position of shapes on the screen.

## 2.3 Colors and Vertices

### 2.3.1 Selecting a Color

To select a color, use `glColor3f` and specify the `red`, `green`, and `blue` values, as arguments.
Below is the `glColor3f` function signature:

```cpp
void glColor3f(float red, float green, float blue);
```

Below is a list of common primary and secondary colors:

```cpp
glColor3f(0.0, 0.0, 0.0);   // black
glColor3f(1.0, 0.0, 0.0);   // red
glColor3f(0.0, 1.0, 0.0);   // green
glColor3f(1.0, 1.0, 0.0);   // yellow
glColor3f(0.0, 0.0, 1.0);   // blue
glColor3f(1.0, 0.0, 1.0);   // magenta
glColor3f(0.0, 1.0, 1.0);   // cyan
glColor3f(1.0, 1.0, 1.0);   // white
```

### 2.3.2 Describing a Vertex

In OpenGL, all geometric objects are described by vertices.
A vertex is represented by a pair of floating-point numbers.
To create a vertex, use `glVertex2f` and specify the `x` and `y` values, as arguments.
Below is the `glVertex2f` function signature:

```cpp
void glVertex2f(float x, float y);
```

All calls to `glVertex2f` must be inside of `glBegin` and `glEnd` pair.

### 2.3.3 glBegin and glEnd

A `glBegin` marks the beginning of a vertex list which describes a geometric primitive object.
Below is the `glBegin` function signature:

```cpp
void glBegin(GLenum mode);
```

The `GLenum mode` can be one of the following geometric primitive objects:

  * `GL_POINTS`: Treats each vertex as a single point.
  * `GL_LINES`: Treats each pair of vertices as an independent line segments.
  * `GL_POLYGON`: Treats all vertices as a single, convex polygon.

A `glEnd` marks the end of the vertex list.
Below is the `glEnd` function signature:

```cpp
void glEnd();
```

## 2.4 Points

### 2.4.1 Describing Points

A point is described by a vertex.
By default, a point is drawn as a single pixel on the screen.

### Specifying the Point Size

To control the size of a rendered point, use `glPointSize` and specify the `size`, in pixels, as the argument.
The `size` must be greater than `0.0`.
Below is the `glPointSize` function signature:

```cpp
void glPointSize(float size);
```

**Note**: The point size cannot be specified inside of a `glBegin` and `glEnd` pair.

### Enable and Disable Smooth Points

By default, a point is drawn as a square.
However, in the Bobcat UI context, points are drawn as round by default.

To make a point appear round, use the following function:

```cpp
glEnable(GL_POINT_SMOOTH);
```

Once enabled, to disable smooth points, use the following function:

```cpp
glDisable(GL_POINT_SMOOTH);
```

**Note**: Enabling and Disabling smooth points cannot be specified inside of a `glBegin` and `glEnd` pair.

### 2.4.2 Drawing Points

Points must be drawn using a vertices inside of a `glBegin(GL_POINTS)` and `glEnd` pair.

### Drawing a Non Smooth Point

The following code snippet draws a black non-smooth point at the origin:

```cpp
// disable smooth points
glDisable(GL_POINT_SMOOTH);

// set color to black and point size to 20
glColor3f(0.0, 0.0, 0.0);
glPointSize(20.0);

// draw point
glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
glEnd();
```

### Drawing a Smooth Point

The following code snippet draws a black smooth point at the origin:

```cpp
// enable smooth points
glEnable(GL_POINT_SMOOTH);

// set color to black and point size to 20
glColor3f(0.0, 0.0, 0.0);
glPointSize(20.0);

// draw point
glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
glEnd();
```

### Drawing Smooth and Non Smooth Points

The following code snippet draws two black points, one smooth and the other non smooth:

```cpp
// set color to black and point size to 20
glColor3f(0.0, 0.0, 0.0);
glPointSize(20.0);

// enable smooth point and draw point
glEnable(GL_POINT_SMOOTH);
glBegin(GL_POINTS);
    glVertex2f(-0.2, 0.0);
glEnd();

// disable smooth points and draw point
glDisable(GL_POINT_SMOOTH);
glBegin(GL_POINTS);
    glVertex2f(0.2, 0.0);
glEnd();
```

### Drawing Different Sized Smooth Points

The following code snippet draws a two different sized black smooth points:

```cpp
// set color to black and enable smooth points
glColor3f(0.0, 0.0, 0.0);
glEnable(GL_POINT_SMOOTH);

// set point size to 10 and draw point
glPointSize(10.0);
glBegin(GL_POINTS);
    glVertex2f(-0.2, 0.0);
glEnd();

// set point size to 20 and draw point
glPointSize(20.0);
glBegin(GL_POINTS);
    glVertex2f(0.2, 0.0);
glEnd();
```

### Drawing Different Colored Smooth Points

The following code snippet draws four different colored smooth points, each one in a different quadrant:

```cpp
// enable smooth points and set point size to 20
glPointSize(20.0);
glEnable(GL_POINT_SMOOTH);

glBegin(GL_POINTS);
    // red point in top right quadrant
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.5, 0.5);

    // green point in top left quadrant
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, 0.5);

    // blue point in bottom left quadrant
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-0.5, -0.5);

    // magenta point in bottom right quadrant
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(0.5, -0.5);
glEnd();
```

## 2.5 Lines

### 2.5.1 Describing Lines

A line, which refers to a line segment, is represented by a pair of vertices.
By default, a line is drawn solid and one pixel wide.

### Specifying the Line Width

To control the size of the rendered line, use `glLineWidth` and specify the `size`, in pixels, as the argument.
The `size` must be greater than `0.0`.
Below is the `glLineWidth` function signature:

```cpp
void glLineWidth(float size);
```

**Note**: The line width cannot be specified inside of a `glBegin` and `glEnd` pair.

### 2.5.2 Drawing Lines

Lines must be drawn using a pairs of vertices inside of a `glBegin(GL_LINES)` and `glEnd` pair.

### Drawing a Line

The following code snippet draws a black horizontal line segment on the origin:

```cpp
// set color to black and line width to 5 pixels
glColor3f(0.0, 0.0, 0.0);
glLineWidth(5.0);

glBegin(GL_LINES);
    // line segment
    glVertex2f(-0.5, 0.0);
    glVertex2f(0.5, 0.0);
glEnd();
```

### Drawing Multiple Lines

The following code snippet draws a two black horizontal line segments:

```cpp
// set color to black and line width to 5 pixels
glColor3f(0.0, 0.0, 0.0);
glLineWidth(5.0);

glBegin(GL_LINES);
    // line segment
    glVertex2f(-0.5, 0.3);
    glVertex2f(0.5, 0.3);

    // line segment
    glVertex2f(-0.5, -0.3);
    glVertex2f(0.5, -0.3);
glEnd();
```

### Drawing Lines of Varying Line Widths

The following code snippet draws two black horizontal line segments of varying line widths:

```cpp
// set color to black
glColor3f(0.0, 0.0, 0.0);

// set line width to 5 pixels and draw line
glLineWidth(5.0);
glBegin(GL_LINES);
    glVertex2f(-0.5, 0.3);
    glVertex2f(0.5, 0.3);
glEnd();

// set line width to 10 pixels and draw line
glLineWidth(10.0);
glBegin(GL_LINES);
    glVertex2f(-0.5, -0.3);
    glVertex2f(0.5, -0.3);
glEnd();
```

### Drawing Lines of Varying Line Widths and Color

The following code snippet draws three horizontal line segments of varying line widths and colors:

```cpp
// thin (3 line width) red line segment
glColor3f(1.0, 0.0, 0.0);
glLineWidth(3.0);
glBegin(GL_LINES);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
glEnd();

// medium (5 line width) green line segment
glColor3f(0.0, 1.0, 0.0);
glLineWidth(5.0);
glBegin(GL_LINES);
    glVertex2f(-0.5, 0.0);
    glVertex2f(0.5, 0.0);
glEnd();

// thick (10 line width) blue line segment
glColor3f(0.0, 0.0, 1.0);
glLineWidth(10.0);
glBegin(GL_LINES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
glEnd();
```

## 2.6 Polygons

### 2.6.1 Describing Polygons

A polygon is the area enclosed by a single closed series of line segments, where each line segment is represented by a pair of vertices.

In OpenGL, polygons must follow two rules:

  * The edges of a polygon cannot intersect.
  * Polygons must be convex, meaning that the surface must be curved/rounded outwards.

By default, a polygon is drawn solid and filled in.

### Specifying the Polygon Mode

The `glPolygonMode` can specify in what mode the polygon should be drawn: as points, as outlined, as solid (filled in).
Below is the `glPolygonMode` function signature:

```cpp
glPolygonMode(GLenum face, GLenum mode);
```

The `gGLenum face` can be one of the following:

  * `GL_FRONT_AND_BACK`: Controls drawing for front and back face.
  * `GL_FRONT`: Controls drawing for front face.
  * `GL_BACK`: Controls drawing for back face.

The `GLenum mode` can be one of the following:

  * `GL_FILL`: Polygon will be drawn and filled in.
  * `GL_LINE`: Polygon will be drawn as outlined.
  * `GL_POINT`: Polygon will be drawn as points.

### 2.6.2 Drawing Polygons

A polygon must be drawn using a set of vertices inside of a `glBegin(GL_POLYGON)` and `glEnd` pair.

### Drawing a Solid Polygon

The following code snippet draws a solid black square polygon:

```cpp
// set color to black
glColor3f(0.0, 0.0, 0.0);

// draw polygon (default is solid/filled in)
glBegin(GL_POLYGON);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
glEnd();
```

### Drawing an Outlined Polygon

The following code snippet draws an outlines black square polygon:

```cpp
// set color to black and enable smooth points
glColor3f(0.0, 0.0, 0.0);
glEnable(GL_POINT_SMOOTH);

// set point size and line with to 10
glPointSize(10.0);
glLineWidth(10.0);

// set polygon mode to drawn as outlined
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
glBegin(GL_POLYGON);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
glEnd();
```

### Drawing a Polygon as Points

The following code snippet draws a black square polygon as points:

```cpp
// set color to black and enable smooth points
glColor3f(0.0, 0.0, 0.0);
glEnable(GL_POINT_SMOOTH);

// set point size and line with to 10
glPointSize(10.0);
glLineWidth(10.0);

// set polygon mode to drawn as points
glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
glBegin(GL_POLYGON);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
glEnd();
```
