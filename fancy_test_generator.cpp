#include <ranges>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <set>
#include <vector>

#include <memory>

#include "problem.h"
#include "problem_formatters.h"
#include "header_builder.h"

// ****************************************************************************
// Configuration details

// Variable information to be printed on the test
std::string CLASS = "Arithmetic";
std::string TERM = "Fall 2025";
std::string EXAM = "925";
std::string TIME = "Day";
std::string TITLE = "Final Exam";
std::string FORM = "A";

// Source file for problem bank
std::string BANK = "math_problems.tex";

// Filename for the created test
std::string FILENAME = "fancy_test.tex";

// Constraints on the problem choice.
int NUM_PROBLEMS = 10; // The test must have 20 problems.
int MIN_LONG_PROBLEMS = 3;
int MAX_LONG_PROBLEMS = 4;
int MIN_PROBLEMS_BY_AUTHOR = 1;
int MAX_PROBLEMS_BY_AUTHOR = 2;
int MIN_PROBLEMS_BY_TOPIC = 1;
int MAX_PROBLEMS_BY_TOPIC = 2;
// int MIN_TOPIC = 3; // Each topic must be covered 
// int MAX_TOPIC = 7; // by 3-7 problems.
// int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined 
// int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75.

// tex files to include in the test file
std::string TEX_HEADER = "fancy_tex_header.tex";
std::string CONTENT_HEADER = "fancy_content_header.tex";

// ****************************************************************************

 bool valid(std::vector<TopicAuthorLengthProblem> potentialList, std::map<std::string, int> topics, std::map<std::string, int> authors){
                int problem_count = 0;
                int long_problems = 0;
                for (auto&topic : topics){
                    if (topic.second > MAX_PROBLEMS_BY_TOPIC || topic.second < MIN_PROBLEMS_BY_TOPIC){
                        return false;
                    }
                }
                for (auto&author : authors){
                    if(author.second > MAX_PROBLEMS_BY_AUTHOR || author.second < MIN_PROBLEMS_BY_AUTHOR){
                        return false;
                    }
                
                }
                for (TopicAuthorLengthProblem problem : potentialList){
                    problem_count += 1;
                    if (problem.getIsLong()){
                        long_problems += 1;
                    }
                }
                if (problem_count != NUM_PROBLEMS){
                    return false;
                }
                if (long_problems > MAX_LONG_PROBLEMS || long_problems < MIN_LONG_PROBLEMS){
                    return false;
                }
                return true;
            }

//Randomize Strategy Interface
class RandomizeStrategy {
    public:
        virtual std::vector<TopicAuthorLengthProblem> randomizeTestProblems(std::vector<TopicAuthorLengthProblem> bank) = 0;
};

//Concrete Randomizing Strategy
class BetterRandomizer : public RandomizeStrategy {
    public:
        // Given a bank of possible test problems, return randomly-chosen 
        // problems that form a valid test, according to the contraints above.
    std::vector<TopicAuthorLengthProblem> randomizeTestProblems(std::vector<TopicAuthorLengthProblem> bank) override{

        while (true){
            // Determine the topics covered on the test
            std::map<std::string, int> topics;
            std::map<std::string, int> authors;
            for (TopicAuthorLengthProblem p : bank) {
                if (topics.find(p.getTopic()) == topics.end()) {
                    topics.insert({p.getTopic(), 0});
                }
                if (authors.find(p.getAuthor()) == authors.end()) {
                    authors.insert({p.getAuthor(), 0});
                }
            }

           

            // Used for random generation
            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(bank.begin(), bank.end(), gen);
            std::vector<TopicAuthorLengthProblem> testProblems;
            int num_used_problems = 0;
            size_t current_problem_idx = 0;
            int long_problems = 0;
            int short_problems = 0;

            while (num_used_problems < NUM_PROBLEMS && current_problem_idx < bank.size()){
                TopicAuthorLengthProblem  current_problem = bank[current_problem_idx];

                if (topics[current_problem.getTopic()] >= MAX_PROBLEMS_BY_TOPIC){
                    current_problem_idx += 1;
                    continue;
                }
                if (authors[current_problem.getAuthor()] >= MAX_PROBLEMS_BY_AUTHOR){
                    current_problem_idx += 1;
                    continue;
                }
                if (current_problem.getIsLong() && long_problems >= MAX_LONG_PROBLEMS){
                    current_problem_idx += 1;
                    continue;
                }
                if (!current_problem.getIsLong() && short_problems >= (NUM_PROBLEMS - MIN_LONG_PROBLEMS) ){
                    current_problem_idx += 1;
                    continue;
                }

                testProblems.push_back(current_problem);
                num_used_problems += 1;
                topics[current_problem.getTopic()] += 1;
                authors[current_problem.getAuthor()] += 1;
                if (current_problem.getIsLong()){
                    long_problems += 1;
                } else {
                    short_problems += 1;
                }
                current_problem_idx+=1;
               
            }

            if(valid(testProblems, topics, authors)){
                std::sort(testProblems.begin(), testProblems.end(), [](TopicAuthorLengthProblem& a, TopicAuthorLengthProblem& b){
                    return a.getIsLong() < b.getIsLong();
                });
                return testProblems;
            }
            
        }
    }
};

//Implements concrete strategy patterns (can add functionality for switching strategies)
class Context{
    private:
        std::unique_ptr<RandomizeStrategy> strategy_;

    public:
        Context(std::unique_ptr<RandomizeStrategy> &&strategy = {}) : strategy_(std::move(strategy)) {}

        std::vector<TopicAuthorLengthProblem> randomize(std::vector<TopicAuthorLengthProblem> bank){
            return strategy_->randomizeTestProblems(bank);
        }
};

int main() {
    // Read in problem list and convert to Problem objects
    std::vector<TopicAuthorLengthProblem> bank = TopicAuthorLengthProblem::problemList(BANK);

    // Open the file to write the test to
    std::ofstream outputFile(FILENAME); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }


    // Generate the test problems
    Context context(std::make_unique<BetterRandomizer>());
    std::vector<TopicAuthorLengthProblem> test = context.randomize(bank);


    // Generate the header
    HeaderBuilder builder(TEX_HEADER, CONTENT_HEADER);
    builder.addHeaderElement("class", CLASS);
    builder.addHeaderElement("term", TERM);
    builder.addHeaderElement("examno", EXAM);
    builder.addHeaderElement("dayeve", TIME);
    builder.addHeaderElement("formletter", FORM);
    builder.addHeaderElement("numproblems", NUM_PROBLEMS);
    builder.addHeaderElement("testtitle", TITLE);

    std::string header = builder.build();

    // Write the tex header to the file
    outputFile << header;

    // Write the problems to the file
    FancyProblemFormatter formatter;

    for (TopicAuthorLengthProblem problem : test) {
        if (problem.getIsLong()){
            outputFile << formatter.formatLongProblem(problem);
        } else {
            outputFile << formatter.formatProblem(problem);
        }
        
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();
}