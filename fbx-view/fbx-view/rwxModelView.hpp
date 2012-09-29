#ifndef RWX_MODELVIEW_HPP
#define RWX_MODELVIEW_HPP

#include "recondite.hpp"
#include "rEngine.hpp"
#include "rwx/rwxGlView.hpp"

#include "rModel.hpp"

#include <wx/wx.h>

class rwxModelView : public rwxGLView{
public:
	rwxModelView(rEngine* engine, wxWindow* parent, wxWindowID id=wxID_ANY);

	void DrawScene();

	void OnPaint(wxPaintEvent& event);
	void CalculateCameraDefaultPosition(const rAlignedBox3& box);

	void SetModel(rModel* model);

private:

	void DrawModelBox();
	void DrawModelSkeleton();
	void DrawSkeletonPositions(rBoneList& bones);
	void DrawSkeletonBones(rBoneList& bones);

private:
	rModel* m_model;

	DECLARE_EVENT_TABLE()
};

#endif