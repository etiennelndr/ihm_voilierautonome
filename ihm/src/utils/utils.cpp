#include "utils.h"

/**
 * METHOD
 *
 * @brief split : split a string into multiple strings
 * @param data
 * @param delimiter
 * @return
 */
vector<string> split(string data, string delimiter) {
    vector<string> tokens;
    size_t pos = 0;
	// Tant que nous ne sommes pas arrivés à un caractère de fin...
    while ((pos = data.find(delimiter)) != string::npos) {
		// ... On ajoute ce nouveau string à notre vector
        tokens.push_back(data.substr(0, pos));
		// On supprime le string précédemment ajouté
        data.erase(0, pos + delimiter.length());
    }
	// Ne pas oublier d'ajouter le dernier string
    tokens.push_back(data);
    return tokens;
}
