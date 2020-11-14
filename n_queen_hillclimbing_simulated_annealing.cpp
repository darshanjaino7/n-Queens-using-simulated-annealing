#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#define TEMPERATURE 4000
using namespace std;

/**************************************************************************************************************************************************************

 function name: print_chessboard.
 variable names: chess_matrix ----> stores the positon of queen.
                 j ---> this counter for for loop.
                 queen---> counter variable for for loop.

  this function has a parameter of type vector<int> which stores the  position of queen int the respective row.
  this function print the the chess board the queen position as 'Q' and other position as '*'.


 ***************************************************************************************************************************************************************/
void print_chessboard(vector<int> chess_matrix) { 

		cout<<"      ";
		for(int j=0;j<chess_matrix.size();j++)
		cout<<"----";
		cout<<endl;
	    for (int queen = 0; queen < chess_matrix.size(); queen++)
		{
	        cout << queen+1 << " => " <<" |";
			for(int j=0;j<chess_matrix.size();j++)
			{
				if(j==chess_matrix[queen])
				cout<<" Q"<<" |";
				else
				cout<<" * |";
			}
			cout<<endl;
			cout<<"      ";
			for(int j=0;j<chess_matrix.size();j++)
				cout<<"----";
			cout<<endl;
		}
}

/***************************************************************************************************************************************************************

  function  name: threat_calculate 

  this function has a parameter of type int and have return type int. 
  this function calculate the number of threaten queen.


****************************************************************************************************************************************************************/

int threat_calculate(int n) 
{ 

    if (n < 2) return 0;
    if (n == 2) return 1;
    return (n - 1) * n / 2;
}


/**************************************************************************************************************************************************************

function name : cost

this function has a parameter of type vector<int> chess_matrix and has a return type  int.
ths  function calculate the total pair of threaten queen using the function threat_calculate.

variable used : chess_matrix,i,m_chessboard,warning,size,counter,counter_a.

***************************************************************************************************************************************************************/

int cost(vector<int> chess_matrix) 
{ 
    unsigned long size = chess_matrix.size();
    int warning = 0;
    int m_chessboard[size];
    int a_chessboard[size];

    for (int i = 0; i < size; i++) 
    {
        a_chessboard[i] = i + chess_matrix[i];
        m_chessboard[i] = i - chess_matrix[i];
    }

    sort(m_chessboard, m_chessboard + size);
    sort(a_chessboard, a_chessboard + size);

    int counter = 1;
    int counter_a = 1;

    for (int i = 0; i < size - 1; i++) 
    {
        int j = i + 1;
        if (m_chessboard[i] == m_chessboard[j]) 
        	counter += 1;
        else 
        {
            warning += threat_calculate(counter);
            counter = 1;
        }
        if (a_chessboard[i] == a_chessboard[j]) 
        	counter_a += 1;
        else 
        {
            warning += threat_calculate(counter_a);
            counter_a = 1;
        }
        if (j == size - 1) 
        {
            warning += threat_calculate(counter);
            warning += threat_calculate(counter_a);
            break;
        }
    }

    return warning;
}

/***********************************************************************************************************************************************************

    function name : main

    variable used: start,radn,n_queens,ans,i,j,stop,start,test,cost_answer.
    function first take the number of queen as input and then create a vector named n_queen and fill it with its index number and then shuffle the content of
    vector randomly.
    it print the random generated chess board 

    then it takes input for the number of solution it will print in variable test.
    we have used cost_answer variable to store cost to avoide recounting in case we cannot find a better solution.
    the after there is code for simulation of annealing.

    variable start and stop store the clock cycle of start and end to find out the execution time.

***********************************************************************************************************************************************************/

int main() 
{
    clock_t start = clock();
    srand((unsigned int) time(nullptr));
    random_device radn;
    mt19937 g(radn());
    vector<int> ans;
    unsigned int n_queens;
    
    cout << "Number of queens: ";
    cin >> n_queens;
    
    ans.reserve(n_queens);
    for (int i = 0; i < n_queens; i++) 
    { 
        ans.emplace_back(i);
    }
    shuffle(ans.begin(), ans.end(), g); 
	cout<<"The Random Generated n Queens Matix Original positions  "<<endl;   
	cout<<"      ";
	for(int j=0;j<ans.size();j++)
	cout<<"----";
	cout<<endl;
	for(int i=0;i<ans.size();i++)
	{
		cout << i << " => " <<" |";
		for(int j=0;j<ans.size();j++)
		{
			if(j==ans[i])
			cout<<" Q"<<" |";
			else
			cout<<" *"<<" |";
		}
		cout<<endl;
		cout<<"      ";
		for(int j=0;j<ans.size();j++)
		cout<<"----";
		cout<<endl;
	}
	int test;
	cout<<"Enter the number of solution you want to print"<<endl;
	cin>>test;
	double runt=0.0000000;
	for(int no=0;no<test;no++)
	{
	    int cost_answer = cost(ans);
	    
	    vector<int> next_up;
	    next_up.reserve(n_queens);
	    double t = TEMPERATURE;
	    double sch = 0.99;
	    while (t > 0) {
	        int rand_col_1;
	        int rand_col_2;
	        t *= sch;
	        next_up = ans;
	        while (true) 
	        { 
	       
	            rand_col_1 = (int) random() % n_queens;
	            rand_col_2 = (int) random() % n_queens;
	            if (next_up[rand_col_1] != next_up[rand_col_2]) 
	            	break;
	        }
	        swap(next_up[rand_col_1], next_up[rand_col_2]); 
	       
	        double delta = cost(next_up) - cost_answer;
	        if (delta < 0)
	        {
	            ans = next_up;
	            cost_answer = cost(ans);
	        }
	        else 
	        {
	            double p = exp(-delta / t);
	            if (random() / double(RAND_MAX) < p) 
	            {
	                ans = next_up;
	                cost_answer = cost(ans);
	            }
	        }
	        if (cost_answer == 0) 
	        {
				cout<<"Final Output matrix no => "<<no+1<<endl;
	            print_chessboard(ans);
	            break;
	        }
	    }

	    clock_t stop = clock();
	    cout << "Runtime: " << (float) (stop - start)/1000000 << " seconds" << endl;
	    runt=runt+(float) (stop - start)/1000000;
	}
	cout<<"Total Runtime "<<runt<<endl;
    return 0;

}
