// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("init():" + std::string(SDL_GetError()));

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("init(): SDL_image could not initialize! "
            "SDL_image Error: " +
            std::string(IMG_GetError()));


}

namespace {
    // Defining a namespace without a name -> Anonymous workspace
    // Its purpose is to indicate to the compiler that everything
    // inside of it is UNIQUELY used within this source file.

    SDL_Surface* load_surface_for(const std::string& path,
        SDL_Surface* window_surface_ptr) {

        // Helper function to load a png for a specific surface
        // See SDL_ConvertSurface
    }
} // namespace


bool animal::collision(animal& a) {
    return (this->x_ < a.getX_() + size &&
        this->x_ + size > a.getX_() &&
        this->y_ < a.getY_() + size &&
        size + this->y_ > a.getY_());
}

float animal::distance(animal& a) {
    return sqrt( pow((this->x_+(size/2)) - (a.getX_() + (size / 2)),2) + pow((this->y_ + (size / 2)) - (a.getY_() + (size / 2)), 2));
}

void animal::normalize() {

    float norm = sqrt(this->dirX_ * this->dirX_ + this->dirY_ * this->dirY_);
    this->dirX_ = this->dirX_ / norm;
    this->dirY_ = this->dirY_ / norm;
}

void animal::move() {}
void sheep::move() {
    if (fleeing) {
        if (this->x_ + this->dirX_ * this->speedX_ + size <= frame_width - frame_boundary && this->x_ + this->dirX_ * this->speedX_ >= frame_boundary) {
            this->setX_(this->x_ + this->dirX_ * this->speedX_);
        }
        if (this->y_ + this->dirY_ * this->speedY_ + size <= frame_height - frame_boundary && this->y_ + this->dirY_ * this->speedY_ >= frame_boundary) {
            this->setY_(this->y_ + this->dirY_ * this->speedY_);
        }
    }
    else {
        if (this->x_ + this->dirX_ * this->speedX_ + size > frame_width - frame_boundary || this->x_ + this->dirX_ * this->speedX_ < frame_boundary) {
                this->setDirX(-this->dirX_);
        }
        if (this->y_ + this->dirY_ * this->speedY_ + size > frame_height - frame_boundary || this->y_ + this->dirY_ * this->speedY_ < frame_boundary) {
                this->setDirY(-this->dirY_);
        }
        this->setX_(this->x_ + this->dirX_ * this->speedX_);
        this->setY_(this->y_ + this->dirY_ * this->speedY_);
        
    }
    
}
void wolf::move() {
    if (fleeing) {
        if (this->x_ + this->dirX_ * this->speedX_ + size <= frame_width - frame_boundary && this->x_ + this->dirX_ * this->speedX_ >= frame_boundary) {
            this->setX_(this->x_ + this->dirX_ * this->speedX_);
        }
        if (this->y_ + this->dirY_ * this->speedY_ + size <= frame_height - frame_boundary && this->y_ + this->dirY_ * this->speedY_ >= frame_boundary) {
            this->setY_(this->y_ + this->dirY_ * this->speedY_);
        }
    }
    else {
        if (this->x_ + this->dirX_ * this->speedX_ + size > frame_width - frame_boundary || this->x_ + this->dirX_ * this->speedX_ < frame_boundary) {
            this->setDirX(-this->dirX_);
        }
        if (this->y_ + this->dirY_ * this->speedY_ + size > frame_height - frame_boundary || this->y_ + this->dirY_ * this->speedY_ < frame_boundary) {
            this->setDirY(-this->dirY_);
        }
        this->setX_(this->x_ + this->dirX_ * this->speedX_);
        this->setY_(this->y_ + this->dirY_ * this->speedY_);

    }
}

void dog::move() {

    if (this->x_ + this->dirX_ * this->speedX_ + size <= frame_width - frame_boundary && this->x_ + this->dirX_ * this->speedX_ >= frame_boundary) {
        this->setX_(this->x_ + this->dirX_ * this->speedX_);
    }
    if (this->y_ + this->dirY_ * this->speedY_ + size <= frame_height - frame_boundary && this->y_ + this->dirY_ * this->speedY_ >= frame_boundary) {
        this->setY_(this->y_ + this->dirY_ * this->speedY_);
    }
 
}

