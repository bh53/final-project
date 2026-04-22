## Your Task:
For this project, you will create a complete paint application, using the Bobcat UI Library (a derivative of FLTK, but direct use of FLTK is not allowed), with the following tools and features (points indicate feature importance):

* 10 points: paint brush tool (draw points as a scribble while mouse is down)
* 5 points: eraser tool (delete shape/scribble)
* 5 points: clear screen tool (delete all shapes/scribbles)
* 10 points: RGB slider color picker
* 10 points: 5 distinct shape tools (e.g. circle, rectangle, triangle, pentagon, star, etc.)
* 10 points: selector tool (ability to select a shape/scribble by clicking on it)
* 10 points: ability to undo/redo drawing actions (creation of shapes/scribbles only)
* 10 points: ability to resize selected shape
* 10 points: ability to change color of selected shape/scribble
* 10 points: ability to move selected shape/scribble by dragging
* 10 points: ability to change drawing order (bring selected shape/scribble to front and send to back)

**Important**: A "scribble" is defined as the collection of all points drawn during a single mouse-drag event (from mouse-down to mouse-up). Rather than storing each point individually, all points drawn while the mouse is pressed should be stored together as a single object. This will allow the entire scribble to be treated as one unit, and make it possible to select it, move it, or delete it.

**Important**: All shapes and scribbles must be stored to a single, shared container, rather than creating separate containers for each one. This ensures consistent behavior when managing drawing order (bring to front, send to back).
