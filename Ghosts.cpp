#include "Ghosts.h"
#include <queue>
Position Ghosts::move_ghost(){
	Position dir_pos;
	set_direction();

	if (direction == (int)Direction::UP)
	{
		dir_pos.set_xy(pos.get_x(), pos.get_y() + 1); 
	}
	else if (direction == (int)Direction::DOWN)
	{
		dir_pos.set_xy(pos.get_x(), pos.get_y() - 1);
	}
	else if (direction == (int)Direction::LEFT)
	{
		dir_pos.set_xy(pos.get_x()-1, pos.get_y());
	}
	else //RIGHT
	{  
		dir_pos.set_xy(pos.get_x()+1, pos.get_y());
	}

	return dir_pos;
}
void Ghost::handle_smart_move()
{
    Position curr_pos, next_pos;
    for (int i = 0; i < 2/*NUM_OF_GHOSTS*/; i++)
    {

    }
}


void Game::handle_ghost_move() {
    Position curr_pos, next_pos;
    for (int i = 0; i < NUM_OF_GHOSTS; i++)
    {
        curr_pos = ghosts[i].get_position();
        next_pos = ghosts[i].move_ghost();
        while (is_invalid_place(next_pos) || board.get_cell(next_pos) == (unsigned char)Board::TELEPORT)
        {
            ghosts[i].rotate_direction();
            next_pos = ghosts[i].move_ghost();
        }

        ghosts[i].set_position(next_pos);

        if (board.get_cell(curr_pos) == (unsigned char)Board::POINT)
        {
            board.set_cell(curr_pos, (unsigned char)Board::POINT);
            print_move(curr_pos, (unsigned char)Board::POINT);
        }
        else
            print_move(curr_pos, ' ');//deletes the previous symbol

        print_move(next_pos, GHOST_ICON);
    }
}



//smart ghost using BFS
//void Ghosts::smart(int grid[][COL], bool vis[][COL], int row, int col)
void Ghosts::smart(int grid[][25], Position curr_pos)
{
    int ghost_x = curr_pos.get_x(), ghost_y = curr_pos.get_y();
    std::queue<Position> moving_queue;
    bool is_visted[][25] = { false }; //init all cells as unvisited cells.
    Position new_pos;

    moving_queue.push(curr_pos);
    is_visted[ghost_x][ghost_y] = true;

    while (!moving_queue.empty()) {

        Position cell = moving_queue.front();

        int x = cell.get_x();
        int y = cell.get_y();

        cout << grid[x][y] << " ";

        moving_queue.pop();

        // Direction vectors
        int move_vector_row[] = { -1, 0, 1, 0 };
        int move_vector_col[] = { 0, 1, 0, -1 };


        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

            new_pos.set_xy(x = ghost_x + move_vector_row[i], y = ghost_y + move_vector_col[i]);
            //if (is_invalid_place(new_pos))
            {
                moving_queue.push(new_pos);
                is_visted[new_pos.get_x()][new_pos.get_y()] = true;
            }
        }
    }
}




#include <bits/stdc++.h>

#define ROW 4
#define COL 4



// Function to check if a cell
// is be visited or not
bool isValid(bool vis[][COL],
    int row, int col)
{
    // If cell lies out of bounds
    if (row < 0 || col < 0
        || row >= ROW || col >= COL)
        return false;

    // If cell is already visited
    if (vis[row][col])
        return false;

    // Otherwise
    return true;
}

// Function to perform the BFS traversal
void Ghosts::BFS(int grid[][COL], bool vis[][COL],
    int row, int col)
{
    // Stores indices of the matrix cells
    queue<pair<int, int>> q;

    // Mark the starting cell as visited
    // and push it into the queue
    q.push({ row, col });
    vis[row][col] = true;

    // Iterate while the queue
    // is not empty
    while (!q.empty()) {

        pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;

        cout << grid[x][y] << " ";

        q.pop();

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

            int adjx = x + dRow[i];
            int adjy = y + dCol[i];

            if (isValid(vis, adjx, adjy)) {
                q.push({ adjx, adjy });
                vis[adjx][adjy] = true;
            }
        }
    }
}

// Driver Code
int main()
{
    // Given input matrix
    int grid[ROW][COL] = { { 1, 2, 3, 4 },
                           { 5, 6, 7, 8 },
                           { 9, 10, 11, 12 },
                           { 13, 14, 15, 16 } };

    // Declare the visited array
    bool vis[ROW][COL];
    memset(vis, false, sizeof vis);

    BFS(grid, vis, 0, 0);

    return 0;
}
/*
bool Ghosts::Entity::is_collided_ghost(const Position pacman_pos,Ghosts ghosts[],int num_of_ghosts,Pacman pacman) {
	int d1, d2, x_dif, y_dif;
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].get_position() == pacman.get_position())
			return true;

		//edge cases
		d1 = ghosts[i].get_direction();
		d2 = pacman.get_direction();
		x_dif = pacman_pos.get_x() - ghosts[i].get_position().get_x();
		y_dif = pacman_pos.get_y() - ghosts[i].get_position().get_y();
		Position dif(x_dif, y_dif);

		if ((d1 == UP && d2 == DOWN && dif == Position(0, 1) ||
			d1 == DOWN && d2 == UP && dif == Position(0, -1) ||
			d1 == LEFT && d2 == RIGHT && dif == Position(-1, 0) ||
			d1 == RIGHT && d2 == LEFT && dif == Position(1, 0)))
			return true;
	}
	return false;
}*/



