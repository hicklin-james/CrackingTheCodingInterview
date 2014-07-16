#include <iostream>
#include <iterator>     // std::advance
#include <set>
#include <queue>
#include <string>
#include <vector>
#include <utility>


int nthFib(int n) {
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return 1;
	}

	return nthFib(n-1) + nthFib(n-2);
	
}

unsigned nChoosek( unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

// number of paths that a robot can take from the top left
// to the bottom right of an nXn grid, only making right and down moves
int possibleRobotMoves(int n) {

	int s = (n-1) + (n-1);
	int k = (n-1);
	
	return nChoosek(s, k);

}

void copy_set(std::set<char> &ds, std::set<char> &ss)
{
    std::set<char>::iterator it;
    for(it = ss.begin(); it != ss.end(); ++it){
        ds.insert(*it);
    }
}

void print_set(std::set<std::set<char> > set) {
	std::set<std::set<char> >::iterator its;
	for (its = set.begin(); its != set.end(); ++its) {
		std::set<char>::iterator it;
		std::set<char> this_set = *its;
		for (it = this_set.begin(); it != this_set.end(); ++it) {
			char t = *it;
			std::cout << t << " ";
		}
		std::cout << "\n";
	}
}

// Compute all subsets of a set
std::set<std::set<char> > get_subsets(std::set<char> &set, int index)
{
    std::set<std::set<char> > allsubsets;
	if (set.size() == index) {
		std::set<char> emptySet;
		allsubsets.insert(emptySet);
	}
	else {
	 	allsubsets = get_subsets(set, index + 1);
	 	std::set<char>::iterator it = set.begin();
	 	std::advance (it, index);
	 	char item = *it;
	 	std::set<std::set<char> >::iterator its;
	 	std::set<std::set<char> > moresubsets;

	 	for (its = allsubsets.begin(); its != allsubsets.end(); ++its) {
	 		std::set<char> newSubset;
	 		std::set<char>::iterator this_it;
	 		std::set<char> this_ss = *its;
	 		for (this_it = this_ss.begin(); this_it != this_ss.end(); this_it++) {
	 			char c = *this_it;
	 			newSubset.insert(c);
	 		}
	 		newSubset.insert(item);
	 		moresubsets.insert(newSubset);
	 	}

	 	std::set<std::set<char> >::iterator another_it;
	 	for (another_it = moresubsets.begin(); another_it != moresubsets.end(); another_it++) {
	 		std::set<char> this_ss = *another_it;
	 		allsubsets.insert(this_ss);
	 	}
	 }
	 return allsubsets;
}

std::string insertAt(std::string word, char c, int i) {
	std::string start = word.substr(0, i);
	std::string end = word.substr(i,std::string::npos);
	return start + c + end;
}

// Compute all permutations of a string
std::vector<std::string> get_permutations(std::string input) {

	std::vector<std::string> allPerms;

	if (input.size() == 0) { 
		allPerms.push_back("");
		return allPerms;
	}
	char front = input.front();
	std::string remainder = input.substr(1, std::string::npos);
	//std::cout << "Front: " << front << " Remainder: " << remainder << "\n";
	std::vector<std::string> words = get_permutations(remainder);
	for (int i = 0; i < words.size(); i++) {
		std::string word = words.at(i);
		//std::cout << word << "\n";
		for (int j = 0; j <= word.length(); j++) {
			std::string new_word = insertAt(word, front, j);
			//std::cout << new_word;
			allPerms.push_back(new_word);
		}
	}

	return allPerms;
}

void print_permutations(std::vector<std::string> strings) {
	for (int i = 0; i < strings.size(); i++) {
		std::cout << strings.at(i) << "\n";
	}
}

/**
Implement an algorithm to print all valid (e.g., properly opened and closed) combi- nations of n-pairs of parentheses.
EXAMPLE:
input: 3 (e.g., 3 pairs of parentheses)
output: ()()(), ()(()), (())(), ((()))
**/

void print_parenthesis(int l, int r, std::string input, int count) {
	if (l < 0 || r < l)
		return;
	if (l == 0 && r == 0)
		std::cout << input << "\n";
	else {
		if (l > 0) {
			std::string newString = insertAt(input, '(', count);
			print_parenthesis(l-1, r, newString, count+1);
		}
		if (r > l) {
			std::string newString = insertAt(input, ')', count);
			print_parenthesis(l, r-1, newString, count+1);
		}
	}
}

void printPar(int count) {
	std::string mystring;
	print_parenthesis(count,count,mystring,0);
}

/**
Implement the “paint fill” function that one might see on many image editing programs. That is, given a screen 
(represented by a 2 dimensional array of Colors), a point, and a new color, fill in the surrounding area until 
you hit a border of that color.’
**/

void paintFill(int colors[][5], std::pair<int, int> point, int color, int ocolor) {
	if (colors[point.first][point.second] != ocolor) 
		return;
	std::pair<int,int> point1(point.first-1, point.second);
	std::pair<int,int> point2(point.first+1, point.second);
	std::pair<int,int> point3(point.first, point.second-1);
	std::pair<int,int> point4(point.first, point.second+1);

	colors[point.first][point.second] = color;

	paintFill(colors, point1, color, ocolor);
	paintFill(colors, point2, color, ocolor);
	paintFill(colors, point3, color, ocolor);
	paintFill(colors, point4, color, ocolor);

	return;
}

void paintFillInit(int colors[][5], std::pair<int, int> point, int color) {
	paintFill(colors, point, color, colors[point.first][point.second]);
}

void print_matrix(int colors[][5]) {

	for (int i = 0; i < 5; i++) {
    	for (int s = 0; s < 5; s++) {
    		std::cout << colors[i][s] << " ";
    	}
    	std::cout << "\n";
    }

}

/**
 Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents) and pennies (1 cent), write 
 code to calculate the number of ways of representing n cents.
 **/

/** First Attempt - buggy as it includes 5+1 and 1+5 as two different attempts to make 6 **/
int print_cents(int curr, int goal) {
	//std::cout << "hello\n";
	if (curr > goal)
		return 0;
	if (curr == goal)
		return 1;

	return print_cents(curr+25, goal) +
		   print_cents(curr+10, goal) +
		   print_cents(curr+5, goal) +
		   print_cents(curr+1, goal);
}

int printCents(int n) {
	int ways = print_cents(0,n);
	return ways;
}

/** Second attempt - correct **/
int makeChange(int n, int denom) { 
	int next_denom = 0;
	switch (denom) {
		case 25:
			next_denom = 10;
		    break;
		case 10:
			next_denom = 5;
		    break;
		case 5:
			next_denom = 1;
		    break;
		case 1:
			return 1; 
		}

	int ways = 0;
	for(int i=0; i*denom<=n; i++ ){
		ways += makeChange(n - i * denom, next_denom); 
	}
	return ways; 
}

/**
Write an algorithm to print all ways of arranging eight queens on a chess board so that none of them share 
the same row, column or diagonal.
**/

bool checkDiagonals(char board[][8], int x, int y) {
	int tempx = x;
	int tempy = y;
	while ( tempx > -1 && tempy > -1) {
		if (board[tempx][tempy] == 'Q')
			return false;
		tempx--;
		tempy--;
	}
	tempx = x;
	tempy = y;
	while (tempx < 8 && tempy < 8) {
		if (board[tempx][tempy] == 'Q')
			return false;
		tempx++;
		tempy++;
	}
	tempx = x;
	tempy = y;
	while ( tempx > -1 && tempy < 8) {
		if (board[tempx][tempy] == 'Q')
			return false;
		tempx--;
		tempy++;
	}
	tempx = x;
	tempy = y;
	while (tempx < 8 && tempy > -1) {
		if (board[tempx][tempy] == 'Q')
			return false;
		tempx++;
		tempy--;
	}
	return true;
}

bool checkVertical(char board[][8], int x) {
	int row = 0;
	while (row < 8) {
		if (board[x][row] == 'Q') 
			return false;
		row++;
	}
	return true;
}

bool checkHorizontal(char board[][8], int y) {
	int col = 0;
	while (col < 8) {
		if (board[col][y] == 'Q') 
			return false;
		col++;
	}
	return true;
}

bool checkSolution(char board[][8]) {
	int queen_count = 0;
	for (int i = 0; i < 8; i++) {
		for (int s = 0; s < 8; s++) {
			if (board[i][s] == 'Q') {
				queen_count++;
			}
		}
	}
	if (queen_count == 8)
		return true;
	else
		return false;
}

void print_board(char board[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int s = 0; s < 8; s++) {
				std::cout << "|" << board[i][s];
		}
		std::cout << "|\n";
	}
	std::cout << "\n";
}


