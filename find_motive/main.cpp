#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void hasMotive(std::string s, std::string motive, int& c) {
	
	int max = s.size();
	int min = motive.size();
	int verif = 0;
	bool alreadyCounted = 0;
	if (max >= min) {

		for (int i = 0; i < max - min + 1; i++) {
			
			if (s[i] == motive[0] && !alreadyCounted) {
				
				for (int j = 0; j < min; j++) {
					
					if (j == min - 1 && s[i+j]==motive[j]) {
						
						c++;
						alreadyCounted = 1;

					}
					else if (s[i + j] != motive[j]) {
						break;
					}
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {
    int count = 0;
    std::string motif = argv[2];

    std::ifstream myfile;
    std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
    
	myfile.open(argv[1]);
    if (myfile.is_open()) {
        while (myfile >> contenu) {  // on met dans "contenu" la ligne
            hasMotive(contenu, motif, count);
        }
        std::cout << "The file " << argv[1] << " contains " << count << " words containing the motive " << argv[2] << "\n";
        myfile.close();
        return 1;
    }
    else {
        std::cout << "can't open file" << std::endl;
        return 0;
    }

}
