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

class AppMainMenu : public mooncake::AppAbility {
public:
    AppMainMenu();
    ~AppMainMenu() = default;

    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;

private:
    struct View {
        std::unique_ptr<smooth_ui_toolkit::lvgl_cpp::Button> btn_demo;
        std::unique_ptr<smooth_ui_toolkit::lvgl_cpp::Button> btn_alarm;
        std::unique_ptr<smooth_ui_toolkit::lvgl_cpp::Label> label_title;
        
        void init();
        void cleanup();
    };
    std::unique_ptr<View> _view;
};