#include "IpMenu.h"
#include "../../common_src/Colors.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FONT_PATH "/usr/local/share/counter2d/resources/common/img/digital-7.ttf"
#define FONT_PATH2 "/usr/local/share/counter2d/resources/common/img/aerial.ttf"
#define BACKGROUND "/usr/local/share/counter2d/resources/common/img/counter.jpeg"
#define FONT_SIZE 26
#define FONT_SIZE_TYPE 20
#define MUSIC_PATH "/usr/local/share/counter2d/resources/common/sound/menu.wav"
#define MARGIN 20

enum TextTextureType : int {PUT_TEXT, VARIABLE_TEXT};

IpMenu::IpMenu():window("IpMenu", SCREEN_WIDTH, SCREEN_HEIGHT),
    renderer(&window), background(renderer, BACKGROUND){

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    music = Mix_LoadMUS(MUSIC_PATH);
	if( music == NULL ){
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}

    this->renderText = false;
    this->variableText = " ";
    this->ip = "";
    this->port = "";

    this->map.emplace(PUT_TEXT, new TextTexture(renderer, FONT_PATH, FONT_SIZE));
    this->map[PUT_TEXT]->setText("Type the IP", WHITE);

    this->map.emplace(VARIABLE_TEXT, new TextTexture(renderer, FONT_PATH2, FONT_SIZE_TYPE));
    this->map[VARIABLE_TEXT]->setText(this->variableText, WHITE);
}

void IpMenu::start(){

    bool quit = false;
    SDL_Event event;
    SDL_PollEvent(&event);
    isPort = false;

    Mix_PlayMusic(this->music, -1);
    Mix_VolumeMusic(32);
    bool mute = false;

    TextTexture muteText(this->renderer, FONT_PATH, 15);
    muteText.setText("Click here to mute or unmute", WHITE);
    Size muteSize = muteText.getSize();
    Coordinate mutePos = {SCREEN_WIDTH - muteSize.w - MARGIN, SCREEN_HEIGHT - MARGIN - muteSize.h};
    muteText.setCoordinate(mutePos);

    while (!quit) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_BACKSPACE && this->variableText.length() > 0){
                    this->variableText.pop_back();
                    this->renderText = true;
                }else if (event.key.keysym.sym == SDLK_RETURN && event.key.repeat == 0){
                    if (variableText[0] == ' '){
                        variableText.erase(variableText.begin());
                    }
                    if (isPort && variableText.compare("") != 0 ){
                        this->port = variableText;
                        quit = true;
                    }else if (variableText.compare("") != 0){
                        this->ip = variableText;
                        this->variableText = "";
                        this->map[PUT_TEXT]->setText("Type the Port", WHITE);
                        renderText = true;
                        isPort = true;
                    }
                }
            }else if (event.type == SDL_TEXTINPUT){
                if (isPort){
                    char aux = event.text.text[0];
                    if (aux >= 48 && aux <= 57){
                        this->variableText += event.text.text;
                    }
                }else{
                    this->variableText += event.text.text;
                }
                this->renderText = true;
            }
            if((event.type == SDL_MOUSEBUTTONDOWN) && event.button.button == SDL_BUTTON_LEFT && muteText.isMouseTouching()) {
                if (mute) {
                    Mix_ResumeMusic();
                } else {
                    Mix_PauseMusic();
                }
                mute = !mute;
            }
        }
        if (renderText){
            if (this->variableText == ""){
                this->map[VARIABLE_TEXT]->setText(" ", WHITE);
            }else{
                this->map[VARIABLE_TEXT]->setText(this->variableText, WHITE);
            }
        }
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        this->background.render(0, 0, window.getWidth(), window.getHeight());

        this->map[PUT_TEXT]->render({(window.getWidth() - this->map[PUT_TEXT]->getSize().w)/2,
         (window.getHeight() - this->map[PUT_TEXT]->getSize().h)/2 - 100});

        this->map[VARIABLE_TEXT]->render({(window.getWidth() - this->map[VARIABLE_TEXT]->getSize().w)/2,
         (window.getHeight() - this->map[VARIABLE_TEXT]->getSize().h)/2});

        muteText.render();
        
        renderer.updateScreen();
    }
    Mix_HaltMusic();
}

std::string IpMenu::getIp(){
    return this->ip;
}

std::string IpMenu::getPort(){
    return this->port;
}

IpMenu::~IpMenu(){
    Mix_FreeMusic(this->music);
    Mix_CloseAudio();
	Mix_Quit();
}
