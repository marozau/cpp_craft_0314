#include <fstream>

using namespace std;

bool compare( double*, size_t, double );

int main()
{
	ifstream in( SOURCE_DIR "/input.txt" );
	if ( !in.is_open() )
		return 0;
	size_t n;
	in >> n;
	double* arr = new double[ n ];
	for ( size_t i = 0; i < n; ++i )
		in >> arr[i];
	ofstream out( SOURCE_DIR "/output.txt" );
	if ( !out.is_open() )
		return 0;
	while ( !in.eof() )
	{
		double buf;
		in >> buf;
		out << ( ( compare( arr, n, buf ) ) ? "YES" : "NO" ) << endl;
	}
	in.close();
	out.close();
	return 0;
}

bool compare ( double *ar, size_t size, double elem )
{
	for ( size_t i = 0; i < size; ++i )
		if (abs(elem-ar[i]) <= 0.0001)
			return true;
	return false;
}