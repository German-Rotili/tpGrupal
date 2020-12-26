#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

class ClientSettings {
 public:
    int screenWidth;
    int screenHeight;
    int fps;
    float fov;
		ClientSettings(int screenWidth, int screenHeight, int fps, int fov);
		~ClientSettings();
    // Esto deberia ir en otra clase
    float distance(float x1, float y1, float x2, float y2);
};

#endif  // CLIENTSETTINGS_H
