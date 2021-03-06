/*
 * CMenuList.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#include "menu/CMenuList.h"

#include "menu/CMenuListEntry.h"
#include "menu/CMenuWindow.h"

#include "common.hpp"
#include "sdk.hpp"

CMenuList::CMenuList(std::string name, CMenuWindow *parent)
    : CBaseContainer(name, parent)
{
}

void CMenuList::AddEntry(std::string id, std::string name)
{
    CMenuListEntry *entry = new CMenuListEntry("entry_" + id, this, id);
    entry->SetText(name);
    entry->SetCallback([this](CBaseButton *thisptr) {
        CMenuWindow *window =
            dynamic_cast<CMenuWindow *>(thisptr->GetParent()->GetParent());
        window->SelectTab(thisptr->Props()->GetString("entry"));
    });
    AddChild(entry);
}

void CMenuList::SelectEntry(std::string id)
{
    m_pSelected = dynamic_cast<CMenuListEntry *>(ChildByName("entry_" + id));
}

void CMenuList::MoveChildren()
{
    int cc  = ChildCount();
    auto ms = GetMaxSize();
    for (int i = 0; i < cc; i++)
    {
        auto child = ChildByIndex(i);
        child->SetMaxSize(ms.first, ms.second / cc);
        child->SetOffset(0, (ms.second / cc) * i);
    }
}
