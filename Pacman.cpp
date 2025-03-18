#include <clase_player_fantome.cpp>
#include <functii_meniu.cpp>
#include <functii_movement_harta.cpp>



class functii_main : public functii_meniu,public fucntii_movement,public functii_harta{
    public:
    int alg_dificultate=0;
    int optiune;
    int size1,putere_cd,nrSpir;
    functii_main(int alg,int alge) : alg_dificultate(alg),optiune(alge) {}
    void alocheaza_tot(
        unique_ptr<joc>& date_joc,
        unique_ptr<functii_harta>& functii_harta,
        unique_ptr<fucntii_movement>& movement_functii,
        unique_ptr<functii_meniu>& functii_meniu,
        unique_ptr<functii_main>& functii_main_functii
        ){
        do {
            // Display meniu and handle user input
        functii_meniu->tipareste_titlu(functii_main_functii->optiune);
            if (functii_main_functii->optiune == 1)
                functii_meniu->setari(functii_main_functii->alg_dificultate);
            if (functii_main_functii->optiune == 2)
                exit(0);
        } while (functii_main_functii->optiune != 0);


        // Configure joc difficulty
        functii_meniu->dificultate_setter(
            functii_main_functii->alg_dificultate,
            functii_main_functii->size1,
            functii_main_functii->putere_cd,
            functii_main_functii->nrSpir
        );


        // Initialize joc resources
        date_joc->alocheaza_MA_AB_NR(
            functii_main_functii->size1,
            functii_main_functii->putere_cd,
            functii_main_functii->nrSpir
        );
        functii_meniu->dificultate_setter(
            functii_main_functii->alg_dificultate,
            functii_main_functii->size1,
            functii_main_functii->putere_cd,
            functii_main_functii->nrSpir
        );


        // Initialize joc resources
        date_joc->alocheaza_MA_AB_NR(
            functii_main_functii->size1,
            functii_main_functii->putere_cd,
            functii_main_functii->nrSpir
        );


        date_joc->alocheaza_fantome(date_joc->NR_FANTOME);
        date_joc->alocheaza_harta(date_joc->HARTA_SIZE);
        date_joc->alocheaza_harta_scoring_tiles(date_joc->HARTA_SIZE);




        functii_harta->initializeazaHarta(
            date_joc->harta,
            date_joc->harta_scoring_tiles,
            date_joc->HARTA_SIZE,
            functii_main_functii->alg_dificultate
        );
        movement_functii->CreazaFantome(
            date_joc->NR_FANTOME,
            date_joc->HARTA_SIZE,
            date_joc->Fantome,
            date_joc->harta
        );




        date_joc->SCOR_CASTIGATOR = functii_harta->calc_punctaj_castigator(
            date_joc->HARTA_SIZE,
            date_joc->harta_scoring_tiles
        ) - 1;
        date_joc->punctaj = 0;
        date_joc->harta[date_joc->jucator_y][date_joc->jucator_x] = 'C';
    }
    void abilitati_si_input
        (
        unique_ptr<joc>& date_joc,
        unique_ptr<fucntii_movement>& movement_functii
        )
        {
        movement_functii->verificare_putere_cooldown(
        date_joc->jucator_putere_cooldown,
        date_joc->jucator_are_putere
        );
        date_joc->x_anterior = date_joc->jucator_x;
        date_joc->y_anterior = date_joc->jucator_y;


        date_joc->jucator_s_a_misca = movement_functii->gestioneazaInput(
            date_joc->jucator_x,
            date_joc->jucator_y,
            date_joc->HARTA_SIZE
        );
        }
    void coliziuni
    (
        unique_ptr<joc>& date_joc,
        unique_ptr<fucntii_movement>& movement_functii
    )
    {
        movement_functii->coliziune_cu_perete(
            date_joc->harta,
            date_joc->jucator_x,
            date_joc->jucator_y,
            date_joc->x_anterior,
            date_joc->y_anterior,
            date_joc->jucator_s_a_misca
        );




        movement_functii->verifica_daca_jucatorul_are_putere(
            date_joc->harta,
            date_joc->jucator_x,
            date_joc->jucator_y,
            date_joc->jucator_are_putere,
            date_joc->jucator_putere_cooldown,
            date_joc->ABILITATE_COOLDOWN
        );




        movement_functii->coliziune_cu_fantome(
            date_joc->Fantome,
            date_joc->harta,
            date_joc->NR_FANTOME,
            date_joc->jucator_x,
            date_joc->jucator_y,
            date_joc->jucator_are_putere,
            date_joc->jucator_a_murit
        );
    }


