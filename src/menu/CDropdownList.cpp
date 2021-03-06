/*
 * CDropdownList.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: nullifiedcat
 */

#include "menu/CDropdownList.h"
#include "menu/CDropdownEntry.h"
#include "menu/CDropdown.h"

#include "common.hpp"
#include "sdk.hpp"

CDropdownList::CDropdownList(std::string name, CDropdown *menu, int offset)
    : CBaseContainer(name, nullptr)
{
    m_pMenu = menu;
    Hide();
    SetZIndex(5);
}

CDropdownList::~CDropdownList()
{
    for (auto entry : m_entries)
    {
        delete entry;
    }
}

void CDropdownList::AddEntry(std::string name)
{
    CDropdownEntry *entry =
        new CDropdownEntry("entry", this, name, m_entries.size());
    auto size = GetSize();
    entry->SetSize(size.first, 18);
    AddChild(entry);
    m_entries.push_back(entry);
    SetSize(size.first, m_entries.size() * 18);
}

void CDropdownList::SetValue(int value)
{
    m_pMenu->SetValueInternal(value);
    Hide();
}

void CDropdownList::Draw(int x, int y)
{
    auto size = GetSize();
    draw::DrawRect(x, y, size.first, size.second,
                   colorsint::Transparent(colorsint::black, 0.85));
    draw::OutlineRect(x, y, size.first, size.second, NCGUIColor());
    CBaseContainer::Draw(x, y);
}

void CDropdownList::MoveChildren()
{
    for (int i = 0; i < ChildCount(); i++)
    {
        auto child = ChildByIndex(i);
        child->SetOffset(0, i * 18);
    }
}
