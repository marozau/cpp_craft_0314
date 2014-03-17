#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Tile
{
    bool _checked;
    bool _earth;
    
public:
    Tile(bool earth = false){_checked = false; _earth = earth;}
    
    void setChecked(bool checked){_checked = checked;}
    bool isChecked(){return _checked;}
    void setEarth(bool earth){_earth = earth;}
    bool isEarth(){return _earth;}
};



void check_left_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width);
void check_bottom_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width);
void check_right_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width);
void check_top_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width);

void check_neighbors(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width)
{
    check_left_neighbor(map,tile_idx,map_width);
    check_right_neighbor(map,tile_idx,map_width);
    check_top_neighbor(map,tile_idx,map_width);
    check_bottom_neighbor(map,tile_idx,map_width);
}

void check_left_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width)
{
    
    if(tile_idx == 0)
        return;
    
    size_t left_idx = tile_idx - 1;

    Tile *left_tile = map.at(left_idx);
    
    if(!left_tile->isChecked())
    {
        left_tile->setChecked(true);
        if(left_tile->isEarth())
            check_neighbors(map, left_idx, map_width);
    }
}

void check_right_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width)
{
    size_t height = map.size()/map_width;
    size_t right_idx = tile_idx + 1;

    if(right_idx % height >= map_width ||
       right_idx >= map.size())
        return;
    
    Tile *right_tile = map.at(right_idx);
    
    if(!right_tile->isChecked())
    {
        right_tile->setChecked(true);
        if(right_tile->isEarth())
            check_neighbors(map, right_idx, map_width);
    }
}

void check_top_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width)
{
    if(tile_idx < map_width)
        return;
    
    size_t top_idx = tile_idx - map_width;

    Tile *top_tile = map.at(top_idx);
    
    if(!top_tile->isChecked())
    {
        top_tile->setChecked(true);
        if(top_tile->isEarth())
            check_neighbors(map, top_idx, map_width);
    }
}

void check_bottom_neighbor(std::vector<Tile*> &map,const size_t tile_idx,const size_t map_width)
{
    size_t bottom_idx = tile_idx + map_width;
    if(bottom_idx >= map.size())
        return;
    
    Tile *bottom_tile = map.at(bottom_idx);
    
    if(!bottom_tile->isChecked())
    {
        bottom_tile->setChecked(true);
        if(bottom_tile->isEarth())
            check_neighbors(map, bottom_idx, map_width);
    }
}

int main(int argc, const char * argv[])
{
    std::ifstream in_file(BINARY_DIR "/input.txt");
    std::ofstream out_file(BINARY_DIR "/output.txt");
    
    if(!in_file.is_open()||!out_file.is_open())
    {
        std::cout << "Couldn't open files!\n";
        return 1;
    }
    
    std::string line;
    size_t map_width;
    std::vector<Tile*> map_vector;
    
    while (!in_file.eof())
    {
        std::getline(in_file, line);
        
        if(line.length())
            map_width = line.length();
        
        for(size_t i = 0; i < line.length(); i++)
        {
            Tile *tile = new Tile((line[i]!='~'));
            map_vector.push_back(tile);
        }
    }


    size_t islands = 0;
    
    for(size_t i = 0; i < map_vector.size(); i++)
    {
        Tile *tile = map_vector[i];
        
        if(tile->isChecked())
            continue;
        
        tile->setChecked(true);
        
        if(tile->isEarth())
        {
            islands++;
            check_neighbors(map_vector, i, map_width);
        }
    }

    out_file << islands;
    
    
    for(size_t i = 0; i < map_vector.size();i++)
        delete map_vector[i];
    
    
    in_file.close();
    out_file.close();
    
	return 0;
}
