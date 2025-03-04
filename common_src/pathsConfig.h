#ifndef PATHS_CONFIG
#define PATHS_CONFIG

#ifdef DEVELOPMENT

#define CONFIG_PATH "../resources/config/"
#define CLIENT_CONFIG_PATH "../resources/config/clientConfig.yaml"
#define SERVER_CONFIG_PATH "../resources/config/serverConfig.yaml"
#define EDITOR_CONFIG_PATH "../resources/config/editorConfig.yaml"
#define MAP_LIST_PATH "../resources/config/MapList.yaml"

#else

#define CONFIG_PATH "/var/wolfenstein/config/"
#define CLIENT_CONFIG_PATH "/var/wolfenstein/config/clientConfig.yaml"
#define SERVER_CONFIG_PATH "/var/wolfenstein/config/serverConfig.yaml"
#define EDITOR_CONFIG_PATH "/var/wolfenstein/config/editorConfig.yaml"
#define MAP_LIST_PATH "/var/wolfenstein/config/MapList.yaml"

#endif

#endif /* PATHS_CONFIG */
