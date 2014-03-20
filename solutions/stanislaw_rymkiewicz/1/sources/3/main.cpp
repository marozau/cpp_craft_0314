#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const string input_file_name = BINARY_DIR "/input.txt";
const string output_file_name = BINARY_DIR "/output.txt";

const char LAND = 'o';
const char WATER = '~';
const char VISITED = 'v';

typedef  unsigned int  UInt ;
static UInt rows = 0;
static UInt columns = 0;

void checkNeighbours( vector<string>& map, UInt i, UInt j)
{    
    if ( i >= rows ||  j >= columns )
    {
		return;
    }
	
	if( map[i][j] == LAND )
    {
		map[i][j] = VISITED;
	    checkNeighbours( map, i + 1, j );
        if(i)
        {
	        checkNeighbours( map, i - 1, j );
        }

	    checkNeighbours( map, i, j + 1 );
        if(j)
        {
	        checkNeighbours( map, i, j - 1 );
        }
    }	
}

int main(int argc, char* argv[]) 
{
    UInt islands_count = 0;
    
	ifstream inFile( input_file_name );

	if( !inFile.is_open() )
	{
		cout<<"error occured while opening file " << input_file_name;
		return 1;
	}

    string row;
    vector<string> world_map;
	
    while( !inFile.eof())
    {
        getline(inFile, row);
                
        if(row.size())
        {
            columns = static_cast<UInt>( row.size() );
            world_map.push_back( row );
        }
        
    }
	inFile.close();

    rows = static_cast<UInt>(world_map.size());

    for(UInt r = 0; r < rows; ++r )
    {
        for( UInt c = 0; c < columns ; ++c )
        {
            if(world_map[r][c] == LAND)
            {
                checkNeighbours(world_map, r,c);
                islands_count += 1;
            }
        }
        
    }

	

	ofstream outFile( output_file_name );
    if( !outFile.is_open() )
	{
		cout<<"error occured while opening file " << output_file_name;
		return 1;
	}
    else
    {
        outFile << islands_count << endl;
    }
		
	outFile.close();
	return 0;
}
