#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <new>
#include <set>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


static const int MAP_WATER = -1;
static const int MAP_START_GROUND = 0;

typedef boost::numeric::ublas::matrix<int> islands_union_array;


void union_cells(islands_union_array &islands_map, size_t i1, size_t j1,
                 size_t i2, size_t j2) {
    /*std::cerr << "DEBUG: i1=" << i1 << ", j1=" << j1 << ", i2=" << i2 
              << ", j2=" << j2 << "\n";*/

    //we don't perform unions for water cells
    if (islands_map(i1, j1) == MAP_WATER) 
        return;
    if (islands_map(i2, j2) == MAP_WATER) 
        return;


    //we use far from optimal quick find method, which
    //could be significantlly optimized later e.g. by
    //using weighted quick union
    int ground_idx = islands_map(i1, j1);
    islands_map(i1, j1) = islands_map(i2, j2);
    for (size_t i = 0; i < islands_map.size1(); ++i)
        for (size_t j = 0; j < islands_map.size2(); ++j) {
            if (islands_map(i, j) == ground_idx) {
                islands_map(i, j) = islands_map(i2, j2);
            }
        }
}


void process_cell(islands_union_array &islands_map, size_t i, size_t j) {
    size_t top_i = i - 1;
    size_t top_j = j;
    if (i > 0) {
        union_cells(islands_map, i, j, top_i, top_j);
    }
    size_t down_i = i + 1;
    size_t down_j = j;
    if (down_i < islands_map.size1()) {
        union_cells(islands_map, i, j, down_i, down_j);
    }

    size_t left_i = i;
    size_t left_j = j - 1;
    if (j > 0) {
        union_cells(islands_map, i, j, left_i, left_j);
    }
    
    size_t right_i = i;
    size_t right_j = j + 1;
    if (right_j < islands_map.size2()) {
        union_cells(islands_map, i, j, right_i, right_j);
    }
}


int main(int argc, char **argv) {
    std::ifstream input;
    std::ofstream output;

    //some scaffolds
    //std::cerr << "DEBUG: SOURCE_DIR is " << SOURCE_DIR << "\n";
    //std::cerr << "DEBUG: BINARY_DIR is " << BINARY_DIR << "\n";

    input.open(BINARY_DIR "/input.txt");
    output.open(BINARY_DIR "/output.txt");
    if (not input.is_open()) {
        std::cerr << "Unable to open the input file. Reason: " << 
                      strerror(errno) << "\n";
        return 1;
    }
    if (not output.is_open()) {
        std::cerr << "Unable to open the output file. Reason: " << 
                      strerror(errno) << "\n";
        return 1;
    }

    std::vector<std::string> islands_map;
    std::string line;

    while ( std::getline(input, line) ) {
        //std::cerr << "DEBUG: line is " << line << "\n";
        islands_map.push_back(line);
    }
    input.close();

    size_t column_count = islands_map[0].size();
    size_t row_count = islands_map.size();
    //piece of useful debug print
    //std::cerr << "column_count is " << column_count << ", row_count is " 
    //          << row_count << "\n";

    //int *union_array = new int[row_count];
    islands_union_array union_array(row_count, column_count);

    int ground_counter = MAP_START_GROUND;

    for(size_t i = 0; i < islands_map.size(); ++i) {
        const std::string & map_row = islands_map[i];
        for(size_t j=0; j < map_row.size(); ++j) {
           const char c = map_row[j];
           if (c == 'o') {
                union_array(i, j) = ground_counter;
                ++ground_counter;
           } else if (c == '~') {
                union_array(i, j) = MAP_WATER;
           } else {
               std::cerr << "ERROR: invalid symbol `" << c << "`" 
                         << " in map. Row: " << i << ", col: " << j << "\n";
               return 1;
           }
        }
    }

    for (size_t i = 0; i < union_array.size1(); ++i)
        for (size_t j = 0; j < union_array.size2(); ++j) {
            process_cell(union_array, i, j);
        }
    //piece of useful debug print
    //std::cerr << "DEBUG: union_array is " << union_array << std::endl;


    std::set<int> islands_counter;
    for (size_t i = 0; i < union_array.size1(); ++i)
        for (size_t j = 0; j < union_array.size2(); ++j) {
            if (union_array(i, j) != MAP_WATER) {
                islands_counter.insert(union_array(i, j));
            }
        }

    output << islands_counter.size() << "\n";
    output.close();


    return 0;
}
