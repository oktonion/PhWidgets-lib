# PhWidgets-lib
### lightweight fast C++ interface library for QNX Photon microGUI


PhWidgets is a C++ library interface for the QNX Photon Application Builder Widgets. Full support of PhAB for QNX 6.

All classes of the library provide simple and convenient access to 'resources' of corresponding Photon Widgets as 'properties' with minimum or no overhead. 

Also library implements easy raw access to 'resources' of Photon Widget and the Widget itself, its callbacks, etc as well. The classes of the library itself are lightweight proxies for standart C-functions of Photon Library (like PtSetResource, PtGetResource, ...). Use of the hierarchy of classes constructs userfriendly interface with less ways for "shooting yourself in the foot".

instead of this:
```
PtWidget_t *label = widget;
PtArg_t arg;
PtSetArg( &arg, Pt_ARG_TEXT_STRING, 0, 0 );
PtGetResources( label, 1, &arg );
const char *text = (const char *)(arg.value);

const char *input_text = "test text";
PtSetResource(label, Pt_ARG_TEXT_STRING, input_text, 0);
```

just write this:
```
std::string text = label.Caption; //thats it!

label.Caption = "test text"; //thats it!
```

or in case you need a raw access to resource:
```
const char *text = label.resource.argument[Label::Arguments::text_string].get();

label.resource.argument[Label::Arguments::text_string].set("test text");
```

for callbacks instead of:
```
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);//callback is defined somewhere

PtCallback_t callbacks[] = { {push_button_cb, NULL} };
PtWidget_t *button = widget;
PtAddCallbacks(button, Pt_CB_ACTIVATE, callbacks, 1);
```

just write that:
```
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);//callback is defined somewhere

button.Activate += push_button_cb; //simple as that!
```

or in case you need a raw access to callback:
```
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);//callback is defined somewhere

button.resource.callback[Button::Callbacks::activate].add(push_button_cb);
```

# Build
To build lib execute '.makelib.sh' - directory slib will contain your library with all headers and source code needed.

# Install
- To install lib to PhAB project simply call '.exportlib.sh' with path to your project directory as 1st parameter. 
- To install manually copy 'include' directory and 'AbWidgetsWrap.cpp' to your PhAB project destination ('AbWidgetsWrap.cpp' **should be** in the same dir as PhAB project headers 'ablibs.h' and 'abimport.h' to be compiled). Place library 'libphwidgets.a' where you store the lib-files (f.e. '$ProjectDir\x86\o\' and '$ProjectDir\x86\o-g\' for x86 platform). 

**Do not forget to include 'libphwidgets.a' to your project build!**

