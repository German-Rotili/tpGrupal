#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H
#include <string>

class ClientSettings {
 public:
    const int screenWidth;
    const int screenHeight;
    const int fps;
    const double fov;
    std::string username;
    int myCurrentId;
		ClientSettings(int screenWidth, int screenHeight, int fps, int fov);
		~ClientSettings();
};

#endif  // CLIENTSETTINGS_H
