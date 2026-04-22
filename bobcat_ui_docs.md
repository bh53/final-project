## 1.1 Introduction

This chapter presents all the relevant Bobcat UI components that can be used to build GUI applications. Each component follows basic Object-Oriented Programming principles, with the primary structure being the `Application` class.

In a typical Bobcat UI application, the code is organized across two files: `Application.h` and `Application.cpp`. The `Application.h` file contains the declarations, including instance variables for the components and function prototypes, while the `Application.cpp` file handles the initialization of instance variables and contains the actual definitions of the functions declared in `Application.h`.

Components are typically declared as instance variables of the `Application` class and initialized in its constructor. Event handlers can be registered to perform actions in response to user interactions, such as button clicks.

-----

## 1.2 Window Component

Every Bobcat UI application should have a window, so that it can display an interface for the user to interact. The window is displayed inside of the remote desktop screen. This guide provides an overview on how to create a `Window` component in your Bobcat UI application.

### Include Header File

To use the window component, include the following header file:

```cpp
#include <bobcat_ui/window.h>
```

### Declaring a `Window*` Variable

You can declare a `bobcat::Window*` variable as follows:

```cpp
bobcat::Window* window;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Window*` Variable

To initialize the `Window*` variable, use the following constructor:

```cpp
window = new Window(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the windows's top-left corner with respect to the remote desktop screen.
  * `w` and `h`: Define the width and height of the window.
  * `path`: Defines the text displayed in the window's title bar.

This initialization is typically done in the constructor of `Application`:

```cpp
window = new Window(100, 100, 400, 400, "Bobcat UI Window");
```

### Making the Window Appear

To make the window visible on the remote desktop screen, you must call the `show()` method:

```cpp
window->show();
```

### Other Useful Member Methods

The image component provides additional useful methods to interact with it:

  * `show()`: displays the window on the remote desktop screen
  * `redraw()`: redraws the window, including all child components

### Complete Example

The following example creates and renders a window component on the remote desktop.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Window");
    window->show();
}
```

*Application.cpp*

-----

## 1.3 Button Components

There are two flavors of buttons in Bobcat UI, a regular button and a return button. Each is described separately below. Even thought a return button is not strictly necessary for GUI applications, it provides a convenient way for users to simulate the click action of it by pressing the return (enter) key. It can be used for the default action in the application, where the user can simply press the return key on their keyboard, instead of clicking the button with their mouse. Needless to say, there should only be 1 return button on a given interface, otherwise the user may be confused.

### 1.3.1 Button Component

A button component allows you to perform actions when the button is clicked. This guide provides an overview on how to create a `Button` component in your Bobcat UI application. You will also learn how to register an action that will be executed when the button is clicked.

### Include Header File

To use the button component, include the following header file:

```cpp
#include <bobcat_ui/button.h>
```

### Declaring a `Button*` Variable

You can declare a `bobcat::Button*` variable as follows:

```cpp
bobcat::Button* button;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Button*` Variable

To initialize the `Button*` variable, use the following constructor:

```cpp
button = new Button(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the button's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the button.
  * `label`: Defines the text displayed inside the button.

This initialization is typically done in the constructor of `Application`:

```cpp
button = new Button(25, 350, 350, 25, "Click Me");
```

### Default Configuration

By default, a button has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: center
  * Label placement: inside

### Registering a Click Handler

You can register an on-click event handler and provide an `Application` member method that specifies the actions to be performed when the button is clicked:

```cpp
ON_CLICK(button, Application::handleClick);
```

For more details on registering event handlers, refer to section 12.

### Complete Example

The following example creates a button component and registers an on-click event handler for it.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    cout << "Button was clicked" << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Button Component");
    
    button = new Button(25, 350, 350, 25, "Click Me");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

### 1.3.2 Return Button Component

A return button component allows you to perform actions when the button is clicked or the "return" key is pressed. This guide provides an overview on how to create a `ReturnButton` component in your Bobcat UI application. You will also learn how to register an action that will be executed when the button is clicked or the "return" key is pressed.

### Include Header File

To use the return button component, include the following header file:

```cpp
#include <bobcat_ui/return_button.h>
```

### Declaring a `ReturnButton*` Variable

You can declare a `bobcat::ReturnButton*` variable as follows:

```cpp
bobcat::ReturnButton* button;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `ReturnButton*` Variable

To initialize the `ReturnButton*` variable, use the following constructor:

