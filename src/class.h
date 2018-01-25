// inbuilt libraries
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<ctime>

using namespace std;

// ADT for linked list
class LinkedList
{
protected:
	int Size;
public:
	LinkedList();
	~LinkedList();
	bool LinkedListIsEmpty();
};

// structure for event node
struct EventNode
{
	int EventID;
	string EventName;
	EventNode * Next;
};

// ADT for event list
class EventList : public LinkedList
{
private:
	EventNode * Head;
	EventNode * PtrTo (int);
public:
	class EventListError {};
	EventList();
	~EventList();
	void EventListInsert(bool&);
	EventNode * EventListSearchID (int);
	void EventListRetrieve(int,string&, bool&);
	void EventListDelete(int,bool&);
	void EventListDisplay();
	int EventListLength();
	void SaveEventList(string);
};

// structure for participant node
struct ParticipantNode
{
	int ParticipantID;
	string ParticipantName;
	int PreferenceList[3]; 
	ParticipantNode * Next;
};

// ADT for participant list
class ParticipantList : public LinkedList
{
private:
	ParticipantNode * Head;
	ParticipantNode * PtrTo (int);
public:
	class ParticipantListError {};
	ParticipantList();
	~ParticipantList();
	void ParticipantListInsert(EventList&,bool&);
	void ParticipantListDelete(int,bool&);
	void ParticipantListDisplay(EventList&);
	int ParticipantListLength();
	int ParticipantFirstPreference(int);
	void SaveParticipantList(string);
};

// structure for schedule
struct EventSchedule
{
	int StartTime;
	int EndTime;
	int EventID;
};

// prototypes for main functions
void createeventlist(char&,bool&,EventList&);
void createparticipantlist(char&,bool&,EventList&,ParticipantList&);
void createnumberofpreferencesarray(EventList&,ParticipantList&,int*);
void createnumberofpreferencessortedarray(EventList&,int*,int*);
int returneventid(int*,int*,bool*,EventList&);
void instructions();
