#include "ui_game.hpp"


UIGame::UIGame(std::shared_ptr<Game> _game) : 
    game(_game)
{
    bd_size = game->BoardSize();
}

ui::Component UIGame::ModalComponent(std::function<void()> act_again, std::function<void()> act_quit) {
    auto component = ui::Container::Vertical({
        ui::Button("Try again", act_again, ui::ButtonOption::Animated()),
        ui::Button("Quit", act_quit, ui::ButtonOption::Animated()),
    });

    

    // Polish how the two buttons are rendered:
    component |= ui::Renderer([&](ui::Element inner) {
        ui::Element text = game->IsWin() ? ui::text("YOU WIN") : ui::text("GAME OVER");

        return ui::vbox({
            text,
            ui::separator(),
            inner,
        }) | ui::size(ui::WIDTH, ui::GREATER_THAN, 30) | ui::border;
    });
    return component;
};

void UIGame::Setup(){
    board_renderer = ui::Renderer([&]{
        ui::Canvas canvas(bd_size.first * 2, bd_size.second * 4);
        
        auto hide = [&](uint8_t x, uint8_t y){
            canvas.DrawBlock(x, y    , true, ui::Color::White);
            canvas.DrawBlock(x, y + 1, true, ui::Color::White);
            canvas.DrawBlock(x, y + 2, true, ui::Color::White);
            canvas.DrawBlock(x, y + 3, true, ui::Color::White);

            canvas.DrawBlock(x + 1, y    , true, ui::Color::White);
            canvas.DrawBlock(x + 1, y + 1, true, ui::Color::White);
            canvas.DrawBlock(x + 1, y + 2, true, ui::Color::White);
            canvas.DrawBlock(x + 1, y + 3, true, ui::Color::White);
        };

        for (int i = 0; i < bd_size.first * 2; i+=2){
            for (int j = 0; j < bd_size.second * 4; j+=4){
                auto value = game->GetValue(i >> 1, j >> 2);

                if(value.marked) {
                    canvas.DrawText(i, j, "?", ui::Color::Aquamarine1);
                    continue;
                }

                if(value.hidden) {
                    canvas.DrawText(i, j, "+");
                    continue;
                }

                if (value.value == -1){
                    canvas.DrawText(i, j, "*", ui::Color::DarkRed);
                } else if(value.value == 0){
                    canvas.DrawText(i, j, " ");
                } else {
                    canvas.DrawText(i, j, std::to_string(value.value), colors[value.value]);
                }
                
            }
        }
        return ui::canvas(canvas);
    });
    
    board_renderer |= ui::CatchEvent([&](ui::Event e){
        if(!e.is_mouse()) return false;

        int x = e.mouse().x - 1;
        int y = e.mouse().y - 1 - 2;

        if(x <  0) return false;
        if(x > bd_size.first) return false;
        if(y <  0) return false;
        if(y > (bd_size.second - 1)) return false;

        game->MouseEvent(Position{x, y}, e.mouse());

        return false;
    });
}

void UIGame::Show(){
    auto main_window = ui::Container::Vertical({
        board_renderer
    });

    auto main_window_renderer = ui::Renderer(main_window, [&]{
        auto component = (game->IsGameOver()) ? board_renderer : board_renderer;

        return ui::vbox({
            ui::text(game->GetHeaderText()),
            ui::separator(),
            component->Render(),
        }) | ui::border;
    });

    ui::ScreenInteractive screen = ui::ScreenInteractive::FitComponent();

    auto modal_lose =  ModalComponent(
        [&]{ game->Restart(); }, 
        screen.ExitLoopClosure()
    );

    auto modal_win =  ModalComponent(
        [&]{ game->Restart(); }, 
        screen.ExitLoopClosure()
    );

    main_window_renderer |= ui::Modal(modal_lose, &game->IsGameOver());
    main_window_renderer |= ui::Modal(modal_win,  &game->IsWin());

    screen.Loop(main_window_renderer);
}
