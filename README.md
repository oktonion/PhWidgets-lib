# PhWidgets-lib

### lightweight fast C++ interface library for QNX Photon microGUI

PhWidgets is an Object-Oriented C++ library interface for the QNX 6 Photon Application Builder Widgets. Full support of PhAB for QNX 6.5 .

All classes of the library provide simple and convenient access to 'resources' of corresponding Photon Widgets as 'properties' with minimum or no overhead. 

Also library implements easy raw access to 'resources' of Photon Widget and the Widget itself, its callbacks, etc as well. The classes of the library itself are lightweight proxies for standart C-functions of Photon Library (like PtSetResource, PtGetResource, ...). Use of the hierarchy of classes constructs userfriendly interface with less ways for "shooting yourself in the foot".

### Implemented widgets ###

![Hierarchy](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_widget.png)

* [Widget](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_widget.html)
* [Basic](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_basic.html)
* [Timer](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_timer.html)
* [Container](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_container.html)
* [Graphic](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_graphic.html)
* [Label](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_label.html)
* [Compound](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_compound.html)
* [Disjoint](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_disjoint.html)
* [Button](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_button.html)
* [Text](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_text.html)
* [Numeric](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_numeric.html)
* [Window](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_window.html)
* [OnOffButton](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_on_off_button.html)
* [ToggleButton](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_toggle_button.html)
* [NumericFloat](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_numeric_float.html)
* [NumericInteger](https://oktonion.github.io/PhWidgets-lib/html/class_ph_widgets_1_1_numeric_integer.html)

### Quick start ###

Now if you have a pointer to standard Photon widget (PtWidget_t*) or it's ABN_ id then with this library widgets are now simple and convenient, just do:

```cpp
PtWidget_t *label_widget;

PhWidgets::Label label(label_widget);// from now on you could manage 'label_widget' with this object 'label'
```

instead of this:

```cpp
PtWidget_t *label = widget;
PtArg_t arg;
PtSetArg( &arg, Pt_ARG_TEXT_STRING, 0, 0 );
PtGetResources( label, 1, &arg );
const char *text = (const char *)(arg.value);

const char *input_text = "test text";
PtSetResource(label, Pt_ARG_TEXT_STRING, input_text, 0);
```

just write this:

```cpp
std::string text = label.Text; //thats it!

label.Text = "test text"; //thats it!
```

or in case you need a raw access to resource:

```cpp
const char *text = label.resource.argument[Label::Arguments::text_string].get();

label.resource.argument[Label::Arguments::text_string].set("test text");
```

for callbacks instead of:

```cpp
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);//callback is defined somewhere

PtCallback_t callbacks[] = { {push_button_cb, NULL} };
PtWidget_t *button = widget;
PtAddCallbacks(button, Pt_CB_ACTIVATE, callbacks, 1);
```

just write that:

```cpp
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);//callback is defined somewhere

button.Activate += push_button_cb; //simple as that!
```

or in case you need a raw access to callback:

```cpp
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);//callback is defined somewhere

button.resource.callback[Button::Callbacks::activate].add(push_button_cb);
```

More complex use case:

```cpp
// You have constructed somewhere PhWidgets::Button button1
{
    using namespace PhWidgets;

    Containter button1_containter = button1.Parent;

    std::set<Widget> widgets = button1_containter.Widgets;

    // turn all buttons of the button1 parent red
    // except for button1
    // change cursors of all buttons respectively

    for(std::set<Widget>::iterator iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if(nullptr == dynamic_widget_cast<Button>(*it))
            continue;
        
        Button button = *it;
        if(button != button1)
        {
            button.Color = Drawing::Colors::Red;
            button.Cursor = Cursors::No;
        }
        else
        {
            button.Color = Drawing::Colors::Green;
            button.Cursor = Cursors::Finger;
        }
        
    }
}
```

PhWidgets library use default photon microGUI libraries (like 'Ap', 'ph' etc.) and photon microGUI 'phexlib' library.

# Build

To build lib execute '.makelib.sh' - directory slib will contain your library with all headers and source code needed.

# Install

* To install lib to PhAB project simply call '.exportlib.sh' with path to your project directory as 1st parameter.
* To install manually copy 'include' directory and 'AbWidgetsWrap.cpp' to your PhAB project destination ('AbWidgetsWrap.cpp' **should be** in the same dir as PhAB project headers 'ablibs.h' and 'abimport.h' to be compiled). Place library 'libphwidgets.a' where you store the lib-files (f.e. '$ProjectDir\x86\o\' and '$ProjectDir\x86\o-g\' for x86 platform).

**Do not forget to include 'libphwidgets.a' and 'phexlib' to your project build!**
