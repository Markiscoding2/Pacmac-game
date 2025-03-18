#include <stdc++.h>
using namespace std;
class Fantoma {
    public:
        bool moarta;
        int x_curent, y_curent;
        int x_urmator, y_urmator;
        char caracter_original;
        Fantoma(int y, int x, vector<string>& harta, bool este_moarta)
            : x_curent(x), y_curent(y),caracter_original(harta[y][x]), moarta(este_moarta) {}
        virtual ~Fantoma() {}
    
    
    
    
    
    
    
    
        virtual void pozitieUrmatoare(vector<string>& harta, const int HARTA_SIZE, const int jucator_y, const int jucator_x,bool jucator_are_putere) = 0;
    
    
    
    
        void actualizeazaPozitia(vector<string>& harta) {
            harta[y_curent][x_curent] = caracter_original;
            caracter_original = harta[y_urmator][x_urmator];
            harta[y_urmator][x_urmator] = 'F';
            y_curent = y_urmator;
            x_curent = x_urmator;
        }
    };
    
    
    
    
    class Fantoma_Agresiva : public Fantoma{
        public:
            Fantoma_Agresiva(int y, int x, vector<string>& harta, bool este_moarta) : Fantoma(y, x, harta, este_moarta){}
            void pozitieUrmatoare(vector<string>& harta, const int HARTA_SIZE, const int jucator_y, const int jucator_x, bool jucator_are_putere) override {
            vector<pair<int, int>> directions = {
                {0, 1},   // Right
                {0, -1},  // Left
                {1, 0},   // Down
                {-1, 0}   // Up
            };
    
            // Sort directions based on Manhattan distance to the player
            sort(directions.begin(), directions.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
                int distA = abs((y_curent + a.first) - jucator_y) + abs((x_curent + a.second) - jucator_x);
                int distB = abs((y_curent + b.first) - jucator_y) + abs((x_curent + b.second) - jucator_x);
                return distA < distB;
            });
    
            // Attempt to move in prioritized directions
            for (const auto& dir : directions) {
                int new_y = y_curent + dir.first;
                int new_x = x_curent + dir.second;
    
                // Check if the position is valid
                if (new_x >= 0 && new_x < HARTA_SIZE && new_y >= 0 && new_y < HARTA_SIZE) {
                    char tile = harta[new_y][new_x];
                    if (tile != '|' && tile != '-' && tile != 'F' && tile != '#') {
                        if (jucator_are_putere && (tile == 'C' || tile == 'O')) continue;
    
                        x_urmator = new_x;
                        y_urmator = new_y;
                        return;
                    }
                }
            }
    
            // Fallback to random movement if all prioritized directions are blocked
            for (int attempts = 0; attempts < 10; ++attempts) {
                int random_dir = rand() % 4;
                int new_y = y_curent + directions[random_dir].first;
                int new_x = x_curent + directions[random_dir].second;
    
                if (new_x >= 0 && new_x < HARTA_SIZE && new_y >= 0 && new_y < HARTA_SIZE) {
                    char tile = harta[new_y][new_x];
                    if (tile != '|' && tile != '-' && tile != 'F' && tile != '#') {
                        if (jucator_are_putere && (tile == 'C' || tile == 'O')) continue;
    
                        x_urmator = new_x;
                        y_urmator = new_y;
                        return;
                    }
                }
            }
    
            // Absolute fallback: move to the nearest valid tile
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int new_y = y_curent + dy;
                    int new_x = x_curent + dx;
    
                    if (new_x >= 0 && new_x < HARTA_SIZE && new_y >= 0 && new_y < HARTA_SIZE) {
                        char tile = harta[new_y][new_x];
                        if (tile != '|' && tile != '-' && tile != 'F' && tile != '#') {
                            x_urmator = new_x;
                            y_urmator = new_y;
                            return;
                        }
                    }
                }
            }
    
            // If absolutely no move is possible, stay in place
            x_urmator = x_curent;
            y_urmator = y_curent;
        }
    
    
    };
    
    
    
    
    class Fantoma_Random : public Fantoma{
        public:
            Fantoma_Random(int y, int x, vector<string>& harta, bool este_moarta) : Fantoma(y, x, harta, este_moarta){}
            void pozitieUrmatoare(vector<string>& harta, const int HARTA_SIZE, const int jucator_y, const int jucator_x,bool jucator_are_putere) override{
                int x = x_curent;
                int y = y_curent;
                int attempts = 0;
                while (true) {
                    if(attempts==10)return;
                    attempts++;
                    int directie = rand() % 4 + 1;
                    x = x_curent;
                    y = y_curent;
    
    
    
    
                    switch (directie) {
                        case 1: if (x < HARTA_SIZE - 1) x++; break; // Right
                        case 2: if (x > 0) x--; break;          // Left
                        case 3: if (y < HARTA_SIZE - 1) y++; break; // Down
                        case 4: if (y > 0) y--; break;          // Up
                    }
    
    
    
    
                    if (harta[y][x] != '|' && harta[y][x] != '-' && harta[y][x] != 'F' ) {
                        if(jucator_are_putere==1 && harta[y][x]=='C' || harta[y][x]=='O')continue;
                        else{
                        x_urmator = x;
                        y_urmator = y;
                        return;
                        }
                    }
                }
            }
    
    
    
    
    };
    
    
    
    
    class joc{
        public:
        int HARTA_SIZE;
        int ABILITATE_COOLDOWN;
        int NR_FANTOME;
        int punctaj=0;
        int SCOR_CASTIGATOR;
        int jucator_x = 0, jucator_y = 2;
        int jucator_putere_cooldown = 0;
        bool jucator_a_murit = false;
        bool jucator_are_putere = false;
        int x_anterior,y_anterior;
        bool jucator_s_a_misca;
        vector<unique_ptr<Fantoma>> Fantome;
        vector<string> harta;
        vector<vector<bool>> harta_scoring_tiles;
    
    
        void alocheaza_fantome(const int nr_fantome){
            Fantome.clear();
            Fantome.resize(nr_fantome);
        }
        void alocheaza_harta(int harta_size){
            harta.clear();
            harta.resize(harta_size,string(harta_size,'*'));
        }
    
    
        void alocheaza_harta_scoring_tiles(int harta_size){
            harta_scoring_tiles.clear();
            harta_scoring_tiles.resize(harta_size,vector<bool>(harta_size,false));
        }
        void alocheaza_MA_AB_NR(int size1,int putere_cd,int nrSpir){
            punctaj=0;
            SCOR_CASTIGATOR=0;
            jucator_a_murit=false;
            jucator_are_putere=false;
            jucator_x=9;
            jucator_y=8;
            HARTA_SIZE=size1;
            ABILITATE_COOLDOWN=putere_cd;
            NR_FANTOME=nrSpir;
        }
        joc() {}
        virtual ~joc() {}
    };