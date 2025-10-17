#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

static string listOfFilteredAndSplitJobDescription[11000][8] = {""}; //static so it takes different space
static string listOfFilteredAndSplitResume[11000][8] = {""};
static string listOfFilteredJobDescription[11000] = {""};
static string listOfFilteredResume[11000] = {""};
static int searchContainer[11000][2];

void clearSearchContainer()
{
    for(int i = 0; i < 11000; i++)
    {
        searchContainer[i][0] = -1;
        searchContainer[i][1] = 0;
    }
}

string trimCsvContents(string text) 
{
    int index = text.find(" in ");
    string trimmedString = "";

    if (index == string::npos)
    {
        return text;
    }

    index = index + 4;

    for (int i = index; text[i] != '.'; i = i + 1)
    {
        trimmedString = trimmedString + text[i];
    }
    return trimmedString;
}

string *extractJobDescription(string filteredFileContents[11000], string filepath)
{
    string buffer;
    int count = 0;
    bool ignoreFirst = false;

    ifstream fileContents(filepath);
    while (getline(fileContents, buffer))
    {
        if(ignoreFirst == true)
        {
            buffer = trimCsvContents(buffer);
            filteredFileContents[count] = buffer;
            count = count + 1;
        }
        ignoreFirst = true;
    }
    return filteredFileContents;
}

string* split(string& inputText, string outputText[], char delimiter)
{
    int index = 0;
    string buffer = "";

    for(char character : inputText)
    {
        if(character == delimiter)
        {
            outputText[index] = buffer;
            index = index + 1;
            buffer = "";
        }
        else
        {
            buffer = buffer + character;
        }
    }

    outputText[index] = buffer;
    return outputText;
}

void helpResumeFindJob()
{
    clearSearchContainer();
    cout << "Select resume: " << endl;
    int input = 0;
    cin >> input;
    if(input < 2)
    {
        input = 0;
    }
    else
    {
        input = input - 2;
    }

    // for(string skill: listOfFilteredAndSplitResume[input]) //per skill
    // {
    //     for(int i = 0; listOfFilteredAndSplitJobDescription[i][1] != ""; i++) //per job
    //     {
    //         searchContainer[i][0] = i;
    //         for(int j = 0; listOfFilteredAndSplitJobDescription[i][j] != ""; j++) //per job requirement
    //         {
    //             if(listOfFilteredAndSplitJobDescription[i][j] == skill)
    //             {
    //                 searchContainer[i][1] = searchContainer[i][1] + 1;
    //             }
    //         }
    //     }
    // }


    for(int i = 0; listOfFilteredAndSplitJobDescription[i][0] != "" ; i++) //repeat for each job
    {
        int matchingScore = 0;
        for(int j = 0; listOfFilteredAndSplitResume[input][j] != "" ; j++) //across each resume skill
        {
            for(int k = 0; listOfFilteredAndSplitJobDescription[i][k] != ""; k++) //across each current job's skill
            {
                if(listOfFilteredAndSplitResume[input][j] == listOfFilteredAndSplitJobDescription[i][k])
                {
                    matchingScore++;
                    break;
                }
            }
        }
        searchContainer[i][0] = i;
        searchContainer[i][1] = matchingScore;
    }


    int count2 = 0;
    for(int i = 0; searchContainer[i][0] != -1; i++)
    {
        count2 = count2 + 1;
    }
    //
    // for(int i = 0; i < count2; i++)
    // {
    //     int temp[2];
    //     if(searchContainer[i+1][1] < searchContainer[i][1])
    //     {
    //         temp[0] = searchContainer[i+1][0];
    //         temp[1] = searchContainer[i+1][1];
    //         searchContainer[i+1][0] = searchContainer[i][0];
    //         searchContainer[i+1][1] = searchContainer[i][1];
    //         searchContainer[i][0] = temp[0];
    //         searchContainer[i][1] = temp[1];
    //     }
    // }


    for (int i = 0; i < count2 - 1; i++)
    {
        for (int j = i + 1; j < count2; j++)
        {
            if (searchContainer[j][1] > searchContainer[i][1])
            {
                swap(searchContainer[j][0], searchContainer[i][0]);
                swap(searchContainer[j][1], searchContainer[i][1]);
            }
        }
    }


    // for(int i = 0; i < 100; i++)
    // {
    //     cout << searchContainer[i][0] << endl;
    //     cout << searchContainer[i][1] << endl;
    // }

    cout << "The given resume" << endl;
    cout << listOfFilteredResume[input] << endl;
    cout << "Search result:" << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << i+1 << ". " << endl;
        cout << "The job in question: " << endl;
        cout << listOfFilteredJobDescription[searchContainer[i][0]] << endl;
        cout << "Job ID: " << searchContainer[i][0]+2 << endl;
    }
}

