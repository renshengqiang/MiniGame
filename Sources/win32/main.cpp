#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "Utils.h"

USING_NS_CC;
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("MiniGame");
    eglView->setFrameSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	eglView->setFrameZoomFactor(0.5);
    return CCApplication::sharedApplication()->run();
}
