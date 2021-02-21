#include "HitscanRaycast.h"
#include <math.h> 
#include "Map.h"
#include "Player.h"
#include <iostream>

static std::tuple<int, int> getTileSteps(double dir) {
  if ((0 > dir) && (dir >= -90)) {
    return std::make_pair(1, -1);
  } else if ((-90 > dir) && (dir >= -180)) {
    return std::make_pair(-1, -1);
  } else if ((-180 > dir) && (dir >= -270)) {
    return std::make_pair(-1, 1);
  } else {
    return std::make_pair(1, 1);
  }
}


std::pair<float, float> HitscanRaycast::get_impact_point(Map *map, Player *player) {
    int x = (int) player->get_pos_x();
    int y = (int) player->get_pos_y();
    double dx = x - player->get_pos_x();
    double dy = y - player->get_pos_y();

    double rayAngle = player->get_direction();

    double xStep, yStep, xIntercept, yIntercept;
    int tileStepX, tileStepY;
    if (rayAngle >= 0) {
      rayAngle -= 360;
    } else if (rayAngle < -360) {
      rayAngle +=360;
    }

    std::tie(tileStepX, tileStepY) = getTileSteps(rayAngle);


    if (rayAngle == -360) {
      xStep = 60;
      yStep = 0;
    } else if (rayAngle == -180) {
      xStep = -60;
      yStep = 0;
    } else if (rayAngle == -90) {
      xStep = 0;
      yStep = -60;
    } else if (rayAngle == -270) {
      xStep = 0;
      yStep = 60;
    } else {
      xStep = tileStepY/tan(rayAngle * M_PI/180.0);
      yStep = tileStepX*tan(rayAngle * M_PI/180.0);
    }

    if (rayAngle <= -180) {
      xIntercept = x + dx + (1-dy)*xStep;
    } else {
      xIntercept = x + dx + dy*xStep;
    }

    if (rayAngle <= -90 && rayAngle >= -270) {
      yIntercept = y + dy + (dx)*yStep;
    } else {
      yIntercept = y + dy + (1-dx)*yStep;
    }

    // Distancia de la pared
    //double distortedDist;

    // Loopea hasta encontrar pared
    bool wallFoundX = false;
    bool wallFoundY = false;
    for (int i = 0; !(wallFoundX && wallFoundY) ; i++) {
      if (!wallFoundX) {
        if (map->is_impactable(int(xIntercept), y+tileStepY)) {
          wallFoundX = true;
        } else {
          y += tileStepY;
          xIntercept += xStep;
        }
      }
      if (!wallFoundY) {
        if (map->is_impactable(x+tileStepX, int(yIntercept))) {
          wallFoundY = true;
        } else {
          x += tileStepX;
          yIntercept += yStep;
        }
      }
    }
    std::cout << "shot x : " << xIntercept << " shot y : " << yIntercept << std::endl;
  return std::make_pair(xIntercept,yIntercept);
}
