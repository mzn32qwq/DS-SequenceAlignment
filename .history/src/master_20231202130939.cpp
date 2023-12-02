
#include "controller/master_controller.h"
#include "gflags/gflags.h"
#include <iostream>
#include <queue>
#include <mutex>
#include <string>
#include <readfile.cpp>
#include <vector>
#include <map>

class MessageQueue {
    DEFINE_int32(port, 8000, "port on which the websocket listens");

private:
    std::queue<std::string> queue; // Standard library queue to store messages
    std::mutex mutex; // Mutex for thread safety

public:
    // Function to add a message to the queue
    void pushMessage(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex); // Lock before modifying the queue
        queue.push(message);
        std::cout << "Message added: " << message << std::endl;
    }

    // Function to remove and retrieve a message from the queue
    std::string popMessage() {
        std::lock_guard<std::mutex> lock(mutex); // Lock before accessing the queue
        if (queue.empty()) {
            return ""; // Return an empty string if the queue is empty
        }
        std::string message = queue.front();
        queue.pop();
        return message;
    }

    // Function to check if the queue is empty
    bool isEmpty() const {
        return queue.empty();
    }
};



int main(int argc, char **argv) {
    //initialize the variables of smith-waterman
    std::string pattern;
    std::string database;
    std int match_score;
    std int mismatch_pentalty;
    std int gap_extra;
    std int gap_open;

    std::vector<std::string> sequences;
    //assuming have mutiple sequences in the database
    readFASTAfile([&sequences](const std::string& id, const std::string& sequence) {
        std::cout << id << " : " << sequence << std::endl;
        sequences.push_back(sequence);  // adding the sequence to the vector
    });
    //Q:没有做database还是pattern的标识符 所以这里先假设database在sequences[0]里面
    database = sequences[0];
    //Q:没有做database还是pattern的标识符 所以这里先假设pattern在sequences[1]里面
    pattern = sequences[1];
    
    //get the parameters of smith-waterman
    std::cout <<"Please enter the match score: ";
    std::cin >> match_score;
    std::cout <<"Please enter the mismatch pentalty: ";
    std::cin >> mismatch_pentalty;
    std::cout <<"Please enter the gap extra: ";
    std::cin >> gap_extra;
    std::cout <<"Please enter the gap open: ";
    std::cin >> gap_open;
     
  
    //Initialize the score and direction tables
    int pattern_len = pattern.size();
	int database_len = database.size();
	int score_table[pattern_len + 1][database_len + 1];
	char direction_table[pattern_len + 1][database_len + 1];
    // fill in the 0th columns
	for(int i = 1; i < pattern_len + 1; i++){
		score_table[i][0] = 0;
		direction_table[i][0] = 'u';
	}

	// fill in the 0th rows
	for(int j = 1; j < database_len + 1; j++){
		score_table[0][j] = 0;
		direction_table[0][j] = 'l';
	}
	int i_max = 0;
	int j_max = 0;
	int max_value = 0;
	


    //Initialize the controller
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    MasterController controller;
    controller.onInit();
    controller.run(FLAGS_port); 

    //initialize the message queue
    std::map<std::string, std::string> Worker;
    std::mutex mtx;
    std::map<std::string, std::string> HistoryTask;
 


    //send the first block



    controller.sendMessageToPeer(); //这里具体传参没写,从id_to_connections返回最上面的connection？  
    //generate the task
    
    return 0;
}

