#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class model{
    private:
        int x,y;

    public:
        model(int x_, int y_){
            x=x_;
            y=y_;
        }
        int getX(){return x;}
        int getY(){return y;}
        void setX(int x_){x=x_;}
        void setY(int y_){y=y_;}
};

class view{
    private:
        model &m;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *capivara;
        SDL_Texture *taquaral;
        SDL_Rect target;
        const Uint8 *state;
    
    public:

        view(model &m_):m(m_){}

        SDL_Rect* getTarget(){return &target;}
        const Uint8* getState(){return state;}

        int init(){
         
            if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
                std::cout << SDL_GetError();
                return 1;
            }

            window = nullptr;
            window = SDL_CreateWindow("Demonstracao do SDL2",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
            if (window==nullptr) { // Em caso de erro...
                std::cout << SDL_GetError();
                SDL_Quit();
                return 1;
            }

            renderer = nullptr; 
            renderer = SDL_CreateRenderer(
            window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer==nullptr) { // Em caso de erro...
                SDL_DestroyWindow(window);
                std::cout << SDL_GetError();
                SDL_Quit();
                return 1;
            }

            capivara = IMG_LoadTexture(renderer, "./capi.png" );
            taquaral = IMG_LoadTexture(renderer, "./park.jpeg" );

            target.x = 0;
            target.y = 0;

            SDL_QueryTexture(capivara, nullptr, nullptr, &target.w, &target.h);

            state = SDL_GetKeyboardState(nullptr);
        }

        void render(){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, taquaral, nullptr, nullptr);
            SDL_RenderCopy(renderer, capivara, nullptr, &target);
            SDL_RenderPresent(renderer);

            SDL_Delay(10);
        }

        void quit(){
            SDL_DestroyTexture(capivara);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
};

class controller{
    
    private:
        view &v;
        model &m;
    
    public:
        controller(view &v_, model &m_): m(m_), v(v_){}

        void update(){
            const Uint8 *state = v.getState();
            SDL_Rect* target = v.getTarget();

            SDL_PumpEvents();
            if (state[SDL_SCANCODE_LEFT]) m.setX(m.getX()-1);
            if (state[SDL_SCANCODE_RIGHT]) m.setX(m.getX()+1);
            if (state[SDL_SCANCODE_UP]) m.setY(m.getY()-1);
            if (state[SDL_SCANCODE_DOWN]) m.setY(m.getY()+1);

            target->x = m.getX();
            target->y = m.getY();
        }
};


int main(){

    model m = model(0,0);
    view v = view(m);
    v.init();
    controller c = controller(v,m);

    bool rodando = true;
    SDL_Event evento;

    while(rodando){
        c.update();

        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT){
                rodando = false;
            }
        }
        v.render();
    }
    v.quit();
    
    return 0;
}