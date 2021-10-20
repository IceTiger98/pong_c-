#pragma once
#include "define.h"
#include "CVue.h"
#include "CJoueur.h"


class CBalle {

private:


protected:


	int speed_x;
	int speed_y;

	coords position;
	dimensions taille;
	collider collisionBalleJoueur;

	SDL_Rect rectBalle;
	SDL_Surface* pSurfaceBalle;
	SDL_Texture* pTextureBalle;


public:

	//constructeur :
	CBalle();
	CBalle(int x, int y, int w, int h, int v);

	~CBalle();


	//accesseurs :
	coords getPos();
	int getXPos();
	int getYPos();
	dimensions getTaille();
	int getWTaille();
	int getHTaille();
	SDL_Rect getRectBalle();
	collider GetColBalleJoueur();
	SDL_Surface* getPSurfaceBalle();
	SDL_Texture* getPTextureBalle();

	//mutateurs :
	void setPos(coords position);
	void setTaille(dimensions taille);
	void setRectBalle(SDL_Rect rect);
	void setPSurfaceBalle(SDL_Surface* surface);
	void setPTextureBalle(SDL_Texture* texture);

	//methodes :
	int createTexture(char* cheminIMG, SDL_Renderer* pRenderer);

	collider collision(CJoueur& joueur1, CJoueur& joueur2);
	void dpltCollision();
	void inversDirection();
	void checkLimitsBalle(int nb_windowHeight, int nb_separatePixels);
	void dpltB();
	void dpltH();
	void dpltG_D();

	void butJoueur(CJoueur& J1, CJoueur& J2, int ptScore, int nb_WindowWidth, int nb_WindowHeight);
	int respawnBalle(char* cheminIMG, SDL_Renderer* pRenderer, int nb_WindowWidth, int nb_WindowHeight);



};

