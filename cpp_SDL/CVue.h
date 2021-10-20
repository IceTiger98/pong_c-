#pragma once
#include "define.h"

using namespace std;

class CVue {

private:

protected:
	int nb_windowHeight;
	int nb_windowWidth;
	bool beginPlay;
	int nb_separationPixels;
	int nb_fps;
	int nb_frameDelay;

	SDL_bool isOpen;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;



public:
	//constructeurs
	CVue();
	CVue(int nb_windowHeight, int nb_windowWidth, int nb_SeparatPixels, int nb_fps, int nb_ms);

	//constructeur de copie 
	CVue(CVue& vue);

	//destructeur :
	~CVue();


	//accesseurs 
	SDL_Window* getPWindow()const;
	SDL_Renderer* getPRenderer()const;
	SDL_bool getIsOpen()const;

	int getNb_WindowHeight()const;
	int getNb_Fps()const;
	int getNb_FrameDelay()const;
	int getNb_WindowWidth()const;
	bool getBeginPlay()const;


	//mutateurs 
	void setPWindow(SDL_Window* window);
	void setPRenderer(SDL_Renderer* renderer);
	void setIsOpen(SDL_bool open);
	void setNb_WindowHeight(int windowHeight);
	void setNb_WindowWidth(int windowWidth);
	void setBeginPlay(bool isBeginPlay);


	//methodes :
	void SDL_Inits();
	int SDL_InitImg();
	int createWindow();
	int createWindow(char* pTitreFenetre); 
	void createTerrain();
 

	void nettoyerEcran();
	void delay(int duree);
	void affichRendu();



};
