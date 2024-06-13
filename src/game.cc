#include "game.hpp"

void Game::_reveal(Position pos, std::shared_ptr<Board> board){
    if(!board->IsEmpty(pos)) return;

    std::list<Position> q;
    q.push_back(pos);

    if(!board->IsMine(pos) && board->IsHidden(pos) && !board->IsMarked(pos)){
        board->SetHidden(pos, false);
    }

    while(!q.empty()){
        Position _pos = q.front();
        {
            auto rpos = Position{_pos.x + 1, _pos.y};
            if(!board->IsMine(rpos) && board->IsHidden(rpos) && !board->IsMarked(rpos)){
                if(board->IsEmpty(rpos))
                    q.push_back(rpos);
                board->SetHidden(rpos, false);
            }
        }
        {
            auto rpos = Position{_pos.x, _pos.y + 1};
            if(!board->IsMine(rpos) && board->IsHidden(rpos) && !board->IsMarked(rpos)){
                if(board->IsEmpty(rpos))
                    q.push_back(rpos);
                board->SetHidden(rpos, false);
            }
        }
        {
            auto rpos = Position{_pos.x - 1, _pos.y};
            if(!board->IsMine(rpos) && board->IsHidden(rpos) && !board->IsMarked(rpos)){
                if(board->IsEmpty(rpos))
                    q.push_back(rpos);
                board->SetHidden(rpos, false);
            }
        }
        {
            auto rpos = Position{_pos.x, _pos.y - 1};
            if(!board->IsMine(rpos) && board->IsHidden(rpos) && !board->IsMarked(rpos)){
                if(board->IsEmpty(rpos))
                    q.push_back(rpos);
                board->SetHidden(rpos, false);
            }
        }
        q.pop_front();
    }
};

Game::Game(uint8_t bd_size_x, uint8_t bd_size_y)
{
    board = std::make_shared<Board>(bd_size_x, bd_size_y);
};

std::pair<uint8_t, uint8_t> Game::BoardSize() const
{
    return board->GetSize();
}

std::shared_ptr<Board> Game::GetBoard()
{
    return board;
}

BoardValue Game::GetValue(uint8_t x, uint8_t y)
{
    return board->GetValue(Position{x, y});
}

std::string Game::GetHeaderText() const
{
    return ("STEPS: " + std::to_string(steps));
}

bool Game::MouseEvent(Position pos, ui::Mouse& mouse)
{
    if(mouse.motion != ui::Mouse::Motion::Pressed)
        return false;

    if ((mouse.button == ui::Mouse::Button::Right ) || 
        (mouse.button == ui::Mouse::Button::Middle))
    {
        if(board->IsHidden(pos)) board->ToggleMark(pos);

        if(board->IsMarked(pos)) 
        {
            if(board->IsMine(pos)){
                marked_mines.push_back(pos);
            } else {
                marked_miss.push_back(pos);
            }
        } 
        else 
        {
            if(board->IsMine(pos)){
                marked_mines.remove(pos);
            } else {
                marked_miss.remove(pos);
            }
        }

        win = ((marked_mines.size() == last_amount_mine) && (marked_miss.size() == 0));

        return false;
    }

    if (mouse.button != ui::Mouse::Button::Left) return false;

    if(board->IsMarked(pos)) return false;

    if(board->IsEmpty(pos))
    {
        _reveal(pos, board);
    } 
    else 
    {
        board->SetHidden(pos, false);

        if(board->IsMine(pos)){ //GAME OVER
            game_over = true;
        }
    }

    steps++;

    return false;
}

void Game::FillBoardRandomMine(uint8_t amount)
{
    last_amount_mine = amount;

    std::srand(time(0));

    for(auto i = 0; i < amount; i++){
        uint8_t x = std::rand() % (board->GetSize().first  - 1);
        uint8_t y = std::rand() % (board->GetSize().second - 1);
        board->AddMine(Position{x, y});
    }
}

bool& Game::IsGameOver()
{
    return game_over;
}

bool& Game::IsWin()
{
    return win;
}

void Game::Restart()
{
    game_over = false;
    steps = 0;
    marked_mines.clear();
    marked_miss.clear();
    win = false;
    board->Clear();
    FillBoardRandomMine(last_amount_mine);
}