int main()
{
    cout << "Trimmed Job Requirements: " << endl;
    extractJobDescription(listOfFilteredJobDescription, "job_description.csv");
    cout << "Trimmed Resume Requirements: " << endl;
    extractJobDescription(listOfFilteredResume, "resume.csv");


    // int maxEntries = 1;
    // for(string string : listOfFilteredResume) //find max entries
    // {
    //     int tempMaxEntries = 1;
    //     for(char character : string)
    //     {
    //         if(character == ',')
    //         {
    //             tempMaxEntries = tempMaxEntries + 1;
    //         }
    //     }
    //     if(tempMaxEntries > maxEntries)
    //     {
    //         maxEntries = tempMaxEntries;
    //     }
    // }
    // for(string string : listOfFilteredJobDescription) //find max entries
    // {
    //     int tempMaxEntries = 1;
    //     for(char character : string)
    //     {
    //         if(character == ',')
    //         {
    //             tempMaxEntries = tempMaxEntries + 1;
    //         }
    //     }
    //     if(tempMaxEntries > maxEntries)
    //     {
    //         maxEntries = tempMaxEntries;
    //     }
    // }

    for(int i = 0; listOfFilteredResume[i] != ""; i++)
    {
        split(listOfFilteredResume[i] ,listOfFilteredAndSplitResume[i], ',');
        for (int j = 0; listOfFilteredAndSplitResume[i][j] != ""; j++)
        {
            if(j != 0)
            {
                listOfFilteredAndSplitResume[i][j].erase(0, 1);
            }
        }
    }
    for(int i = 0; listOfFilteredJobDescription[i] != ""; i++)
    {
        split(listOfFilteredJobDescription[i] ,listOfFilteredAndSplitJobDescription[i], ',');
        for (int j = 0; listOfFilteredAndSplitJobDescription[i][j] != ""; j++)
        {
            if(j != 0)
            {
                listOfFilteredAndSplitJobDescription[i][j].erase(0, 1);
            }
        }
    }

    // for(int i = 0; i < 10; i++)
    // {
    //     cout << listOfFilteredJobDescription[i] << endl;
    // }
    // for(int i = 0; i < 10; i++)
    // {
    //     cout << listOfFilteredResume[i] << endl;
    // }
    // for(int i = 0; i < 10; i++)
    // {
    //     for(int j = 0; listOfFilteredAndSplitResume[i][j] != ""; j++)
    //     {
    //         cout << listOfFilteredAndSplitResume[i][j] << endl;
    //     }
    // }

    cout << "Job Matching System\n1. Top 10 best-matched jobs (Rule-based)\n2. Top 10 worst-matched jobs (Rule-based)\n3. Filter jobs for a resume (Rule-based)\n4. Screen reumes for a job (Rule-based)\n5. Boolean search for jobs\n6. Boolean search for resumes\n7. Show all keywords\n8. Add new keyword\n9. Show invalid resumes\n10. Exit\nEnter your choice: ";
    int choice;
    cin >> choice;
    cout << choice;
    if(choice == 3)
    {
        helpResumeFindJob();
    }
    else if(choice == 4)
    {

    }
}
