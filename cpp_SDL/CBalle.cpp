#include "CBalle.h"

CBalle::CBalle()
{
	this->position.x = 0;
	this->position.y = 0;
	this->taille.w = 0;
	this->taille.h = 0;

	this->speed_x = 0;
	this->speed_y = 0;
	this->collisionBalleJoueur = collider::none;

	this->rectBalle = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceBalle = nullptr;
	this->pTextureBalle = nullptr;

}

CBalle::CBalle(int x, int y, int w, int h, int v)
{
	this->position.x = x;
	this->position.y = y;
	this->taille.w = w;
	this->taille.h = h;

	this->speed_x = v;
	this->speed_y = v;
	this->collisionBalleJoueur = collider::none;

	this->rectBalle = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceBalle = nullptr;
	this->pTextureBalle = nullptr;
}

CBalle::~CBalle()
{
	if (this->pTextureBalle) {
		SDL_FreeSurface(this->pSurfaceBalle);
		SDL_DestroyTexture(this->pTextureBalle);
	}
	cout << "Destruction CJoueur faite" << endl;
}

coords CBalle::getPos()
{
	return this->position;
}

int CBalle::getXPos()
{
	return this->position.x;
}

int CBalle::getYPos()
{
	return this->position.y;
}

dimensions CBalle::getTaille()
{
	return this->taille;
}

int CBalle::getWTaille()
{
	return this->taille.w;
}

int CBalle::getHTaille()
{
	return this->taille.h;
}

SDL_Rect CBalle::getRectBalle()
{
	return this->rectBalle;
}

collider CBalle::GetColBalleJoueur()
{
	return this->collisionBalleJoueur;
}

SDL_Surface* CBalle::getPSurfaceBalle()
{
	return this->pSurfaceBalle;
}

SDL_Texture* CBalle::getPTextureBalle()
{
	return this->pTextureBalle;
}

void CBalle::setPos(coords position)
{
	this->position = position;
}

void CBalle::setTaille(dimensions taille)
{
	this->taille = taille;
}

void CBalle::setRectBalle(SDL_Rect rect)
{
	this->rectBalle = rect;
}

void CBalle::setPSurfaceBalle(SDL_Surface* surface)
{
	this->pSurfaceBalle = surface;
}

void CBalle::setPTextureBalle(SDL_Texture* texture)
{
	this->pTextureBalle = texture;
}





int CBalle::createTexture(char* cheminIMG, SDL_Renderer* pRenderer)
{
	this->pSurfaceBalle = IMG_Load(cheminIMG);

	if (!this->pSurfaceBalle) {
		SDL_Log("Unable to set surface: %s", SDL_GetError());
		return 1;
	}
	else {
		this->pTextureBalle = SDL_CreateTextureFromSurface(pRenderer, pSurfaceBalle);

		if (!this->pTextureBalle) {
			SDL_Log("Unable SDL_CreatetextureFromSurface %s", SDL_GetError());
			return 1;
		}
	}
	SDL_Rect dst_IMG = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	rectBalle = dst_IMG;
	SDL_RenderCopy(pRenderer, pTextureBalle, NULL, &rectBalle);

	return 0;
}

int CBalle::respawnBalle(char* cheminIMG, SDL_Renderer* pRenderer, int nb_WindowWidth, int nb_WindowHeight)
{

	int returnError = 0;
	int centreXBalle = this->position.x + this->taille.w / 2;
	int centreXTerrain = nb_WindowWidth / 2 - this->taille.w / 2;
	int centreYTerrain = nb_WindowHeight / 2 - this->taille.h / 2;

	//si la balle sort du terrain alors on respawn
	if (centreXBalle <0 || centreXBalle> nb_WindowWidth) {

		returnError = this->createTexture(cheminIMG, pRenderer);
		this->position.x = centreXTerrain;
		this->position.y = centreYTerrain;
		cout << "respawn balle" << endl;
		this->inversDirection();
	}

	return returnError;
}

