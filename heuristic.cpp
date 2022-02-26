#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <bitset>
#include <tuple>

using namespace std;

int n = 0, m = 0;

constexpr int DX8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
constexpr int DY8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

// pair<int, int> setplace[10] = {{14, 1}, {3, 7}, {3, 13}, {3, 19}, {3, 25}, {26, 1}, {26, 7}, {26, 13}, {26, 19}, {26, 25}};
pair<int, int> setplace[10] = {{13, 0}, {1, 16}, {28, 13}, {16, 28}, {0, 6}, {0, 6}, {0, 6}, {0, 6}, {0, 6}, {0, 6}};
//pair<int, int> setplace[10] = {{2, 1}, {2, 7}, {2, 13}, {2, 19}, {2, 25}, {6, 1}, {6, 7}, {6, 13}, {6, 19}, {6, 25}};

bitset<32> check_mask(0uL);
bitset<32> block_mask((1uL<<31));

// constexpr char filldata[4]={'u', 'd', 'l', 'r'};
// const char upperfilldata[10] = {'l', 'd', 'R', 'd', 'R', 'd', 'R', 'd', 'R', 'd'};
// const char lowerfilldata[10] = {'l', 'u', 'R', 'u', 'R', 'u', 'R', 'u', 'R', 'u'};
// const char upperbarrier[7] = {'r', 'U', 'r', 'U', 'r', 'U', 'r'};
// const char lowerbarrier[7] = {'r', 'D', 'r', 'D', 'r', 'D', 'r'};

const char wallupleft[42] = {'d', 'R', 'd', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'R', 'r', 'U', 'r', 'U'};
const char wallupright[40] = {'l', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'D', 'd', 'R', 'd', 'R'};
const char walldownleft[65] = {'r', 'U', 'r', 'u', 'L', 'L', 'U', 'U', 'r', 'u', 'L', 'L', 'U', 'U', 'r', 'u','L', 'L', 'U', 'U', 'r', 'u','L', 'L', 'U', 'U', 'r', 'u','L', 'L', 'U', 'U', 'r', 'u', 'L', 'U', 'u', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'};
const char walldownright[40] = {'u', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'L', 'l', 'D', 'l', 'D'};

//Restrict all.
// const char wallupleft[43] = {'d', 'R', 'd', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'U', 'R', 'R', 'd', 'r', 'U', 'R', 'r', 'U', 'r', 'U', 'r'};
// const char wallupright[41] = {'l', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'R', 'D', 'D', 'l', 'd', 'R', 'D', 'd', 'R', 'd', 'R', 'd'};
// const char walldownleft[37] = {'r', 'U', 'r', 'u', 'L', 'L', 'U', 'U', 'r', 'u', 'L', 'L', 'U', 'U', 'r', 'u','L', 'L', 'U', 'U', 'r', 'u','L', 'L', 'U', 'U', 'r', 'u','L', 'L', 'U', 'U', 'r', 'u', 'L', 'U', 'u'};
// const char walldownright[41] = {'u', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'D', 'L', 'L', 'u', 'l', 'D', 'L', 'l', 'D', 'l', 'D', 'l'};

bool workdone = false;
bool searchend = false;

//unsigned long long int priority[30][30] = {};
vector<vector<bitset<32>>> grid(30, vector<bitset<32>>(30, 0uL));

//{Type, {X, Y}}
vector<pair<int, pair<int, int>>> pplace;

//{X, Y}
vector<pair<int, int>> hplace;

//{ith nextmove}
vector<queue<char>> next_move;

void input(){
    cin >> n;
    pplace.resize(n);
    for (int i = 0; i < n; i++){
        int px, py, pt;
        cin >> px >> py >> pt;
        px--; py--;
        pplace[i] = {pt, {px, py}};
        grid[px][py].set(i+10);
    }

    cin >> m;
    hplace.resize(m);
    next_move.resize(m);
    for (int i = 0; i < m; i++){
        int px, py;
        cin >> px >> py;
        px--; py--;
        hplace[i] = {px, py};
        grid[px][py].set(i);

        //Move to a certain point.
        //X is height, Y is width
        int dx, dy;
        dx = setplace[i].first - px;
        dy = setplace[i].second - py;

        while (dy < 0) {next_move[i].push('L'); dy++;}
        while (dy > 0) {next_move[i].push('R'); dy--;}

        while (dx < 0) {next_move[i].push('U'); dx++;}
        while (dx > 0) {next_move[i].push('D'); dx--;}        

        while(1) {
            next_move[i].push('.');
            if (next_move[i].size() >= 100) break;
        }

        //Set wall-placing as work
        // for (int w = 0; w < 11; w++) next_move[i].push(filldata[w]);
        if (i == 0) for (auto w : wallupleft) next_move[i].push(w);
        else if (i == 1) for (auto w : wallupright) next_move[i].push(w);
        else if (i == 2) for (auto w : walldownleft) next_move[i].push(w);
        else if (i == 3) for (auto w : walldownright) next_move[i].push(w);
        
        /*---First Attempt-------------------------------------------------------
        
        // else if (i < 5) for (auto w : upperfilldata) next_move[i].push(w);
        // else for (auto w : lowerfilldata) next_move[i].push(w);

        // //Place shutter
        // if (i+1 == m){
        //     if (i < 5) for (auto w : upperbarrier) next_move[i].push(w);
        //     else for (auto w : lowerbarrier) next_move[i].push(w);
        // }

        -----First Attempt-------------------------------------------------------*/
    }
}

void display(){
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 30; j++){
            cerr << setfill('0') << setw(9) << grid[i][j].to_ulong() << " ";
        }
        cerr << endl;
    }
}

