#ifndef RWX_MODELPREVIEW_HPP
#define RWX_MODELPREVIEW_HPP

#include <map>

#include "recondite.hpp"
#include "rEngine.hpp"

#include "rwxModelView.hpp"
#include "rModel.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/splitter.h>

typedef std::map<wxDataViewItem , rBone*> rwxDataItemBoneMap;

class rwxModelPreview : public wxPanel {
public:
	rwxModelPreview(rEngine* engine, wxWindow* parent, wxWindowID id=wxID_ANY);

	void SetModel(rModel* model);

private:
	void InitModelPreview();

	void BuildSkeletonTree(rModel* model);
	void CreateSkeletonTreeNode(wxDataViewItem& parentItem, rBone* bone);

	void OnSkeletonTreeBoneSelect(wxDataViewEvent& event);

private:
	rwxModelView* m_view;
	rEngine* m_engine;

	wxDataViewTreeCtrl* m_skeletonTree;
	rwxDataItemBoneMap m_boneMap;

public:
	enum{
		rwxPREVIEW_SKELETON_TREE = 5000
	};

	DECLARE_EVENT_TABLE()
};

#endif