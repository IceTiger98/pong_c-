#include "CVue.h"

CVue::CVue()
{
    this->nb_windowWidth = 1080;
    this->nb_windowHeight = this->nb_windowWidth;
    this->nb_separationPixels = 1;

    this->nb_fps = 60;
    this->nb_frameDelay = 1000 / FPS;
    this->beginPlay = false;

    this->pWindow = NULL;
    this->pRenderer = NULL;
    this->isOpen = SDL_TRUE;
}

CVue::CVue(int nb_windowHeight, int nb_windowWidth, int nb_SeparatPixels, int nb_fps, int nb_ms)
{
    this->nb_windowHeight = nb_windowHeight;
    this->nb_windowWidth = nb_windowWidth;
    this->nb_separationPixels = nb_SeparatPixels;

    this->nb_fps = nb_fps;
    this->nb_frameDelay = nb_ms / FPS;
    this->beginPlay = false;

    this->pWindow = NULL;
    this->pRenderer = NULL;
    this->isOpen = SDL_TRUE;


}

CVue::CVue(CVue& vue)
{
    this->nb_windowHeight = vue.nb_windowHeight;
    this->nb_windowWidth = vue.nb_windowWidth;
    this->nb_separationPixels = vue.nb_separationPixels;

    this->nb_fps = vue.nb_fps;
    this->nb_frameDelay = vue.nb_frameDelay;
    this->beginPlay = vue.beginPlay;

    this->isOpen = vue.isOpen;
    this->pRenderer = vue.pRenderer;
    this->pWindow = vue.pWindow;
}

CVue::~CVue()
{
    if (pRenderer) {
        SDL_DestroyRenderer(pRenderer);
    }
    if (pWindow) {
        SDL_DestroyWindow(pWindow);
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    cout << "Destruction CVue" << endl;
}


//accesseurs :

SDL_Window* CVue::getPWindow()const
{
    return this->pWindow;
}

SDL_Renderer* CVue::getPRenderer()const
{
    return this->pRenderer;
}

SDL_bool CVue::getIsOpen() const
{
    return this->isOpen;
}

int CVue::getNb_WindowHeight() const
{
    return this->nb_windowHeight;
}

int CVue::getNb_Fps() const
{
    return this->nb_fps;
}

int CVue::getNb_FrameDelay() const
{
    return this->nb_frameDelay;
}

int CVue::getNb_WindowWidth() const
{
    return this->nb_windowWidth;
}

bool CVue::getBeginPlay() const
{
    return this->beginPlay;
}


//mutateurs :

void CVue::setPWindow(SDL_Window* window)
{
    this->pWindow = window;
}

void CVue::setPRenderer(SDL_Renderer* renderer)
{
    this->pRenderer = renderer;
}

void CVue::setIsOpen(SDL_bool open)
{
    this->isOpen = open;
}

void CVue::setNb_WindowHeight(int windowHeight)
{
    this->nb_windowHeight = windowHeight;
}

void CVue::setNb_WindowWidth(int windowWidth)
{
    this->nb_windowWidth = windowWidth;
}

void CVue::setBeginPlay(bool isBeginPlay)
{
    this->beginPlay = isBeginPlay;
}

//methodes :

void CVue::SDL_Inits()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
    }
}

int CVue::SDL_InitImg()
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        SDL_Log("IMG_Init:Failed to init required jpg and png support !\n");
        SDL_Log("IMG_Init: %s\n", IMG_GetError());
        return -1;
    }

    return 0;
}

int CVue::createWindow()
{
    this->pWindow = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->nb_windowWidth,
        this->nb_windowHeight,
        SDL_WINDOW_SHOWN);

    if (this->pWindow) {
        cout << "fenetre ok" << endl;
        this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_PRESENTVSYNC);


        if (pRenderer == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
            SDL_Quit();
            return EXIT_FAILURE;
        }
        else {
            cout << "Renderer ok" << endl;
        }
    }
    else {
        fprintf(stderr, "Erreur création de la fenêtre: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return 0;
}

int CVue::createWindow(char* pTitreFenetre)
{
    this->pWindow = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,this->nb_windowWidth,this->nb_windowHeight,SDL_WINDOW_SHOWN);

    if (this->pWindow) {
        cout << "Fenetre ouverte" << endl;
        this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

        //AJOUTER TITRE A LA FENETRE :
        SDL_SetWindowTitle(this->pWindow, pTitreFenetre);


        if (pRenderer == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
            SDL_Quit();
            return EXIT_FAILURE;
        }
        else {
            cout << "Renderer fait" << endl;
        }
    }
    else {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return 0;
}

void CVue::createTerrain()
{

    for (int i = 0; i < this->nb_windowHeight; i += this->nb_separationPixels) {

        SDL_SetRenderDrawColor(this->pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(this->pRenderer, this->nb_windowWidth / 2, i);
        SDL_SetRenderDrawColor(this->pRenderer, 109, 59, 125, SDL_ALPHA_OPAQUE);

    }
}

void CVue::nettoyerEcran()
{
    SDL_RenderClear(this->pRenderer);
    SDL_SetRenderDrawColor(this->pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

}

void CVue::delay(int duree)
{
    SDL_Delay(duree);
}

void CVue::affichRendu()
{
    SDL_RenderPresent(this->pRenderer);
}
