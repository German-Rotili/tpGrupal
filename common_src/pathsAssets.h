#ifndef PATHS_ASSETS
#define PATHS_ASSETS

#ifdef DEVELOPMENT

//TEXTURAS
#define WALLS_TEXTURE_PATH "../resources/textures/walls.png"
#define OBJECTS_TEXTURE_PATH "../resources/textures/objects.png"
#define PLAYER_PATH "../resources/textures/player.png"
#define PLAYER_FACES_PATH "../resources/textures/playerFaces.png"
#define ROCKET_PATH "../resources/textures/rocket.png"
#define EXPLOSION_PATH "../resources/textures/explosion_strip9.png"
#define BULLET_HIT_PATH "../resources/textures/bullethit_strip9.png"
#define AMMO_ICON_PATH "../resources/textures/icons/bullet.png"
#define LIVE_ICON_PATH "../resources/textures/icons/live.png"

#define GUARD_DOG_DOWN "../resources/textures/enemies/guardDog/down_strip5.png"
#define GUARD_DOG_DOWN_LEFT "../resources/textures/enemies/guardDog/downleft_strip5.png"
#define GUARD_DOG_LEFT "../resources/textures/enemies/guardDog/left_strip5.png"
#define GUARD_DOG_UP_LEFT "../resources/textures/enemies/guardDog/upleft_strip5.png"
#define GUARD_DOG_UP "../resources/textures/enemies/guardDog/up_strip5.png"
#define GUARD_DOG_SHOOTING "../resources/textures/enemies/guardDog/shooting_strip3.png"
#define GUARD_DOG_DYING "../resources/textures/enemies/guardDog/dying_strip5.png"

#define GUARD_DOWN "../resources/textures/enemies/guard/down_strip5.png"
#define GUARD_DOWN_LEFT "../resources/textures/enemies/guard/downleft_strip5.png"
#define GUARD_LEFT "../resources/textures/enemies/guard/left_strip5.png"
#define GUARD_UP_LEFT "../resources/textures/enemies/guard/upleft_strip5.png"
#define GUARD_UP "../resources/textures/enemies/guard/up_strip5.png"
#define GUARD_SHOOTING "../resources/textures/enemies/guard/shooting_strip3.png"
#define GUARD_DYING "../resources/textures/enemies/guard/dying_strip5.png"

#define SS_DOWN "../resources/textures/enemies/ss/down_strip5.png"
#define SS_DOWN_LEFT "../resources/textures/enemies/ss/downleft_strip5.png"
#define SS_LEFT "../resources/textures/enemies/ss/left_strip5.png"
#define SS_UP_LEFT "../resources/textures/enemies/ss/upleft_strip5.png"
#define SS_UP "../resources/textures/enemies/ss/up_strip5.png"
#define SS_SHOOTING "../resources/textures/enemies/ss/shooting_strip3.png"
#define SS_DYING "../resources/textures/enemies/ss/dying_strip5.png"

#define OFFICER_DOWN "../resources/textures/enemies/officer/down_strip5.png"
#define OFFICER_DOWN_LEFT "../resources/textures/enemies/officer/downleft_strip5.png"
#define OFFICER_LEFT "../resources/textures/enemies/officer/left_strip5.png"
#define OFFICER_UP_LEFT "../resources/textures/enemies/officer/upleft_strip5.png"
#define OFFICER_UP "../resources/textures/enemies/officer/up_strip5.png"
#define OFFICER_SHOOTING "../resources/textures/enemies/officer/shooting_strip3.png"
#define OFFICER_DYING "../resources/textures/enemies/officer/dying_strip5.png"

#define MUTANT_DOWN "../resources/textures/enemies/mutant/down_strip5.png"
#define MUTANT_DOWN_LEFT "../resources/textures/enemies/mutant/downleft_strip5.png"
#define MUTANT_LEFT "../resources/textures/enemies/mutant/left_strip5.png"
#define MUTANT_UP_LEFT "../resources/textures/enemies/mutant/upleft_strip5.png"
#define MUTANT_UP "../resources/textures/enemies/mutant/up_strip5.png"
#define MUTANT_SHOOTING "../resources/textures/enemies/mutant/shooting_strip3.png"
#define MUTANT_DYING "../resources/textures/enemies/mutant/dying_strip5.png"

