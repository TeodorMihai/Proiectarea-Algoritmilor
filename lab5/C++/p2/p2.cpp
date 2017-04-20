#include <bits/stdc++.h>

using namespace std;

#include "reversi.h"

#define inf 0x3f3f3f3f

const int H = 7;

int cnt;

inline int abs(int x)
{
    return x > 0 ? x : -x;
}

Move::Move(int player, int x = -1, int y = -1): player(player), x(x), y(y)
{
}

Move::Move() : player(0), x(0), y(0) { }

vector<Move> Reversi::get_moves(int player) {

    vector<Move> moves ;

    for(int i = 0 ; i < N; ++i)
        for(int j = 0 ; j  < N; ++j) {

            Reversi state = *this;
            Move my_move = Move(player, i, j);

            if( state.apply_move(my_move) )
                moves.push_back(my_move);
        }
    return moves;
}

Reversi::Reversi()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            data[i][j] = 0;
    data[N / 2 - 1][N / 2 - 1] = data[N / 2][N / 2] = 1;
    data[N / 2 - 1][N / 2] = data[N / 2][N / 2 - 1] = -1;
}


/**
 * Intoarce true daca jocul este intr-o stare finala
 */
 bool Reversi::ended() {

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            Reversi tmp(*this);
            if (tmp.apply_move(Move(1, i, j)))
                return false;
            tmp = *this;
            if (tmp.apply_move(Move(-1, i, j)))
                return false;
        }
    return true;
}

/**
 * Returns 1 if player won, 0 if draw and -1 if lost
 */
int Reversi::winner(int player) {
    if (!ended())
        return 0;

    int s = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (data[i][j] == player)
                s++;
            else if (data[i][j] == -player)
                s--;
        }
    return s > 0 ? 1 : s == 0 ? 0 : -1;
}

/**
 * Functia de evaluare a starii curente a jocului
 * Evaluarea se face din perspectiva jucatorului
 * aflat curent la mutare (player)
 */


int Reversi::count_dif(int player) {

    int cnt = 0;

    for(int i = 0 ; i < N ; ++i)
        for(int j = 0 ; j < N ; ++j) {
            if(data[i][j] == player)
                cnt++;
            if(data[i][j] == -player)
                cnt--;
        }

    
    return cnt;
}

int Reversi::eval(int player) {
    
    if(ended()) {
        if(winner(player) == 1)
            return 100;
        else
            return -100;
    }

    return count_dif(player);
}

/**
 * Aplica o mutare a jucatorului, modificand starea jocului
 * Plaseaza piesa jucatorului move.player in pozitia move.x, move.y
 * Mutarea move.x == -1, move.y == -1 semnifica ca jucatorul
 * paseaza randul la mutare
 * Returneaza true daca mutarea este valida
 */
bool Reversi::apply_move(const Move &move) {

    if (move.x == -1 && move.y == -1)
        return true;

    if (data[move.x][move.y] != 0)
        return false;

    bool ok = false;

    for (int x_dir = -1; x_dir <= 1; x_dir++)
        for (int y_dir = -1; y_dir <= 1; y_dir++)
        {
            if (x_dir == 0 && y_dir == 0)
                continue;
            int i = move.x + x_dir, j = move.y + y_dir;
            for (; i >= 0 && j >= 0 && i < N && j < N && data[i][j] == -move.player; i += x_dir, j += y_dir);
            if (i >= 0 && j >= 0 && i < N && j < N && data[i][j] == move.player && (abs(move.x - i) > 1 || abs(move.y - j) > 1))
            {
                ok = true;
                for (i = move.x + x_dir, j = move.y + y_dir; i >= 0 && j >= 0 && i < N && j < N && data[i][j] == -move.player; i += x_dir, j += y_dir)
                    data[i][j] = move.player;
            }
        }

    if (!ok)
        return false;

    data[move.x][move.y] = move.player;

    return true;
}

/**
 * Afiseaza starea jocului
 */
