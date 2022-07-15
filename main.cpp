/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkej�?: risti (X), nolla (0) ja tyhj�? (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysyt�?�?n koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimm�?iseksi t�?ytetty�? peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi p�?�?tty�? my�?s sellaiseen tilanteeseen, ett�? peliruudukko on
 * t�?ynn�? merkkej�?, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pit�?�? olla
 * peliruudukon sis�?ll�?, tai koordinaatit saavat ylitty�? tai alittua
 * korkeintaan yhdell�?. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdell�?, peliruudukko laajenee oikealle ja alasp�?in. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alasp�?in. Peliruudukko siis pysyy aina neli�?n muotoisena.
 *   Pelin p�?�?ttyess�? kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * Ohjelman kirjoittajat
 * Nimi: Konsta Tauriainen
 * Opiskelijanumero: k430829
 * kt430829 https://course-gitlab.tuni.fi/comp.cs.110-ohj-2_2021-SYKSY/kt430829.git
 * E-Mail: konsta.tauriainen@tuni.fi
 * ja
 * Nimi: Aaro Tuohi
 * K�?ytt�?j�?tunnus msaatu
 * Opiskelijanumero: 050280618
 * S�?hk�?posti: aaro.tuohi@tuni.fi
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Funktio ottaa paremetrina pelilaudan tiedot, ja tulostaa pelilaudan.
void draw_board(const vector<vector<char>> board) {

    // K�?yd�?�?n l�?pi sarakkeiden numerointi, ja vaihdetaan tulostettava merkki
    // apumuuttujan avulla, jos laudan koko kasvaa kaksinumeroiseksi luvuksi.
    cout << "   ";
    for (int i = 1; i <= (int)board.size(); ++i) {
        int big_column;
        if (i >= 10) {
            big_column = i % 10;
            cout << big_column << " ";

        } else {
        cout << i << " ";
        }
    }

    // K�?yd�?�?n rivien numerointi l�?pi
    for (int i = 1; i <= (int)board.size(); ++i) {
        int big_row;
        if (i >= 10) {
            big_row = i % 10;
            cout << endl;
            cout << " " << big_row << " ";
            for(unsigned int j = 0; j < board.size(); ++j) {
                cout << board[big_row+9][j];
                cout << " ";
            }
        } else {
            cout << endl;
            cout << " " << i << " ";
            for(unsigned int j = 0; j < board.size(); ++j) {
                cout << board.at(i-1).at(j);
                cout << " ";
            }
        }
        }
        cout << endl;
        cout << endl;

}

// Funktio ottaa parametrina pelilaudan seka tarkistettavan syotteen merkkijonona.
// Paluuarvona funktiossa on totuusarvo syotteen oikeellisuudesta.
bool input_check(string input1, string input2, vector<vector<char>>& board) {
    bool input_legit = true;
    // Tarkistetaan onko ensimmainen syote lopetuskomento
    //if (input1 == "q") {
     //   return EXIT_SUCCESS;
    //}

    // Verrataan onko koordinaatti hyvaksytyissa rajoissa.
    try {
        if (stoi(input1) > (int)board.size() +1 || stoi(input1) < 0) {
           input_legit = false;
        }
    }  catch (...) {
        input_legit = false;
    }
    try {
        if (stoi(input2) > (int)board.size() +1 || stoi(input2) < 0) {
           input_legit = false;
        }
    }  catch (...) {
        input_legit = false;
    }

    if (!input_legit) {
        cout << "Coordinate outside the board" << endl;
    }
    return input_legit;
}

void enter( int column, int row, char ch, vector<vector<char>>& board, int& vuoro) {
    if (board[row][column] != '.') {
        cout << "The given place is already occupied" << endl;
    }
     else {
        board[row][column] = ch;
        draw_board(board);
        ++vuoro;
    }
}

void grow_board_to_right(vector<vector<char>>& board, int board_size) {
    for(int i=0; i<board_size; i++) {
        board.push_back(vector<char>());
        for(; i < board_size; i++) {
            board[i].push_back('.');
            if (i == board_size -1) {
                for(int j=0; j<board_size; j++) {
                  board[i].push_back('.');
                }
            }
        }
    }
}

void grow_board_to_left(vector<vector<char>>& board, int board_size) {
    grow_board_to_right(board, board_size);
    for (int i = board_size-1; i > 0; --i) {
        for (int j = board_size-1; j > 0; --j) {
            board[i][j] = board[i-1][j-1];
        }
    }
    for (int y = board_size - 1; y >= 0; --y) {
    board[y][0] = '.';
    }
    for (int x = board_size - 1; x >= 0; --x) {
    board[0][x] = '.';
    }
}
//Fukntio takistaa pelilaudan ja jos voittajaa ei löydy palauttaa arvon tosi
bool check_draw(const vector<vector<char>>& board) {
for(int i=0;i<(int)board.size();i++) {
    for(int j=0;j<(int)board.size();j++) {
        if(board[i][j]=='.') {
            return false;
            break;
            }
        }
    }
    return true;
}
//Fukntio tarkistaa pelilaudan pystysuorasti ja palauttaa voittajan jos tosi
bool check_vertical(char choice, const vector<vector<char>>& board) {
int count;
for(int i=0;i<(int)board.size();i++) {
    count=0;
    for(int j=0;j<(int)board.size();j++) {
        if(board[j][i]==choice) {
            count++;
        }
            if(count == (int)board.size()) {
            return true;
            }
        }
    }
    return false;
}
//Funktio tarkistaa pelilaudan vaakasuorasti ja palauttaa voittajan jos tosi
bool check_horizontal(char choice, const vector<vector<char>>& board) {
int count;
for (int i=0; i<(int)board.size(); i++) {
    count=0;
    for(int j=0;j<(int)board.size();j++) {
        if(board[i][j]==choice) {
            count++;
        }
        if(count== (int)board.size()) {
            return true;
        }
    }
}
    return false;
}
//Funktio tarkistaa pelilaudan lävistäjän oikealta vasemalle ja palautaa voittajan jos tosi

bool check_diagonal_right_to_left(char choice, const vector<vector<char>>& board) {
    int count=0;
    for(int i=0;i<(int)board.size();i++) {
        if (board[i][i]==choice) {
            count++;
        }
    }
    if(count==(int)board.size()) {
        return true;
    }
    return false;
}
//Funktio tarkistaa pelilaudan lavistajan vasemmalta oikealle
bool check_diagonal_left_to_right(char symbol, const vector<vector<char>>& board) {
    int count = 0;

    for (int i = 0; i < (int)board.size(); i++) {
        if (board[i][board.size() - 1 - i] == symbol) {
            count++;
            if (count == (int)board.size()) {
                return true;
            }
        }
    }
    return false;
}
//Funktio ottaa parametrikseen pelilaudan
//Funktio koostuu pelilaudan tarkistukseen tehdyista apufunktioista. Mikali tarkistusfunktion arvo on tosi fukntio palautaa
//kyseisen apufuktion paluuarvon enter_coordinates funktioon
bool win_condition(const vector<vector<char>>& board) {
    bool game_over = false;
    if (check_vertical('X', board)) {
       cout << "Cross won vertically" << endl;
       game_over = true;
    }
    if (check_horizontal('X', board)) {
       cout << "Cross won horizontally" << endl;
       game_over = true;
    }
    if (check_diagonal_left_to_right('X', board)) {
        cout << "Cross won diagonally" << endl;
        game_over = true;
    }
    if (check_diagonal_right_to_left('X', board)) {
        cout << "Cross won diagonally" << endl;
        game_over = true;
    }
    if (check_vertical('0', board)) {
       cout << "Nought won vertically" << endl;
       game_over = true;
    }
    if (check_horizontal('0', board)) {
       cout << "Nought won horizontally" << endl;
       game_over = true;
    }
    if (check_diagonal_left_to_right('0', board)) {
        cout << "Nought won diagonally" << endl;
        game_over = true;
    }
    if (check_diagonal_right_to_left('0', board)) {
        cout << "Nought won diagonally" << endl;
        game_over = true;
    }
    if (check_draw(board)) {
        cout << "No empty places" << endl;
        game_over = true;
    }
    return game_over;
}
//Funktio ottaa parametrikseen pelilaudan
//Funktio toimii ohjelman kayttoliittym�?, jossa suoritetaan vuoronvaihto sek�? pelin eteneminen. Kutsuu apufunktioita
//koordinaattien tarkistukseen, pelilaudan laajentamiseen oikealle ja alas seka vasemmalle ja yl�?s. Myos pelimerkkien X ja 0
//lisaaminen suoritetaan funktiossa.
void enter_coordinates_to_gameboard(vector<vector<char>>& board) {
    // Alustetaan apumuuttuja, jonka kokoa suurennetaan, jos syotetyt koordinaatit menee pelilaudan ulkopuolelle.
    int column,row;
    string input_one, input_two;
    int board_size = board.size();
    char ch;
    bool input_legit;

    for (int i = 0; i < (int)board.size()*(int)board.size();) {
        if (i == 0 || i%2 == 0) {
            ch = 'X';
        } else {
            ch = '0';
        }

    do {
        input_legit = false;
        cout << "For " << ch << ", enter coordinates: x y> ";
        cin >> input_one;

        if (input_one == "q") {
            cout << "Why on earth you are giving up the game?" << endl;
            return;
        }
        cin >> input_two;
        if (input_check(input_one, input_two, board)) {
            column = (stoi(input_one)) -1;
            row = (stoi(input_two)) -1;
            input_legit = true;
            }
        } while (!input_legit);

        // Tarkistetaan onko koordinaatit laudan ulkopuolella molemmista p???ist???
        if ((row == -1 && column > board_size -1) || (column == -1 && row > board_size -1)) {
            cout << "Coordinate outside the board" << endl;
        }

        // Kasvatetaan laudan kokoa jos jompikumpi koordinaatti on pelilaudan ulkopuolella
        else if (row == (int)board.size() || column == (int)board.size()) {
            board_size = board.size() + 1;
            grow_board_to_right(board, board_size);
        }


        // Kasvatetaan laudan kokoa jos jompikumpi koordinaatti on pelilaudan ulkopuolella
        else if (row == -1 || column == -1) {
            board_size = board.size() + 1;
            grow_board_to_left(board, board_size);
            if (row == -1) {
               row = row + 1;
               column = column + 1;
               enter(column, row, ch, board, i);
               continue;

           }
            else if (column == -1) {
                 column = column + 1;
                 row = row + 1;
                 enter(column, row, ch, board, i);
                 continue;
           }


        }
        if (row < (int)board.size() && column < (int)board.size()) {
            enter(column, row, ch, board, i);
          }

        if (win_condition(board)) {
            cout << "Game over!" << endl;
            return;
        }
    }
}


int main() {
    // Luodaan 3x3 pelilauta.
    vector<vector<char>> board(3, vector<char>(3, '.'));

    // Tulostetaan pelin aloitusviesti sek??? pelilauta
    cout << "Start game:" << endl;
    draw_board(board);

    // Kutsutaan funktiota, joka lis?????? merkkej??? pelilautaan
    enter_coordinates_to_gameboard(board);

    return 0;
}
