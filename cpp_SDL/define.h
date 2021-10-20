#pragma once
#include<iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 640 
#define MAX_SCORE 10
#define COEFF_SCORE 1
#define FPS 60
#define MS 1000
#define SEPARATE_PIXELS 4
#define SEPARATE_PIXELS_LIMITS 20

#define TITRE_FENETRE "RAYPONG"
#define CHEMIN_SPRITE_JOUEUR1 "../Images/paddle1.png"
#define CHEMIN_SPRITE_JOUEUR2 "../Images/paddle2.png"
#define CHEMIN_SPRITE_BALLE "../Images/ball.png"
//#define CHEMIN_SPRITE_FOND "../Images/fond.png"
//#define CHEMIN_POLICE_TEXT "../Font/BATMOS.ttf"

//Sprite
#define WIDTHJOUEUR 30
#define HEIGHTJOUEUR 100
#define SEPARATE_BORDSJ1 5
#define SEPARATE_BORDSJ2 35
#define VITESSEDEPLT 18
#define VITESSE_BALLE 5
#define WIDTHBALLE 30
#define HEIGHTBALLE 30
// taille de la chaine de caractère par défaut
#define TAILLE 45


typedef struct coords {

	int x;
	int y;
}coords;

typedef struct dimensions {
	int w;
	int h;
}dimensions;

enum class controller { 
	up, 
	down, 
	idle
};

enum class collider { 
	col_H = 1,
	col_C, 
	col_B, 
	none = 0 
};
