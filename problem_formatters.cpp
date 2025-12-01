#include "problem.h"
#include "problem_formatters.h"

#include <string>

std::string SimpleProblemFormatter::formatProblem(Problem problem)
{
    std::string outputString = "";
    outputString = outputString + "\\item \\question{" + problem.getQuestion() + "}\n";
    outputString = outputString + "\\answer{" + problem.getAnswer() + "}\n";

    return outputString;
}

std::string FancyProblemFormatter::formatProblem(Problem problem)
{
    std::string outputString = "";
    if (problemNumber % 2 == 1)
    {                                                    // Start a new page before
        outputString = outputString + "\\pagebreak\n\n"; // each odd-numbered problem
    }
    else
    {                                                        // Insert blank space before
        outputString = outputString + "\\vspace{350pt}\n\n"; // each even-numbered problem
    }
    outputString = outputString + "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
    outputString = outputString + problem.getQuestion();
    outputString = outputString + "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";

    problemNumber += 1;

    return outputString;
}

std::string FancyProblemFormatter::formatLongProblem(TopicAuthorLengthProblem problem)
{
    std::string outputString = "";
    outputString = outputString + "\\pagebreak\n\n";
    outputString = outputString + "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
    outputString = outputString + problem.getQuestion();
    outputString = outputString + "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";

    problemNumber += 1;

    return outputString;
}

// std::string simple_formatter(Problem problem)
// {
//     std::string outputString = "";
//     outputString.append("\\item \\question{");
//     outputString.append(problem.getQuestion());
//     outputString.append("}\n");
//     outputString.append("\\answer{");
//     outputString.append(problem.getAnswer());
//     outputString.append("}\n");

//     return outputString;
// }

// std::string fancy_formatter(Problem problem){

// }