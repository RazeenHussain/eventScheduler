#include"class.h"

int main()
{
	system("color 0a");

	srand(time(0));
	// splash screen
	cout<<"\n\n\n\t\t\t     W E L C O M E   T O\n\n\t\t\tE V E N T   S C H E D U L E R\n\n\n\n\n\n\n\t\t\t\t  CREATED BY\n\n\t\t\t\tRAZEEN HUSSAIN\n\n\t\t\t  2011-NUST-CEME-BE-MTS-363\n\n\n\n\n\t\t\t";
	system("pause");
	system("cls");
	// instructions
	instructions();
	// festival name input
	string festivalname;
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\tENTER FESTIVAL NAME : ";
	cin>>festivalname;
	system("cls");
	
	char input='a';
	bool Success;
	// creation of event list
	EventList events;
	createeventlist(input, Success, events);
	// creation of participant list
	ParticipantList participants;
	createparticipantlist(input, Success, events, participants);
	// creation of arrays to help generate festival schedule
	int * preferenceptr = new int[events.EventListLength()];
	createnumberofpreferencesarray(events,participants,preferenceptr);
	int * preferenceptrsorted = new int[events.EventListLength()];
	createnumberofpreferencessortedarray(events,preferenceptr,preferenceptrsorted);
	// input of schedule parameters
	int slots;
	int parallelslots;
	cout<<"\n\n\n\n\n\t  EVENT SCHEDULE PARAMETERS\n\n\n\n";
	cout<<"\tNUMBER OF AVAILABLE SLOTS : ";
	cin>>slots;
	cout<<"\tNUMBER OF PARALLEL SLOTS : ";
	cin>>parallelslots;
	// creation of festival schedule
	EventSchedule*  schedulearray= new EventSchedule[slots*parallelslots];
	EventSchedule** schedule = new EventSchedule*[slots];
	for (int i = 0; i < slots; ++i)
		schedule[i] = schedulearray + parallelslots*i;
	int start=1000;
	int end=1200;
	for (int i=0;i<slots;i++)
	{
		for(int j=0;j<parallelslots;j++)
		{
			schedule[i][j].StartTime=start;
			schedule[i][j].EndTime=end;
			schedule[i][j].EventID=0;
		}
		start+=200;
		end+=200;
		if (end>2000)
		{
			start=1000;
			end=1200;
		}
	}
	bool * eventtrackingptr = new bool[events.EventListLength()];
	for (int i=0;i<events.EventListLength();i++)
		eventtrackingptr[i]=false;
	for (int i=0; i<slots;i++)
	{
		schedule[i][0].EventID=returneventid(preferenceptr,preferenceptrsorted,eventtrackingptr,events);
	}
	int x,y,check;
	while(1)
	{
		check=0;
		x=rand()%slots;
		y=rand()%(parallelslots-1)+1;
		if (schedule[x][y].EventID==0)
			schedule[x][y].EventID=returneventid(preferenceptr,preferenceptrsorted,eventtrackingptr,events);
		else 
			continue;
		for (int i=0;i<slots;i++)
		{
			for (int j=0; j<parallelslots;j++)
			{
				if (schedule[i][j].EventID!=0)
				{
					check++;
				}
			}
		}
		if (check==events.EventListLength())
			break;
	}
	system("cls");
		cout<<"\n\n\n\n\n\t\tGENERATING FESTIVAL SCHEDULE";
	for (int i=0;i<5;i++)
	{
		cout<<" .";			   
		for(double wait=0;wait<222222222;wait++)
		{}
	}
	system("cls");
	cout<<"\n\n\t\tEVENT SCHEDULE\n\n";
	string name;
	for (int i=0;i<slots;i++)
	{
		for(int j=0;j<parallelslots;j++)
		{
			if (schedule[i][j].EventID != 0)
			{
				cout<<"\tEVENT ID : "<<schedule[i][j].EventID<<"\n";
				events.EventListRetrieve(schedule[i][j].EventID,name,Success);
				cout<<"\tEVENT NAME : "<<name<<"\n";
				cout<<"\tSTART TIME : "<<schedule[i][j].StartTime<<"\n";
				cout<<"\tEND TIME : "<<schedule[i][j].EndTime<<"\n\n";
			}
		}
		cout<<endl;
	}
	cout<<"\n\t";
	// saving festival details on different text files
	string filename;
	filename=festivalname+"Events.txt";
	events.SaveEventList(filename);
	filename.clear();
	filename=festivalname+"Participants.txt";
	participants.SaveParticipantList(filename);
	filename.clear();
	filename=festivalname+"Schedule.txt";
	ofstream F(filename);
	for (int i=0;i<slots;i++)
	{
		for(int j=0;j<parallelslots;j++)
		{	
			if (schedule[i][j].EventID != 0)
			{
				F<<"\tEVENT ID : "<<schedule[i][j].EventID<<"\n";
				events.EventListRetrieve(schedule[i][j].EventID,name,Success);
				F<<"\tEVENT NAME : "<<name<<"\n";
				F<<"\tSTART TIME : "<<schedule[i][j].StartTime<<"\n";
				F<<"\tEND TIME : "<<schedule[i][j].EndTime<<"\n\n";
			}
		}
		F<<"\n";
	}
	F.close( );

	return 0;
}	// end of program
