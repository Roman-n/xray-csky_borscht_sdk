//---------------------------------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include "imgui.h"
#include "IM_TextEditor.h"

//---------------------------------------------------------------------------

IM_TextEditor::IM_TextEditor(size_t bufsize)
	: status(esInactive)
{
	buffer.resize(bufsize);
}

#pragma package(smart_init)
