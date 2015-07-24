#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::_priv::osxBridge
    @ingroup _priv
    @brief OSX app wrapper (only used for Metal renderer)
    
    This manages the NSApplication object, window, MTKView and 
    calls the application-on-frame method from the controlled by the MTKView.
    
    NOTE: the event handling code has been mostly ripped from GLFW3!
*/
#include "Core/Types.h"
#include "Core/Macros.h"
#include "Core/osx/osxInputDefs.h"

#if defined(__OBJC__)
#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>
#define ORYOL_OBJC_TYPED_ID(clazz) id<clazz>
#define ORYOL_OBJC_ID id
static_assert(sizeof(void*) == sizeof(id), "sizeof(void*) doesn't match sizeof(id)!");
#else
#define ORYOL_OBJC_TYPED_ID(clazz) void*
#define ORYOL_OBJC_ID void*
typedef void* MTLDevice;
typedef void MTKView;
#endif

#if ORYOL_USE_ARC
#define ORYOL_OBJC_RELEASE(obj)
#else
#define ORYOL_OBJC_RELEASE(obj) [obj release]
#endif

namespace Oryol {
class App;
namespace _priv {

class osxBridge {
public:
    /// constructor
    osxBridge();
    /// destructor
    ~osxBridge();
    /// get checked pointer
    static osxBridge* ptr();

    /// setup the object
    void setup(App* app);
    /// discard the object
    void discard();
    /// start the main loop (does not return until app quits)
    void startMainLoop();
    /// return true if the window requests app to close
    bool shouldClose();

    /// called from AppState Destroy
    void onDestroy();
    /// called by app delegate when app has launched
    void onDidFinishLaunching();
    /// called by app delagate when application should terminate
    void onShouldTerminate();
    /// called by app delegate when application will terminate
    void onWillTerminate();
    /// called by app delegate when screen parameters have changed
    void onDidChangeScreenParameters();
    /// called by app when occlusion state changes
    void onDidChangeOcclusionState();

    /// called when window receives close request
    void onWindowShouldClose();
    /// called when window did resize
    void onWindowDidResize();
    /// called when window did miniaturize
    void onWindowDidMiniaturize();
    /// called when window did deminiaturize
    void onWindowDidDeminiaturize();
    /// called when window did become key window
    void onWindowDidBecomeKey();
    /// called when window no longer key window
    void onWindowDidResignKey();

    /// called from view when mouse is clicked
    void onMouseClick(int button, int action, int mods);
    /// called from view when mouse cursor moves
    void onCursorMotion(float64 x, float64 y);
    /// called form view when mouse cursor enters/leaves window
    void onCursorEnter(bool entered);
    /// called from view when a key has been pressed
    void onInputKey(int key, int scancode, int action, int mods);
    /// called from view when a character has been entered
    void onInputChar(unsigned int codepoint, int mods, int plain);
    /// called form view when mouse wheel is scrolled
    void onInputScroll(float64 xoffset, float64 yoffset);

    /// called per frame by the MTKView delegate
    void onFrame();

    /// create the application window (hidden)
    void createWindow();
    /// actually show the window (called from displayMgr)
    void showWindow();
    /// setup the key translation table
    void setupKeyTable();

    /// callbacks (similar to GLFW)
    struct {
        // callback function typedefs
        typedef void (*windowFocusFunc)(bool gainedInputFocus);
        typedef void (*windowIconifyFunc)(bool iconified);
        typedef void (*framebufferSizeFunc)(int x, int y);
        typedef void (*mouseButtonFunc)(int btn, int action, int modifiers);
        typedef void (*cursorPosFunc)(double x, double y);
        typedef void (*cursorEnterFunc)(bool entered);
        typedef void (*scrollFunc)(double x, double y);
        typedef void (*keyFunc)(int key, int scancode, int action, int modifiers);
        typedef void (*charFunc)(uint32 codepoint);
        typedef void (*charModsFunc)(uint32 codepoint, int modifiers);

        /// window position changed callback hook
        windowFocusFunc focus = nullptr;
        windowIconifyFunc iconify = nullptr;
        framebufferSizeFunc fbsize = nullptr;
        mouseButtonFunc mouseButton = nullptr;
        cursorPosFunc cursorPos = nullptr;
        cursorEnterFunc cursorEnter = nullptr;
        scrollFunc scroll = nullptr;
        keyFunc key = nullptr;
        charFunc character = nullptr;
        charModsFunc charmods = nullptr;
    } callbacks;

    static osxBridge* self;
    App* app;
    bool shouldCloseFlag;
    ORYOL_OBJC_ID appDelegate;
    ORYOL_OBJC_ID appWindow;
    ORYOL_OBJC_ID appWindowDelegate;
    ORYOL_OBJC_TYPED_ID(MTLDevice) mtlDevice;
    ORYOL_OBJC_ID mtkViewDelegate;
    MTKView* mtkView;

    uint32 modifierFlags;
    float64 warpDeltaX, warpDeltaY;
    char  mouseButtons[ORYOL_OSXBRIDGE_MOUSE_BUTTON_LAST + 1];
    char  keys[ORYOL_OSXBRIDGE_KEY_LAST + 1];
    int16 publicKeys[256];
};

} // namespace _priv
} // namespace Oryol

