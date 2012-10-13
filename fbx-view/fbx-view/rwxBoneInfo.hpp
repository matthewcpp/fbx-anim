#ifndef RWX_BONEINFO_HPP
#define RWX_BONEINFO_HPP

#include "rTypes.hpp"
#include "rBone.hpp"

class rwxBoneInfo : public wxFrame{
public:
	rwxBoneInfo(wxWindow *parent, wxWindowID id);
	void SetBone(rBone* bone);

	void ClearBoneAttrs();

private:
	void OnClose(wxCloseEvent& event);

	void InitBoneInfo();
	void SetBoneAttrs();
	

	wxBoxSizer* AddBoneInfoRow(const wxString& label , wxStaticText* staticText);

private:
	rBone* m_bone;
	wxPanel* m_infoPanel;

	wxStaticText* m_boneName;
	wxStaticText* m_boneType;
	wxStaticText* m_limbLength;
	wxStaticText* m_boneSize;

	DECLARE_EVENT_TABLE()
};

#endif