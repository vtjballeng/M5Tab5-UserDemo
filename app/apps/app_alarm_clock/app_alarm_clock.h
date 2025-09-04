/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mooncake.h>
#include <memory>
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>

class AppAlarmClock : public mooncake::AppAbility {
public:
    AppAlarmClock();
    ~AppAlarmClock() = default;

    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;

private:
    struct View {
        std::unique_ptr<smooth_ui_toolkit::lvgl_cpp::Label> label_test;
        std::unique_ptr<smooth_ui_toolkit::lvgl_cpp::Button> btn_back;
        
        void init();
        void cleanup();
    };
    std::unique_ptr<View> _view;
};