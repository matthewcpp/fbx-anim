#ifndef FBXVIEW_MAINFRAME_HPP
#define FBXVIEW_MAINFRAME_HPP

#include "rwx/rwxEngine.hpp"

#include "rwxModelPreview.hpp"

#include "rModel.hpp"
#include "rModelLoader.hpp"

#include <wx/wx.h>

class fbxViewMainFrame : public wxFrame{
public:
	fbxViewMainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize);
	~fbxViewMainFrame();
private:
	void OnFileExit(wxCommandEvent& event);
	void OnFileOpen(wxCommandEvent& event);

	void LoadFBX();

private:
	void InitFrame();
	void InitMenuBar();

	DECLARE_EVENT_TABLE()

	rwxModelPreview* m_preview;
	rwxEngine* m_engine;

	rModel m_model;
};

#endif