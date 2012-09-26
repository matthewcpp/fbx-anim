#include "fbxViewMainFrame.hpp"

BEGIN_EVENT_TABLE(fbxViewMainFrame , wxFrame)
	EVT_MENU(wxID_EXIT, fbxViewMainFrame::OnFileExit)
END_EVENT_TABLE()

fbxViewMainFrame::fbxViewMainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size)
	:wxFrame(parent , id , title , pos , size)
{
	m_engine = new rwxEngine();
	InitFrame();
}

fbxViewMainFrame::~fbxViewMainFrame(){
	delete m_engine;
}

void fbxViewMainFrame::InitFrame(){
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	m_preview = new rwxModelPreview(m_engine, this, wxID_ANY);
	mainSizer->Add(m_preview , 1 , wxALL | wxEXPAND , 5);
	SetSizer(mainSizer);

	InitMenuBar();
	CreateStatusBar(2);
}

void fbxViewMainFrame::InitMenuBar(){
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(wxID_EXIT , "&Exit\tCtrl+Q");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu , "&File");

	SetMenuBar(menuBar);
}

void fbxViewMainFrame::OnFileExit(wxCommandEvent& event){
	Close(true);
}