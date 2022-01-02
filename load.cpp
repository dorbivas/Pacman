#include "load.h"

void Load::read_params_from_line(string line) {

    /*--- format example:"P:w:G0:0:G1:1:G2:2:G3:0:F:0 or F:5:2:30:20" --- */
    int i = 0, fruit_x, fruit_y;

    line.erase(0, 2); // "P:"
    current_key = unsigned char(line[0]);
    line.erase(0, 2); // "w:"

    while (line[0] == 'G') 
    {
        line.erase(0, 3); // "Gi:" **0<=i<=3**
        ghosts_directions[i++] = Entity::Direction(line[0] - '0');
        line.erase(0, 2); // "0":
    }

    line.erase(0, 2); // "F:"
    if (line[0] == '0') // "0"
        is_fruit_dead = true;

    else {
        fruit_shape = (line[0] - '0');// "5"

        line.erase(0, 2);

        fruit_direction = (Entity::Direction)(line[0] - '0');// "2"

        line.erase(0, 2); // "5:"
        if (line[1] == ':')
        {
            fruit_x = line[0] - '0';
            line.erase(0, 2); // "fruit_x 0-9"
        }
        else
        {
            fruit_x = ((line[0] - '0') * 10) + (line[1] - '0');
            line.erase(0, 3); // "fruit_x 10-max length"
        }
        if (line[1] == '\0') // end or fruit_y is 10 - max length
            fruit_y = line[0] - '0';

        else
            fruit_y = ((line[0] - '0') * 10) + (line[1] - '0');

        fruit_pos.set_xy(fruit_x, fruit_y);
    }
}

void Load::init_load_file() {
    string file_name = "pacman_03.result";
    //string file_name = strcat(find_file(last file), ".result");TODO
    steps_file.open(file_name);
    if (!steps_file) {
        //throw; TODO
    }
}

void Load::finish_loading() {
    steps_file.close();
}

void Load::load_line() 
{
    string line;
    if (!steps_file.eof())
    {
        
        getline(steps_file, line);
        read_params_from_line(line);
    }
    else
        finish_loading();
    
       
}
/*yarden solution:
    the last line in the step_file is the numbers of pacman steps
    so the num of lines should be as total_pacman_steps+1
    global counter fo num of lines shoud be equal to pacman_steps+1
*/