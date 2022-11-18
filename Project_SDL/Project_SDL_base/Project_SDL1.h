// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>
#include <math.h>
#include< set >

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

constexpr unsigned size = 50;

// Helper function to initialize SDL
void init();

class animal {
private:
    SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
    // animal to be drawn, also non-owning
    SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
    // load_surface_for
// todo: Attribute(s) to define its position
protected:
    float x_;
    float y_;
    float speedX_;
    float speedY_;
    float dirX_;
    float dirY_;
    bool male;
    float speedBoost = 20;
    bool fleeing = false;
    bool exhausted = false;
    int matingTimer = 0;

public:
    animal(const std::string& file_path, SDL_Surface* window_surface_ptr) {
        window_surface_ptr_ = window_surface_ptr;
        image_ptr_ = IMG_Load(file_path.c_str());
        x_ = (rand() % (frame_width - frame_boundary - 3*size) + frame_boundary);
        y_ = (rand() % (frame_height - frame_boundary - 3*size) + frame_boundary);
        speedX_;
        speedY_;
        float theta = rand() % 1000;
        dirX_ = cos(theta);
        dirY_ = sin(theta);
        male = rand() % 2 == 0;

    };
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    ~animal() {}; // todo: Use the destructor to release memory and "clean up
    // behind you"

    SDL_Surface* getWindow_surface_ptr_() { return window_surface_ptr_; };
    SDL_Surface* getImage_ptr_() { return image_ptr_; };
    float getX_() { return x_; };
    float getY_() { return y_; };
    float getSpeedX() { return speedX_; };
    float getSpeedY() { return speedY_; };
    float getDirX() { return dirX_; };
    float getDirY() { return dirY_; };
    bool getMale() { return male; };
    void setWindow_surface_ptr_(SDL_Surface* setWindow_surface_ptr) { window_surface_ptr_ = setWindow_surface_ptr; };
    void setImage_ptr_(SDL_Surface* image_ptr) { image_ptr_ = image_ptr; };
    void setX_(float x) { x_ = x; };
    void setY_(float y) { y_ = y; };
    void setSpeedX(float speedX) { speedX_ = speedX; };
    void setSpeedY(float speedY) { speedY_ = speedY; };
    void setDirX(float dirX) { dirX_ = dirX; };
    void setDirY(float dirY) { dirY_ = dirY; };
    void normalize();

    float distance(animal& a);

    bool collision(animal& a);

    float getSpeedBoost() { return speedBoost; };
    void setSpeedBoost(float n) { speedBoost = n ; };
    bool getExhausted() { return exhausted; };
    void setExhausted(bool b) { exhausted = b; };
    bool getFleeing() { return fleeing; };
    void setFleeing(bool b) { fleeing = b; };
    int getMatingTimer() { return matingTimer; };
    void setMatingTimer(int n) { matingTimer = n; };


    void draw() {
        auto rect = SDL_Rect{ (int)(x_ ) ,(int)(y_),size,size};
        SDL_BlitSurface(image_ptr_, NULL, window_surface_ptr_, &rect);
    };
    
    virtual void move() = 0;
    virtual bool isPrey() = 0;
    virtual bool isFriendly() = 0;
};

// class sheep, derived from animal
class sheep : public animal {

private:

public:
    sheep(SDL_Surface* window_surface_ptr) : animal("sheep.png", window_surface_ptr) { speedX_ = 5; speedY_ = 5; };
    sheep(SDL_Surface* window_surface_ptr, float x, float y) : animal("sheep.png", window_surface_ptr) { speedX_ = 5; speedY_ = 5; x_ = x; y_ = y; };
    void move();
    bool isPrey() { return true; };
    virtual bool isFriendly() { return true; };
    


};
class wolf : public animal {
    private:
        bool fleeing = false;
    public:
        wolf(SDL_Surface* window_surface_ptr) : animal("wolf.png", window_surface_ptr) { speedX_ = 7; speedY_ = 7; };
        void move();
        bool isPrey() { return false; };
        virtual bool isFriendly() { return false; };

};