    void miscare_player_fantome
    (
    unique_ptr<joc>& date_joc,
    unique_ptr<fucntii_movement>& movement_functii,
    unique_ptr<functii_harta>& harta_functii


    )
    {
        if (date_joc->jucator_s_a_misca) {
                    harta_functii->actualizeazaHartaJocului(
                    date_joc->harta,
                    date_joc->jucator_x,
                    date_joc->jucator_y,
                    date_joc->x_anterior,
                    date_joc->y_anterior,
                    date_joc->punctaj,
                    date_joc->harta_scoring_tiles
                );
            }
        // Ghost-related updates
        movement_functii->Miscare_fantome(
            date_joc->Fantome,
            date_joc->NR_FANTOME,
            date_joc->harta,
            date_joc->HARTA_SIZE,
            date_joc->jucator_y,
            date_joc->jucator_x,
            date_joc->jucator_are_putere
        );


    }


    void afisare_completa
    (
    unique_ptr<joc>& date_joc,
    unique_ptr<functii_harta>& harta_functii
    )
    {
        cout << harta_functii->afiseazaHarta(
            date_joc->harta,
            date_joc->punctaj,
            date_joc->jucator_putere_cooldown,
            date_joc->HARTA_SIZE
        );
        cout << endl << endl << date_joc->SCOR_CASTIGATOR;
        harta_functii->mutaCursorLaInceput();
        Sleep(100);
    }


    void ecran_castig_mort
    (
        unique_ptr<joc>& date_joc,
        unique_ptr<functii_meniu>& meniu_functii,
        unique_ptr<functii_main>& functii_main_functii
    )
    {
            system("CLS");
            cout << (date_joc->jucator_a_murit ? "AI PIERDUT" : "FELICITARI!") << endl;
            Sleep(500);
            meniu_functii->optiune_dupa_moarte_castig(functii_main_functii->optiune);
    }


};




int main() {
    cout << "Se incarca..";
    unique_ptr<functii_meniu> meniu_functii = make_unique<functii_meniu>();
    unique_ptr<fucntii_movement> movement_functii = make_unique<fucntii_movement>();
    unique_ptr<functii_harta> harta_functii = make_unique<functii_harta>();
    unique_ptr<functii_main> functii_main_functii = make_unique<functii_main>(0, 3);
    unique_ptr<joc> date_joc = make_unique<joc>();
    while (true) {
        system("CLS");
        srand(time(NULL));


        functii_main_functii->alocheaza_tot(
            date_joc,
            harta_functii,
            movement_functii,
            meniu_functii,
            functii_main_functii
        );


        if (functii_main_functii->optiune == 0) {
            harta_functii->mutaCursorLaInceput();
            while (true) {
                functii_main_functii->abilitati_si_input(date_joc,movement_functii);
                functii_main_functii->coliziuni(date_joc,movement_functii);


                if (date_joc->jucator_a_murit) break;


                functii_main_functii->miscare_player_fantome(date_joc,movement_functii,harta_functii);
                functii_main_functii->afisare_completa(date_joc,harta_functii);


                if (date_joc->punctaj == date_joc->SCOR_CASTIGATOR) break;
            }
            functii_main_functii->ecran_castig_mort(date_joc,meniu_functii,functii_main_functii);


            if (functii_main_functii->optiune == 1) break;
            else{

            }
        }
    }
}