void organizeQueens(char board[][8], int row) {

	// check if we are out of bounds
	if (row >= 8) {
		print_board(board);
		return;
	}
	// check if we are at a solution
	//if (checkSolution(board)) {
	//	print_board(board);
	//	return;
	//}

	for (int i = 0; i < 8; i++) {
		if (checkVertical(board, i) && checkHorizontal(board, row) && checkDiagonals(board, i, row)) {
			board[i][row] = 'Q';
			organizeQueens(board, row+1);
			// set Q back to nothing so that checkHorizontal passes
			board[i][row] = ' ';
		}
	}

}

int main() {
	std::cout << "3rd fib: " << nthFib(3) << "\n";
	std::cout << "4th fib: " << nthFib(4) << "\n";
	std::cout << "5th fib: " << nthFib(5) << "\n";
	std::cout << "6th fib: " << nthFib(6) << "\n";

	std::set<char> s;

    s.insert('a');
    s.insert('b');
    s.insert('c');
    std::cout << "\nFind Subsets Input String: abc\nOutput:";
    std::set<std::set<char> > ss = get_subsets(s, 0);
    print_set(ss);

    std::cout << "\nString Permutations Input String: abcd\n";
    std::vector<std::string> strings = get_permutations("abcd");
    std::cout << "Output:\n";
    print_permutations(strings);

    std::cout << "\nPrint Parenthesis for n=3\n";
    printPar(3);
    std::cout << "Print Parenthesis for n=2\n";
    printPar(2);

    std::cout << "\nPaint fill:\nBefore filling point x=2 y=2 with the color 3:\n";

    int matrix[5][5] = { {1,1,1,1,1},
    					 {1,2,2,2,1},
    					 {1,2,2,2,2},
    					 {1,2,2,2,1},
    					 {1,1,1,1,1} };

   	print_matrix(matrix);
    paintFillInit(matrix, std::pair<int,int>(2,2), 3);
    std::cout << "After filling point x=2 y=2 with the color 3:\n";
    print_matrix(matrix);

    std::cout << "\nNumber of Ways to calculate 1 cent:\n";
    int ways = makeChange(1,25);
    std::cout << ways << "\n";
    std::cout << "\nNumber of Ways to calculate 5 cents:\n";
    ways = makeChange(5,25);
    std::cout << ways << "\n";
	std::cout << "\nNumber of Ways to calculate 1000 cents:\n";
    ways = makeChange(100,25);
    std::cout << ways << "\n";

    std::cout << "\n8 Queens on a chessboard:\n";

    char chessBoard[8][8] = { {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '},
    						  {' ',' ',' ',' ',' ',' ',' ',' '} };

    organizeQueens(chessBoard, 0);


}