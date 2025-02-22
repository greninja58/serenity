/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Mustafa Quraish <mustafa@serenityos.org>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "PickerTool.h"
#include "../ImageEditor.h"
#include "../Layer.h"
#include <LibGUI/BoxLayout.h>
#include <LibGUI/CheckBox.h>

namespace PixelPaint {

void PickerTool::on_mousedown(Layer* layer, MouseEvent& event)
{
    if (!layer)
        return;
    auto layer_event = event.layer_event();
    m_editor->set_editor_color_to_color_at_mouse_position(layer_event, m_sample_all_layers);
}

void PickerTool::on_mouseup(Layer*, MouseEvent& event)
{
    auto layer_event = event.layer_event();
    if (layer_event.buttons() & GUI::MouseButton::Primary || layer_event.buttons() & GUI::MouseButton::Secondary)
        return;
    m_editor->set_appended_status_info(DeprecatedString::empty());
}

void PickerTool::on_mousemove(Layer* layer, MouseEvent& event)
{
    if (!layer)
        return;
    auto layer_event = event.layer_event();
    if (!(layer_event.buttons() & GUI::MouseButton::Primary || layer_event.buttons() & GUI::MouseButton::Secondary))
        return;
    m_editor->set_editor_color_to_color_at_mouse_position(layer_event, m_sample_all_layers);
}

GUI::Widget* PickerTool::get_properties_widget()
{
    if (!m_properties_widget) {
        m_properties_widget = GUI::Widget::construct();
        m_properties_widget->set_layout<GUI::VerticalBoxLayout>();

        auto& sample_checkbox = m_properties_widget->add<GUI::CheckBox>(String::from_utf8("Sample all layers"sv).release_value_but_fixme_should_propagate_errors());
        sample_checkbox.set_checked(m_sample_all_layers);
        sample_checkbox.on_checked = [&](bool value) {
            m_sample_all_layers = value;
        };
    }

    return m_properties_widget.ptr();
}

}
