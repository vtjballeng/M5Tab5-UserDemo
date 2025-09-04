/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "app_alarm_clock.h"
#include "../app_main_menu/app_main_menu.h"
#include <hal/hal.h>
#include <mooncake.h>
#include <mooncake_log.h>
#include <lvgl.h>
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>

using namespace mooncake;
using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

void AppAlarmClock::View::init() {
        LvglLockGuard lock;
        
        // Set background color
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
        lv_obj_remove_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);
        
        // TEST label
        label_test = std::make_unique<Label>(lv_screen_active());
        label_test->setText("TEST");
        label_test->setTextFont(&lv_font_montserrat_36);
        label_test->setTextColor(lv_color_hex(0xFFFFFF));
        label_test->align(LV_ALIGN_CENTER, 0, 0);
        
        // Back button
        btn_back = std::make_unique<Button>(lv_screen_active());
        btn_back->setSize(200, 60);
        btn_back->align(LV_ALIGN_BOTTOM_MID, 0, -50);
        btn_back->setRadius(15);
        btn_back->setBgColor(lv_color_hex(0xE74C3C));
        btn_back->setShadowWidth(0);
        btn_back->label().setText("Back");
        btn_back->label().setTextFont(&lv_font_montserrat_24);
        btn_back->label().setTextColor(lv_color_hex(0xFFFFFF));
}

void AppAlarmClock::View::cleanup() {
        LvglLockGuard lock;
        label_test.reset();
        btn_back.reset();
}

AppAlarmClock::AppAlarmClock()
{
    setAppInfo().name = "AppAlarmClock";
}

void AppAlarmClock::onCreate()
{
    mclog::tagInfo(getAppInfo().name, "on create");
    open();
}

void AppAlarmClock::onOpen()
{
    mclog::tagInfo(getAppInfo().name, "on open");
    
    _view = std::make_unique<View>();
    _view->init();
    
    // Connect back button handler
    _view->btn_back->onClick().connect([&]() {
        mclog::tagInfo(getAppInfo().name, "Going back to main menu");
        close();
        // Install and open main menu
        auto app_id = GetMooncake().installApp(std::make_unique<AppMainMenu>());
        GetMooncake().openApp(app_id);
    });
}

void AppAlarmClock::onRunning()
{
    // Update logic if needed
}

void AppAlarmClock::onClose()
{
    mclog::tagInfo(getAppInfo().name, "on close");
    
    if (_view) {
        _view->cleanup();
        _view.reset();
    }
}