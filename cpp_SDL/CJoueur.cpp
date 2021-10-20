#include "CJoueur.h"

CJoueur::CJoueur()
{
	this->nb_score = 0;
	this->position.x = 0;
	this->position.y = 0;

	this->taille.w = 0;
	this->taille.h = 0;
	this->control = controller::idle;

	this->rectJoueur = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceJoueur = nullptr;
	this->pTextureJoueur = nullptr;
}

CJoueur::CJoueur(int x, int y, int w, int h)
{
	this->nb_score = 0;
	this->position.x = x;
	this->position.y = y;

	this->taille.w = w;
	this->taille.h = h;
	this->control = controller::idle;

	this->rectJoueur = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceJoueur = nullptr;
	this->pTextureJoueur = nullptr;

}

CJoueur::CJoueur(CJoueur& joueur)
{
	this->nb_score = joueur.nb_score;
	this->position.x = joueur.position.x;
	this->position.y = joueur.position.y;
	this->taille.w = joueur.taille.w;
	this->taille.h = joueur.taille.h;
	this->control = joueur.control;

	this->rectJoueur = joueur.rectJoueur;
	this->pSurfaceJoueur = joueur.pSurfaceJoueur;
	this->pTextureJoueur = joueur.pTextureJoueur;
}

CJoueur::~CJoueur()
{
	if (this->pTextureJoueur) {
		SDL_DestroyTexture(this->pTextureJoueur);
	}
	cout << "Destruction CJoueur faite" << endl;

}

int CJoueur::getNbScore()
{
	return this->nb_score;
}

coords CJoueur::getPos()
{
	return this->position;
}

int CJoueur::getXPos()
{
	return this->position.x;
}

int CJoueur::getYPos()
{
	return this->position.y;
}

dimensions CJoueur::getTaille()
{
	return this->taille;
}

int CJoueur::getWTaille()
{
	return this->taille.w;
}

int CJoueur::getHTaille()
{
	return this->taille.h;
}

controller CJoueur::getControl()
{
	return this->control;
}

SDL_Rect CJoueur::getRectJoueur()
{
	return this->rectJoueur;
}

SDL_Surface* CJoueur::getPSurfaceJoueur()
{
	return this->pSurfaceJoueur;
}

SDL_Texture* CJoueur::getPTextureJoueur()
{
	return this->pTextureJoueur;
}

void CJoueur::setNbScore(int nb_score)
{
	this->nb_score = nb_score;
}

void CJoueur::setPos(coords position)
{
	this->position = position;
}

void CJoueur::setTaille(dimensions taille)
{
	this->taille = taille;
}

void CJoueur::setControl(controller controls)
{
	this->control = controls;
}

void CJoueur::setRectJoueur(SDL_Rect rect)
{
	this->rectJoueur = rect;
}

void CJoueur::setPSurfaceJoueur(SDL_Surface* surfaceJ)
{
	this->pSurfaceJoueur = surfaceJ;
}

void CJoueur::setPTextureJoueur(SDL_Texture* textureJ)
{
	this->pTextureJoueur = textureJ;
}





int CJoueur::createTexture(char* cheminIMG, SDL_Renderer* pRenderer)
{
	this->pSurfaceJoueur = IMG_Load(cheminIMG);

	if (!this->pSurfaceJoueur) {
		SDL_Log("Unable to set surface: %s", SDL_GetError());
		return 1;
	}
	else {
		this->pTextureJoueur = SDL_CreateTextureFromSurface(pRenderer, pSurfaceJoueur);
		SDL_FreeSurface(this->pSurfaceJoueur);

		if (!this->pTextureJoueur) {
			SDL_Log("Unable SDL_CreatetextureFromSurface %s", SDL_GetError());
			return 1;
		}
	}
	SDL_Rect dst_IMG = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->rectJoueur = dst_IMG;
	SDL_RenderCopy(pRenderer, pTextureJoueur, NULL, &dst_IMG);

	return 0;
}

void CJoueur::handleEvent(controller controls, int vitesse, int nb_WindowHeight)
{

	this->control = controls;

	if (this->control == controller::up) {
		depltHaut(vitesse);
	}
	else if (this->control == controller::down) {
		depltBas(vitesse, nb_WindowHeight);
	}
	else {
		this->control = controller::idle;
	}
}

void CJoueur::depltHaut(int vitesse)
{
	if (this->position.y > 0) {
		this->position.y = this->position.y - vitesse;
	}

}

void CJoueur::depltBas(int vitesse, int nb_WindowHeight)
{
	if (this->position.y + this->taille.h < nb_WindowHeight) {
		this->position.y = this->position.y + vitesse;
	}

}

void CJoueur::addScore(int ptScore)
{
	this->nb_score += ptScore;
	cout << nb_score << endl;
}