#pragma once
#include "define.h"
#include "CVue.h"

class CJoueur {

private:


protected:

	int nb_score;
	coords position;
	dimensions taille;
	controller control;
	//collider collisionJoueurBalle;

	SDL_Rect rectJoueur;
	SDL_Surface* pSurfaceJoueur;
	SDL_Texture* pTextureJoueur;



public:


	//constructeur :
	CJoueur();
	CJoueur(int x, int y, int w, int h);

	//constructeur de copie :
	CJoueur(CJoueur& joueur);
	//destructeur :
	~CJoueur();


	//accesseurs :
	int getNbScore();
	coords getPos();
	int getXPos();
	int getYPos();
	dimensions getTaille();
	int getWTaille();
	int getHTaille();
	controller getControl();
	//collider getCollision();
	SDL_Rect getRectJoueur();
	SDL_Surface* getPSurfaceJoueur();
	SDL_Texture* getPTextureJoueur();

	//mutateurs :
	void setNbScore(int nb_score);
	void setPos(coords position);
	void setTaille(dimensions taille);
	void setControl(controller controls);
	void setRectJoueur(SDL_Rect rect);
	void setPSurfaceJoueur(SDL_Surface* surfaceJ);
	void setPTextureJoueur(SDL_Texture* tectureJ);


	//methodes :
	int createTexture(char* cheminIMG, SDL_Renderer* pRenderer);
	void handleEvent(controller controls, int vitesse, int nb_WindowHeight);
	void depltHaut(int vitesse);
	void depltBas(int vitesse, int nb_WindowHeight);

	void addScore(int ptScore);



};
