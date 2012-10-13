#ifndef RWX_MODELPREVIEW_HPP
#define RWX_MODELPREVIEW_HPP

#include <map>

#include "recondite.hpp"
#include "rEngine.hpp"

#include "rwxModelView.hpp"
#include "rModel.hpp"
#include "rwxBoneInfo.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/splitter.h>

#include "rwxModelAnimationPanel.hpp"

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
	void OnSkeletonTreeBoneActivated(wxDataViewEvent& event);

	void OnAnimPlayButton(wxCommandEvent& event);
	void OnAnimPauseButton(wxCommandEvent& event);
	void OnAnimStopButton(wxCommandEvent& event);
	void OnAnimSelect(wxCommandEvent& event);
	void OnTick(wxTimerEvent& event);

	void OnSkeletonTreeKeyEvent(wxKeyEvent& event);

private:
	rwxModelView* m_view;
	rEngine* m_engine;
	rGameTime m_gameTime;
	rModel* m_model;

	wxDataViewTreeCtrl* m_skeletonTree;
	rwxDataItemBoneMap m_boneMap;

	rwxModelAnimationPanel* m_animPanel;

	bool m_isPlaying;
	wxTimer m_timer;
	rwxBoneInfo* m_boneInfo;

	DECLARE_EVENT_TABLE()

public:
	enum{
		rwxPREVIEW_SKELETON_TREE = 5000
	};
};

#endif