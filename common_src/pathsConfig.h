#ifndef PATHS_CONFIG
#define PATHS_CONFIG

#ifdef DEVELOPMENT

#define CONFIG_PATH "../resources/config"
#define CLIENT_CONFIG_PATH "../resources/config/clientConfig.yaml"
#define SERVER_CONFIG_PATH "../resources/config/serverConfig.yaml"
#define EDITOR_CONFIG_PATH "../resources/config/editorConfig.yaml"
#define MAP_LIST_PATH "../resources/config/MAPLIST.yaml"

#else

#define CONFIG_PATH "etc/wolfenstein/config"
#define CLIENT_CONFIG_PATH "etc/wolfenstein/config/clientConfig.yaml"
#define SERVER_CONFIG_PATH "etc/wolfenstein/config/serverConfig.yaml"
#define EDITOR_CONFIG_PATH "etc/wolfenstein/config/editorConfig.yaml"
#define MAP_LIST_PATH "etc/wolfenstein/config/MAPLIST.yaml"

#endif

#endif /* PATHS_CONFIG */
