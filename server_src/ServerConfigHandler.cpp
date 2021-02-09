#include <string>
#include <iostream>
#include <fstream>
#include "ServerConfigHandler.h"


void ServerConfigHandler::initConfig(std::string path) {
  root = YAML::LoadFile(path);
}

weaponStats_t ServerConfigHandler::getWeaponStats(WeaponType type) {
  std::string weaponName;
  switch (type) {
    case GUN:
    weaponName = "gun";
    break;

    case MACHINEGUN:
    weaponName = "machine gun";
    break;

    case MINIGUN:
    weaponName = "minigun";
    break;

    case ROCKETLAUNCHER:
    weaponName = "rocket launcher";
    break;
  }
  const YAML::Node& weaponNode = root[weaponName];
  weaponStats_t weapon;
  weapon.type = type;
  weapon.speed = weaponNode["speed"].as<int>();
  weapon.ammo = weaponNode["ammo"].as<int>();
  weapon.damage = weaponNode["damage"].as<int>();
  return weapon;
}

actorStats_t ServerConfigHandler::getActorStats() {
  const YAML::Node& actorNode = root["actor"];
  actorStats_t actor;
  actor.speed = actorNode["speed"].as<int>();
  actor.health = actorNode["health"].as<int>();
  actor.max_ammo = actorNode["max ammo"].as<int>();
  return actor;
}