void CBalle::checkLimitsBalle(int nb_windowHeight, int nb_separatePixels)
{
	if (this->position.y <= 0) {
		this->speed_y = this->speed_y * -1;
	}
	if (this->position.y >= nb_windowHeight - nb_separatePixels) {
		this->speed_y = this->speed_y * -1;
	}
}



collider CBalle::collision(CJoueur& joueur1, CJoueur& joueur2)
{
	SDL_Rect rectBalle = this->rectBalle;
	SDL_Rect rectJoueur1 = joueur1.getRectJoueur();
	SDL_Rect rectJoueur2 = joueur2.getRectJoueur();

	int balleYCentre = this->position.y + this->taille.h / 2;
	int joueur1YCentre = joueur1.getYPos() + joueur1.getHTaille() / 2;
	int joueur2YCentre = joueur2.getYPos() + joueur2.getHTaille() / 2;


	if (SDL_HasIntersection(&rectBalle, &rectJoueur1) && !SDL_HasIntersection(&rectBalle, &rectJoueur2)) {

		if (balleYCentre < joueur1YCentre && balleYCentre >= joueur1.getYPos()) {
			this->collisionBalleJoueur = collider::col_H;
			this->inversDirection();
		}
		if (balleYCentre == joueur1YCentre) {
			this->collisionBalleJoueur = collider::col_C;
			this->inversDirection();

		}
		if (balleYCentre > joueur1YCentre && balleYCentre <= joueur1.getYPos() + joueur1.getHTaille()) {
			this->collisionBalleJoueur = collider::col_B;
			this->inversDirection();
		}
	}
	if (SDL_HasIntersection(&rectBalle, &rectJoueur2) && !SDL_HasIntersection(&rectBalle, &rectJoueur1)) {

		if (balleYCentre < joueur2YCentre && balleYCentre >= joueur2.getYPos()) {
			this->collisionBalleJoueur = collider::col_H;
			this->inversDirection();
		}
		if (balleYCentre == joueur2YCentre) {
			this->collisionBalleJoueur = collider::col_C;
			this->inversDirection();

		}
		if (balleYCentre > joueur2YCentre && balleYCentre <= joueur2.getYPos() + joueur2.getHTaille()) {
			this->collisionBalleJoueur = collider::col_B;
			this->inversDirection();
		}
	}


	return this->collisionBalleJoueur;
}

void CBalle::dpltCollision()
{
	switch (this->collisionBalleJoueur) {
	case collider::col_H:
		this->dpltB();
		this->dpltG_D();
		break;

	case collider::col_C:
		this->dpltG_D();
		break;

	case collider::col_B:
		this->dpltH();
		this->dpltG_D();
		break;

	case collider::none:
		this->dpltG_D();
		break;

	}
}

void CBalle::dpltH()
{
	this->position.y -= this->speed_y;

}

void CBalle::dpltB()
{
	this->position.y = this->position.y + this->speed_y;
}

void CBalle::dpltG_D()
{
	this->position.x += this->speed_x;
}

void CBalle::butJoueur(CJoueur& J1, CJoueur& J2, int ptScore, int nb_WindowWidth, int nb_WindowHeight)
{
	int returnError = 0;
	int centreXBalle = this->position.x + this->taille.w / 2;
	int centreXTerrain = nb_WindowWidth / 2 - this->taille.w / 2;
	int centreYTerrain = nb_WindowHeight / 2 - this->taille.h / 2;

	//Quand le J1 marque un point
	if (centreXBalle < 0) {
		J2.addScore(ptScore);
	}
	//Quand le J2 marque un point
	if (centreXBalle > nb_WindowWidth) {
		J1.addScore(ptScore);
	}
}

void CBalle::inversDirection()
{
	//si collision, alors la balle change de sens
	this->speed_x = this->speed_x * -1;

}