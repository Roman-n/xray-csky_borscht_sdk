#ifndef IM_ManipulatorH
#define IM_ManipulatorH

class IM_Manipulator
{
	public:
	bool m_active;
	
	IM_Manipulator()
		: m_active(false)
	{}
	
	void Render();
};

extern IM_Manipulator imManipulator;

#endif