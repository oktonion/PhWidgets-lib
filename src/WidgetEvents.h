#ifndef WIDGET_EVENTS_H
#define WIDGET_EVENTS_H

#include <photon/PhT.h>

namespace PhWidgets
{
	struct Events
	{
		enum eEvents
		{

			boundary = Ph_EV_BOUNDARY,///Emitted when the pointer crosses region boundaries.
			press = Ph_EV_BUT_PRESS,///Emitted when the user presses a button on a pointing device.
			release = Ph_EV_BUT_RELEASE,///Emitted when the user releases a pointing-device button.
			repeat = Ph_EV_BUT_REPEAT,///Emitted when the user presses an auto-repeating button on a pointing device.
			dndrop = Ph_EV_DNDROP,///These events are emitted during a drag-and-drop operation.
			drag = Ph_EV_DRAG,///Used by an application to initiate drag events, to determine their completion, and to indicate intermediate drag-motion events.
			draw = Ph_EV_DRAW,///Emitted by the Pg functions when applications perform draw operations.
			expose = Ph_EV_EXPOSE,///Emitted by the Photon Manager on behalf of a region being moved, resized, or removed from the event space.
			info = Ph_EV_INFO,///All regions must always be transparent to Ph_EV_INFO events. They are emitted by applications or service providers to disseminate information or respond to requests.
			key = Ph_EV_KEY,///Emitted when a key state changes (for example, the user presses or releases a key).
			button = Ph_EV_PTR_MOTION_BUTTON,///Emitted when the user moves the pointing device while pressing a button.
			nobutton = Ph_EV_PTR_MOTION_NOBUTTON,///Emitted when the user moves the pointing device without pressing a button.
			raw = Ph_EV_RAW,///These are raw, unfocused events that the Photon server handles. 
			service = Ph_EV_SERVICE,///These events may be emitted by applications requesting services or providing information to services, other applications that provide some kind of service in a Photon system.
			system = Ph_EV_SYSTEM,///Are emitted when Photon or a service wants to inform applications of changes in the system.
			timer = Ph_EV_TIMER,///Emitted by an application directly to the Device region to request a reciprocal event after a specific amount of time has elapsed (arm a timer).
			user = Ph_EV_USER,///A custom event type that your application can use to interact with other applications. 
			wm = Ph_EV_WM///Both the Window Manager and applications can emit this event. The Window Manager emits this event when an application has asked to be notified. An application can emit this event to communicate to the Window Manager regarding windows. 

		};
	};
}

#endif // WIDGET_EVENTS_H