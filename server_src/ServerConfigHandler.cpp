#include "ServerConfigHandler.h"
#include "../common_src/pathsConfig.h"
#include <fstream>
#include <iostream>
#include <string>

void ServerConfigHandler::initConfig(std::string path) {
  root = YAML::LoadFile(path);
}

weaponStats_t ServerConfigHandler::getWeaponStats(WeaponType type) {
  std::string weaponName;
  switch (type) {
  case KNFIE:
    weaponName = "knife";
    break;
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
  const YAML::Node &weaponNode = root[weaponName];
  weaponStats_t weapon;
  weapon.type = type;
  weapon.max_damage = weaponNode["max_damage"].as<int>();
  weapon.max_spread = weaponNode["max_spread"].as<int>();
  weapon.ammo_cost = weaponNode["ammo_cost"].as<int>();
  weapon.cooldown = weaponNode["cooldown"].as<int>();
  weapon.stability_reset = weaponNode["stability_reset"].as<int>();
  weapon.max_acurate_range = weaponNode["max_acurate_range"].as<int>();

  return weapon;
}

actorStats_t ServerConfigHandler::getPlayerStats() {
  const YAML::Node &actorNode = root["player"];
  actorStats_t actor;
  actor.health = actorNode["health"].as<int>();
  actor.lives = actorNode["lives"].as<int>();
  actor.hitbox_radius = actorNode["hitbox_radius"].as<int>();
  actor.linear_vel = actorNode["linear_vel"].as<int>();
  actor.angular_vel = actorNode["angular_vel"].as<int>();


  return actor;
}

ServerConfigHandler::ServerConfigHandler() { initConfig(SERVER_CONFIG_PATH); }
