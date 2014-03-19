bool find()
{
for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
		if ( a[i][j] == c )
			return true;
return false;
}
int main() {
	const int n = 20;
	const int m = 30;
	char** a = new char*[n];
	for (int i = 0; i < n; ++i)
		a[i] = new char[m];
	fill_array(a, n, m);
	char c;
	fill_char(c);
	if (find()) // print;
		;
	for (int i = 0; i < n; ++i)
		delete[] a[i];
	delete[] a;
	return 0;
}