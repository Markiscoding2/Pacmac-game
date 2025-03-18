#include <stdc++.h>
#include <Windows.h>
using namespace std;
void mutaCursorLaInceput() {
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(consola, coord);
}


class functii_meniu{
public:
    functii_meniu() {}
    virtual ~functii_meniu() {}




    void tipareste_alegeri(vector<string>& optiune,int& alg,bool spatiu){
        if(!spatiu)
        for (int i = 0; i < optiune.size(); i++) {
                if (i == alg) {
                    cout << ">" << optiune[i];cout << "<    " << '\n'; // Highlight the current option
                }
                else {
                    cout << optiune[i] <<"      "<< '\n';
                }
        }
        else{
            const string space="                                    ";
            for (int i = 0; i < optiune.size(); i++) {
                if (i == alg) {
                    cout <<space<< ">" << optiune[i];cout << "<     " << '\n'; // Highlight the current option
                }
                else {
                    cout <<space<< optiune[i] <<"       "<< '\n';
                }
            }
        }
    }




    bool choice_input(int& i, bool& ales,vector<string>& optiune) {
        int alg_original=i;
        bool miscat;
        if (GetAsyncKeyState(VK_UP) & 0x8000 && i > 0) {
            miscat=true;
            i--;  // Move up
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && i < optiune.size()-1) {  // Limit the range to 2 (index 0-2)
            miscat=true;
            i++;  // Move down
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            i = alg_original;  // Exit or confirm selection
            ales=true;
        }
        Sleep(10);
        return miscat;
    }




    void optiune_dupa_moarte_castig(int& alg){
        system("CLS");
        vector<string> optiune(2);
        bool ales=false;
        optiune[0]="Da";
        optiune[1]="Nu";
        cout <<"\nDoresti sa mai joci?\n";
        tipareste_alegeri(optiune,alg,false);
        while(true){
            if (ales)
            {
                Sleep(100);
                break;
            }
            bool miscat=choice_input(alg,ales,optiune);
            if(miscat){
                system("CLS");
                cout <<"\nDoresti sa mai joci?\n";
                tipareste_alegeri(optiune,alg,false);
                miscat=false;
                Sleep(10);
            }
        Sleep(10);
        }
    }




    void tipareste_titlu(int& alg) {
        system("CLS");
        vector<string> optiune(3);
        bool ales=false;
        optiune[0] = "Start";
        optiune[1] = "Dificultate";
        optiune[2] = "Iesire";
        alg = 0;
        cout << "           " << "  ____        _       ____    __  __      _       _   _   \n";
        cout << "           " << " U|  _\"\\ u U  /\"\\  u  U /\"___| U|' \\/ '|u U  /\"\\  u   | \\ |\"|   \n";
        cout << "           " << " \\| |_) |/  \\/ _ \\/   \\| | u   \\| |\\/| |/  \\/ _ \\/   <|  \\| |>   \n";
        cout << "           " << "  |  __/  / ___ \\    | |/__   | |  | |   / ___ \\   U| |\\  |u   \n";
        cout << "           " << "  |_|     /_/   \\_\\ \\____|  |_|  |_|  /_/   \\_\\   |_| \\_|   \n";
        cout << "           " << "  ||>>_   \\\\    >>   _// \\\\  <<,-,,-. \\\\    >>   ||   \\\\,-. \n";
        cout << "           " << " (__)__)   (__)  (__) (__)(__)  (./  \\.)  (__)  (__)  (_\")  (_/  \n";
        tipareste_alegeri(optiune,alg,true);




        while (true) {
            if (ales)
            {
                Sleep(100);
                break;
            }  // Exit the bucla when "4" is selected (Enter key pressed)
            bool miscat=choice_input(alg,ales,optiune);
            if(miscat){
                mutaCursorLaInceput();  // Reset cursor position for smooth re-drawing
                cout << "           " << "  ____        _       ____    __  __      _       _   _   \n";
                cout << "           " << " U|  _\"\\ u U  /\"\\  u  U /\"___| U|' \\/ '|u U  /\"\\  u   | \\ |\"|   \n";
                cout << "           " << " \\| |_) |/  \\/ _ \\/   \\| | u   \\| |\\/| |/  \\/ _ \\/   <|  \\| |>   \n";
                cout << "           " << "  |  __/  / ___ \\    | |/__   | |  | |   / ___ \\   U| |\\  |u   \n";
                cout << "           " << "  |_|     /_/   \\_\\ \\____|  |_|  |_|  /_/   \\_\\   |_| \\_|   \n";
                cout << "           " << "  ||>>_   \\\\    >>   _// \\\\  <<,-,,-. \\\\    >>   ||   \\\\,-. \n";
                cout << "           " << " (__)__)   (__)  (__) (__)(__)  (./  \\.)  (__)  (__)  (_\")  (_/  \n";




                tipareste_alegeri(optiune,alg,true);




                miscat=false;
                Sleep(80);
            }




            // Update the selected option based on user input
            Sleep(10);  // Pause briefly to avoid excessive CPU usage
        }




        // Additional functionality after the meniu is exited can be placed here, if needed
    }




    void setari(int& alg){
        system("CLS");
        vector<string> optiune(4);
        bool ales=false;
        optiune[0] = "Usor";
        optiune[1] = "Normal";
        optiune[2] = "Greu";
        optiune[3] = "NIGHTMARE";
        alg = 0;
        tipareste_alegeri(optiune,alg,false);
        while (true) {
            if (ales)
            {
                Sleep(100);
                break;
            }  // Exit the bucla when "4" is selected (Enter key pressed)
            bool miscat=choice_input(alg,ales,optiune);
            if(miscat){
                mutaCursorLaInceput();  // Reset cursor position for smooth re-drawing
                tipareste_alegeri(optiune,alg,false);
                miscat=false;
                Sleep(50);
            }




            // Update the selected option based on user input
            Sleep(10);  // Pause briefly to avoid excessive CPU usage
        }








    }




    void dificultate_setter(int alg_dificultate,int& size1,int& putere_cd,int& nrSpir){
        switch(alg_dificultate){
                case 0:size1=18;putere_cd=500;nrSpir=3;break;
                case 1:size1=24;putere_cd=400;nrSpir=6;break;
                case 2:size1=30;putere_cd=300;nrSpir=8;break;
                case 3:size1=40;putere_cd=200;nrSpir=10;break;
        }
    }




};