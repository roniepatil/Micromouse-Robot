#include <iostream>
#include <array>
#include "../include/node/node.h"

#include "../include/mouse/mouse.h"

void log(const std::string& text) {
std::cerr << text << std::endl;
}

int main() {
	log("Running...");
	rwa2::Mouse mouse;
	mouse.display_walls();
	
	// rwa2::Node node_origin;
	// node_origin.set_n_x_y(0,0);
	// mouse.n=node_origin;
	mouse.n.x=0;
	mouse.n.y=0;

	mouse.m_pos.x=0;
	mouse.m_pos.y=0;
	//std::cout<< mouse.search_maze(n) << "\n";
	//mouse.search_maze(node_origin);
	while(mouse.search_maze(mouse.m_pos)){
		if(mouse.traverse_stack()){
			break;
		}
	}

}

