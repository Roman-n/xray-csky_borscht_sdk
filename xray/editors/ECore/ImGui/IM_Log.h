//---------------------------------------------------------------------------

#ifndef IM_LogH
#define IM_LogH

#include "IM_Window.h"
//---------------------------------------------------------------------------

class IM_Log : public IM_Window
{
	public:
    enum MessageType
    {
    	mtInfo,
        mtError,
        mtConfirmation
    };

    struct Message
    {
    	MessageType type;
    	bool selected;
        xr_string text;

        Message(MessageType mt, const char* text)
        	: type(mt),
              selected(false),
              text(text)
        {
        }
    };

    bool show_log;
    bool has_new_messages;
    xr_list<Message> msgs;

	public:
    IM_Log()
    	: show_log(true),
          has_new_messages(false)
    {
    }
    ~IM_Log()
    {
    	Clear();
    }

    void Open() { show_log = true; }
    void Close() { show_log = false; }
    bool IsOpen() const { return show_log; }

    void Clear();
    void ClearSelected();

    void AddMessage(MessageType mt, const char* msg);

    virtual void Render();
};

extern ECORE_API IM_Log imLog;

#endif
