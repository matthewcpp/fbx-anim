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
	m_fbxBoneGlobalPosition = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);
	m_fbxBoneGlobalRotation = new wxStaticText(m_infoPanel, wxID_ANY, wxEmptyString);

	m_gridSizer = new wxFlexGridSizer(2);
	m_infoPanel->SetSizer(m_gridSizer);
	AddBoneInfoRow("Name", m_boneName);
	AddBoneInfoRow("FBX Bone Type", m_boneType);
	AddBoneInfoRow("Limb Length", m_limbLength);
	AddBoneInfoRow("Bone Size", m_boneSize);
	AddBoneInfoRow("Initial Bone Position", m_initialBonePosition);
	AddBoneInfoRow("Current Bone Position", m_currentBonePosition);
	AddBoneInfoRow("Current Bone Global Position", m_currentBoneGlobalPosition);
	AddBoneInfoRow("FBX Bone Node Global Position", m_fbxBoneGlobalPosition);
	AddBoneInfoRow("FBX Bone Node Global Rotation", m_fbxBoneGlobalRotation);

	wxBoxSizer * mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_infoPanel, 1 , wxEXPAND);
	SetSizer(mainSizer);
}

void rwxBoneInfo::AddBoneInfoRow(const wxString& label , wxStaticText* staticText){
	m_gridSizer->Add(new wxStaticText(m_infoPanel, wxID_ANY, label + ":"), 0 , wxRIGHT, 5);
	m_gridSizer->Add(staticText);
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
	
	m_fbxBoneGlobalPosition->SetLabelText(wxString::Format("%f, %f, %f", m_bone->m_fbxGlobalDefaultPosition.x, m_bone->m_fbxGlobalDefaultPosition.y, m_bone->m_fbxGlobalDefaultPosition.z));
	m_fbxBoneGlobalRotation->SetLabelText(wxString::Format("%f, %f, %f", m_bone->m_fbxGlobalDefaultRotation.x, m_bone->m_fbxGlobalDefaultRotation.y, m_bone->m_fbxGlobalDefaultRotation.z));

}

void rwxBoneInfo::ClearBoneAttrs(){
	m_boneName->SetLabelText(wxEmptyString);
	m_boneType->SetLabelText(wxEmptyString);
	m_limbLength->SetLabelText(wxEmptyString);
	m_boneSize->SetLabelText(wxEmptyString);
	m_initialBonePosition->SetLabelText(wxEmptyString);
	m_currentBonePosition->SetLabelText(wxEmptyString);
	m_currentBoneGlobalPosition->SetLabelText(wxEmptyString);
	m_fbxBoneGlobalRotation->SetLabelText(wxEmptyString);
	m_fbxBoneGlobalPosition->SetLabelText(wxEmptyString);
}
