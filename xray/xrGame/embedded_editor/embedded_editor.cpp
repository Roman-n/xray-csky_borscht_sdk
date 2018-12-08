#include "stdafx.h"
#include "embedded_editor.h"
#include <functional>

namespace {
using Registry = std::map<Editors, std::function<EditorCreator>>;
Registry& registry()
{
    static Registry registry;
    return registry;
}

using EditorId = std::pair<Editors, void*>;
std::map<EditorId, std::unique_ptr<Editor>> activeEditors;
}

EditorRegistrator::EditorRegistrator(Editors type, EditorCreator creator) { registry().emplace(type, creator); }

void switchEditor(Editors type)
{
    EditorId id(type, nullptr);
    if (activeEditors.find(id) == activeEditors.end()) {
        activeEditors[id] = std::unique_ptr<Editor>(registry()[type]());
    } else
        activeEditors.erase(id);
}

void showEditor(Editor* editor)
{
    EditorId id(editor->type(), editor);
    if (activeEditors.find(id) == activeEditors.end()) {
        activeEditors[id] = std::unique_ptr<Editor>(editor);
    } else
        activeEditors.erase(id);
}

void drawActiveEditors()
{
    for (auto i = activeEditors.begin(), end = activeEditors.end(); i != end; ++i) {
        bool show = i->second->draw();
        if (!show)
            activeEditors.erase(i->first);
    }
}

bool editorExists(std::function<bool(Editor*)> f)
{
    auto i = std::find_if(activeEditors.begin(), activeEditors.end(), [f](const auto& el) { return f(el.second.get()); });
    return i != activeEditors.end();
}
