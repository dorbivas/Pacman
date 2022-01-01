#include "load.h"

    //unsigned char current_key;
    //Entity::Direction ghosts_directions[Board::MAX_GHOSTS];
    //bool fruit_is_dead;
    //Position fruit_pos;
    //Entity::Direction fruit_direction;
    //ifstream steps_file;steps.txt
    //format: P:w:G0:0:G1:0:F:5:0:30:20
    //if fruit is dead-> example: P:w:G0:0:G1:0:F:0     - 0 refers to shape


void Load::split(string line) {

	string delimiter = ":" , token;
	size_t pos = 0;

    pos = line.find();
	while ((pos = line.find()) != -1) // -1 = npos
	{
		token = line.substr(0, pos);

        if (token == "P")
        {
            line.erase(0, pos + delimiter.length());
            current_key = unsigned char(line[0]);

        }
            
        while (token == "G0" || token == "G1" || token == "G2" || token == "G3")
        {

        }

        if (token == "P")
        if (token == "P")
        


		cout << token << endl;

	    line.erase(0, pos + delimiter.length());

	}
	cout << line << endl;
}




void Load::read_from_file()
{
 /*
 format: P:w:G0:0G1:0F:5:0:30:20
 
every read_line: from i=0 to eof
    READ CURRENT KEY format
    READ GHOSTS[i] direction:
    read fruit_is_dead
    read fruit pos

*/
}