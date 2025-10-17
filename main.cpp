#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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



int main()
{
    string listOfFilteredJobDescription[11000];
    string listOfFilteredResume[11000];
    cout << "Trimmed Job Requirements: " << endl;
    extractJobDescription(listOfFilteredJobDescription, "job_description.csv");
    cout << "Trimmed Resume Requirements: " << endl;
    extractJobDescription(listOfFilteredResume, "resume.csv");

    for (int i = 0; i < 10; i++)
    {
        cout << listOfFilteredJobDescription[i] << endl;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << listOfFilteredResume[i] << endl;
    }

    int maxEntries = 1;
    for(string string : listOfFilteredResume) //find max entries
    {
        int tempMaxEntries = 1;
        for(char character : string)
        {
            if(character == ',')
            {
                tempMaxEntries = tempMaxEntries + 1;
            }
        }
        if(tempMaxEntries > maxEntries)
        {
            maxEntries = tempMaxEntries;
        }
    }
    for(string string : listOfFilteredJobDescription) //find max entries
    {
        int tempMaxEntries = 1;
        for(char character : string)
        {
            if(character == ',')
            {
                tempMaxEntries = tempMaxEntries + 1;
            }
        }
        if(tempMaxEntries > maxEntries)
        {
            maxEntries = tempMaxEntries;
        }
    }

    string listOfFilteredAndSplitJobDescription[11000][maxEntries];
    string listOfFilteredAndSplitResume[11000][maxEntries];
    for()

    cout << "Job Matching System\n1. Top 10 best-matched jobs (Rule-based)\n2. Top 10 worst-matched jobs (Rule-based)\n3. Filter jobs for a resume (Rule-based)\n4. Screen reumes for a job (Rule-based)\n5. Boolean search for jobs\n6. Boolean search for resumes\n7. Show all keywords\n8. Add new keyword\n9. Show invalid resumes\n10. Exit\nEnter your choice: ";
    int choice;
    cin >> choice;
    cout << choice;
}
