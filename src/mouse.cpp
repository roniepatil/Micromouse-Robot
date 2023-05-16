#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include "../include/node/node.h"
#include <string>
#include <vector>
#include <iostream>

void rwa2::Mouse::mlog(const std::string& text) {
    std::cerr << text << std::endl;
}
void rwa2::Mouse::nlog(const int& num){
    std::cerr << num << std::endl;
}

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}

bool rwa2::Mouse::search_maze(Node nodeobject){
    g.x = 7;
    g.y = 7;
    // nlog(nodeobject.y);
    
    mlog("Recalculating path");
    if(nodeobject.x == g.x && nodeobject.y == g.y){
        return true;
    }
    else{
        if(s.empty()){
            API::setColor(nodeobject.x,nodeobject.y,'G');
            s.push(nodeobject);
        }
    }
    if(!vector_contains(v,nodeobject)){
        v.push_back(nodeobject);
    }
    if((!m_maze.at(nodeobject.x).at(nodeobject.y).is_wall(direction::NORTH)) && (!vector_contains_next_direction(v,nodeobject.x,nodeobject.y+1))){
        nodeobject.y+=1;
        API::setColor(nodeobject.x,nodeobject.y,'G');
        s.push(nodeobject);
    }
    else if((!m_maze.at(nodeobject.x).at(nodeobject.y).is_wall(direction::EAST)) && (!vector_contains_next_direction(v,nodeobject.x+1,nodeobject.y))){
        nodeobject.x+=1;
        API::setColor(nodeobject.x,nodeobject.y,'G');
        s.push(nodeobject);
    }
    else if((!m_maze.at(nodeobject.x).at(nodeobject.y).is_wall(direction::SOUTH)) && (!vector_contains_next_direction(v,nodeobject.x,nodeobject.y-1))){
        nodeobject.y-=1;
        API::setColor(nodeobject.x,nodeobject.y,'G');
        s.push(nodeobject);
    }
    else if((!m_maze.at(nodeobject.x).at(nodeobject.y).is_wall(direction::WEST)) && (!vector_contains_next_direction(v,nodeobject.x-1,nodeobject.y))){
        nodeobject.x-=1;
        API::setColor(nodeobject.x,nodeobject.y,'G');
        s.push(nodeobject);
    }
    else{
        if(!s.empty()){
            s.pop();
        }
        else{
            return false;
        }
    }
    if(!s.empty()){
        nodeobject=s.top();
        // n=nodeobject;
        search_maze(nodeobject);
    }
    else{
        mlog("end");
        return false;
    }
}
bool rwa2::Mouse::vector_contains(std::vector<Node> v, const Node& n){
    bool result = false;
    for(Node & i:v){
        if(i.x == n.x && i.y == n.y){
            result = true;
            break;
        }
    }
    return result;
}
bool rwa2::Mouse::vector_contains_next_direction(std::vector<Node> v, int x, int y){
    bool result = false;
    for(Node & i:v){
        if(i.x == x && i.y == y){
            result = true;
            break;
        }
    }
    return result;
}

bool rwa2::Mouse::move_mouse(Node curr,Node asn){
  
    // if(API::wallFront()){
    //     m_maze.at(curr.x).at(curr.y).set_wall(direction::NORTH,true);
    //     display_walls();
    // }
    // else if(API::wallRight()){
    //     m_maze.at(curr.x).at(curr.y).set_wall(direction::EAST,true);
    //     display_walls();
    // }
    // else if(API::wallLeft()){
    //     m_maze.at(curr.x).at(curr.y).set_wall(direction::WEST,true);
    //     display_walls();
    // }
    // nlog(curr.y);
    // n=curr;
    curr=m_pos;
    nlog(m_pos.x);
    nlog(m_pos.y);
    nlog(asn.x);
    nlog(asn.y);
    if(m_pos.x == g.x && m_pos.y == g.y){
        return true;
    }
  
    //North
    if((m_pos.x == asn.x) && (asn.y-m_pos.y==1)){
        API::setColor(m_pos.x,m_pos.y,'a');
        direction=0;
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::NORTH,API::wallFront());
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::EAST,API::wallRight());
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::WEST,API::wallLeft());
        // move_forward();
        API::setColor(asn.x,asn.y,'a');
    }
    //East
    else if((asn.x-curr.x==1) && (asn.y == curr.y)){
        API::setColor(curr.x,asn.y,'a');
        turn_right();
        direction=1;
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::EAST,API::wallFront());
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::NORTH,API::wallLeft());
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::SOUTH,API::wallRight());
        // move_forward();
        API::setColor(asn.x,asn.y,'a');
    }
    //West
    else if((asn.x-curr.x==-1) && (asn.y == curr.y)){
        API::setColor(curr.x,curr.y,'a');
        direction=3;
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::NORTH,API::wallRight());
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::WEST,API::wallFront());
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction::SOUTH,API::wallLeft());
        turn_left();
        // move_forward();
        API::setColor(asn.x,asn.y,'a');
    }
    else{mlog("no direction found");}
    
    if(API::wallFront()){
        m_maze.at(m_pos.x).at(m_pos.y).set_wall(direction,true);
        display_walls();
        empty_stack(s);
        v.clear();
        return false;

    }
    else
        move_forward();

    // if((API::wallFront())){
    //     // mlog("entering wall front loop");
    //     if(!API::wallRight()){
    //         turn_right();
    //         empty_stack(s);
    //         v.clear();
    //         return false;
    //     }
    //     else if(!API::wallLeft()){
    //         turn_left();
    //         empty_stack(s);
    //         v.clear();
    //         return false;
    //     }
    //     else{
    //         turn_right();
    //         turn_right();
    //         empty_stack(s);
    //         v.clear();
    //         return false;
    //     }
          
    // }
}

void rwa2::Mouse::print_stack(){
    mlog("printing stack");
    int l=r_s.size();
    nlog(l);
    for(int i=0;i<l;++i){
        nlog(r_s.top().y);
        r_s.pop();
    }
}

bool rwa2::Mouse::traverse_stack(){
    mlog("Inside traffe_stack");
    r_s = reverse_stack(s);
    Node curr=r_s.top();
    r_s.pop();
    Node asn = r_s.top();
    int l=r_s.size();
    // nlog(l);
    // print_stack();
    for(int i=0;i<l;++i){
        // nlog(curr.x);
        // nlog(curr.y);
        if(!move_mouse(curr,asn)){
            return false;
        }
        curr=asn;
        r_s.pop();
        asn=r_s.top();
    }
    return true;

}

std::stack<rwa2::Node> rwa2::Mouse::reverse_stack(std::stack<Node> abc){
    Node item;
    std::stack<Node> tmpStack;
    while(!abc.empty()){
        item = abc.top();
        abc.pop();
        //std::cerr << item.x << " " << item.y << "\n";
        tmpStack.push(item);  
        // nlog(tmpStack.top().y);
    }
    return tmpStack;
}

void rwa2::Mouse::empty_stack(std::stack<Node> xyz){
    while(!xyz.empty()){
        xyz.pop();
    }
}

void rwa2::Mouse::move_forward(){
    API::moveForward();
    if(direction==0)m_pos.y+=1;
    else if(direction==1)m_pos.x+=1;
    else if(direction==2)m_pos.y-=1;
    else if(direction=3)m_pos.x-=1;

}

void rwa2::Mouse::turn_left(){
    API::turnLeft();
}

void rwa2::Mouse::turn_right(){
    API::turnRight();
}