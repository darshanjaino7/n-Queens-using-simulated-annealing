#include<bits/stdc++.h>
#include <iostream>
#include <math.h>
#define endl '\n'
#define pb push_back
int N;
using namespace std;

/************************************************************************************************************************************************************

function name: choosingRandom 

this function has one parameter of type vector<vector<int>> and another of type int pointer and vave return type void.
variable used : matrixBoard,state,temp,i,N,x
this function randomly configure the matrixBoard using function pb.

************************************************************************************************************************************************************/
void choosingRandom(vector<vector<int>> &matrixBoard, int* state)
{
	srand(time(0));

	for(int i=0;i<N;i++)
		{
			vector<int> temp;
			for(int j=0;j<N;j++)
			{
				int x;
				cin>>x;
				temp.pb(x);
			}
			matrixBoard.pb(temp);
		}
}
/*************************************************************************************************************************************************************

    function name printmatrixBoard
    this function has parameter of vector<vector<int>> chess matrix and has return type of type void

    varaible used : j,queen,chessMatrixBoard,N.
    this functio print the chessmatrixBoard from the two dimensional vector passed as parameter in the function.


**************************************************************************************************************************************************************/
void printmatrixBoard(vector<vector<int>> &chessMatrixBoard)
{

		cout<<"      ";
		for(int j=0;j<N;j++)
		cout<<"----";
		cout<<endl;
	   for (int queen = 0; queen < N; queen++)
		{
	        cout << queen+1 << " => " <<" |";
			for(int j=0;j<N;j++)
			{
				if(chessMatrixBoard[queen][j]==1)
				cout<<" Q"<<" |";
				else
				cout<<" * |";
			}
			cout<<endl;
			cout<<"      ";
			for(int j=0;j<N;j++)
				cout<<"----";
			cout<<endl;
		}
    }
/************************************************************************************************************************************************************

function name : print state

this function has parameter of type int pointer and return type of type void
variable used : i,N,state.

this function  print the content of array using index based accces.


************************************************************************************************************************************************************/
void printState(int* state)
{

	for (int i = 0; i < N; i++) 
	{
		cout << " " << state[i] << " ";
	}
	cout << endl;
}
/************************************************************************************************************************************************************

function name: compareState

this function has two parameter of type int pointer and return type of type bool
variable used : i,N,state1,state2.

this function compares the contents of array if all values are same the it return true otherwise it return false.


************************************************************************************************************************************************************/

bool compareStates(int* state1,int* state2)
{

	for (int i = 0; i < N; i++) {
		if (state1[i] != state2[i]) {
			return false;
		}
	}
	return true;
}

/************************************************************************************************************************************************************

function name: fill

this function has one parameter of type vector<vector<int>> and another of type int and has return type of type void
variable used : i,N,matrixBoard,value.

this function fills the two dimensional vector with value value


************************************************************************************************************************************************************/

void fill(vector<vector<int>> &matrixBoard, int value)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrixBoard[i][j] = value;
		}
	}
}

/************************************************************************************************************************************************************

function name: calculateObjective

this function has one parameter of type vector<vector<int>> and another of type int pointer and has return type of type int
variable used : i,N,matrixBoard,state,row,col,attacking.

this function looks for each queen in column it checks for the other queen falling in the line of queen if it find any one then it increment the
variable attacking by one


************************************************************************************************************************************************************/



int calculateObjective(vector<vector<int>> &matrixBoard , int* state)
{

	int row, col,attacking=0;
	for (int i = 0; i < N; i++) 
	{
		row = state[i], col = i - 1;
		while (col >= 0
			&& matrixBoard[row][col] != 1) {
			col--;
		}
		if (col >= 0
			&& matrixBoard[row][col] == 1) {
			attacking++;
		}
		row = state[i], col = i + 1;
		while (col < N
			&& matrixBoard[row][col] != 1) {
			col++;
		}
		if (col < N
			&& matrixBoard[row][col] == 1) {
			attacking++;
		}
		row = state[i] - 1, col = i - 1;
		while (col >= 0 && row >= 0
			&& matrixBoard[row][col] != 1) {
			col--;
			row--;
		}
		if (col >= 0 && row >= 0
			&& matrixBoard[row][col] == 1) {
			attacking++;
		}
		row = state[i] + 1, col = i + 1;
		while (col < N && row < N
			&& matrixBoard[row][col] != 1) {
			col++;
			row++;
		}
		if (col < N && row < N
			&& matrixBoard[row][col] == 1) {
			attacking++;
		}
		row = state[i] + 1, col = i - 1;
		while (col >= 0 && row < N
			&& matrixBoard[row][col] != 1) {
			col--;
			row++;
		}
		if (col >= 0 && row < N
			&& matrixBoard[row][col] == 1) {
			attacking++;
		}
		row = state[i] - 1, col = i + 1;
		while (col < N && row >= 0
			&& matrixBoard[row][col] != 1) {
			col++;
			row--;
		}
		if (col < N && row >= 0
			&& matrixBoard[row][col] == 1) {
			attacking++;
		}
	}
	return (int)(attacking / 2);
}