class dog : public animal {
    public:
        dog(SDL_Surface* window_surface_ptr) : animal("dog.png", window_surface_ptr) {
            x_ = frame_width / 2;
            y_ = frame_height / 2; 
            speedX_ = 8; 
            speedY_ = 8; 
        };
        void move();
        bool isPrey() { return false; };
        virtual bool isFriendly() { return true; };
};

class shepherd {
private:

    SDL_Surface* window_surface_ptr_;
    SDL_Surface* image_ptr_ = IMG_Load("shepherd.gif");;
    float x_;
    float y_;
    int speed = 10;


public:
    shepherd() {
        x_ = frame_width / 2;
        y_ = frame_height / 2;
        
    };

    void setW(SDL_Surface* window_surface_ptr) {
        window_surface_ptr_ = window_surface_ptr;
    }

    void move();

    float getX_() { return x_; };
    float getY_() { return y_; };
    void setX(float x) { x_ += x; };
    void setY(float y) { y_ += y; };

    void draw() {
        auto rect = SDL_Rect{ (int)(x_) ,(int)(y_),size,size };
        SDL_BlitSurface(image_ptr_, NULL, window_surface_ptr_, &rect);
    };
};

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
    // Attention, NON-OWNING ptr, again to the screen
    SDL_Surface* window_surface_ptr_;
    unsigned frames = 0;
    // Some attribute to store all the wolves and sheep
    std::vector< std::unique_ptr<animal> > vAnimal;
    shepherd aShepherd;
    int nAnimal = 0;

public:
    ground(SDL_Surface* window_surface_ptr, int n_sheep, int n_wolf) {
        window_surface_ptr_ = window_surface_ptr;
        nAnimal = n_sheep + n_wolf + 1;
        for (int i = 0; i < n_sheep; i++) {

            std::unique_ptr<animal> s = std::make_unique<sheep>(sheep(window_surface_ptr));
            vAnimal.push_back(std::move(s));
        }
        for (int i = 0; i < n_wolf; i++) {

            std::unique_ptr<animal> s = std::make_unique<wolf>(wolf(window_surface_ptr));
            vAnimal.push_back(std::move(s));
        }
        std::unique_ptr<animal> s = std::make_unique<dog>(dog(window_surface_ptr));
        vAnimal.push_back(std::move(s));
        aShepherd.setW(window_surface_ptr);
    }; // todo: Ctor
    ~ground() {}; // todo: Dtor, again for clean up (if necessary)

    void drawAll();
    void moveAll();

    int getN() { return nAnimal; };
    void setW_(SDL_Surface* setWindow_surface_ptr, int n) {
        (*std::move(this->vAnimal[n])).setWindow_surface_ptr_(setWindow_surface_ptr);
    }
    

    void setWS_(SDL_Surface * setWindow_surface_ptr) {
        this->aShepherd.setW(setWindow_surface_ptr);
    }

    void setWindow_surface_ptr_(SDL_Surface* window_surface_ptr) { window_surface_ptr_ = window_surface_ptr; };
    //void add_animal(some argument here); // todo: Add an animal
    void update(); // todo: "refresh the screen": Move animals and draw them
    // Possibly other methods, depends on your implementation
};

// The application class, which is in charge of generating the window
class application {
private:
    // The following are OWNING ptrs
    SDL_Window* window_ptr_;
    SDL_Surface* window_surface_ptr_;
    SDL_Event window_event_;
    
    ground g_;

    // Other attributes here, for example an instance of ground

public:
    application(unsigned n_sheep, unsigned n_wolf); // Ctor
    ~application();                                 // dtor
    SDL_Window* getWindow_ptr_() { return window_ptr_; };
    int loop(unsigned period); // main loop of the application.
    // this ensures that the screen is updated
    // at the correct rate.
    // See SDL_GetTicks() and SDL_Delay() to enforce a
    // duration the application should terminate after
    // 'period' seconds
};