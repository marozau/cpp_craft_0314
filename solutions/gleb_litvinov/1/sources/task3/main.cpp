#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <queue>
class task
{
	std::ifstream in;
	std::ofstream out;
	std::vector<std::string> field;
	const char earth='o',water='~';
	struct point
	{
		int x,y;
		point(int i,int j)
		{
			x=i;
			y=j;
		}
	};
	int rows_cnt,collums_cnt;
	std::queue<point> points;

	void add(const point& node)
	{
		if (node.x>=0&&node.x<rows_cnt&&node.y>=0&&node.y<collums_cnt&&field[node.x][node.y]==earth) 
		{
			field[node.x][node.y]=water;
			points.push(node);
		}
	}
	void bfs(const point& start)
	{   
		points.push(start);
		field[start.x][start.y]=water;
		while (!points.empty())
		{   
			point& current=points.front();
			add(point(current.x+1,current.y));
			add(point(current.x,current.y+1));
			add(point(current.x,current.y-1));
			add(point(current.x-1,current.y));
			points.pop();
		}
	}


public:
	task()
	{   
		const std::string inp=BINARY_DIR"/Input.txt",
		outp=BINARY_DIR"/Output.txt";
		in.open(inp);
		if (!in.is_open()) throw(std::logic_error("Can't open file"+inp));
		out.open(outp);
		if (!out.is_open()) throw(std::logic_error("Can't open file"+outp));
	}
	
	void solve()
	{
		std::string temp;			
		int answer=0;
		while( !in.eof() )
		{   
			std::getline( in, temp );
			field.push_back(temp);
		}
		if (field.size()==0)
		{
			out<<0;
			return;
		}
		rows_cnt=static_cast<int>field.size();
		collums_cnt=(int)field[0].size();
		for(int i=0;i<rows_cnt;++i)
			for(int j=0;j<collums_cnt;++j)
			{
				if (field[i][j]==earth)
				{
					++answer;
					bfs(point(i,j));
				}
			}
		out<<answer;
	}
	~task()
	{
		in.close();
		out.close();
	}

};
int main()
{   try
    {
		task realization;
		realization.solve();
    }
    catch(const std::logic_error& message)
	{
		std::cout<<message.what()<<"\n";
	}
    
	return 0;
}
