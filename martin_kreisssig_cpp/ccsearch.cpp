#include "ccsearch.h"
#include "Timer.h"
#include <fstream>
#include <cmath>


/** nach Matlab Implementierung vom 14.08.12
  *
  */
cCCSearch::cCCSearch( void )
{

}

/** Find all maximally connected compatible vertex sets in the cc-graph.
  * Algorithm in initiated here and gets the cc-adjacency matrix.
  **/
i_m cCCSearch::findCCIS( i_m AdjM  )
{
    i_v solution, visited_vertices, vertices;
    int v;
    M = int( AdjM.size() );

    for( v = 0; v < M; v++ )
        vertices.push_back(v);

    full_search( AdjM, vertices, solution, visited_vertices );

    return solution_set;
}


/** Recursive function call, according to algorithm in [ICASSP13].
 * CombineAll(), returns list of vectors with cc-vertex indices.
 *
 */
void cCCSearch::full_search( i_m AdjM, i_v vertices, i_v solution, i_v visited_vertices )
{
    int l, v, n, t;
    bool conflict, connected, found;
    i_v compatible_neighbours, conflict_neighbours, reduced_vertices;

    // first iteration: set compatible neighbours to vertex set -> all must be root
    if( solution.empty() )
        compatible_neighbours = vertices;
    else
    {
        // go through all remaining vertices and check for compatbile neighbours (N) and conflicting neighbours (conflict_neighbours)
        for( v = 0; v < int(vertices.size()); v++ )
        {
            conflict = false;
            connected = false;
            for( l = 0; l < int(solution.size()); l++ )
            {
                if( AdjM[ vertices[v] ][ solution[l] ] == -1 )
                    conflict = true;
                if( AdjM[ vertices[v] ][ solution[l] ] == 1 )
                    connected = true;
            }

            // conflict is worse, hence first
            if( conflict )
                conflict_neighbours.push_back( vertices[v] );
            else if( connected )
                compatible_neighbours.push_back( vertices[v] );
        }

    }

    // if no compatible neighbours, solution is maximal, save
    if( compatible_neighbours.empty() )
        solution_set.push_back( solution );
    else
    {
        // V = V \ conflict_neighbours: remove conflicting vertices
        for( v = int(vertices.size())-1; v >= 0; v-- )
        {
            found = false;
            t = 0;
            while( !found && t < int(conflict_neighbours.size()) )
            {
                if( vertices[v] == conflict_neighbours[t] )
                    found = true;
                t++;
            }
            if( found )
                vertices.erase( vertices.begin() + v );
        }

        // N = N \ X: remove already visited vertices from compatible neighbours
        for( v = int(compatible_neighbours.size())-1; v >= 0; v-- )
        {
            found = false;
            t = 0;
            while( !found && t < int(visited_vertices.size()) )
            {
                if( compatible_neighbours[v] == visited_vertices[t] )
                    found = true;
                t++;
            }
            if( found )
                compatible_neighbours.erase( compatible_neighbours.begin() + v );
        }

        // for all compatible neighbours
        for( n = 0; n < int(compatible_neighbours.size()); n++ )
        {
            // T = V \ n: remove neighbour
            reduced_vertices = vertices;
            for( v = 0; v < int(reduced_vertices.size()); v++ )
                if( reduced_vertices[v] == compatible_neighbours[n] )
                    reduced_vertices.erase( reduced_vertices.begin()+v, reduced_vertices.begin()+v+1 );

            // solution = solution U n: add neighbour to solution
            solution.push_back( compatible_neighbours[n] );
            // call recursively
            full_search( AdjM, reduced_vertices, solution, visited_vertices );
            // remove neighbour from solution and proceed
            solution.pop_back();
            // add neighbour to "already visited" set X
            visited_vertices.push_back( compatible_neighbours[n] );
        }
    }
}


void check_kreissig_bigmat(){
	int num_rows;
	std::vector<std::vector<int> > acc;
	int num_entries; // = num_rows*num_rows;
	int ij_index = 0;
	int num_solutions;
	std::vector<int> temp_row;
	std::cout << num_entries << "unique entries" << std::endl;
	
	// https://stackoverflow.com/a/28312037/4955732
	
	std::ifstream input("flatA.txt");
	int count = 0;
	std::string line;
	if (input.is_open()){
		while (!input.eof()){
			std::getline(input, line);
			count++;
		}
		input.close();
	}
	
	num_entries = count-1;
	num_rows = (int)std::sqrt(num_entries);
	std::cout << "Number of entries are: " << num_entries << ". Num rows are:" << num_rows <<" \n";
	// 
	int data[num_entries];
	
	std::ifstream input2("flatA.txt");
	for (int i = 0; i < num_entries; i++) {
        input2 >> data[i];
        }

	// and now assign each row as it comes
	std::cout<<"Miaow miaow" <<"\n";
	for (int i=0; i<num_rows; i++){
		for (int j=0; j<num_rows; j++){
			
			if (i<1){
				//acc.push_back(data[j]);
				temp_row.push_back(data[j]);
				//std::cout << data[j]<< "\n";
			}
			else{
				//acc[i].push_back(data[((i*num_rows)+j)]);
				temp_row.push_back(data[((i*num_rows)+j)]);
				//std::cout << data[(i*num_rows)+j]<< "\n";
			}
		}
		acc.push_back(temp_row);
		temp_row.clear();	
	}

	
	
	cCCSearch uu;
	Timer timer99;
	uu.findCCIS(acc);
	std::cout << "Time taken for big mat is: " << timer99.elapsed() << " s" << "\n";
	/*for (auto ii : uu.solution_set){
		std::cout << "soln start: " << std::endl;
		for (auto jj : ii){
			std::cout << jj << "\n";
		}
	}*/
	
	// now write the outputs 
	// Begin writing the data
	num_solutions = uu.solution_set.size();
	std::cout << "Number of solutions is: " << num_solutions << "\n";
	
	std::ofstream fw("kreissig_cpp_solutions.csv", std::ofstream::out);
	if (fw.is_open()){
		for (auto soln : uu.solution_set){
			for (auto every : soln){
				fw << every << ",";
			}
			fw << "\n";
		}
	fw.close();
	}
	else{
		std::cout << "Problem with opening file";
	}
	
}


void check_ky2013_example(){
	
	std::cout << "hi" << "\n";
	// initialise input data
	std::vector<std::vector<int> > acc;
	std::vector<std::vector<int> >  out;
	
	acc = {{ 0, 1, 0, 0,-1,-1}, 
		   { 1, 0, 1, 1, 0, 1},
		   {0, 1,  0,-1, 1,  0},
		   {0, 1, -1, 0,-1,  0},
		   {-1, 0, 1,-1, 0, 1},
		   {-1, 1, 0, 0, 1, 0}};
	// 
	cCCSearch uu;
	//uu.adjM = acc;
	// Timer timer4;
	uu.findCCIS(acc);
	//std::cout << "Kreissig version took:" << timer4.elapsed() << " s"<< "\n";
	
}

int main(){
	check_ky2013_example();
	check_kreissig_bigmat();
	return 0;
}