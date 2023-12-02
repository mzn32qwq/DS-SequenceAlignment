#include "fasta_reader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define sequence vector<string>
using namespace std;
// TODO: malloc ???

std::string filename = "sequences/GCA_009858895.3_ASM985889v3_genomic.fna";

// TODO: change the return table as string vector
void readFASTAfile(std::string filename){
	ifstream input(filename);
	if(!input.good()){  // if stream not good
		cerr << "Error in opening " << filename << ". Please check the filename. " << endl;
	}
	string id, line;
	string res_sequence;

	// TODO: separate if too long  
	while(getline(input, line)){
		if(line.empty())
			continue;
		if(line[0] == '>'){
			if(!id.empty()){
				cout << id << " : " << res_sequence << endl;
			}
			id = line.substr(1);
			res_sequence.clear();
		} else {
			res_sequence += line;
		}
	}

	if(!id.empty()){
		cout << id << " : " << res_sequence << endl;
	}
	
}

int main(void)
{
	readFASTAfile(filename);
	return 0;
}