/************************************************************************************************************************************************************

function name: generatematrixBoard

this function has one parameter of type vector<vector<int>> and another of type int pointer and has return type of type void

this function set value of matrixBoard to 1 at the index store in array state.


************************************************************************************************************************************************************/

void generatematrixBoard(vector<vector<int>> &matrixBoard,int* state)
{
	fill(matrixBoard, 0);
	for (int i = 0; i < N; i++) 
	{
		matrixBoard[state[i]][i] = 1;
	}
}

/************************************************************************************************************************************************************

function name: making_copyState

this function has two parameters both of type int pointer state1,state2.
variable used : i,state1,state2,N.
this function copies value of state2 to state1.

************************************************************************************************************************************************************/

void making_copyState(int* state1, int* state2)
{

	for (int i = 0; i < N; i++) 
	{
		state1[i] = state2[i];
	}
}

/************************************************************************************************************************************************************

function name: getNeighbour 

this function has one parameter of type vector<vector<int>> and another of type  int pointer and have return type of type void.
 this fuction get the neighbour of the current state having the least objective value amongst all neighbour as well as current state.

************************************************************************************************************************************************************/

void getNeighbour(vector<vector<int>> &matrixBoard,int* state)
{
	vector<vector<int>> opmatrixBoard(N, vector<int> (N,0));
	int opState[N];
	making_copyState(opState,state);
	generatematrixBoard(opmatrixBoard,opState);

	int opObjective
		= calculateObjective(opmatrixBoard,
							opState);
	vector<vector<int>> neighbourBoard(N, vector<int> (N,0));
	int NeighbourState[N];

	making_copyState(NeighbourState,
			state);
	generatematrixBoard(neighbourBoard,
				NeighbourState);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
		if (j != state[i]) 
		{
				NeighbourState[i] = j;
				neighbourBoard[NeighbourState[i]][i]
					= 1;
				neighbourBoard[state[i]][i]
					= 0;
				int temp
					= calculateObjective(
						neighbourBoard,
						NeighbourState);

				if (temp <= opObjective) {
					opObjective = temp;
					making_copyState(opState,
							NeighbourState);
					generatematrixBoard(opmatrixBoard,
								opState);
				}
				neighbourBoard[NeighbourState[i]][i]
					= 0;
				NeighbourState[i] = state[i];
				neighbourBoard[state[i]][i] = 1;
			}
		}
	}

	making_copyState(state, opState);
	fill(matrixBoard, 0);
	generatematrixBoard(matrixBoard, state);
}

/************************************************************************************************************************************************************

function name: hillClimbing

this function has one parameter of type vector<vector<int>> and another of type int pointer and have return type void.

this function implements the hill climbing.

************************************************************************************************************************************************************/

void hillClimbing(vector<vector<int>> &matrixBoard,
				int* state)
{
	vector<vector<int>> neighbourBoard(N, vector<int> (N,0));
	int neighbourState[N];

	making_copyState(neighbourState, state);
	generatematrixBoard(neighbourBoard,neighbourState);
	do {

		making_copyState(state, neighbourState);
		generatematrixBoard(matrixBoard, state);

		getNeighbour(neighbourBoard,
					neighbourState);

		if (compareStates(state,neighbourState)) 
		{
			printmatrixBoard(matrixBoard);
			break;
		}
		else if (calculateObjective(matrixBoard,state)== calculateObjective(neighbourBoard,neighbourState)) 
		{
			neighbourState[rand() % N]
				= rand() % N;
			generatematrixBoard(neighbourBoard,
						neighbourState);
		}

	} while (true);
}

/************************************************************************************************************************************************************

function name: main

************************************************************************************************************************************************************/
int main()
{
	clock_t start = clock();
        cout<<"Enter the size of NxN chessboard"<<endl;
	cin>>N;

        cout<<"Enter the values of "<<N<<"x"<<N<<" matrix"<<endl;
	int state[N] = {};
	vector<vector<int>> matrixBoard(N, vector<int> (N,0) ) ;
	choosingRandom(matrixBoard, state);
	hillClimbing(matrixBoard, state);
	clock_t stop = clock();
	    cout << "Runtime: " << (float) (stop - start)/1000000 << " seconds" << endl;

	return 0;
}
