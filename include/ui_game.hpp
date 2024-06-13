#pragma once

#include "game.hpp"
#include "ui_fwd.hpp"

class UIGame {
private:
    std::shared_ptr<Game> game;
    bool is_inited = false;
    std::pair<uint8_t, uint8_t> bd_size;

    const std::vector<ui::Color> colors = {
        ui::Color::White,
        ui::Color::BlueLight,
        ui::Color::GreenLight,
        ui::Color::RedLight,
        ui::Color::BlueViolet,
        ui::Color::Red,
        ui::Color::RosyBrown,
        ui::Color::CadetBlue,
        ui::Color::Chartreuse3
    };

    ui::Component board_renderer;

public:
    UIGame(std::shared_ptr<Game> _game);

    ui::Component ModalComponent(std::function<void()> act_again, std::function<void()> act_quit);
    
    void Setup();
    void Show();
};
