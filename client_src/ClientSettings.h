#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

class ClientSettings {
 public:
    const int screenWidth;
    const int screenHeight;
    const int fps;
    const double fov;
		ClientSettings(int screenWidth, int screenHeight, int fps, int fov);
		~ClientSettings();
    // Esto deberia ir en otra clase
    double distance(double x1, double y1, double x2, double y2);
};

#endif  // CLIENTSETTINGS_H
