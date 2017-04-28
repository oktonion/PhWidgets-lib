# PhWidgets-lib
### lightweight fast C++ interface library for QNX Photon GUI


PhWidgets is a C++ library interface for the QNX Photon Widgets. 

All classes of the library provide simple and convenient access to 'resources' of corresponding Photon Widgets as 'properties' with minimum or no overhead. 

Also library implements easy raw access to 'resources' of Photon Widget and the Widget itself, its callbacks, etc as well. The classes of the library itself are lightweight proxies for standart C-functions of Photon Library (like PtSetResource, PtGetResource, ...). Use of the hierarchy of classes constructs userfriendly interface with less ways to "shooting yourself in the foot".

instead of this:
```
PtWidget_t *label = widget;
PtArg_t arg;
PtSetArg( &arg, Pt_ARG_TEXT_STRING, 0, 0 );
PtGetResources( label, 1, &arg );
const char *text = (const char *)(arg.value);
```

just write this:
```
std::string text = label.Caption; //thats it!
```

or in case you need a raw access to resource:
```
 // you can use Pt_ARG_TEXT_STRING instead of Label::Arguments::text_string btw
const char *text = label.resource.argument[Label::Arguments::text_string].get(); //a little bit excessive syntax, so may change
```

for callbacks instead of:
```
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);

PtCallback_t callbacks[] = { {push_button_cb, NULL} };
PtWidget_t *button = widget;
PtAddCallbacks(button, Pt_CB_ACTIVATE, callbacks, 1);
```

just write that:
```
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);

button.Activate += push_button_cb; //simple as that!
```

or in case you need a raw access to callback:
```
int push_button_cb( PtWidget_t *, void *, PtCallbackInfo_t *);

 // you can use Pt_CB_ACTIVATE instead of Button::Callbacks::activate btw
button.resource.callback[Button::Callbacks::activate].add(push_button_cb); //a little bit excessive syntax, so may change
```
