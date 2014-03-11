#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Tile
{
public:
    bool checked;
    bool earth;
    
};

void check_left_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width);
void check_bottom_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width);
void check_right_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width);
void check_top_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width);

void check_neighbors(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width)
{
    check_left_neighbor(map,tile_idx,map_width);
    check_right_neighbor(map,tile_idx,map_width);
    check_top_neighbor(map,tile_idx,map_width);
    check_bottom_neighbor(map,tile_idx,map_width);
}


void dump_map(std::vector<Tile*> *map,int64_t map_width)
{
//    std::cout << std::endl;
//    
//    for(int i = 0; i < map->size(); i++)
//    {
//        if(i > 0 && i%map_width==0)
//            std::cout << std::endl;
//        
//        Tile * t = map->at(i);
//        if(t->earth)
//        {
//            if(t->checked)
//                std::cout << "X";
//            else
//                std::cout << "0";
//        }else
//        {
//            if(t->checked)
//                std::cout << "-";
//            else
//                std::cout << "~";
//        }
//        
//        
//    }
//    
//    std::cout << std::endl;
}


void check_left_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width)
{
    int64_t height = map->size()/map_width;
    int64_t left_idx = tile_idx - 1;
    if(left_idx % height < 0)
        return;
    
    Tile *left_tile = map->at(left_idx);
    
    if(!left_tile->checked)
    {
        left_tile->checked = true;
        if(left_tile->earth)
            check_neighbors(map, left_idx, map_width);
    }
}

void check_right_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width)
{
    int64_t height = map->size()/map_width;
    
    
    
    int64_t right_idx = tile_idx + 1;

    if(right_idx % height >= map_width ||
       right_idx >= map->size())
        return;
    
    Tile *right_tile = map->at(right_idx);
    
    if(!right_tile->checked)
    {
        right_tile->checked = true;
        if(right_tile->earth)
            check_neighbors(map, right_idx, map_width);
    }
}

void check_top_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width)
{
    int64_t top_idx = tile_idx - map_width;
    if(top_idx < 0)
        return;
    
    Tile *top_tile = map->at(top_idx);
    
    if(!top_tile->checked)
    {
        top_tile->checked = true;
        if(top_tile->earth)
            check_neighbors(map, top_idx, map_width);
    }
}

void check_bottom_neighbor(std::vector<Tile*> *map,int64_t tile_idx,int64_t map_width)
{
    int64_t bottom_idx = tile_idx + map_width;
    if(bottom_idx >= map->size())
        return;
    
    Tile *bottom_tile = map->at(bottom_idx);
    
    if(!bottom_tile->checked)
    {
        bottom_tile->checked = true;
        if(bottom_tile->earth)
            check_neighbors(map, bottom_idx, map_width);
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream input_file(SOURCE_DIR "/input.txt");
    std::ofstream output_file(SOURCE_DIR "/output.txt");
    
    if(!input_file.is_open())
        return 1;
    
    std::string line;
    int64_t map_width;
    std::vector<Tile*> map_vector;
    
    while (!input_file.eof())
    {
        std::getline(input_file, line);
        
        if(line.length())
            map_width = line.length();
        
        for(size_t i = 0; i < line.length(); i++)
        {
            Tile *tile = new Tile();
            tile->earth = (line[i]!='~');
            tile->checked = false;
            map_vector.push_back(tile);
        }
    }
    
    dump_map(&map_vector, map_width);
    
    
    int64_t islands = 0;
    
    for(size_t i = 0; i < map_vector.size(); i++)
    {
        Tile *tile = map_vector[i];
        
        if(tile->checked)
            continue;
        
        tile->checked = true;
        
        if(tile->earth)
        {
            islands++;
            check_neighbors(&map_vector, i, map_width);
        }
        
        dump_map(&map_vector, map_width);
    }

    output_file << islands << std::endl;
    
    
    input_file.close();
    output_file.close();
    
	return 0;
}
