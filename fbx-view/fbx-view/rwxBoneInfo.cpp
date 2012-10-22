#include "rwxBoneInfo.hpp"

BEGIN_EVENT_TABLE(rwxBoneInfo , wxFrame)
	EVT_CLOSE(rwxBoneInfo::OnClose)
END_EVENT_TABLE()

rwxBoneInfo::rwxBoneInfo(wxWindow *parent, wxWindowID id)
	:wxFrame(parent, id, "Bone Info", wxDefaultPosition, wxSize(320, 240))
{
	InitBoneInfo();
}

void rwxBoneInfo::OnClose(wxCloseEvent& event){
	event.Veto();
	Hide();
}

void rwxBoneInfo::SetBone(rBone* bone){
	m_bone = bone;
	SetBoneAttrs();
}

void rwxBoneInfo::InitBoneInfo(){
	m_infoPanel = new wxPanel(this , wxID_ANY);
	m_boneName = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_boneType = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_limbLength = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_boneSize = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_initialBonePosition = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_currentBonePosition = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_currentBoneGlobalPosition = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);

	wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
	m_infoPanel->SetSizer(panelSizer);
	panelSizer->Add(AddBoneInfoRow("Name", m_boneName));
	panelSizer->Add(AddBoneInfoRow("FBX Bone Type", m_boneType));
	panelSizer->Add(AddBoneInfoRow("Limb Length", m_limbLength));
	panelSizer->Add(AddBoneInfoRow("Bone Size", m_boneSize));
	panelSizer->Add(AddBoneInfoRow("Initial Bone Position", m_initialBonePosition));
	panelSizer->Add(AddBoneInfoRow("Current Bone Position", m_currentBonePosition));
	panelSizer->Add(AddBoneInfoRow("Current Bone Global Position", m_currentBoneGlobalPosition));

	wxBoxSizer * mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_infoPanel, 1 , wxEXPAND);
	SetSizer(mainSizer);
}

wxBoxSizer* rwxBoneInfo::AddBoneInfoRow(const wxString& label , wxStaticText* staticText){
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(new wxStaticText(m_infoPanel, wxID_ANY, label + ":"), 0 , wxRIGHT, 5);
	sizer->Add(staticText);
	return sizer;
}

void rwxBoneInfo::SetBoneAttrs(){
	if (!m_bone)
		ClearBoneAttrs();

	FbxSkeleton* fbxBone = FbxCast<FbxSkeleton>(m_bone->fbxNode->GetNodeAttribute());

	m_boneName->SetLabelText(m_bone->Name());
	m_boneType->SetLabelText(m_bone->fbxNode->GetTypeName());
	m_limbLength->SetLabelText(wxString::Format("  Length: %f", fbxBone->LimbLength.Get()));
	m_boneSize->SetLabelText(wxString::Format("  Size: %f", fbxBone->Size.Get()));
	m_initialBonePosition->SetLabelText(wxString::Format("%f, %f, %f", m_bone->m_initialPosition.x, m_bone->m_initialPosition.y, m_bone->m_initialPosition.z));
	m_currentBonePosition->SetLabelText(wxString::Format("%f, %f, %f", m_bone->m_currentPosition.x, m_bone->m_currentPosition.y, m_bone->m_currentPosition.z));
	
	rVector3 boneGlobalPosition = m_bone->GetGlobalPosition();
	m_currentBoneGlobalPosition->SetLabelText(wxString::Format("%f, %f, %f", boneGlobalPosition.x, boneGlobalPosition.y, boneGlobalPosition.z));
}

void rwxBoneInfo::ClearBoneAttrs(){
	m_boneName->SetLabelText(wxEmptyString);
	m_boneType->SetLabelText(wxEmptyString);
	m_limbLength->SetLabelText(wxEmptyString);
	m_boneSize->SetLabelText(wxEmptyString);
	m_initialBonePosition->SetLabelText(wxEmptyString);
	m_currentBonePosition->SetLabelText(wxEmptyString);
	m_currentBoneGlobalPosition->SetLabelText(wxEmptyString);
}
