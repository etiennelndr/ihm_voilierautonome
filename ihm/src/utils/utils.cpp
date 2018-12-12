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
	// Tant que nous ne sommes pas arriv�s � un caract�re de fin...
    while ((pos = data.find(delimiter)) != string::npos) {
		// ... On ajoute ce nouveau string � notre vector
        tokens.push_back(data.substr(0, pos));
		// On supprime le string pr�c�demment ajout�
        data.erase(0, pos + delimiter.length());
    }
	// Ne pas oublier d'ajouter le dernier string
    tokens.push_back(data);
    return tokens;
}
