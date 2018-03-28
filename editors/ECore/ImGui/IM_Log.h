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

    bool open;
    bool has_new_messages;
    xr_list<Message> msgs;

	public:
    IM_Log()
    	: open(true),
          has_new_messages(false)
    {
    }
    ~IM_Log()
    {
    	Clear();
    }

    void Open() { open = true; }
    void Close() { open = false; }
    bool IsOpen() const { return open; }

    void Clear();
    void ClearSelected();

    void AddMessage(MessageType mt, const char* msg);

    virtual void Render();
};

extern IM_Log imLog;

#endif