int pet_check(int x, int y, int human){
    bitset<32> hmask(0uL);
    hmask.set(human);
    hmask = hmask^check_mask;

    if (grid[x][y][31] == 0 && (grid[x][y]&hmask).any()) return 1;

    for (int i = 0; i < 8; i++){
        if (x+DX8[i] < 0 || x+DX8[i] >= 30 || y+DY8[i] < 0 || y+DY8[i] >= 30) continue;

        if (grid[x+DX8[i]][y+DY8[i]][31] == 0 && (grid[x+DX8[i]][y+DY8[i]]&hmask).any()) return 1;
    }

    return 0;
}

char hwork(int human, char nextwork){
    auto [nx, ny] = hplace[human];

    char res = '.';

    switch(nextwork){
        case 'U':
            if (nx-1 < 0 || nx-1 >= 30) return '.'; //Out of range.
            if (grid[nx-1][ny][31]) return '.'; //If There is a stop.

            grid[nx][ny].reset(human);
            nx--;
            grid[nx][ny].set(human);
            res = 'U';
            break;
        case 'D':
            if (nx+1 < 0 || nx+1 >= 30) return '.'; //Out of range.
            if (grid[nx+1][ny][31]) return '.'; //If There is a stop.

            grid[nx][ny].reset(human);
            nx++;
            grid[nx][ny].set(human);
            res = 'D';
            break;
        case 'R':
            if (ny+1 < 0 || ny+1 >= 30) return '.'; //Out of range.
            if (grid[nx][ny+1][31]) return '.'; //if there is a stop.

            grid[nx][ny].reset(human);
            ny++;
            grid[nx][ny].set(human);
            res = 'R';            
            break;
        case 'L':
            if (ny-1 < 0 || ny-1 >= 30) return '.'; //Out of range.
            if (grid[nx][ny-1][31]) return '.'; //if there is a stop.

            grid[nx][ny].reset(human);
            ny--;
            grid[nx][ny].set(human);
            res = 'L';
            break;
        case 'u':
            if (nx-1 < 0 || nx-1 >= 30) return '.'; //Out of range.
            if (grid[nx-1][ny][31] == 0 && pet_check(nx-1, ny, human) == 1) return '.'; //Not restricted but some animals or humans.
            if (grid[nx-1][ny][31]){ //There's already block
                next_move[human].pop();
                return '.';
            }

            grid[nx-1][ny].set(31);
            res = 'u';
            break;
        case 'd':
            if (nx+1 < 0 || nx+1 >= 30) return '.'; //Out of range.
            if (grid[nx+1][ny][31] == 0 && pet_check(nx+1, ny, human) == 1) return '.'; //Not restricted but some animals or humans.
            if (grid[nx+1][ny][31]){ //There's already block
                next_move[human].pop();
                return '.';
            }

            grid[nx+1][ny].set(31);
            res = 'd';
            break;
        case 'r':
            if (ny+1 < 0 || ny+1 >= 30) return '.'; //Out of range.
            if (grid[nx][ny+1][31] == 0 && pet_check(nx, ny+1, human) == 1) return '.'; //Not restricted but some animals or humans.
            if (grid[nx][ny+1][31]){ //There's already block
                next_move[human].pop();
                return '.';
            }

            grid[nx][ny+1].set(31);
            res = 'r';
            break;
        case 'l':
            if (ny-1 < 0 || ny-1 >= 30) return '.'; //Out of range.
            if (grid[nx][ny-1][31] == 0 && pet_check(nx, ny-1, human) == 1) return '.'; //Not restricted but some animals or humans.
            if (grid[nx][ny-1][31]){ //There's already block
                next_move[human].pop();
                return '.';
            }

            grid[nx][ny-1].set(31);
            res = 'l';
            break;
        case '.':
            res = '.';
            next_move[human].pop();
            break;
        default:
            break;
    }

    hplace[human] = {nx, ny};
    return res;
}