```cpp
button = new ReturnButton(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the button's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the button.
  * `label`: Defines the text displayed inside the button.

This initialization is typically done in the constructor of `Application`:

```cpp
button = new ReturnButton(25, 350, 350, 25, "Click Me");
```

### Default Configuration

By default, a return button has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: center
  * Label placement: inside

### Registering a Click Handler

You can register an on-click event handler and provide an `Application` member method that specifies the actions to be performed when the return button is clicked or the "return" key is pressed:

```cpp
ON_CLICK(button, Application::handleClick);
```

For more details on registering event handlers, refer to section 12.

### Complete Example

The following example creates a button component and registers an on-click event handler for it.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::ReturnButton* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    cout << "Button was clicked" << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Return Button Component");
    
    button = new ReturnButton(25, 350, 350, 25, "Click Me");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

## 1.4 Textbox Component

A textbox component allows you to display text. This guide provides an overview on how to create a `TextBox` component in your Bobcat UI application.

### Include Header File

To use the textbox component, include the following header file:

```cpp
#include <bobcat_ui/textbox.h>
```

### Declaring a `TextBox*` Variable

You can declare a `bobcat::TextBox*` variable as follows:

```cpp
bobcat::TextBox* textbox;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `TextBox*` Variable

To initialize the `TextBox*` variable, use the following constructor:

```cpp
textbox = new TextBox(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the textbox's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the textbox.
  * `label`: Defines the text displayed inside the textbox.

This initialization is typically done in the constructor of `Application`:

```cpp
textbox = new TextBox(25, 25, 350, 25, "TextBox content goes here...");
```

### Default Configuration

By default, a textbox has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: left
  * Label placement: inside

### Complete Example

The following example creates a textbox component.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::TextBox* textbox;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI TextBox Component");
    
    textbox = new TextBox(25, 25, 350, 25, "TextBox content goes here...");

    window->show();
}
```

*Application.cpp*

-----

## 1.5 Image Component

A image component allows you display an image by specifying its path. This guide provides an overview on how to create a `Image` component in your Bobcat UI application.

### Include Header File

To use the image component, include the following header file:

```cpp
#include <bobcat_ui/image.h>
```

### Declaring a `Image*` Variable

You can declare a `bobcat::Image*` variable as follows:

```cpp
bobcat::Image* image;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Image*` Variable

To initialize the `Image*` variable, use the following constructor:

```cpp
image = new Image(int x, int y, int w, int h, string path);
```

where:

  * `x` and `y`: Define the position of the image's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the image.
  * `path`: Defines the path of the image file.

This initialization is typically done in the constructor of `Application`:

```cpp
image = new Image(50, 50, 300, 300, "./assets/rufus.png");
```

### Other Useful Member Methods

The image component provides additional useful methods to interact with it:

  * `increase(int number)`: increase image width and height by `number` pixels
  * `decrease(int number)`: decrease image width and height by `number` pixels
  * `moveLeft(int number)`: move image left by `number` pixels
  * `moveRight(int number)`: move image right by `number` pixels
  * `setImage(string path)`: defines the `path` of new image file to render

### Complete Example

