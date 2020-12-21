#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

class ClientSettings {
 public:
    int screenWidth;
    int screenHeight;
    float fov;
    float pi;
		ClientSettings(int screenWidth, int screenHeight, int fov, float pi);
		~ClientSettings();
    float distance(float x1, float y1, float x2, float y2);
};

#endif  // CLIENTSETTINGS_H
