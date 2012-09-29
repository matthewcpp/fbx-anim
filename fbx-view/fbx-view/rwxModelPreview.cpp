#include "rwxModelPreview.hpp"

BEGIN_EVENT_TABLE(rwxModelPreview, wxPanel)
	EVT_DATAVIEW_SELECTION_CHANGED(rwxModelPreview::rwxPREVIEW_SKELETON_TREE , rwxModelPreview::OnSkeletonTreeBoneSelect)
END_EVENT_TABLE()

rwxModelPreview::rwxModelPreview(rEngine* engine, wxWindow* parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_engine = engine;

	InitModelPreview();
}

void rwxModelPreview::InitModelPreview(){
	wxSplitterWindow* m_splitter = new wxSplitterWindow(this, wxID_ANY);

	m_skeletonTree = new wxDataViewTreeCtrl(m_splitter, rwxPREVIEW_SKELETON_TREE);
	m_skeletonTree->SetMinSize(wxSize(150, -1));
	m_view = new rwxModelView(m_engine , m_splitter , wxID_ANY);

	m_splitter->SplitVertically(m_skeletonTree,m_view, 150);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(m_splitter , 1 , wxEXPAND);
	SetSizer(mainSizer);
}

void rwxModelPreview::SetModel(rModel* model){
	model->CalculateBoundingBox();

	BuildSkeletonTree(model);
	m_view->SetModel(model);
}

void rwxModelPreview::BuildSkeletonTree(rModel* model){
	m_skeletonTree->DeleteAllItems();
	m_boneMap.clear();

	wxDataViewItem root(NULL);

	rSkeleton* skeleton = model->GetSkeleton();
	CreateSkeletonTreeNode(root , skeleton->GetRoot());
}

void rwxModelPreview::CreateSkeletonTreeNode(wxDataViewItem& parentItem, rBone* bone){
	wxDataViewItem item;

	if (bone){
		size_t childCount = bone->NumChildren();

		if (childCount == 0)
			item = m_skeletonTree->AppendItem(parentItem, bone->Name());
		else{
			item = m_skeletonTree->AppendContainer(parentItem, bone->Name());
			for (size_t i = 0; i < childCount; i++)
				CreateSkeletonTreeNode(item , bone->GetChild(i));
		}

		m_boneMap[item] = bone;
	}
}

void rwxModelPreview::OnSkeletonTreeBoneSelect(wxDataViewEvent& event){
	m_view->SetSelectedBone(m_boneMap[event.GetItem()]);
}