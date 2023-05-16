/**
 * @file node.h
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief This file contains a class to represent a node in a maze.
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef NODE_H
#define NODE_H

#include <array>

namespace rwa2 {
    /**
     * @brief Class to represent a node (cell) in a maze.
     *
     *A node is just a space delimited by 4 walls
     *
     */
    class Node
    {
    public:
        Node() {
            for (int i = 0; i < 4; i += 1) {
                m_walls[i] = false;
            }
        }
        /**
         * @brief Set the wall of a cell
         *
         * @param direction NORTH, EAST, SOUTH, or WEST
         * @param is_wall true if there is a wall, otherwise false
         */
        void set_wall(int direction, bool is_wall);
        /**
         * @brief Return whether or not there is a wall in a cell
         *
         * @param direction Direction to set for wall (NORTH, EAST, SOUTH, or WEST)
         * @return true There is a wall in the given direction in the cell
         * @return false There is no wall in the given direction in the cell
         */
        bool is_wall(int direction) const;
        /**
         * @brief Compute the number of walls surrounding a node
         * 
         * @return int Number of walls surrounding a node
         */
        int compute_number_of_walls() const;
        int x; //x position of the robot in the maze
        int y; //y position of the robot in the maze
        void set_n_x_y(int x_1, int y_1){
            x=x_1;
            y=y_1;
        }
        int get_n_x(){
            return x;
        }
        int get_n_y(){
            return y;
        }
        friend bool operator!=(const Node& lhs,const Node& rhs){
            if (lhs.x != rhs.x)
            {
                if (lhs.y != rhs.y)
                {
                    return true;
                }
                else{
                    return false;
                }
                
            }
            else{
                return false;
            }
            
            //return (lhs.n_x != rhs.n_x && lhs.n_y != rhs.n_y);
        }
        friend bool operator==(const Node& lhs,const Node& rhs){
            if (lhs.x == rhs.x)
            {
                if (lhs.y == rhs.y)
                {
                    return true;
                }
                else{
                    return false;
                }
                
            }
            else{
                return false;
            }
            //return (lhs.n_x == rhs.n_x && lhs.n_y == rhs.n_y);
        }
    private:
        std::array<bool, 4> m_walls; //all four walls in a cell

    };
    
}
#endif
