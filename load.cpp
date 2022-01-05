#include "load.h"

void Load::read_params_from_steps(string line) { // 

    /*--- format example:"P:w:G0:0:G1:1:G2:2:G3:0:F:0 or F:5:2:30:20" --- */
    int i = 0, fruit_x, fruit_y;
    if (line[0] == 'P')
    {
        line.erase(0, 2); // "P:"
        current_key = unsigned char(line[0]);
        line.erase(0, 2); // "w:"

        while (line[0] == 'G')
        {
            line.erase(0, 3); // "Gi:" **0<=i<=3**
            ghosts_directions[i++] = int(line[0] - '0');
            line.erase(0, 2); // "0":
        }

        line.erase(0, 2); // "F:"
        if (line[0] == '0') // "0"
            is_fruit_dead = true;

        else {
            is_fruit_dead = false;

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
    else // last line
    {
        if (line[1] == '\0')
            num_of_steps = line[0] - '0';
        else if (line[1] && line[2] == '\0')
            num_of_steps = ((line[0] - '0') * 10) + (line[1] - '0');
        else if (line[1] && line[2])
            num_of_steps = ((line[0] - '0') * 100) + (line[1] - '0') * 10 + (line[2] - '0');
    }
}

void Load::read_line_from_result(string line) { 

    /*--format xxx:0\1 any other format will be throwed--*/

    if (line[1] == ':')
    {
        result_steps = line[0] - '0';
        pacman_status = line[2] - '0';
    }
    else if (line[2] == ':')
    {
        result_steps = ((line[0] - '0') * 10) + (line[1] - '0');
        pacman_status = line[3] - '0';
    }
    else if (line[3] == ':')
    {
        result_steps = ((line[0] - '0') * 100) + (line[1] - '0') * 10 + (line[2] - '0');
        pacman_status = line[4] - '0';
    }
    else
        throw " unvalid result file no steps! ";
}

void Load::init_load_files() {
    ghosts_directions.resize(num_of_ghosts);

    string result_file_name, steps_file_name;
    result_file_name = steps_file_name = board_name = board_name.substr(0, board_name.find('.'));

    steps_file_name += ".steps";
    result_file_name += ".result";
    steps_file.open(steps_file_name);

    if (!steps_file) {
        throw " unable to open file. ";
    }
    result_file.open(result_file_name);
    if (!result_file) {
        throw " unable to open file. ";
    }

}

void Load::finish_loading() {
    ghosts_directions.clear();
    steps_file.close();
    result_file.close();
}

void Load::load_line(int select) 
{
    string line;
    if (select == 0)
    {
        if (steps_file.is_open())
        {
            if (!steps_file.eof())
            {
                getline(steps_file, line);
                read_params_from_steps(line);
            }
        }
        else
            throw " steps_file is closed ";
        
    }
    else if (select == 1)
    {
        if (result_file.is_open())
        {
            if (!result_file.eof())
            {
                getline(result_file, line);
                read_line_from_result(line);
            }
        }
        else
            throw " result_file is closed ";
    }
}