The following example uses an image component to render the `rufus.png` image found in the `assets` folder.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Image* image;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Image Component");
    
    image = new Image(50, 50, 300, 300, "./assets/rufus.png");

    window->show();
}
```

*Application.cpp*

-----

## 1.6 Input Components

There are 3 flavors of input components in Bobcat UI. In general, an input component is an area on the screen with a text cursor, allowing the user to type text there, as well as copy/paste it. The programmer can extract the text written by the user for whatever purpose the program needs it, but there are different ways to interpret the text written by the user. That is to say, the text entered by the user can be treated as an unrestricted collection of characters, or a `string` type. It can also be treated as an integer (whole number) numerical value, or an `int` type. The user input can also be treated as a numerical value with with a decimal point (floating point), for non-whole numbers, or a `float` type. The following three components provide a way to restrict the kinds of input text the user is allowed to write, and use the appropriate data type when retrieving the value.

### 1.6.1 Input Components

An input component will allow you to input text using the keyboard. There are no restrictions on what the user can type into this input component, so the value is stored as a `string`. This guide provides an overview on how to create an `Input` component in your Bobcat UI application. You will also learn how to retrieve, set, and clear the input's value.

### Include Header File

To use the input component, include the following header file:

```cpp
#include <bobcat_ui/input.h>
```

### Declaring a `Input*` Variable

You can declare a `bobcat::Input*` variable as follows:

```cpp
bobcat::Input* input;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Input*` Variable

To initialize the `Input*` variable, use the following constructor:

```cpp
input = new Input(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the input's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the input.
  * `label`: Defines the label displayed above the input field.

This initialization is typically done in the constructor of `Application`:

```cpp
input = new Input(25, 25, 350, 25, "Input");
```

### Default Configuration

By default, an input has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: left
  * Label placement: above

### Extracting the Value of the Input Field

You can retrieve the current value of the input field by calling the `value()` method.

```cpp
string value = input->value();
```

Extracting the value is typically performed in response to a user action, such a button click. For more details on registering event handlers, refer to section 12.

### Other Useful Member Methods

The input component provides additional useful methods to interact with it:

  * `value()`: returns the current value of the input field as a `string`
  * `value(string newValue)`: sets the input field's value to `newValue`
  * `empty()`: returns `true` if the input field is empty, `false` otherwise
  * `clear()`: clears the value of the input field
  * `readonly()`: returns `true` if the input field is readonly, `false` otherwise
  * `readonly(bool newValue)`: sets the input field's readonly property to  `newValue`

### Complete Example

The following example creates an input component and registers an on-click event handler to retrieve the current value of the input field in response to a button click.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Input* input;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    string value = input->value();
    cout << "Value: " << value << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Input Component");
    
    input = new Input(25, 25, 350, 25, "Input");

    button = new Button(25, 350, 350, 25, "Extract Value");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

### 1.6.2 Int Input Component

An int input component will allow you to input whole numbers using the keyboard. The user is only allowed to enter numerical values on the keyboard. The minus sign (-) can appear as the first character in the input, but not anywhere else, since negative numbers are supported. The value of the input is stored as an `int`.  This guide provides an overview on how to create an `IntInput` component in your Bobcat UI application. You will also how to retrieve, set, and clear the int input's value.

### Include Header File

To use the int input component, include the following header file:

```cpp
#include <bobcat_ui/int_input.h>
```

### Declaring a `IntInput*` Variable

You can declare a `bobcat::IntInput*` variable as follows:

```cpp
bobcat::IntInput* intInput;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `IntInput*` Variable

To initialize the `IntInput*` variable, use the following constructor:

```cpp
intInput = new IntInput(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the input field's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the input field.
  * `label`: Defines the label displayed above the input field.

This initialization is typically done in the constructor of `Application`:

```cpp
intInput = new IntInput(25, 25, 350, 25, "Int Input");
```

### Default Configuration

By default, an int input has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: left
  * Label placement: above

### Extracting the Value of the Input Field

You can retrieve the current value of the int input field by calling the `value()` method, as attempting to retrieve a value from an empty int input field will throw an error:

```cpp
int value = intInput->value();
```

Extracting the value is typically performed in response to a user action, such a button click. For more details on registering event handlers, refer to section 12.

### Other Useful Member Methods

The int input component provides additional useful methods to interact with it:

  * `value()`: returns the current value of the int input field as an `int`
  * `value(int newValue)`: sets the int input field's value to `newValue`
  * `empty()`: returns `true` if the int input field is empty, `false` otherwise
  * `clear()`: clears the value of the int input field
  * `readonly()`: returns `true` if the int input field is readonly, `false` otherwise
  * `readonly(bool newValue)`: sets the int input field's readonly property to  `newValue`

### Complete Example

The following example creates an int input component and registers an on-click event handler to retrieve the current value of the input field in response to a button click.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::IntInput* intInput;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    if (!intInput->empty()) {
        int value = intInput->value();
        cout << "Value: " << value << endl;
    }
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Int Input Component");
    
    intInput = new IntInput(25, 25, 350, 25, "Int Input");

    button = new Button(25, 350, 350, 25, "Extract Value");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

### 1.6.3 Float Input Component

A float input component will allow you to input numbers with a decimal point using the keyboard. The minus sign (-) is allowed to be at the beginning of the input, and one point (.) character is allowed in the text. That is to support positive and negative decimal numbers, with a floating point. The value of this component is stored as a `float`. This guide provides an overview on how to create an `FloatInput` component in your Bobcat UI application. You will also learn how to retrieve, set, and clear the float input's value.

### Include Header File

To use the float input component, include the following header file:

```cpp
#include <bobcat_ui/float_input.h>
```

### Declaring a `FloatInput*` Variable

You can declare a `bobcat::FloatInput*` variable as follows:

```cpp
bobcat::FloatInput* floatInput;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `FloatInput*` Variable

To initialize the `FloatInput*` variable, use the following constructor:

```cpp
floatInput = new FloatInput(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the input field's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the input field.
  * `label`: Defines the label displayed above the input field.

This initialization is typically done in the constructor of `Application`:

```cpp
floatInput = new FloatInput(25, 25, 350, 25, "Float Input");
```

### Default Configuration

By default, a float input has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: left
  * Label placement: above

### Extracting the Value of the Input Field

You can retrieve the current value of the float input field by calling the `value()` method, as attempting to retrieve a value from an empty float input field will throw an error:

```cpp
float value = floatInput->value();
```

Extracting the value is typically performed in response to a user action, such a button click. For more details on registering event handlers, refer to section 12.

### Other Useful Member Methods

The float input component provides additional useful methods to interact with it:

  * `value()`: returns the current value of the float input field as an `float`
  * `value(float newValue)`: sets the float input field's value to `newValue`
  * `empty()`: returns `true` if the float input field is empty, `false` otherwise
  * `clear()`: clears the value of the float input field
  * `readonly()`: returns `true` if the float input field is readonly, `false` otherwise
  * `readonly(bool newValue)`: sets the float input field's readonly property to  `newValue`

### Complete Example

The following example creates a float input component and registers an on-click event handler to retrieve the current value of the input field in response to a button click.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::FloatInput* floatInput;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    if (!floatInput->empty()) {
        float value = floatInput->value();
        cout << "Value: " << value << endl;
    }
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Float Input Component");
    
    floatInput = new FloatInput(25, 25, 350, 25, "Float Input");

    button = new Button(25, 350, 350, 25, "Extract Value");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

## 1.7 Dropdown Component

A dropdown component will allow you to select from a collapsible list of options. This guide provides an overview on how to create a `Dropdown` component in your Bobcat UI application. You will also learn how to add and remove options from the dropdown, retrieve the selected option, and programmatically select an option.

### Include Header File

To use the dropdown component, include the following header file:

```cpp
#include <bobcat_ui/dropdown.h>
```

### Declaring a `Dropdown*` Variable

You can declare a `bobcat::Dropdown*` variable as follows:

```cpp
bobcat::Dropdown* dropdown;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Dropdown*` Variable

To initialize the `Dropdown*` variable, use the following constructor:

```cpp
dropdown = new Dropdown(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the dropdown's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the dropdown.
  * `label`: Defines the label displayed above the dropdown field.

This initialization is typically done in the constructor of `Application`:

```cpp
dropdown = new Dropdown(25, 25, 350, 25, "Dropdown");
```

### Default Configuration

By default, a dropdown has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: left
  * Label placement: above

### Adding Options to the Dropdown List

You can add options to the dropdown list by calling the `add(string option)` and specifying the option name as an argument:

```cpp
dropdown->add("Option 1");
dropdown->add("Option 2");
dropdown->add("Option 3");
```

The first option that is added will be set as the default choice, in this case, "Option 1".

### Extracting the Selected Dropdown Option

You can retrieve the currently selected dropdown option by calling the `text()` method.

```cpp
std::string value = dropdown->text();
```

Extracting the selected dropdown option is typically performed in response to a user action, such a button click. For more details on registering event handlers, refer to section 12.

### Other Useful Member Methods

The dropdown component provides additional useful methods to interact with it:

  * `add(string option)`: adds `option` to the dropdown list
  * `text()`: returns the currently selected option
  * `text(string option)`: sets `option` as the selected option
  * `value()`: returns the `index` of the currently selected option
  * `value(int index)`: sets the selected option by its `index`
  * `remove(string option)`: removes `option` from the dropdown list
  * `remove(int index)`: removes the option at the specified `index`
  * `clear()`: removes all options from the dropdown list

### Complete Example

The following example creates a dropdown component and registers an on-click event handler to retrieve the currently selected option in response to a button click.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Dropdown* dropdown;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    std::string value = dropdown->text();
    cout << "Value: " << value << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Dropdown Component");
    
    dropdown = new Dropdown(25, 25, 350, 25, "Dropdown");
    dropdown->add("Option 1");
    dropdown->add("Option 2");
    dropdown->add("Option 3");

    button = new Button(25, 350, 350, 25, "Extract Value");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

## 1.8 Checkbox Component

A checkbox component will allow you mark an option as selected or not selected. This guide provides an overview on how to create a `Checkbox` component in your Bobcat UI application. You will also learn how to get the checkbox's state, and programmatically check and uncheck it.

### Include Header File

To use the checkbox component, include the following header file:

```cpp
#include <bobcat_ui/checkbox.h>
```

### Declaring a `Checkbox*` Variable

You can declare a `bobcat::Checkbox*` variable as follows:

```cpp
bobcat::Checkbox* checkbox;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Checkbox*` Variable

To initialize the `Checkbox*` variable, use the following constructor:

```cpp
checkbox = new Checkbox(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the checkbox's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the checkbox.
  * `label`: Defines the label displayed to the right of the checkbox.

This initialization is typically done in the constructor of `Application`:

```cpp
checkbox = new Checkbox(25, 25, 350, 25, "Checkbox Option");
```

### Default Configuration

By default, a checkbox has the following properties:

  * Label size: 14 pixels
  * Label color: black
  * Label font: Helvetica
  * Label alignment: left
  * Label placement: right

### Extracting the State of the Checkbox

You can retrieve the state of the checkbox by calling the `value()` method.

```cpp
bool value = checkbox->value();
```

Extracting the state of a checkbox is typically performed in response to a user action, such a button click. For more details on registering event handlers, refer to section 12.

### Other Useful Member Methods

The checkbox component provides additional useful methods to interact with it:

  * `check()`: programmatically checks the checkbox
  * `uncheck()`: programmatically unchecks the checkbox
  * `checked()`: returns `true` if the checkbox is checked, `false` otherwise
  * `value()`: returns `true` if the checkbox is checked, `false` otherwise
  * `value(bool state)`: sets the state of the checkbox to `state`

### Complete Example

The following example creates a checkbox component and registers an on-click event handler to retrieve the current state of the checkbox in response to a button click.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Checkbox* checkbox;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    bool value = checkbox->value();
    cout << "Value: " << value << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Checkbox Component");
    
    checkbox = new Checkbox(25, 25, 350, 25, "Checkbox Option");

    button = new Button(25, 350, 350, 25, "Extract Value");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

## 1.9 ListBox

A listbox component will allow you to add items to a scrollable list. This guide provides an overview on how to create a `ListBox` component in your Bobcat UI application. You will also learn how to add and remove items from the listbox, and retrieve the selected item.

### Include Header File

To use the listbox component, include the following header file:

```cpp
#include <bobcat_ui/list_box.h>
```

### Declaring a `ListBox*` Variable

You can declare a `bobcat::ListBox*` variable as follows:

```cpp
bobcat::ListBox* listbox;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `ListBox*` Variable

To initialize the `ListBox*` variable, use the following constructor:

```cpp
listbox = new ListBox(int x, int y, int w, int h, string label);
```

where:

  * `x` and `y`: Define the position of the listbox's top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the listbox.
  * `label`: Defines the label displayed above the listbox.

This initialization is typically done in the constructor of `Application`:

```cpp
listbox = new ListBox(25, 25, 350, 100, "ListBox");
```

### Adding Items to the Listbox List

You can add items to the listbox by calling the `add(string option)` and specifying the item name as an argument:

```cpp
listbox->add("Item 1");
listbox->add("Item 2");
listbox->add("Item 3");
```

### Extracting the Selected Listbox Item

You can retrieve the currently selected listbox option by calling the `getSelected()` method.

```cpp
std::string selected = listbox->getSelected();
```

Extracting the selected listbox option is typically performed in response to a user action, such a button click. For more details on registering event handlers, refer to section 12.

### Other Useful Member Methods

The listbox component provides additional useful methods to interact with it:

  * `add(std::string item)`: adds `item` to the listbox
  * `getSelected()`: returns the currently selected item
  * `removeSelected()`: removes the currently selected item
  * `get(int index)`: returns the item at the specified `index`
  * `clear()`: removes all options from the listbox

### Complete Example

The following example creates a listbox component and registers an on-click event handler to retrieve the currently selected item in response to a button click.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::ListBox* listbox;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    std::string selected = listbox->getSelected();
    cout << "Selected: " << selected << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI ListBox Component");
    
    listbox = new ListBox(25, 25, 350, 100, "ListBox");
    listbox->add("Item 1");
    listbox->add("Item 2");
    listbox->add("Item 3");

    button = new Button(25, 350, 350, 25, "Extract Selected");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

## 1.10 Canvas

A canvas component allows you to render custom shapes using OpenGL. This guide provides an overview on how to create a `Canvas` component in your Bobcat UI application.

Unlike other BobcatUI components, creating a canvas requires you to inherit, or extend, from Bobcat UI's base `Canvas_` class and implement a `render` function, which is where the custom OpenGL shapes can be drawn.

### Creating `Canvas.h` header file

```cpp
#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>

class Canvas : public bobcat::Canvas_ {

public:
    Canvas(int x, int y, int w, int h);

    void render();
};

#endif
```

*Canvas.h*

In the code snippet above, the `Canvas` class publicly inherits from `bobcat::Canvas_`, are declared.

### Creating `Canvas.cpp` source file

```cpp
#include "Canvas.h"
#include <GL/freeglut.h>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    //
}

void Canvas::render() {
    glBegin(GL_POINTS);
        glVertex2f(0.0, 0.0);
    glEnd();
}
```

*Canvas.cpp*

The code snippet above implements the `Canvas` class. The constructor draws a point at the xy-coordinates `(0.0, 0.0)`, rendering a black point in the center of the canvas.

For more details on drawing objects using OpenGL, refer to section Chapter 2.

### Include Header File

To use the canvas component, include the following header file:

```cpp
#include "Canvas.h"
```

### Declaring a `Canvas*` Variable

You can declare a `Canvas*` variable as follows:

```cpp
Canvas* canvas;
```

This declaration is typically made as an instance variable in the `Application` class.

### Initializing a `Canvas*` Variable

To initialize the `Canvas*` variable, use the following constructor:

```cpp
canvas = new Canvas(int x, int y, int w, int h);
```

where:

  * `x` and `y`: Define the position of the canvas' top-left corner with respect to the window.
  * `w` and `h`: Define the width and height of the canvas.

This initialization is typically done in the constructor of `Application`:

```cpp
canvas = new Canvas(50, 50, 300, 300);
```

### Default Configuration

By default, a canvas has the following properties:

  * Background Color: white
  * Point Size: 7
  * Color: black

### Complete Example

The following example creates a canvas component.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Canvas.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Canvas Component");

    canvas = new Canvas(50, 50, 300, 300);

    window->show();
}
```

*Application.cpp*

-----

## 1.11 Typography

This section provides some documentation on the supported colors, fonts, alignments, and box types, and how to update them.

### Colors

The following `Fl_Color` enums represent the more common colors:

  * `FL_BLACK`
  * `FL_WHITE`
  * `FL_RED`
  * `FL_GREEN`
  * `FL_YELLOW`
  * `FL_BLUE`
  * `FL_MAGENTA`
  * `FL_CYAN`
  * `FL_DARK_RED`
  * `FL_DARK_GREEN`
  * `FL_DARK_YELLOW`
  * `FL_DARK_BLUE`
  * `FL_DARK_MAGENTA`
  * `FL_DARK_CYAN`

The following `Fl_Color` enums are commonly used for box type colors:

  * `FL_GRAY0`
  * `FL_DARK3`
  * `FL_DARK2`
  * `FL_DARK1`
  * `FL_LIGHT1`
  * `FL_LIGHT2`
  * `FL_LIGHT3`

The following `Fl_Color` enums are commonly used for default widget colors:

  * `FL_BACKGROUND_COLOR`: default background color
  * `FL_FOREGROUND_COLOR`: default foreground color used for labels and text
  * `FL_BACKGROUND2_COLOR`: default background color for text, list, and valuator widgets
  * `FL_INACTIVE_COLOR`: inactive foreground color
  * `FL_SELECTION_COLOR`: default selection/highlight color

### Custom RGB Color

In Bobcat UI, you can define a custom color using the `fl_rgb_color` method:

```cpp
fl_rgb_color(int red, int green, int blue);
```

This method creates a custom color using the RGB color format. RGB stands for Red, Green, and Blue, and it is a common method for representing colors in digital systems. Each of the three color components can range from 0 to 255 where 0 means none of the color, and 255 means full intensity of that color.

For example, the RGB values (255, 0, 255) represent a bright magenta color, combining full red, no green, and full blue.

### Changing the Color of Labels, Text, and Background

The color of a components can be changed using the following methods:

  * `labelcolor(Fl_Color color)`: changes the component label color to the specified `color`
  * `textcolor(Fl_Color color)`: changes component text color to the specified `color`
  * `color(Fl_Color color)`: changes the component background color to the specified `color`
  * `cursorcolor(Fl_Color color)`: changes the input cursor color to the specified `color`

### Complete Example

The following example creates an input component and changes the colors as follows:

  * the label color to `FL_RED`
  * the text color to `FL_BLUE`
  * the background color to `FL_DARK2`
  * the cursor color `fl_rgb_color(255, 0, 255)`, representing the color magenta

<!-- end list -->

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Input* input;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Colors");
    
    input = new Input(25, 25, 350, 25, "Input Label");

    input->labelcolor(FL_RED);
    input->textcolor(FL_BLUE);
    input->color(FL_DARK2);
    input->cursor_color(fl_rgb_color(255, 0, 255));

    window->show();
}
```

*Application.cpp*

### Fonts

The following `Fl_Font` enums are supported:

  * `FL_HELVETICA`
  * `FL_HELVETICA_BOLD`
  * `FL_HELVETICA_ITALIC`
  * `FL_HELVETICA_BOLD_ITALIC`
  * `FL_COURIER`
  * `FL_COURIER_BOLD`
  * `FL_COURIER_ITALIC`
  * `FL_COURIER_BOLD_ITALIC`
  * `FL_TIMES`
  * `FL_TIMES_BOLD`
  * `FL_TIMES_ITALIC`
  * `FL_TIMES_BOLD_ITALIC`
  * `FL_SYMBOL`
  * `FL_SCREEN`
  * `FL_SCREEN_BOLD`
  * `FL_ZAPF_DINGBATS`
  * `FL_FREE_FONT`
  * `FL_BOLD`
  * `FL_ITALIC`
  * `FL_BOLD_ITALIC`

### Changing the Font of Labels and Text

The label and text fonts of a component can be changed using the `labelfont` and `textfont` methods:

  * `labelfont(Fl_Font)`: changes the label font to the specified `font`
  * `textfont(Fl_Font)`: changes the text font to the specified `font`

### Changing the Font Size

The label and text size of a component can be changed using the `labelsize` and `textsize` methods:

  * `labelsize(int size)`: changes the label font size to the specified `size`
  * `textsize(int size)`: changes the text font size to the specified `size`

### Complete Example

The following example creates an input component and changes the font and size of the label and text as follows:

  * the label font to `FL_BOLD`
  * the label size to `16`
  * the text font to `FL_COURIER_ITALIC`
  * the text size to `14`

<!-- end list -->

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Input* input;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Colors");
    
    input = new Input(25, 25, 350, 25, "Input Label");

    input->labelfont(FL_BOLD);
    input->labelsize(16);

    input->textfont(FL_COURIER_ITALIC);
    input->textsize(14);

    window->show();
}
```

*Application.cpp*

### Alignment

The following `Fl_Align` enums are supported:

  * `FL_ALIGN_CENTER`
  * `FL_ALIGN_TOP`
  * `FL_ALIGN_BOTTOM`
  * `FL_ALIGN_LEFT`
  * `FL_ALIGN_RIGHT`
  * `FL_ALIGN_INSIDE`
  * `FL_ALIGN_TOP_LEFT`
  * `FL_ALIGN_TOP_RIGHT`
  * `FL_ALIGN_BOTTOM_LEFT`
  * `FL_ALIGN_BOTTOM_RIGHT`

### Changing the Alignment

The alignment of a components can be changed using the `align` method:

  * `align(Fl_Align alignment)`: changes the components alignment to the specified `alignment`

### Complete Example

The following example creates three textboxes, each with different alignment:

  * the `textboxLeft` alignment is set to `FL_ALIGN_LEFT`
  * the `textboxCenter` alignment is set to `FL_ALIGN_CENTER`
  * the `textboxRight` alignment is set to `FL_ALIGN_RIGHT`

<!-- end list -->

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::TextBox* textboxLeft;
    bobcat::TextBox* textboxCenter;
    bobcat::TextBox* textboxRight;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Textboxes");
    
    textboxLeft = new TextBox(25, 25, 350, 25, "Text goes here...");
    textboxLeft->align(FL_ALIGN_LEFT);

    textboxCenter = new TextBox(25, 75, 350, 25, "Text goes here...");
    textboxCenter->align(FL_ALIGN_CENTER);

    textboxRight = new TextBox(25, 125, 350, 25, "Text goes here...");
    textboxRight->align(FL_ALIGN_RIGHT);

    window->show();
}
```

*Application.cpp*

### Box Types

The following figure represents the standard `Fl_Boxtype` enums that are supported:

\<div align="center"\>
\<img src="[https://storage.googleapis.com/education-platform-public/fltk-boxtypes.png](https://storage.googleapis.com/education-platform-public/fltk-boxtypes.png)" width="95%" /\>
\<br /\>
\<a href="[https://www.fltk.org/doc-1.4/common.html\#common\_boxtypes](https://www.fltk.org/doc-1.4/common.html#common_boxtypes)"\>FLTK 1.4.1 Documentation\</a\>
\</div\>

### Changing the Box Type

The box type of a components can be changed using the `box` method:

  * `box(Fl_Boxtype boxType)`: changes the components box type to the specified `boxType`

### Complete Example

The following example creates three textboxes, each with different box type:

  * the `textboxBox` box type is set to `FL_BORDER_BOX`
  * the `textboxOval` box type is set to `FL_OVAL_BOX`
  * the `textboxRounded` box type is set to `FL_ROUNDED_BOX`

<!-- end list -->

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::TextBox* textboxBox;
    bobcat::TextBox* textboxOval;
    bobcat::TextBox* textboxRounded;

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Textboxes");
    
    textboxBox = new TextBox(25, 25, 350, 25, "Text goes here...");
    textboxBox->box(FL_BORDER_BOX);

    textboxOval = new TextBox(25, 75, 350, 25, "Text goes here...");
    textboxOval->box(FL_OVAL_BOX);

    textboxRounded = new TextBox(25, 125, 350, 25, "Text goes here...");
    textboxRounded->box(FL_ROUNDED_BOX);

    window->show();
}
```

*Application.cpp*

-----

## 1.12 Manipulation

This section provides an some documentation on how you can change the visibility of components and deactivate/active them.

### Changing the Visibility

The visibility of components can be changed by using `hide()` and `show()`:

  * `hide()`: makes the component invisible
  * `show()`: makes the component visible

### Deactivating and Activating a Component

The visibility of components can be changed by using `hide()` and `show()`:

  * `deactivate()`: makes the component deactivated
  * `activate()`: makes the component visible

### Complete Example

The following example creates creates an input component and four buttons. An on-click event handler determines which button initiated the click event and performs one of the following actions:

  * when the `hideButton` is clicked, the input is hidden
  * when the `showButton` is clicked, the input is shown
  * when the `deactivateButton` is clicked, the input is deactivated
  * when the `activateButton` is clicked, the input is activated

<!-- end list -->

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Input* input;
    bobcat::Button* hideButton;
    bobcat::Button* showButton;
    bobcat::Button* deactivateButton;
    bobcat::Button* activateButton;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    if (sender == hideButton) {
        input->hide();
    }
    else if (sender == showButton) {
        input->show();
    }
    else if (sender == deactivateButton) {
        input->deactivate();
    }
    else if (sender == activateButton) {
        input->activate();
    }
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI Component Manipulation");
    
    input = new Input(25, 25, 350, 25, "Input");

    hideButton = new Button(25, 300, 150, 25, "Hide");
    showButton = new Button(225, 300, 150, 25, "Show");
    deactivateButton = new Button(25, 350, 150, 25, "Deactivate");
    activateButton = new Button(225, 350, 150, 25, "Activate");

    ON_CLICK(hideButton, Application::handleClick);
    ON_CLICK(showButton, Application::handleClick);
    ON_CLICK(deactivateButton, Application::handleClick);
    ON_CLICK(activateButton, Application::handleClick);

    window->show();
}
```

*Application.cpp*

-----

## 1.13 Event Handling

This section provides an overview on how to create and register callback functions that specify the actions to be performed in response to a user action, such as a click event, or when a component state is changed.

All Bobcat UI event callback function must follow two rules:

  * the return type of the function must be `void`
  * the function must take a `bobcat::Widget*` as a parameter

### On Click Event

This section provides an overview on how to create and register a callback function that is executed when a component is clicked.

### Components that Support the On Click Event

All Bobcat UI functions support on-click events.

### Declaring an On Click Event Callback Function Prototype

You can declare an on-click event callback function prototype as follows:

```cpp
void handleClick(bobcat::Widget*);
```

Recall that a Bobcat UI event callback function must take a `bobcat::Widget*` as a parameter and have a `void` return type.

This function prototype declaration is typically made in the `Application` class

### Implementing an On Click Event Callback Function

You can implement the on-click event callback function prototype as follows:

```cpp
void Application::handleClick(Widget* sender) {
    cout << "Button was clicked" << endl;
}
```

This function implementation is typically done in `Application.cpp`.

### Registering the On Click Event Callback Function

To ensure that your on-click event callback function is called when a component changes, you need to register it with that component.

You can register your callback function by specifying the Bobcat UI component and the callback function as arguments in the `ON_CLICK` handler:

```cpp
ON_CLICK(button, Application::handleClick);
```

This registration is typically done in `Application.cpp`.

### Complete Example

The following example defines, implements, and registers an on-click event handler for a button component.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Input* input;
    bobcat::Button* button;

    void handleClick(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleClick(Widget* sender) {
    cout << "Button was clicked" << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI On Click Event");
    
    button = new Button(25, 350, 350, 25, "Click Me");

    ON_CLICK(button, Application::handleClick);

    window->show();
}
```

