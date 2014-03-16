#include <iostream>
#include <string>
#include <deque>
#include <iosfwd>
#include <fstream>

using namespace std;

namespace Constants
{
    namespace Paths
    {
        const string input_file = BINARY_DIR "/input.txt";
        const string output_file = BINARY_DIR "/output.txt";
    }
}

class cEath final
{
public:
    static const char ms_water;
    static const char ms_island;

public:
    cEath()
    {

    }

    explicit cEath(const deque<string>& _map_eath)
        : m_earths_map(_map_eath)
    {}

    ~cEath()
    {}

    size_t getCountRows() const { return m_earths_map.size(); }
    size_t getCountColumnsForRow(const size_t _row) const 
    {
        if (m_earths_map.size() <= _row)
        {
            exit(-1);
        }

        return m_earths_map[_row].size();
    }

    char getObject(const size_t _row, const size_t _column) const 
    {
        if (_row >= m_earths_map.size())
        {
            exit(-1);
        }

        if (_column >= m_earths_map[_row].size())
        {
            exit(-1);
        }

        return m_earths_map[_row][_column];
    }

    void sinkObject(const size_t _row, const size_t _column)
    {
        if (_row >= m_earths_map.size() || _row < 0)
        {
            return;
        }

        if (_column >= m_earths_map[_row].size() || _column < 0)
        {
            return;
        }

        if (m_earths_map[_row][_column] == ms_island)
        {
            m_earths_map[_row][_column] = ms_water;

            sinkObject(_row - 1, _column);
            sinkObject(_row + 1, _column);
            sinkObject(_row, _column - 1);
            sinkObject(_row, _column + 1);
        }
    }

    void printMap() const
    {
        for (const string& row : m_earths_map)
        {
            cout << row << endl;
        }
        cout << endl;
    }

    void addRow(const string& _row)
    {
        m_earths_map.push_back(_row);
    }

private:
    cEath(const cEath&);
    cEath& operator=(const cEath&);

private:
    deque<string> m_earths_map;
};

const char cEath::ms_water = '~';
const char cEath::ms_island= 'o';

int main( void )
{
    cEath eath;

    ifstream input_file( Constants::Paths::input_file );
    if (!input_file.is_open())
    {
        return -1;
    }

    while (!input_file.eof())
    {
        string row;
        std::getline(input_file, row);
        eath.addRow(row);
    }
    input_file.close();

    int count_island = 0;
    for (size_t row = 0; row < eath.getCountRows(); ++row)
    {
        const size_t column_count = eath.getCountColumnsForRow(row);

        for (size_t column = 0; column < column_count; ++column)
        {
            const char object = eath.getObject(row, column);
            if (object == cEath::ms_island)
            {
                eath.sinkObject(row, column);
                ++count_island;
            }
        }
    }

    ofstream output_file(Constants::Paths::output_file);
    output_file << count_island << endl;
    output_file.close();

    return 0; 
}