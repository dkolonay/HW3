#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>
#include <optional>

class Problem{
public:
    std::string getQuestion();
    std::string getAnswer();

    Problem(std::string rawProblem);
    static std::vector<Problem> problemList(std::string filename);

private:
    std::string question;
    std::string answer;
};

class DetailedProblem : public Problem{
public:
    std::string getTopic();
    int getDifficulty();

    DetailedProblem(std::string rawProblem) : Problem(rawProblem){}

private:
    std::string topic;
    int difficulty;
};

#endif