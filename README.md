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
const char *text = label.argument.resource[Label::Arguments::text_string].get(); //a little bit excessive syntax, so may change
```