bool in_range(int l, int r, int p){
    return ((l <= p)&&(p <= r));
}

int get_most_animal_area(){
    //Available Y grids as [R, L] for each X
    pair<int, int> arange[30] = {{0, 13}, {0, 13}, {0, 13}, {0, 12}, {0, 11}, {0, 10}, {0, 9}, {0, 8}, {0, 7}, {0, 6}, {0, 5}, {0, 4}, {0, 3}, {0, 2}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
    pair<int, int> brange[30] = {{15, 29}, {16, 29}, {16, 29}, {17, 29}, {18, 29}, {19, 29}, {20, 29}, {21, 29}, {22, 29}, {23, 29}, {24, 29}, {25, 29}, {26, 29}, {27, 29}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
    pair<int, int> crange[30] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {29, 29}, {27, 29}, {26, 29}, {25, 29}, {24, 29}, {23, 29}, {22, 29}, {21, 29}, {20, 29}, {19, 29}, {18, 29}, {17, 29}, {16, 29}, {16, 29}, {16, 29}};
    pair<int, int> drange[30] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 13}, {0, 14}};

    int pcount[4] = {};

    for (int i = 0; i < 30; i++){
        for (int anima = 0; anima < n; anima++){
            if (pplace[anima].second.first == i){
                int py = pplace[anima].second.second;

                if (in_range(arange[i].first, arange[i].second, py)) pcount[0]++;
                else if (in_range(brange[i].first, brange[i].second, py)) pcount[1]++;
                else if (in_range(crange[i].first, crange[i].second, py)) pcount[2]++;
                else if (in_range(drange[i].first, drange[i].second, py)) pcount[3]++;
            }
        }
    }

    cerr << "# Animal Searched: [a, " << pcount[0] << "], [b, " << pcount[1] << "], [c, " << pcount[2] << "], [d, " << pcount[3] << "]" << endl;

    int manimal = 0;
    int count = 100;
    for (int i = 0; i < 4; i++){
        if (count > pcount[i]) {
            manimal = i;
            count = pcount[i];
        }
    }

    return manimal; //0 - a, 1 - b, 2 - c, 3 - d
}

