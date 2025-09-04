/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include "app_main_menu.h"
#include <hal/hal.h>
#include <mooncake.h>
#include <mooncake_log.h>
#include <lvgl.h>
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include "../app_launcher/app_launcher.h"
#include "../app_alarm_clock/app_alarm_clock.h"

using namespace mooncake;
using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

void AppMainMenu::View::init() {
        LvglLockGuard lock;
        
        // Set background color
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x1E1E1E), LV_PART_MAIN);
        lv_obj_remove_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);
        
        // Title label
        label_title = std::make_unique<Label>(lv_screen_active());
        label_title->setText("Main Menu");
        label_title->setTextFont(&lv_font_montserrat_36);
        label_title->setTextColor(lv_color_hex(0xFFFFFF));
        label_title->align(LV_ALIGN_TOP_MID, 0, 50);
        
        // Demo button
        btn_demo = std::make_unique<Button>(lv_screen_active());
        btn_demo->setSize(600, 150);
        btn_demo->align(LV_ALIGN_CENTER, 0, -100);
        btn_demo->setRadius(20);
        btn_demo->setBgColor(lv_color_hex(0xD86037));
        btn_demo->setShadowWidth(0);
        btn_demo->label().setText("M5 Tab5 User Demo");
        btn_demo->label().setTextFont(&lv_font_montserrat_36);
        btn_demo->label().setTextColor(lv_color_hex(0xFFFFFF));
        
        // Alarm button
        btn_alarm = std::make_unique<Button>(lv_screen_active());
        btn_alarm->setSize(600, 150);
        btn_alarm->align(LV_ALIGN_CENTER, 0, 100);
        btn_alarm->setRadius(20);
        btn_alarm->setBgColor(lv_color_hex(0x4A90E2));
        btn_alarm->setShadowWidth(0);
        btn_alarm->label().setText("Alarm Clock");
        btn_alarm->label().setTextFont(&lv_font_montserrat_36);
        btn_alarm->label().setTextColor(lv_color_hex(0xFFFFFF));
}

void AppMainMenu::View::cleanup() {
        LvglLockGuard lock;
        btn_demo.reset();
        btn_alarm.reset();
        label_title.reset();
}

AppMainMenu::AppMainMenu()
{
    setAppInfo().name = "AppMainMenu";
}

void AppMainMenu::onCreate()
{
    mclog::tagInfo(getAppInfo().name, "on create");
    open();
}

void AppMainMenu::onOpen()
{
    mclog::tagInfo(getAppInfo().name, "on open");
    
    _view = std::make_unique<View>();
    _view->init();
    
    // Connect button handlers
    _view->btn_demo->onClick().connect([&]() {
        mclog::tagInfo(getAppInfo().name, "Launching demo app");
        // Close this menu and install/open the launcher
        close();
        auto app_id = GetMooncake().installApp(std::make_unique<AppLauncher>());
        GetMooncake().openApp(app_id);
    });
    
    _view->btn_alarm->onClick().connect([&]() {
        mclog::tagInfo(getAppInfo().name, "Launching alarm app");
        // Close this menu and install/open the alarm app
        close();
        auto app_id = GetMooncake().installApp(std::make_unique<AppAlarmClock>());
        GetMooncake().openApp(app_id);
    });
}

void AppMainMenu::onRunning()
{
    // Update logic if needed
}

void AppMainMenu::onClose()
{
    mclog::tagInfo(getAppInfo().name, "on close");
    
    if (_view) {
        _view->cleanup();
        _view.reset();
    }
}