void shepherd::move() {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if ((keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) && this->y_ - speed > frame_boundary) {
        this->y_ -= this->speed;
    }
    if ((keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) && this->y_ + speed + size < frame_height - frame_boundary) {
        this->y_ += this->speed;
    }
    if ((keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) && this->x_ - speed > frame_boundary) {
        this->x_ -= this->speed;
    }
    if ((keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) && this->x_ + speed + size < frame_width - frame_boundary) {
        this->x_ += this->speed;
    }
}

void ground::drawAll() {
    auto rect = SDL_Rect{ 0,0,frame_width,frame_height };
    SDL_BlitSurface(IMG_Load("prairie.png"), NULL, window_surface_ptr_, &rect);
    for (int i = 0; i < this->nAnimal; i++) {

        this->vAnimal[i]->draw();
    }
    aShepherd.draw();
}

void ground::moveAll() {

    std::set<int> deadAnimals;
    std::vector<std::unique_ptr<animal>> newSheeps;

    for (int i = 0; i < nAnimal; i++) {
        if (!vAnimal[i]->isPrey() && !vAnimal[i]->isFriendly()) {
            std::vector<float> distances;
            std::vector<int> dangers;
            for (int j = 0; j < nAnimal; j++) {
                if (vAnimal[j]->isPrey()) {
                    distances.push_back(vAnimal[j]->distance(*this->vAnimal[i]));
                    if (vAnimal[j]->collision(*this->vAnimal[i])) {
                        deadAnimals.insert(j);
                    }


                }
                else if (!vAnimal[j]->isPrey() && vAnimal[j]->isFriendly()) {
                    float distanceWolfDog = vAnimal[j]->distance(*this->vAnimal[i]);
                    distances.push_back(distanceWolfDog);
                    if (distanceWolfDog < 200) {
                       dangers.push_back(j);
                    }
                }

                else {
                    distances.push_back(999999);
                }
            }

            if (dangers.size() == 0) {
                float min_dist = 999999;
                int best_prey = -1;
                for (int j = 0; j < distances.size(); j++) {
                    if (vAnimal[j]->isPrey() && min_dist > distances[j]) {
                        min_dist = distances[j];
                        best_prey = j;
                    }
                }

                if (best_prey != -1) {

                    if (!vAnimal[best_prey]->collision(*std::move(this->vAnimal[i]))) {

                        vAnimal[i]->setDirX(vAnimal[best_prey]->getX_() + (size / 2) - vAnimal[i]->getX_());

                        vAnimal[i]->setDirY(vAnimal[best_prey]->getY_() + (size / 2) - vAnimal[i]->getY_());

                        vAnimal[i]->normalize();
                    }
                    else {
                        deadAnimals.insert(best_prey);
                        vAnimal[i]->setSpeedBoost(20);
                    }

                }


            }

            else {
                this->vAnimal[i]->setFleeing(true);
                float dirXTemp = 0;
                float dirYTemp = 0;
                for (int j : dangers) {
                    dirXTemp += (vAnimal[i]->getX_() - vAnimal[j]->getX_()) * (1 / distances[j]);
                    dirYTemp += (vAnimal[i]->getY_() - vAnimal[j]->getY_()) * (1 / distances[j]);
                }
                vAnimal[i]->setDirX(dirXTemp);
                vAnimal[i]->setDirY(dirYTemp);
                vAnimal[i]->normalize();
            }

            if (this->vAnimal[i]->getSpeedBoost() > 0) { // pour la mort du loup
                this->vAnimal[i]->setSpeedBoost(this->vAnimal[i]->getSpeedBoost() - 0.1);
            }
            else {
                deadAnimals.insert(i);
            }
        }
        else if (vAnimal[i]->isPrey()) {
            if (vAnimal[i]->getMatingTimer()>0)
                vAnimal[i]->setMatingTimer(vAnimal[i]->getMatingTimer()+1);
            
            for (int j = 0; j < nAnimal; j++) {
                if (vAnimal[j]->isPrey() && vAnimal[j]->collision(*this->vAnimal[i]) && vAnimal[j]->getMale()==true && vAnimal[i]->getMale()==false && !vAnimal[j]->getFleeing() && !vAnimal[i]->getFleeing()) {
                    if (vAnimal[i]->getMatingTimer() == 0) {
                        std::unique_ptr<animal> s = std::make_unique<sheep>(sheep(window_surface_ptr_, vAnimal[i]->getX_(), vAnimal[i]->getY_()));
                        s->setMatingTimer(1000); // L'enfant ne peut pas se reproduire tout de suite
                        newSheeps.push_back(std::move(s));
                        
                        vAnimal[i]->setMatingTimer(500);
                    }
                }
                    
            }

            std::vector<float> distances;
            std::vector<int> newSheeps;
            for (int j = 0; j < nAnimal; j++) {
                if (!vAnimal[j]->isPrey() && !vAnimal[i]->isFriendly()) {
                    distances.push_back(vAnimal[j]->distance(*this->vAnimal[i]));
                }
                else {
                    distances.push_back(999999);
                }
            }
            
            
            
            std::vector<int> dangers;
            int index = 0;
            for (float j : distances) {
                if (j < 200) {
                    dangers.push_back(index);
                }
                index++;
            }
            
            if (dangers.size() == 0) {
                this->vAnimal[i]->setSpeedX(3);
                this->vAnimal[i]->setSpeedY(3);
                this->vAnimal[i]->setFleeing(false);
                if (this->vAnimal[i]->getSpeedBoost() <= 20)
                    this->vAnimal[i]->setSpeedBoost(this->vAnimal[i]->getSpeedBoost() + 0.1);
                else
                    this->vAnimal[i]->setExhausted(false);
            }
            else {
                this->vAnimal[i]->setFleeing(true);
                if (this->vAnimal[i]->getSpeedBoost() > 0 && !this->vAnimal[i]->getExhausted()) {
                    this->vAnimal[i]->setSpeedX(10);
                    this->vAnimal[i]->setSpeedY(10);
                    this->vAnimal[i]->setSpeedBoost(this->vAnimal[i]->getSpeedBoost() - 1);
                }
                else {
                    this->vAnimal[i]->setSpeedX(3);
                    this->vAnimal[i]->setSpeedY(3);
                    this->vAnimal[i]->setExhausted(true);
                }

                float dirXTemp = 0;
                float dirYTemp = 0;
                for (int j : dangers) {
                    dirXTemp += (vAnimal[i]->getX_() - vAnimal[j]->getX_()) * (1 / distances[j]);
                    dirYTemp += (vAnimal[i]->getY_() - vAnimal[j]->getY_()) * (1 / distances[j]);
                }
                vAnimal[i]->setDirX(dirXTemp);
                vAnimal[i]->setDirY(dirYTemp);
                vAnimal[i]->normalize();
                
            }

        }
        else {
            this->vAnimal[i]->setDirX((200 * cos(frames / 20.) + aShepherd.getX_() + (size/2) - vAnimal[i]->getX_()));
            this->vAnimal[i]->setDirY((200 * sin(frames / 20.) + aShepherd.getY_() + (size/2) - vAnimal[i]->getY_()));
            this->vAnimal[i]->normalize();
        }
        this->vAnimal[i]->move();
        
    }
    this->aShepherd.move();
    int compteur = 0;
    for (int i : deadAnimals) {
        //vAnimal[i - compteur].reset();
        vAnimal.erase(std::remove(vAnimal.begin(), vAnimal.end(), vAnimal[i - compteur]));
        compteur++;
        
        nAnimal--;
    }

    while (newSheeps.size() != 0) {
        nAnimal++;
        vAnimal.push_back(std::move(newSheeps.back()));
        newSheeps.pop_back();
    }
    
}

void ground::update() {
    
    this->moveAll();
    this->drawAll();
    frames++;
}


application::application(unsigned n_sheep, unsigned n_wolf) : g_(ground(window_surface_ptr_, n_sheep, n_wolf)) {
    window_ptr_ = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        frame_width, frame_height,
        0);
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
    g_.setWindow_surface_ptr_(window_surface_ptr_);

    for (int i = 0; i < g_.getN(); i++) {
        g_.setW_(window_surface_ptr_, i);
    }

    g_.setWS_(window_surface_ptr_);


}

application::~application() {};

int application::loop(unsigned period) {
    auto start = SDL_GetTicks();
    SDL_Event e;
    bool quit = false;
    while (!quit && (SDL_GetTicks() - start < period)) {
        g_.update();
        
        SDL_UpdateWindowSurface(this->getWindow_ptr_());
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
    }
    return 0;
}