void decide_after_placing(){
    //Serach animals and move peoples to the area where number of animals is most low.

    //R, D, L
    const int landing_route[4][3] = {
        {0, 0, 0},
        {23, 0, 0},
        {23, 29, 0},
        {23, 29, 29}
    };

    int res = get_most_animal_area();

    cerr << "# Moving to " << res << endl;

    if (res == 0){
        //Wall upleft;
        for (int w = 0; w < 70; w++) next_move[0].push('.');
        next_move[0].push('r');

        //Wall upright
        for (int w = 0; w < 40; w++) next_move[1].push('.');
        next_move[1].push('d');
        for (int w = 0; w < 13; w++) next_move[1].push('U');
        for (int w = 0; w < 29; w++) next_move[1].push('L');

        //Wall downleft
        for (int w = 0; w < 12; w++) next_move[2].push('R');
        for (int w = 0; w < 29; w++) next_move[2].push('U');
        for (int w = 0; w < 29; w++) next_move[2].push('L');

        //Wall downright
        next_move[3].push('l');
        for (int w = 0; w < 13; w++) next_move[3].push('R');
        for (int w = 0; w < 29; w++) next_move[3].push('U');
        for (int w = 0; w < 29; w++) next_move[3].push('L');
    }
    else if (res == 1){
        //Wall upleft
        for (int w = 0; w < 2; w++) next_move[0].push('R');
        for (int w = 0; w < 7; w++) next_move[0].push('.');
        next_move[0].push('l');

        //Wall upright
        for (int w = 0; w < 40; w++) next_move[1].push('.');
        next_move[1].push('d');
        for (int w = 0; w < 13; w++) next_move[1].push('U');

        //Wall downleft
        for (int w = 0; w < 12; w++) next_move[2].push('R');
        for (int w = 0; w < 29; w++) next_move[2].push('U');

        //Wall downright
        next_move[3].push('l');
        for (int w = 0; w < 13; w++) next_move[3].push('R');
        for (int w = 0; w < 29; w++) next_move[3].push('U');
    }
    else if (res == 2){
        //Wall upleft
        for (int w = 0; w < 3; w++) next_move[0].push('R');
        for (int w = 0; w < 7; w++) next_move[0].push('.');
        next_move[0].push('l');
        for (int w = 0; w < 13; w++) next_move[0].push('R');
        for (int w = 0; w < 29; w++) next_move[0].push('D');
        
        //Wall upright
        for (int w = 0; w < 2; w++) next_move[1].push('D');
        for (int w = 0; w < 45; w++) next_move[1].push('.');
        next_move[1].push('u');

        //Wall downleft
        for (int w = 0; w < 12; w++) next_move[2].push('R');

        //Wall downright
        next_move[3].push('l');
        for (int w = 0; w < 13; w++) next_move[3].push('R');
    }
    else if (res == 3){
        //Wall upleft
        next_move[0].push('R');
        next_move[0].push('R');
        next_move[0].push('R');
        for (int w = 0; w < 7; w++) next_move[0].push('.');
        next_move[0].push('l');

        for (int w = 0; w < 13; w++) next_move[0].push('R');
        for (int w = 0; w < 29; w++) next_move[0].push('D');
        for (int w = 0; w < 29; w++) next_move[0].push('L');


        //Wall upright
        next_move[1].push('D');
        next_move[1].push('D');
        next_move[1].push('D');
        for (int w = 0; w < 35; w++) next_move[1].push('.');
        next_move[1].push('u');
        for (int w = 0; w < 13; w++) next_move[1].push('D');
        for (int w = 0; w < 29; w++) next_move[1].push('L');

        //Wall down left
        for (int w = 0; w < 5; w++) next_move[2].push('L');

        //Wall down right
        next_move[3].push('L');
        next_move[3].push('L');
        for (int w = 0; w < 72; w++) next_move[3].push('.');
        next_move[3].push('r');
    }

    for (int i = 4; i < m; i++){
        for (int w = 0; w < landing_route[res][0]; w++) next_move[i].push('R');
        for (int w = 0; w < landing_route[res][1]; w++) next_move[i].push('D');
        for (int w = 0; w < landing_route[res][2]; w++) next_move[i].push('L');
    }
}

int main(){
    check_mask.set(31);
    check_mask.flip();

    input();

    //display();
    for (int turn = 0; turn < 300; turn++){
        
        //Place square wall at first.
        if (workdone == false){
            for (int human = 0; human < m; human++){
                if (next_move[human].empty()) {
                    //If it has no work, do nothing and continue;
                    cout << '.';
                    continue;
                }

                char hi = hwork(human, next_move[human].front());

                //If work is done, pop it from the queue.
                if (hi != '.') next_move[human].pop();
                
                cout << hi;
            }
            cout << endl;

            workdone = true;
            for (int human = 0; human < m; human++){
                if (next_move[human].empty() == false) {
                    workdone = false;
                    //cerr << "Does not end! [" << human << "]" << endl;
                }
            }
        }
        else {
            // cerr << "Workend!" << endl;
            if (searchend == false) {
                decide_after_placing();
                searchend = true;
            }

            for (int human = 0; human < m; human++){
                if (next_move[human].empty()) {
                    //If it has no work, do nothing and continue;
                    cout << '.';
                    continue;
                }

                char hi = hwork(human, next_move[human].front());

                //If work is done, pop it from the queue.
                if (hi != '.') next_move[human].pop();
                
                cout << hi;
            }
            cout << endl;
        }

        for (int anima = 0; anima < n; anima++){
            string s; cin >> s;

            for (auto moves : s){
                auto [nx, ny] = pplace[anima].second;
                switch(moves){
                    case 'U':
                        grid[nx][ny].reset(anima+10);
                        nx--;
                        grid[nx][ny].set(anima+10);
                        break;
                    case 'D':
                        grid[nx][ny].reset(anima+10);
                        nx++;
                        grid[nx][ny].set(anima+10);
                        break;
                    case 'L':
                        grid[nx][ny].reset(anima+10);
                        ny--;
                        grid[nx][ny].set(anima+10);
                        break;
                    case 'R':
                        grid[nx][ny].reset(anima+10);
                        ny++;
                        grid[nx][ny].set(anima+10);
                        break;
                    default:
                        break;
                };

                pplace[anima].second = {nx, ny};                
            }
        }
    }
}