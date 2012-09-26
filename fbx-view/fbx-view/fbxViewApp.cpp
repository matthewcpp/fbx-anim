#include "fbxViewApp.hpp"

bool fbxViewApp::OnInit(){
	fbxViewMainFrame* frame = new fbxViewMainFrame(NULL , wxID_ANY, "FBX Viewer", wxDefaultPosition, wxSize(640,480));
	frame->Show(true);

	return true;
}

IMPLEMENT_APP(fbxViewApp)