//SONIDOS
#define SND_CUCHILLO_PATH "../resources/sounds/cuchillo.mp3"
#define SND_PISTOLA_PATH "../resources/sounds/pistola1.mp3"
#define SND_PISTOLA2_PATH "../resources/sounds/pistola2.mp3"
#define SND_AMETRALLADORA1_PATH "../resources/sounds/ametralladora1.mp3"
#define SND_AMETRALLADORA2_PATH "../resources/sounds/ametralladora2.mp3"
#define SND_CANIONDECADENA_PATH "../resources/sounds/canionDeCadena.mp3"
#define SND_LANZACOHETES_PATH "../resources/sounds/rocket.mp3"
#define SND_DYING_PATH "../resources/sounds/dying.mp3"
#define SND_EXPLOSION_PATH "../resources/sounds/explosion.mp3"
#define SND_BULLETHIT_PATH "../resources/sounds/bullethit.mp3"
#define SND_DOOR_OPEN_PATH "../resources/sounds/door_open.mp3"
#define SND_DOOR_CLOSE_PATH "../resources/sounds/door_closed.mp3"
#define SND_HURT_PATH "../resources/sounds/hurt.mp3"
#define SND_HEALING_PATH "../resources/sounds/healing.mp3"
#define SND_SCOREUP_PATH "../resources/sounds/scoreup.mp3"
#define SND_PICKAMMO_PATH "../resources/sounds/pick_weaponammo.mp3"
#define MUSIC_MENU_PATH "../resources/music/menu.mp3"
#define MUSIC_RESULTS_PATH "/resources/music/results.mp3"
#define GAME_MUSIC_PATH "../resources/music/music2.mp3"

//FONTS
#define FONT_WOLFENSTEIN_PATH "../resources/fonts/wolfenstein.ttf"
#define FONT_HUD_PATH "../resources/fonts/hudFont.ttf"

#else

//TEXTURAS
#define WALLS_TEXTURE_PATH "/var/wolfenstein/textures/walls.png"
#define OBJECTS_TEXTURE_PATH "/var/wolfenstein/textures/objects.png"
#define PLAYER_PATH "/var/wolfenstein/textures/player.png"
#define PLAYER_FACES_PATH "/var/wolfenstein/textures/playerFaces.png"
#define ROCKET_PATH "/var/wolfenstein/textures/rocket.png"
#define EXPLOSION_PATH "/var/wolfenstein/textures/explosion_strip9.png"
#define BULLET_HIT_PATH "/var/wolfenstein/textures/bullethit_strip9.png"
#define AMMO_ICON_PATH "/var/wolfenstein/textures/icons/bullet.png"
#define LIVE_ICON_PATH "/var/wolfenstein/textures/icons/live.png"

#define GUARD_DOG_DOWN "/var/wolfenstein/textures/enemies/guardDog/down_strip5.png"
#define GUARD_DOG_DOWN_LEFT "/var/wolfenstein/textures/enemies/guardDog/downleft_strip5.png"
#define GUARD_DOG_LEFT "/var/wolfenstein/textures/enemies/guardDog/left_strip5.png"
#define GUARD_DOG_UP_LEFT "/var/wolfenstein/textures/enemies/guardDog/upleft_strip5.png"
#define GUARD_DOG_UP "/var/wolfenstein/textures/enemies/guardDog/up_strip5.png"
#define GUARD_DOG_SHOOTING "/var/wolfenstein/textures/enemies/guardDog/shooting_strip3.png"
#define GUARD_DOG_DYING "/var/wolfenstein/textures/enemies/guardDog/dying_strip5.png"

#define GUARD_DOWN "/var/wolfenstein/textures/enemies/guard/down_strip5.png"
#define GUARD_DOWN_LEFT "/var/wolfenstein/textures/enemies/guard/downleft_strip5.png"
#define GUARD_LEFT "/var/wolfenstein/textures/enemies/guard/left_strip5.png"
#define GUARD_UP_LEFT "/var/wolfenstein/textures/enemies/guard/upleft_strip5.png"
#define GUARD_UP "/var/wolfenstein/textures/enemies/guard/up_strip5.png"
#define GUARD_SHOOTING "/var/wolfenstein/textures/enemies/guard/shooting_strip3.png"
#define GUARD_DYING "/var/wolfenstein/textures/enemies/guard/dying_strip5.png"

