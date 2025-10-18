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
static string listOfKeywords[100] = {""};
static string listOfSplitKeywords[100][2] = {""};

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

string *extractKeywords(string listOfKeywords[100], string filepath)
{
    string buffer;
    int count = 0;
    bool ignoreFirst = false;

    ifstream fileContents(filepath);
    while (getline(fileContents, buffer))
    {
        if(ignoreFirst == true)
        {
            listOfKeywords[count] = buffer;
            count = count + 1;
        }
        ignoreFirst = true;
    }
    return listOfKeywords;
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
    cout << "Select resume: ";
    int input = 0;
    cin >> input;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a number!" << endl;
        return;
    }
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

    int resumeSkillCount = 0;
    for(int i = 0; listOfFilteredAndSplitResume[input][i] != "" ; i++) //count resume skills
    {
        resumeSkillCount++;
    }
    if(resumeSkillCount > 8)
    {
        resumeSkillCount = 8;
    }

    cout << "The given resume" << endl;
    cout << listOfFilteredResume[input] << endl;
    cout << "Search result:" << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << i+1 << ". " << endl;
        cout << "The job in question: " << endl;
        cout << listOfFilteredJobDescription[searchContainer[i][0]] << endl;
        cout << "Score: " << searchContainer[i][1] << "/" << resumeSkillCount << endl;
        cout << "Job ID: " << searchContainer[i][0]+2 << endl;
    }
}

void helpJobFindResume()
{
    clearSearchContainer();
    cout << "Select job: ";
    int input = 0;
    cin >> input;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a number!" << endl;
        return;
    }
    if(input < 2)
    {
        input = 0;
    }
    else
    {
        input = input - 2;
    }

    for(int i = 0; listOfFilteredAndSplitResume[i][0] != "" ; i++) //for each resume
    {
        int matchingScore = 0;
        for(int j = 0; listOfFilteredAndSplitJobDescription[input][j] != "" ; j++)  //for each job skill
        {
            for(int k = 0; listOfFilteredAndSplitResume[i][k] != ""; k++) //for each current resume's skill
            {
                if(listOfFilteredAndSplitJobDescription[input][j] == listOfFilteredAndSplitResume[i][k])
                {
                    matchingScore++;
                    break;
                }
            }
        }
        searchContainer[i][0] = i; //this resume's id is the id
        searchContainer[i][1] = matchingScore; //this resume's score is the score
    }

    int count2 = 0;
    for(int i = 0; searchContainer[i][0] != -1; i++)
    {
        count2 = count2 + 1;
    }

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

    int jobSkillCount = 0;
    for(int i = 0; listOfFilteredAndSplitJobDescription[input][i] != "" ; i++)
    {
        jobSkillCount++;
    }
    if(jobSkillCount > 8)
    {
        jobSkillCount = 8;
    }

    cout << "The given job" << endl;
    cout << listOfFilteredJobDescription[input] << endl;
    cout << "Search result:" << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << i+1 << ". " << endl;
        cout << "The resume in question: " << endl;
        cout << listOfFilteredResume[searchContainer[i][0]] << endl;
        cout << "Score: " << searchContainer[i][1] << "/" << jobSkillCount << endl;
        cout << "Resume ID: " << searchContainer[i][0]+2 << endl;
    }
}

void displayKeywords()
{
    for(int i = 0; listOfSplitKeywords[i][0] != "" ; i++)
    {
        cout << i+1 << ". " << listOfSplitKeywords[i][0];
        if(listOfSplitKeywords[i][1] == "1")
        {
            cout << " <Soft Skill>" << endl;
        }
        else if(listOfSplitKeywords[i][1] == "2")
        {
            cout << " <Tools>" << endl;
        }
        else if(listOfSplitKeywords[i][1] == "3")
        {
            cout << " <Hard Skill>" << endl;
        }
    }
}

int main()
{
    extractJobDescription(listOfFilteredJobDescription, "job_description.csv");
    extractJobDescription(listOfFilteredResume, "resume.csv");
    extractKeywords(listOfKeywords, "keywords.csv");

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
    for(int i = 0; listOfKeywords[i] != ""; i++)
    {
        split(listOfKeywords[i], listOfSplitKeywords[i], ',');
        listOfSplitKeywords[i][1].erase(0, 1);
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

    while(true)
    {
        cout << "Job Matching System\n1. Top 10 best-matched jobs (Rule-based)\n2. Top 10 worst-matched jobs (Rule-based)\n3. Filter jobs for a resume (Rule-based)\n4. Screen reumes for a job (Rule-based)\n5. Boolean search for jobs\n6. Boolean search for resumes\n7. Show all keywords\n8. Add new keyword\n9. Show invalid resumes\n10. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number!" << endl;
            continue;
        }

        if(choice == 3)
        {
            helpResumeFindJob();
        }
        else if(choice == 4)
        {
            helpJobFindResume();
        }
        else if(choice == 7)
        {
            displayKeywords();
        }
        else if(choice == 10)
        {
            break;
        }
        else
        {
            cout << "Unimplemented Feature" << endl;
        }
    }
    cout << "You have exited this program" << endl;
}