*Application.cpp*

### On Change Event

This section provides an overview on how to create and register a callback function that is executed when a component changes. In this demonstration, we will implement an on-change event handler to respond to changes in an input field.

### Components that Support the On Change Event

The following Bobcat UI components support the on-change events:

  * `Input`
  * `IntInput`
  * `FloatInput`
  * `Dropdown`
  * `Checkbox`
  * `ListBox`

### Declaring an On Change Event Callback Function Prototype

You can declare an on-change event callback function prototype as follows:

```cpp
void handleChange(bobcat::Widget*);
```

Recall that a Bobcat UI event callback function must take a `bobcat::Widget*` as a parameter and have a `void` return type.

This function prototype declaration is typically made in the `Application` class

### Implementing an On Change Event Callback Function

You can implement the on-change event callback function prototype as follows:

```cpp
void Application::handleChange(Widget* sender) {
    std::string value = input->value();
    cout << "Value: " << value << endl;
}
```

This function implementation is typically done in `Application.cpp`.

### Registering the On Change Event Callback Function

To ensure that your on-change event callback function is called when a component changes, you need to register it with that component.

You can register your callback function by specifying the Bobcat UI component and the callback function as arguments in the `ON_CHANGE` handler:

```cpp
ON_CHANGE(input, Application::handleChange);
```

This registration is typically done in `Application.cpp`.

### Complete Example

The following example defines, implements, and registers an on-change event handler for an input component.

```cpp
#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Input* input;
    bobcat::Button* button;

    void handleChange(bobcat::Widget*);

public:
    Application();

    friend struct ::AppTest;
};

#endif
```

*Application.h*

```cpp
#include "Application.h"

using namespace bobcat;
using namespace std;

void Application::handleChange(Widget* sender) {
    std::string value = input->value();
    cout << "Value: " << value << endl;
}

Application::Application() {
    window = new Window(100, 100, 400, 400, "Bobcat UI On Change Event");
    
    input = new Input(25, 25, 350, 25, "Input");

    ON_CHANGE(input, Application::handleChange);

    window->show();
}
```

*Application.cpp*
