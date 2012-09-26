#ifndef FBX_VIEW_APP
#define FBX_VIEW_APP

#include <wx/wx.h>

#include "fbxViewMainFrame.hpp"

class fbxViewApp : public wxApp{
	bool OnInit();
};

DECLARE_APP(fbxViewApp)

#endif