#define SS_DOWN "/var/wolfenstein/textures/enemies/ss/down_strip5.png"
#define SS_DOWN_LEFT "/var/wolfenstein/textures/enemies/ss/downleft_strip5.png"
#define SS_LEFT "/var/wolfenstein/textures/enemies/ss/left_strip5.png"
#define SS_UP_LEFT "/var/wolfenstein/textures/enemies/ss/upleft_strip5.png"
#define SS_UP "/var/wolfenstein/textures/enemies/ss/up_strip5.png"
#define SS_SHOOTING "/var/wolfenstein/textures/enemies/ss/shooting_strip3.png"
#define SS_DYING "/var/wolfenstein/textures/enemies/ss/dying_strip5.png"

#define OFFICER_DOWN "/var/wolfenstein/textures/enemies/officer/down_strip5.png"
#define OFFICER_DOWN_LEFT "/var/wolfenstein/textures/enemies/officer/downleft_strip5.png"
#define OFFICER_LEFT "/var/wolfenstein/textures/enemies/officer/left_strip5.png"
#define OFFICER_UP_LEFT "/var/wolfenstein/textures/enemies/officer/upleft_strip5.png"
#define OFFICER_UP "/var/wolfenstein/textures/enemies/officer/up_strip5.png"
#define OFFICER_SHOOTING "/var/wolfenstein/textures/enemies/officer/shooting_strip3.png"
#define OFFICER_DYING "/var/wolfenstein/textures/enemies/officer/dying_strip5.png"

#define MUTANT_DOWN "/var/wolfenstein/textures/enemies/mutant/down_strip5.png"
#define MUTANT_DOWN_LEFT "/var/wolfenstein/textures/enemies/mutant/downleft_strip5.png"
#define MUTANT_LEFT "/var/wolfenstein/textures/enemies/mutant/left_strip5.png"
#define MUTANT_UP_LEFT "/var/wolfenstein/textures/enemies/mutant/upleft_strip5.png"
#define MUTANT_UP "/var/wolfenstein/textures/enemies/mutant/up_strip5.png"
#define MUTANT_SHOOTING "/var/wolfenstein/textures/enemies/mutant/shooting_strip3.png"
#define MUTANT_DYING "/var/wolfenstein/textures/enemies/mutant/dying_strip5.png"

//SONIDOS
#define SND_CUCHILLO_PATH "/var/wolfenstein/sounds/cuchillo.mp3"
#define SND_PISTOLA_PATH "/var/wolfenstein/sounds/pistola1.mp3"
#define SND_PISTOLA2_PATH "/var/wolfenstein/sounds/pistola2.mp3"
#define SND_AMETRALLADORA1_PATH "/var/wolfenstein/sounds/ametralladora1.mp3"
#define SND_AMETRALLADORA2_PATH "/var/wolfenstein/sounds/ametralladora2.mp3"
#define SND_CANIONDECADENA_PATH "/var/wolfenstein/sounds/canionDeCadena.mp3"
#define SND_LANZACOHETES_PATH "/var/wolfenstein/sounds/rocket.mp3"
#define SND_DYING_PATH "/var/wolfenstein/sounds/dying.mp3"
#define SND_EXPLOSION_PATH "/var/wolfenstein/sounds/explosion.mp3"
#define SND_BULLETHIT_PATH "/var/wolfenstein/sounds/bullethit.mp3"
#define SND_DOOR_OPEN_PATH "/var/wolfenstein/sounds/door_open.mp3"
#define SND_DOOR_CLOSE_PATH "/var/wolfenstein/sounds/door_closed.mp3"
#define SND_HURT_PATH "/var/wolfenstein/sounds/hurt.mp3"
#define SND_HEALING_PATH "/var/wolfenstein/sounds/healing.mp3"
#define SND_SCOREUP_PATH "/var/wolfenstein/sounds/scoreup.mp3"
#define SND_PICKAMMO_PATH "/var/wolfenstein/sounds/pick_weaponammo.mp3"
#define MUSIC_MENU_PATH "/var/wolfenstein/music/menu.mp3"
#define MUSIC_RESULTS_PATH "/var/wolfenstein/music/results.mp3"
#define GAME_MUSIC_PATH "/var/wolfenstein/music/music2.mp3"

//FONTS
#define FONT_WOLFENSTEIN_PATH "/var/wolfenstein/fonts/wolfenstein.ttf"
#define FONT_HUD_PATH "/var/wolfenstein/fonts/hudFont.ttf"

#endif

#endif /* PATHS_ASSETS */
