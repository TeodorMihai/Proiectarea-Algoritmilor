/**
 * Proiectarea Algoritmilor, 2014
 * Lab 4: Backtracking si optimizari
 * Task 1: Sudoku - Simple Backtracking
 *
 * @author 	Stefan Ruseti
 * @email	stefan.ruseti@gmail.com
 */
 #include <bits/stdc++.h>

using namespace std;

int bktCounter = 0;
int solutionCounter = 0;
int grid[9][9];

vector<int> posi[9][9];

int pos[9][9];


int values[9];//de cate ori pot pune o anumita valoare
/**
 * Intoarce true daca cifra adaugata la pozitia (row, column)
 * nu contrazice cifrele deja completate
 * 
 */


 struct Casuta{

 	int x; int y;
 	int p;

 	Casuta() {

 	}

 	Casuta(int x, int y, int p) : x(x), y(y), p(p) {}
 };

 //priority_queue<Casuta> pq;

bool isValid(int grid[9][9], int row, int column) {
    
    for (int i = 0; i < 9; i++)
        if (i != column && grid[row][i] != 0 && grid[row][i] == grid[row][column])
            return false;
    
    for (int i = 0; i < 9; i++)
        if (i != row && grid[i][column] != 0 && grid[i][column] == grid[row][column])
            return false;
    
    for (int i = (row / 3) * 3; i < (row / 3 + 1) * 3; i++)
        for (int j = (column / 3) * 3; j < (column / 3 + 1) * 3; j++)
            if ((i != row || j != column) &&
                    grid[i][j] != 0 && grid[i][j] == grid[row][column])
                return false;

    return true;
}

void printGrid(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) cout << " ";
            else cout << grid[i][j];
            cout << " ";
        }
        cout<<'\n';;
    }
    cout<<'\n';
}


vector<int> getOption(int x, int y) {

	vector<int> opt;

	int check[9];

	for(int i = 1; i <= 9 ; ++i)
		check[i] = 0;


	//linie si coloana
	for(int i = 0 ; i < 9 ; ++i)
		check[grid[x][i]]  = check[grid[i][y]] = 1;

	int row = x / 3; int col = y / 3;


	for(int i = row * 3; i < row * 3 + 3 ; i++)
		for(int j = col * 3; j < col * 3 + 3; ++j)
			check[grid[i][j]]  = 1;

		for(int i = 1; i <= 9 ; ++i)
			if(check[i] == 0)
				opt.push_back(i);

	return opt;
}


/*

void doBKT(int row, int column) {

   if(row == 9 && column == 0 && isValid(grid, row, column) ) {
		 solutionCounter++;   	
   		 printGrid(grid);

   		 cout<<"Numar de intrari in recursivitare :"<<bktCounter<<endl;
    	cout<<"Numar de solutii gasite: "<<solutionCounter<<endl;
    	exit(0);

   } else {

   		if(grid[row][column] == 0) {

   			for(int i : getOption(row, column)) {
   				
   				grid[row][column] = i;
			
				bktCounter++;

				if(column == 8)
					doBKT(row + 1, 0);
				else 
					doBKT(row, column + 1);
   

   				grid[row][column] = 0;
   			}

   		} else {
   				if(column == 8) 
					doBKT(row + 1, 0);
				else 
					doBKT(row, column + 1);
				bktCounter++;
			}
   }
}
*/


bool allComplete() {

	for(int i = 0 ; i < 9 ; ++i)
		for(int j = 0 ; j < 9 ; ++j)
			if(grid[i][j])
				return false;

	return true;
}

bool cmp(int x, int y) {

	return values[x] > values[y];
}

void actualizeValues() {

	//actualizez valorile dupa fiecare schimbare
	//si values
	for(int i = 0 ; i <= 9 ; ++i)
		values[i] = 0;

	for(int i = 0 ; i < 9; ++i) 
		for(int j = 0; j < 9 ; ++j)
			if(grid[i][j] == 0) {
				posi[i][j] = getOption(i, j);

				for(int c : posi[i][j])
					values[c]++;
			}
}


void doBKT(int k) { //k = cate am completat

   if( k == 81 ) {

   		printGrid(grid);
   		solutionCounter++;

   		//cout<<"Numar de intrari in recursivitare :"<<bktCounter<<endl;
    	//cout<<"Numar de solutii gasite: "<<solutionCounter<<endl;
   		//exit(0);

   } else {

   		int x = -1 ; int y = -1;

   		unsigned minOpt = 10;

   		//aleg cea mai mica varainta"tensionata casuta"

   		for(int i = 0 ; i < 9 ; ++i)
   			for(int j = 0 ; j < 9 ; ++j) 
   				if(grid[i][j] == 0 && minOpt > posi[i][j].size() ) {
   					minOpt = posi[i][j].size();
   					x = i; y = j;
   				}

   		if(posi[x][y].size() == 0) return ;

   		vector<int> opt = posi[x][y];

   		sort(opt.begin(), opt.end(), cmp);

   		for(int h : opt) {

   			bktCounter++;

   			grid[x][y] = h;

   			actualizeValues();
   		
   			doBKT(k + 1);
   			
   			grid[x][y] = 0;

   			actualizeValues();
   		}
   }
}


int main() {
    ifstream fin("sudoku.in");

    int complete = 0;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            fin>>grid[i][j];
            if(grid[i][j])
            	complete++;
        }

       //setez psoiblitatile intiiale

    for (int i = 0; i < 9; i++)
       for (int j = 0; j < 9; j++) {

       		if(grid[i][j] == 0) {
       			posi[i][j] = getOption(i, j);
       		
       			for(int k : posi[i][j])
       				values[k]++;
       		}
       }
    
    bktCounter = 0;
    
    solutionCounter = 0;

    doBKT(complete);

    cout<<"Numar de intrari in recursivitare :"<<bktCounter<<endl;
    cout<<"Numar de solutii gasite: "<<solutionCounter<<endl;
    return 0;
}



