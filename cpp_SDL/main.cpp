#include "define.h"
#include "CVue.h"
#include "CJoueur.h"
#include "CBalle.h"
#include "CText.h"

using namespace std;

int main(int argc, char** argv)
{
    CVue fenetre(WINDOW_HEIGHT,WINDOW_WIDTH,SEPARATE_PIXELS, FPS, MS);
    fenetre.SDL_Inits();
    fenetre.SDL_InitImg();

    // Création de la fenêtre 
    char* pTitreFenetre = new char[TAILLE];
    strcpy_s(pTitreFenetre, TAILLE, TITRE_FENETRE);
    fenetre.createWindow(pTitreFenetre);   
    
    //init J1
    CJoueur J1(SEPARATE_BORDSJ1, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2, WIDTHJOUEUR, HEIGHTJOUEUR);
    char* pCheminIMG1 = new char[TAILLE];
    strcpy_s(pCheminIMG1, TAILLE, CHEMIN_SPRITE_JOUEUR1);
 
    //init J2
    CJoueur J2(WINDOW_WIDTH-SEPARATE_BORDSJ2,WINDOW_HEIGHT / 2-HEIGHTJOUEUR/2, WIDTHJOUEUR, HEIGHTJOUEUR);
    char* pCheminIMG2 = new char[TAILLE];
    strcpy_s(pCheminIMG2, TAILLE, CHEMIN_SPRITE_JOUEUR2);

    //init Ball
    CBalle balle(WINDOW_WIDTH / 2 - WIDTHBALLE / 2, WINDOW_HEIGHT / 2, WIDTHBALLE, HEIGHTBALLE, VITESSE_BALLE);
    char* pCheminIMGBalle = new char[TAILLE];
    strcpy_s(pCheminIMGBalle, TAILLE, CHEMIN_SPRITE_BALLE);

    //Boucle de jeu 
    SDL_Event events;
    Uint32 frameStart;
    int frameTime;
    balle.inversDirection();

    do
    {
        frameStart = SDL_GetTicks();

        //Affichage :
        fenetre.createTerrain();
        J1.createTexture(pCheminIMG1, fenetre.getPRenderer());
        J2.createTexture(pCheminIMG2, fenetre.getPRenderer());
        balle.createTexture(pCheminIMGBalle, fenetre.getPRenderer());

        //on regarde s'il y a une collision 
        balle.collision(J1, J2);
        //Collision + inversion du sens de la balle
        balle.checkLimitsBalle(WINDOW_HEIGHT, SEPARATE_PIXELS_LIMITS);
        balle.dpltCollision();
        //Joueur marque 1 point
        balle.butJoueur(J1, J2, COEFF_SCORE, WINDOW_WIDTH, WINDOW_HEIGHT);
        //Service de la balle
        balle.respawnBalle(pCheminIMGBalle, fenetre.getPRenderer(), WINDOW_WIDTH,WINDOW_HEIGHT);

        fenetre.affichRendu();

        //Boucle des inputs
        while (SDL_PollEvent(&events))
        {
            //Input J1 
            switch (events.type){
                case SDL_QUIT:
                    fenetre.setIsOpen(SDL_FALSE);
                break;

                case SDL_KEYDOWN :
                    switch (events.key.keysym.sym) {
                        case SDLK_z:
                            J1.handleEvent(controller::up,VITESSEDEPLT,WINDOW_HEIGHT);
                        break;  
                        case SDLK_s:
                            J1.handleEvent(controller::down, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                        default:
                            J1.handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    }
                break;
            }

            //Input J2
            switch (events.type) {
                case SDL_KEYDOWN:
                    switch (events.key.keysym.sym) {
                    case SDLK_UP:
                        J2.handleEvent(controller::up, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    case SDLK_DOWN:
                        J2.handleEvent(controller::down, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    default:
                        J2.handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    }
                break;
             }

           //Si MAX_SCORE atteind, le jeu se termine
            if (J1.getNbScore()==MAX_SCORE || J2.getNbScore()==MAX_SCORE) {
                fenetre.setIsOpen(SDL_FALSE);
            }
            
        }

        fenetre.nettoyerEcran();
        frameTime = SDL_GetTicks() - frameStart;

    } while (fenetre.getIsOpen());

    delete[] pTitreFenetre;
    delete[] pCheminIMG1;
    delete[] pCheminIMG2;
    delete[] pCheminIMGBalle;
   
    return 0;
}
