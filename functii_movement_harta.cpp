#include <stdc++.h>
#include <Windows.h>
#include <clase_player_fantome.cpp>
using namespace std;
class fucntii_movement{
    public:
        fucntii_movement() {}
        virtual ~fucntii_movement() {}
        bool gestioneazaInput(int& jucator_x, int& jucator_y,const int HARTA_SIZE) {
            int x_anterior = jucator_x;
            int y_anterior = jucator_y;
    
    
    
    
            if (GetAsyncKeyState(VK_LEFT) & 0x8000 && jucator_x > 0) jucator_x--;
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && jucator_x < HARTA_SIZE-1) jucator_x++;
            else if (GetAsyncKeyState(VK_UP) & 0x8000 && jucator_y > 0) jucator_y--;
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && jucator_y < HARTA_SIZE-1) jucator_y++;
    
    
    
    
            return (jucator_x != x_anterior || jucator_y != y_anterior);
        }
    
    
    
    
        void Miscare_fantome(vector<unique_ptr<Fantoma>>& Fantome,const int NR_FANTOME,vector<string>& harta,const int HARTA_SIZE,int jucator_y,int jucator_x,bool jucator_are_putere){
            for(int i=0;i<NR_FANTOME;i++){
                int sansa_miscarilor_fantome = rand() % 5 + 1;
                if (sansa_miscarilor_fantome == 1 && !Fantome[i]->moarta) {
                Fantome[i]->pozitieUrmatoare(harta,HARTA_SIZE,jucator_y,jucator_x,jucator_are_putere);
                Fantome[i]->actualizeazaPozitia(harta);
                }
            }
        }
        void CreazaFantome(int NR_FANTOME,int HARTA_SIZE,vector<unique_ptr<Fantoma>>& Fantome,vector<string>& harta){
            for (int i = 0; i < NR_FANTOME; i++) {
                int x, y;
                do {
                    x = rand() % HARTA_SIZE;
                    y = rand() % HARTA_SIZE;
                } while (harta[y][x] != '*' && harta[y][x]=='-' && harta[y][x]=='#' && harta[y][x]=='|' && harta[y][x]=='@');  // Ensure ghosts spawn on valid tiles
            Fantome[i] = make_unique<Fantoma_Agresiva>(y, x, harta, false);
            }
        }
    
    
    
    
        void coliziune_cu_fantome(vector<unique_ptr<Fantoma>>& Fantome,vector<string>& harta, const int NR_FANTOME,int jucator_x,int jucator_y,bool& jucator_are_putere,bool& jucator_a_murit){
            for(int i=0;i<NR_FANTOME;i++){
                if (jucator_x == Fantome[i]->x_curent && jucator_y == Fantome[i]->y_curent && !Fantome[i]->moarta) {
                    if (jucator_are_putere) {
                        Fantome[i]->moarta = true;
                        harta[Fantome[i]->y_curent][Fantome[i]->x_curent] = 'C';
                    }
                    else {
                        jucator_a_murit = true;
                    }
                }
            }
        }
    
    
    
    
        void coliziune_cu_perete(vector<string>& harta,int& jucator_x,int& jucator_y,const int x_anterior,const int y_anterior,bool& jucator_s_a_misca){
            if (harta[jucator_y][jucator_x] == '|' || harta[jucator_y][jucator_x] == '-' || harta[jucator_y][jucator_x] == '#' ) {
                jucator_x = x_anterior;
                jucator_y = y_anterior;
                jucator_s_a_misca = false;
            }
        }
        void powerup_text() {
            const std::string art[] = {
                ".----------------.  .----------------.  .----------------.  .----------------.  .----------------.     .----------------.  .----------------. ",
                "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |   | .--------------. || .--------------. |",
                "| |   ______   | || |  ____    | || | _____  _____ | || |  _________   | || |  _______     | |   | | _____  _____ | || |   ______  | |",
                "| |  |_   __ \\   | || |   .'  .   | || ||_   _||_   _|| || | |_   ___  |  | || | |_   __ \\   | |   | ||_   _||_   _|| || |  |_   __ \\   | |",
                "| |    | |__) |  | || |  /  .--.  \\  | || |  | | /\\ | |  | || |   | |_  \\_|  | || |   | |__) |   | |   | |  | | | |  | || | | |__) |  | |",
                "| |    |  ___/   | || |  | |   | |  | || |  | |/  \\| |  | || |   |  _|  _   | || |   |  __ /  | |   | |  | '  ' |  | || | |  ___/   | |",
                "| |   _| |_    | || |  \\  --'  /  | || |  |   /\\   |  | || |  _| |___/ |  | || |  _| |  \\ \\_  | |   | |   \\ --' /   | || |   _| |_    | |",
                "| |  |_____|   | || |   .____.'   | || |  |__/  \\__|  | || | |_________|  | || | |____| |___| | |   | |   .__.'   | || |  |_____|     | |",
                "| |            | || |              | || |              | || |              | || |              | |   | |           | || |              | |",
                "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |   | '--------------' || '--------------' |",
                " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'    '----------------'  '----------------' "
            };
    
    
    
    
            for (const auto& line : art) {
                std::cout << line << std::endl;
            }
        }
    
    
    
    
        void verifica_daca_jucatorul_are_putere(vector<string>& harta,int jucator_x,int jucator_y,bool& jucator_are_putere,int& jucator_putere_cooldown,const int ABILITATE_COOLDOWN){
        if (harta[jucator_y][jucator_x] == '@') {
                jucator_are_putere = true;
                jucator_putere_cooldown = ABILITATE_COOLDOWN;
                for(int i=0;i<3;i++){
                    system("CLS");
                    Sleep(500);
                    powerup_text();
                    Sleep(500);
                }
    
    
    
    
            }
            system("CLS");
        }
    
    
    
    
        void verificare_putere_cooldown(int& jucator_putere_cooldown,bool& jucator_are_putere){
                if (jucator_putere_cooldown != 0) jucator_putere_cooldown--;
                if (jucator_putere_cooldown == 0) jucator_are_putere = false;
        }
    };
    
    
    
    
    class functii_harta{
    public:
        functii_harta() {}
        virtual ~functii_harta() {}
        int calc_punctaj_castigator(const int HARTA_SIZE,vector<vector<bool>> harta_scoring_tiles){
            int punctaj=0;
            for (const auto& row : harta_scoring_tiles) {
            punctaj += count(row.begin(), row.end(), true);
            }
            return punctaj;
        }
    
    
    
    
    
    
    
    
        string afiseazaHarta(const vector<string>& harta, int punctaj, int timp, const int HARTA_SIZE) {
            ostringstream output;  // Buffer for rendering the harta
    
    
    
    
            // Build the harta display
            for (int i = 0; i < HARTA_SIZE; i++) {
                for (int j = 0; j < HARTA_SIZE; j++) {
                    output << harta[i][j]; // Append harta tile
                    if (harta[i][j]!='*'
                        && harta[i][j]!='C'
                        && harta[i][j]!='O'
                        && harta[i][j]!='F'
                        && harta[i][j]!='|'
                        && harta[i][j]!='@'
                        && harta[i][j]!='#'
                        ) {
                        output << harta[i][j]; // Add space between columns
                    }
                    else output<<' ';
                }
                output << '\n'; // End each row with a newline
            }
    
    
    
    
            // Append punctaje and timer information
            output << "\nScor: " << punctaj;
            output << "\nTimp putere: " << timp << '\n';
    
    
    
    
            // Flush output to string
            return output.str();
        }
    
    
    
    
    
    
    
    
    
    
    
    
        void actualizeazaHartaJocului(vector<string>& harta, int jucator_x, int jucator_y, int x_anterior, int y_anterior, int& punctaj, vector<vector<bool>>& harta_scoring_tiles) {
        if (harta_scoring_tiles[jucator_y][jucator_x]) { // Check if tile was originally punctajing
            punctaj++;
            harta_scoring_tiles[jucator_y][jucator_x] = false; // Avoid double counting
        }
        if(harta[y_anterior][x_anterior]=='C')harta[jucator_y][jucator_x] = 'O';
        else if (harta[y_anterior][x_anterior]=='O')harta[jucator_y][jucator_x] = 'C';
        else harta[y_anterior][x_anterior]='C';
        harta[y_anterior][x_anterior] = ' ';
        }
    
    
    
    
    
    
    
    
    
    
    
    
        void initializeazaHarta(vector<string>& harta, vector<vector<bool>>& harta_scoring_tiles,const int HARTA_SIZE,int tip) {
            harta[5][9] = '@'; // Special power-up
            switch(tip){
            case 0:
                harta[0]="------------------";
                harta[1]="|@**************@|";
                harta[2]="|****************|";
                harta[3]="|*##|********|##*|";
                harta[4]="|***|********|***|";
                harta[5]= "|****--****--****|";
                harta[6]="|*****************|";
                harta[7]="---***--  --***---";
                harta[8]="|*****|*  *|*****|";
                harta[9]="---***------***---";
                harta[10]="|**|**********|**|";
                harta[11]="|**|**********|**|";
                harta[12]="|**|**********|**|";
                harta[13]="|**--********--**|";
                harta[14]="|*##**********##*|";
                harta[15]="|****************|";
                harta[16]="|@**************@|";
                harta[17]="------------------";
            break;
            case 1:
                harta = {
                    "------------------------",
                    "|@*************##*****@|", 
                    "|****|******|*****|****|",
                    "|****|******|*****|****|",
                    "|****|--****|****--|***|", 
                    "|****|##****|****##|***|", 
                    "|**********************|", 
                    "|**|***|********|***|**|", 
                    "|**|---|********|---|**|", 
                    "|**|***|********|***|**|", 
                    "|****|************|****|",
                    "|****|----****----|****|", 
                    "|********|****|********|", 
                    "|********|----|********|", 
                    "|********|****|********|", 
                    "|****|----****----|****|", 
                    "|****|************|****|", 
                    "|**|***|********|***|**|", 
                    "|**|---|********|---|**|", 
                    "|**|***|********|***|**|", 
                    "|**********************|", 
                    "|****|##****|****##|***|", 
                    "|@*************##*****@|",
                    "------------------------"  
                };
                break;
            case 2:
            
    
    
    
            break;
            case 3:
    
    
    
    
            break;
            }
            for (int i = 0; i < HARTA_SIZE; i++) {
                for (int j = 0; j < HARTA_SIZE; j++) {
                    if (harta[i][j] == '*') {
                        harta_scoring_tiles[i][j] = true;
                    }
                }
            }
        }
        void mutaCursorLaInceput() {
            HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coord = {0, 0};
            SetConsoleCursorPosition(consola, coord);
        }
    
    
    
    
    
    
    
    
    };