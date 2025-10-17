#include <iostream>
#include <string>
#include <fstream>

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

    ifstream fileContents(filepath);
    while (getline(fileContents, buffer))
    {
        buffer = trimCsvContents(buffer);
        filteredFileContents[count] = buffer;
        count = count + 1;
    }
    return filteredFileContents;
}

int main()
{

    string listOfFilteredJobDescription[11000];
    string listOfFilteredResume[11000];
    cout << "Trimmed Job Requirements: " << endl;
    extractJobDescription(listOfFilteredJobDescription, "job_description.csv");
    for (int i = 0; i < 10; i++)
    {
        cout << listOfFilteredJobDescription[i] << endl;
    }
    cout << "Trimmed Resume Requirements: " << endl;
    extractJobDescription(listOfFilteredResume, "resume.csv");
    for (int i = 0; i < 10; i++)
    {
        cout << listOfFilteredResume[i] << endl;
    }
}