void Reversi::print() {

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j< N; j++)
        {
            if (data[i][j] == 0)
                std::cout << '.';
            else if (data[i][j] == 1)
                std::cout << 'O';
            else
                std::cout << 'X';
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * Implementarea algoritmului minimax (negamax)
 * Intoarce o pereche <x, y> unde x este cel mai bun scor
 * care poate fi obtinut de jucatorul aflat la mutare,
 * iar y este mutarea propriu-zisa
 */

pair<int, Move> maxi(Reversi , int, int);

pair<int, Move> mini(Reversi state, int player, int depth) {
    //tot timpul evaluarea trebuie facuta din perspectiva playerului care
    //a inceput jocul, in mini tot timpul intru cu celalt player, daca apelez numai
    //maxi(player), asadar apelez state.eval(-player), e oricum tot aia pentru cazul 
    //cand adancimea e para

    cnt++;

    if(depth == 0 || state.ended() )
        return  pair<int, Move> (state.eval(-player) , Move(player, -1, -1) ) ;

    int minv = Inf ;
    Move best_move(player, -1, -1);//cedez mutarea

    vector<Move> moves = state.get_moves(player);

    //ar trebui sa simulez un concede 
    if(moves.size() == 0)
        return make_pair(100, Move(player, -1, -1));


    Reversi next_state = state;   
    
    for(Move m : moves) {

        next_state = state;

        next_state.apply_move(m);
        
        pair<int, Move> res_maxi = maxi(next_state, -1 * player, depth - 1);
        
        int score = res_maxi.first;
        
        if(score < minv) {
            minv = score;
            best_move = m;
        }
    }

    return pair<int, Move>(minv, best_move);
}

pair<int, Move> maxi(Reversi state, int player, int depth) {
    //tot timpul evaluarea trebuie facuta din perspectiva playerului care a inceput jocul
    //adica aici e ok, tot timpul in maxi vom avea playerul care a inceput jocul

    cnt++;

    if(depth == 0 || state.ended())
        return pair<int, Move> (state.eval(player) , Move(player, -1, -1) ) ;

    int maxv = -Inf ;
    Move best_move(player, -1, -1);//mutarea default de cedare

    vector<Move> moves = state.get_moves(player);

    if(moves.size() == 0)
        return make_pair(-100, Move(player, -1, -1));

    Reversi next_state = state;
    
    for(Move m : moves) {

        next_state = state;

        next_state.apply_move(m);

        pair<int, Move> res_mini = mini(next_state, -1 *  player, depth - 1);
        
        int score = res_mini.first;

        if(score > maxv) {
            maxv = score;
            best_move = m;           
        }
    }

    return pair<int, Move>(maxv, best_move);
}



int main() {

    Reversi rev;
    rev.print();

    cout << "Player 1: " <<  "0\n" << "Player -1: " << 'X' << '\n';
    /* Choose here if you want COMP vs HUMAN or COMP vs COMP */
    bool HUMAN_PLAYER = false;
    int player = 1;

    while (!rev.ended()) {

        std::pair<int, Move> p(0, Move(player));
        if (player == 1) {

            p = maxi(rev, player, H);
            std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
            rev.apply_move(p.second);
        } else {
            if (!HUMAN_PLAYER) {
                p = maxi(rev, player, H);
                std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
                rev.apply_move(p.second);
            } else {

                bool valid = false;
                while (!valid) {
                    int x, y;
                    std::cout << "Insert position [0..N - 1], [0..N - 1] ";
                    std::cin >> x >> y;
                    valid = rev.apply_move(Move(player, x, y));
                }
            }
        }

        rev.print();
        player *= -1;
    }

    int w = rev.winner(1);
    if (w == 1)
        std::cout << "Player 1 WON!" << std::endl;
    else if (w == 0)
        std::cout << "Draw" << std::endl;
    else
        std::cout << "Player -1 WON!" << std::endl;
    cout << "Eval made: " << cnt << '\n';

}
