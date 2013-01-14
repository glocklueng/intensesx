/**
 * @file window.h
 * @brief Common window definitions
 * @author Daniel Szot
 */

#ifndef _LIB_GUI_WINDOW_H
#define _LIB_GUI_WINDOW_H

#include "lib/common.h"
#include "guidefs.h"

#define WS_CTRLMASK         0x0000FFFFL

/**
 * None style.
 */
#define WS_NONE             0x00000000L

/**
 * Indicates the window is a child.
 */
#define WS_CHILD            0x40000000L

/**
 * Creates a main window with caption.
 */
#define WS_CAPTION          0x20000000L

/**
 * Creates a window initially visible.
 */
#define WS_VISIBLE          0x08000000L

/**
 * Creates a window initially disabled.
 */
#define WS_DISABLED         0x04000000L

/**
 * Not implemented, reserved for future use.
 * The window has a fixed frame, i.e. user can not
 * drag the border of the window.
 */
#define WS_DLGFRAME         0x00800000L

/**
 * Not implemented, reserved for future use.
 * Creates a window with border.
 */
#define WS_BORDER           0x00400000L

/**
 * Not implemented, reserved for future use.
 * Indicates the user can set the input focus to the control by
 * using arrow keys.
 * @note This style is valid only for controls.
 */
#define WS_FOCUSSTOP          0x00010000L

struct guiMainWindow
{
    struct guiWindow *head;

    // message listener assigned to this window
    struct msgListener *messageListener;
};

enum windowType
{
    WT_MAIN = 0,
    WT_CONTROL,
};

struct guiWindow
{
    /// window type eg: WT_MAIN, WT_PANEL, WT_BUTTON, WT_STATIC_TEXT
    enum windowType type;

    /// Windows style, logical sum of WS_xxx definitions
    UINT32 windowStyle;

    /// client position and size
    struct guiRect clientFrame;
    /// window position and size
    struct guiRect frame;

    struct guiWndClass *wndClass;

    /// Caption for main window showing on title bat,
    /// if this is control this could be also used as
    /// button caption or static text caption as well
    char *caption;

    /// the styles of window. For main window this is style of client arena
    struct guiColorStyle colorStyle;
    struct graphFont *font;     // pointer to logical font.
    
    UINT16 id;      // Window id
    UINT16 focusId; // Focused child window id

    /// If one of this fieldn will be equal to 0 appropriate window will be found
    /// by gui engine. NOT IMPLEMENTED YET!
    UINT16 idLeft; // Id of window where focus will go after pressing left key
    UINT16 idRight; // Id of window where focus will go after pressing right key
    UINT16 idTop; // Id of window where focus will go after pressing top key
    UINT16 idBottom; // Id of window where focus will go after pressing bottom key

    void *addData; /// the additional data.
    void *addData2; /// the second addtional data.

    /// the address of window procedure.
    retcode (*windowProc)(struct guiWindow *, struct msg *, UINT32, UINT32);

    /// the main window that contains this window.
    /// for main window, always be itself.
    struct guiMainWindow *mainWin;
    
    /// the parent of this window.
    /// for main window, always be HWND_DESKTOP.
    struct guiWindow *parent;

    /// next window in the same container like main window or panel
    struct guiWindow *next;

    /// the handle of first child window.
    struct guiWindow *firstChild;
};

struct guiWindow *guiWindowGetFocused();
struct guiMainWindow *guiWindowGetFocusedMain();
struct guiWindow *guiWindowAtXY(UINT16 pX, UINT16 pY);
struct guiMainWindow *guiWindowAtXYMain(UINT16 pX, UINT16 pY);

#endif