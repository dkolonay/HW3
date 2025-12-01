#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class Problem
{
public:
    std::string getQuestion();
    std::string getAnswer();
    Problem(std::string rawProblem);
    static std::vector<Problem> problemList(std::string filename);

private:
    std::string question;
    std::string answer;
};

class TopicDifficultyProblem : public Problem
{
public:
    std::string getTopic();
    int getDifficulty();
    TopicDifficultyProblem(std::string rawProblem);
    static std::vector<TopicDifficultyProblem> problemList(std::string filename);

private:
    std::string topic;
    int difficulty;
};

class TopicAuthorLengthProblem : public Problem
{
public:
    std::string getTopic();
    std::string getAuthor();
    bool getIsLong();
    TopicAuthorLengthProblem(std::string rawProblem);
    static std::vector<TopicAuthorLengthProblem> problemList(std::string filename);

private:
    std::string topic;
    std::string author;
    bool isLong;
};

#endif