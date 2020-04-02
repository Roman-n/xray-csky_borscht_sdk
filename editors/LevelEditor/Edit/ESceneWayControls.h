#ifndef ESceneWayControlsH
#define ESceneWayControlsH

#include "ESceneControlsCustom.h"

// refs
class CWayPoint;

enum{
	estWayModeWay,
	estWayModePoint
};
//---------------------------------------------------------------------------
class TUI_ControlWayPointAdd: public TUI_CustomControl{
public:
    TUI_ControlWayPointAdd(int st, int act, ESceneToolBase* parent);
    virtual ~TUI_ControlWayPointAdd(){;}
	virtual bool Start  (TShiftState _Shift);
    virtual void OnEnter();
};

class TUI_ControlWayPointSelect: public TUI_CustomControl{
public:
    TUI_ControlWayPointSelect(int st, int act, ESceneToolBase* parent);
	virtual bool Start  (TShiftState _Shift);
	virtual bool End    (TShiftState _Shift);
	virtual void Move   (TShiftState _Shift);
};
#endif //UI_WayPointToolsH
