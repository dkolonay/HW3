#ifndef PROBLEM_FORMATTERS_H
#define PROBLEM_FORMATTERS_H

#include "problem.h"
#include "string"

class ProblemFormatter{
    public:
        virtual std::string formatProblem(Problem problem ) = 0;
};

class SimpleProblemFormatter : ProblemFormatter{
    public:
        std::string formatProblem  (Problem problem) override;
};

class FancyProblemFormatter : ProblemFormatter{
    protected:
        int problemNumber = 1;
    public:
        std::string formatProblem (Problem problem) override;
        std::string formatLongProblem(TopicAuthorLengthProblem problem);

};

#endif