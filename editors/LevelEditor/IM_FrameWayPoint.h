#ifndef IM_FrameWayPointH
#define IM_FrameWayPointH

#include "../ECore/ImGui/IM_Window.h"

class IM_FrameWayPoint : public IM_Window
{
	public:
    bool m_way_mode;
    bool m_point_mode;

    bool m_auto_link;

	public:
    IM_FrameWayPoint()
    	: m_way_mode(true),
          m_point_mode(false),
          m_auto_link(false)
    {
    }

    void Add1Links();
    void Add2Links();
    void InvertLinks();
    void ConvertTo1Links();
    void ConvertTo2Links();
    void RemoveLinks();

    virtual void Render();
};

#endif
