#ifndef PHWIDGETS_CURSOR_H
#define PHWIDGETS_CURSOR_H

#include <photon/PhCursor.h>
#include <photon/PhT.h>

namespace PhWidgets
{
    //! Provides a collection of standard cursors for use by a Photon microGUI application.
    struct Cursors
    {
        enum eCursors
        {
            None = Ph_CURSOR_NONE, //!< No cursor at all.
            Inherit = Ph_CURSOR_INHERIT, //!< Inherit cursor not from the class hierarchy, but from the family hierarchy.
            Pointer = Ph_CURSOR_POINTER, //!< The arrow cursor.
            BigPointer = Ph_CURSOR_BIG_POINTER, //!< The big arrow cursor.
            Move = Ph_CURSOR_MOVE, //!< The four-headed sizing cursor, which consists of four joined arrows that point north, south, east, and west.
            Crosshair = Ph_CURSOR_CROSSHAIR, //!< The crosshair cursor.
            Clock = Ph_CURSOR_CLOCK, //!< The clock cursor.
            Wait = Ph_CURSOR_WAIT, //!< The wait cursor, typically an clock shape.
            Noinput = Ph_CURSOR_NOINPUT, //!< The cursor that indicates that the input is disabled.
            Dont = Ph_CURSOR_DONT, //!< The cursor that indicates that a particular region is invalid for the current operation.
            Finger = Ph_CURSOR_FINGER, //!< The finger cursor, typically used when hovering over a Web link.
            Insert = Ph_CURSOR_INSERT, //!< The I-beam cursor, which is used to show where the text cursor appears when the mouse is clicked.
            DragVertical = Ph_CURSOR_DRAG_VERTICAL, //!< The two-headed vertical (north/south) sizing cursor.
            DragTop = Ph_CURSOR_DRAG_TOP, //!< The two-headed vertical (north/south) sizing cursor.
            DragBottom = Ph_CURSOR_DRAG_BOTTOM, //!< The two-headed vertical (north/south) sizing cursor.
            DragHorizontal = Ph_CURSOR_DRAG_HORIZONTAL, //!< The two-headed horizontal (west/east) sizing cursor.
            DragLeft = Ph_CURSOR_DRAG_LEFT, //!< The two-headed horizontal (west/east) sizing cursor.
            DragRight = Ph_CURSOR_DRAG_RIGHT, //!< The two-headed horizontal (west/east) sizing cursor.
            DragBackDiag = Ph_CURSOR_DRAG_BACKDIAG, //!< The two-headed diagonal (northwest/southeast) sizing cursor.
            DragTL = Ph_CURSOR_DRAG_TL, //!< The two-headed diagonal (northwest/southeast) sizing cursor.
            DragBR = Ph_CURSOR_DRAG_BR, //!< The two-headed diagonal (northwest/southeast) sizing cursor.
            DragForeDiag = Ph_CURSOR_DRAG_FOREDIAG, //!< The two-headed diagonal (northeast/southwest) sizing cursor.
            DragTR = Ph_CURSOR_DRAG_TR, //!< The two-headed diagonal (northeast/southwest) sizing cursor.
            DragBL = Ph_CURSOR_DRAG_BL, //!< The two-headed diagonal (northeast/southwest) sizing cursor.
            LongWait = Ph_CURSOR_LONG_WAIT, //!< The hour glass shaped cursor.
            QuestionPoint = Ph_CURSOR_QUESTION_POINT, //!< The question mark cursor.
            Paste = Ph_CURSOR_PASTE, //!< The copy-paste cursor.

            // Visual Studio styles:
            AppStarting = LongWait, // The cursor that appears when an application starts.
            Default = Ph_CURSOR_POINTER, //!< The default cursor, which is usually an arrow cursor.
            Arrow = Ph_CURSOR_POINTER, //!< The arrow cursor.
            Cross = Crosshair, //!< The crosshair cursor.
            Hand = Finger, //!< The hand cursor, typically used when hovering over a Web link.
            Help = QuestionPoint, //!< The Help cursor, which is a question mark.
            Split = DragHorizontal, //!< The cursor that appears when the mouse is positioned over a horizontal splitter bar.
            IBeam = Insert, //!< The I-beam cursor, which is used to show where the text cursor appears when the mouse is clicked.
            No = Dont, //!< The cursor that indicates that a particular region is invalid for the current operation.
            NoMove2D = Move, //!< The cursor that appears during wheel operations when the mouse is not moving, but the window can be scrolled in both a horizontal and vertical direction.
            SizeAll = Move, //!< The four-headed sizing cursor, which consists of four joined arrows that point north, south, east, and west.
            SizeNESW = DragForeDiag, //!< The two-headed diagonal (northeast/southwest) sizing cursor.
            SizeNS = DragVertical, //!< The two-headed vertical (north/south) sizing cursor.
            SizeNWSE = DragBackDiag, //!< The two-headed diagonal (northwest/southeast) sizing cursor.
            SizeWE = DragHorizontal, //!< The two-headed horizontal (west/east) sizing cursor.
            VSplit = DragVertical, //!< The cursor that appears when the mouse is positioned over a vertical splitter bar.
            WaitCursor = Wait //!< The wait cursor, typically an hourglass shape.
        };
    };
    
    //! Represents the image used to paint the mouse pointer.
    class Cursor
    {
    public:
        
        typedef PhWidgets::Cursors Cursors;

        //! (constructor) 
		/*!
			Initializes a new instance of the Cursor class from the specified default cursor ID.
			@param[in] cursor default cursor ID (see PhWidgets::Cursors::eCursors).
		*/
		Cursor(Cursors::eCursors cursor = Cursors::Default);

		//! (constructor) 
		/*!
			Initializes a new instance of the Cursor class from the specified cursor definition.
			@param[in] def cursor definition.
		*/
		Cursor(const PhCursorDef_t &def);

		//! (copy constructor) 
		/*!
			Constructs a Cursor by copy.
			@param[in] other another Cursor to be used as source to initialize the elements of the container with.
		*/
		Cursor(const Cursor &other);

        //! (destructor)
        ~Cursor();
		
		//! Assigns value in Cursor 
		/*!
			Replaces the contents of the Cursor.
			@param[in] other another Cursor to use as data source.
		*/
		Cursor &operator=(const Cursor &other);

		//! Compares Cursors
		/*!
			Compares the Cursors by their definitions.
			@param[in] other Cursor whose contents to compare.
		*/
		bool operator==(const Cursor &other) const;

        //! Compares Cursors
		/*!
			Compares the Cursors by their definitions.
			@param[in] other Cursor whose contents to compare.
		*/
		bool operator!=(const Cursor &other) const;

		//! Compares Cursors
		/*!
			Compares the Cursors by their definitions.
			@param[in] other Cursor whose contents to compare.
		*/
		bool operator<(const Cursor &other) const;

        operator const PhCursorDef_t*() const;

    private:
        PhCursorDef_t *_def;
        Cursors::eCursors _cursor;

        friend class Widget;
    };

    bool operator==(const Cursors::eCursors &lhs, const Cursor &rhs);
    bool operator!=(const Cursors::eCursors &lhs, const Cursor &rhs);
    bool operator<(const Cursors::eCursors &lhs, const Cursor &rhs);
} // namespace PhWidgets


#endif // PHWIDGETS_CURSOR_H
