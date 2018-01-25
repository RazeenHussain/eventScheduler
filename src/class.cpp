#include"class.h"

// functions of linked list ADT
LinkedList::LinkedList():Size(0)	
{}
LinkedList::~LinkedList()	
{}
bool LinkedList::LinkedListIsEmpty()
{
	return(Size==0);
}

// functions of event list ADT
EventNode * EventList::PtrTo (int Position)
{
	if( (Position<1) || (Position> Size ) )
	{
		return NULL;
	}
	else
	{
		EventNode* Traverse=Head;
		for(int i=1;i<Position;i++)
			Traverse=Traverse->Next;
		return Traverse;
	}
}
EventList::EventList():LinkedList(),Head(NULL)
{}
EventList::~EventList()
{
	bool Success;
	while(!LinkedListIsEmpty())
		EventListDelete(1,Success);
}
void EventList::EventListInsert(bool&Success)
{
	int NewLength=Size+1;
	EventNode * AddPosition;
	if (Head!=NULL)
		for(AddPosition=Head;AddPosition->Next!=NULL;AddPosition=AddPosition->Next)
		{}
	else
		AddPosition=Head;
	EventNode*NewPtr=new EventNode;
	Success=(NewPtr!=NULL);
	if (Success)
	{
		Size=NewLength;
		if((AddPosition==Head)&&(Size==1))
		{
			NewPtr->EventID=1;
			NewPtr->Next=Head;
			Head=NewPtr;
		}
		else
		{
			NewPtr->Next=AddPosition->Next;
			AddPosition->Next=NewPtr;
			NewPtr->EventID=AddPosition->EventID+1;
		}
		cout<<"\n\tEVENT ID : "<<NewPtr->EventID;
		cout<<"\n\tENTER EVENT NAME : ";
		cin>>NewPtr->EventName;
	}
	else
		throw EventListError();
}
void EventList::EventListRetrieve(int ID,string& DataItem,bool& Success)
{
	Success=(ID>=1);
	if(Success)
	{
		EventNode* Cur=EventListSearchID(ID);
		DataItem=Cur->EventName;
	}
	else
		throw EventListError();
}
EventNode* EventList::EventListSearchID(int ID)
{
	bool Success=false;
	if(ID<1)
	{
		throw EventListError();
		return NULL;
	}
	else
	{
		for(EventNode* Traverse=Head;Traverse!=NULL;Traverse=Traverse->Next)
		{
			if (Traverse->EventID==ID)
				return Traverse;
		}
	}
	throw EventListError();
	return NULL;
}
void EventList::EventListDelete(int Position,bool& Success)
{
	EventNode* Current;
	Success=( (Position>=1) && (Position<=Size) );
	if(Success)
	{	Size--;
		if(Position==1)
		{
			Current=Head;
			Head=Head->Next;
		}
		else 
		{
			EventNode* Previous=PtrTo(Position-1);
			Current=Previous->Next;
			Previous->Next=Current->Next;
		}
		Current->Next=NULL;
		delete Current;
		Current=NULL;
	}
	else
		throw EventListError();
}
void EventList::EventListDisplay()
{
	cout<<endl<<endl<<"\t"<<setw(10)<<"EVENT ID"<<setw(17)<<"EVENT NAME\n\n";
	EventNode* Current=Head;
	while(Current!=NULL)
	{
		cout<<"\t"<<setw(7)<<Current->EventID;
			cout<<")\t"<<Current->EventName<<endl;
		Current=Current->Next;
	}
}
int EventList::EventListLength()
{
	return Size;
}
void EventList::SaveEventList(string SaveFileName)
{
	ofstream F(SaveFileName);
	EventNode* Cur;
	for(Cur=Head; Cur!=NULL; Cur = Cur->Next)
	{
		F<<Cur->EventID<<") "<<Cur->EventName<<"\n";
	}
	F.close( );
}

// functions of participant list ADT
ParticipantNode * ParticipantList::PtrTo (int Position)
{
	if( (Position<1) || (Position> Size ) )
	{
		return NULL;
	}
	else
	{
		ParticipantNode* Traverse=Head;
		for(int i=1;i<Position;i++)
			Traverse=Traverse->Next;
		return Traverse;
	}

}
ParticipantList::ParticipantList():LinkedList(),Head(NULL)
{}
ParticipantList::~ParticipantList()
{
	bool Success;
	while(!LinkedListIsEmpty())
		ParticipantListDelete(1,Success);
}
void ParticipantList::ParticipantListInsert(EventList& events,bool& Success)
{
	int NewLength=Size+1;
	ParticipantNode * AddPosition;
	if (Head!=NULL)
		for(AddPosition=Head;AddPosition->Next!=NULL;AddPosition=AddPosition->Next)
		{}
	else
		AddPosition=Head;
	ParticipantNode*NewPtr=new ParticipantNode;
	Success=(NewPtr!=NULL);
	if (Success)
	{
		events.EventListDisplay();
		Size=NewLength;
		if((AddPosition==Head)&&(Size==1))
		{
			NewPtr->ParticipantID=1;
			NewPtr->Next=Head;
			Head=NewPtr;
		}
		else
		{
			NewPtr->Next=AddPosition->Next;
			AddPosition->Next=NewPtr;
			NewPtr->ParticipantID=AddPosition->ParticipantID+1;
		}
		cout<<"\n\tPARTICIPANT ID : "<<NewPtr->ParticipantID;
		cout<<"\n\tENTER PARTICIPANT NAME : ";
		cin>>NewPtr->ParticipantName;
		cout<<"\tENTER PARTICIPANT PREFERENCE LIST: \n\t(enter event id of preferred event) \n\t(enter '0' if no more preferences)\n";
		for(int i=0; i<3; i++)
		{
			cout<<"\t"<<setw(5)<<i+1<<")\t";
			cin>>NewPtr->PreferenceList[i];
			while ((NewPtr->PreferenceList[i]<0)||(NewPtr->PreferenceList[i]>events.EventListLength()))
			{
				cout<<"\n\tINCORRECT EVENT ID\n\tPLEASE RE-INPUT\n";
				cout<<"\t"<<setw(5)<<i+1<<")\t";
				cin>>NewPtr->PreferenceList[i];
			}
			for(int j=0;j<i;j++)
			{
				if (NewPtr->PreferenceList[i]==NewPtr->PreferenceList[j])
				{
					cout<<"\n\tEVENT ID ALREADY INPUT\n\tPLEASE RE-INPUT A DIFFERENT ONE\n";
					cout<<"\t"<<setw(5)<<i+1<<")\t";
					cin>>NewPtr->PreferenceList[i];
					continue;
				}
			}
			if (NewPtr->PreferenceList[i]==0)
			{
				for (int j=i; j<3; j++)
				{
					NewPtr->PreferenceList[j]=0;
				}
				break;
			}
		}
	}
	else
		throw ParticipantListError();
}
void ParticipantList::ParticipantListDelete(int Position,bool& Success)
{
	ParticipantNode* Current;
	Success=( (Position>=1) && (Position<=Size) );
	if(Success)
	{	Size--;
		if(Position==1)
		{
			Current=Head;
			Head=Head->Next;
		}
		else 
		{
			ParticipantNode* Previous=PtrTo(Position-1);
			Current=Previous->Next;
			Previous->Next=Current->Next;
		}
		Current->Next=NULL;
		delete Current;
		Current=NULL;
	}
}
void ParticipantList::ParticipantListDisplay(EventList& events)
{
	bool Success;
	cout<<endl;
	string eventname;
	ParticipantNode * Current=Head;
	while(Current!=NULL)
	{
		cout<<"\nPARTICIPANT ID : "<<Current->ParticipantID<<"\n";
		cout<<"PARTICIPANT NAME : "<<Current->ParticipantName<<"\n";
		cout<<"PREFERENCES : \n";
		for (int i=0;i<3;i++)
		{
			eventname.clear();
			if (Current->PreferenceList[i]>0)
			{
				events.EventListRetrieve(Current->PreferenceList[i],eventname,Success);
				cout<<setw(5)<<i+1<<")\t"<<eventname<<"\n";
			}
		}
		Current=Current->Next;
	}
}
int ParticipantList::ParticipantListLength()
{
	return Size;
}
int ParticipantList::ParticipantFirstPreference(int eventid)
{
	int number=0;
	for (ParticipantNode * Current = Head; Current!=NULL; Current=Current->Next)
	{
		if (Current->PreferenceList[0]==eventid)
			number++;
	}
	return number;
}
void ParticipantList::SaveParticipantList(string SaveFileName)
{
	ofstream F(SaveFileName);
	ParticipantNode* Cur;
	for(Cur=Head; Cur!=NULL; Cur = Cur->Next)
	{
		F<<Cur->ParticipantID<<") "<<Cur->ParticipantName<<"    ";
		for(int i=0; i<3; i++)
		{
			F<<" "<<Cur->PreferenceList[i];
		}
		F<<"\n";
	}
	F.close( );
}

// function bodies of main function
void createeventlist(char& input,bool& Success,EventList& events)
{
	cout<<"\n\n\t       PLEASE ENTER \n\t   DETAILS OF THE EVENTS \n\tTO BE HELD IN THE FESTIVAL\n\n\n\n\t";
	system("pause");
	while(1)
	{
		system("cls");
		try
		{
			events.EventListInsert(Success);
		}
		catch (EventList::EventListError)
		{
			cout<<"\n\n\t\tERROR\n\n";
		}
		while (1)
		{
			cout<<"\n\n\tDo You Want To Enter Another Event? (Y/N)\n\t\t";
			cin>>input;
			if (input=='n' || input=='N')
			{
				break;
			}
			else if (input=='y' || input=='Y')
			{
				break;
			}
			else
			{
				system("cls");
				cout<<"\n\n\tINCORRECT INPUT\n\tPLEASE RE-ENTER CHOICE\n\n";
			}
		}
		if (input=='n' || input=='N')
		{
			break;
		}
	}
	system("cls");
	cout<<"\n\n\n\n\n\t\tGENERATING EVENT LIST";
	for (int i=0;i<5;i++)
	{
		cout<<" .";			   
		for(double wait=0;wait<222222222;wait++)
		{}
	}
	system("cls");
	cout<<"\n\t\tLIST OF EVENTS\n";
	events.EventListDisplay();
	cout<<"\n\n\t";
	system("pause");
	system("cls");
}
void createparticipantlist(char& input,bool& Success,EventList& events,ParticipantList& participants)
{
	cout<<"\n\n\t\t PLEASE ENTER \n\t  DETAIL OF THE PARTICIPANTS \n\t TO TAKE PART IN THE FESTIVAL\n\n\n\n\t";
	system("pause");
	while(1)
	{
		system("cls");
		try
		{
			participants.ParticipantListInsert(events,Success);
		}
		catch (ParticipantList::ParticipantListError)
		{
			cout<<"\n\n\t\tERROR\n\n";
		}
		while (1)
		{
			cout<<"\n\n\tDo You Want To Enter Another Participant? (Y/N)\n\t\t";
			cin>>input;
			if (input=='n' || input=='N')
			{
				break;
			}
			else if (input=='y' || input=='Y')
			{
				break;
			}
			else
			{
				system("cls");
				cout<<"\n\n\tINCORRECT INPUT\n\tPLEASE RE-ENTER CHOICE\n\n";
			}
		}
		if (input=='n' || input=='N')
		{
			break;
		}
	}
	system("cls");
	cout<<"\n\n\n\n\n\t\tGENERATING PARTICIPANT LIST";
	for (int i=0;i<5;i++)
	{
		cout<<" .";			   
		for(double wait=0;wait<222222222;wait++)
		{}
	}
	system("cls");
	cout<<"\n\tLIST OF PARTICIPANTS\n";
	participants.ParticipantListDisplay(events);
	cout<<"\n\n";
	system("pause");
	system("cls");
}
void createnumberofpreferencesarray(EventList& events,ParticipantList& participants,int* preferenceptr)
{
	for (int i=0;i<events.EventListLength();i++)
	{
		preferenceptr[i]=participants.ParticipantFirstPreference(i+1);
	}
}
void createnumberofpreferencessortedarray(EventList& events,int* preferenceptr,int* preferenceptrsorted)
{
	for (int i=0;i<events.EventListLength();i++)
	{
		preferenceptrsorted[i]=preferenceptr[i];
	}
	int temp; 
  	for (int i = (events.EventListLength() - 1); i >= 0; i--) 
		for (int j = 1; j <= i; j++) 
			if (preferenceptrsorted[j-1] < preferenceptrsorted[j]) 
			{
				temp=preferenceptrsorted[j];
				preferenceptrsorted[j]=preferenceptrsorted[j-1];
				preferenceptrsorted[j-1]=temp;
			} 
}
int returneventid(int* preferenceptr,int* preferenceptrsorted,bool* eventtrackingptr,EventList& events)
{
	for (int i=0;i<events.EventListLength();i++)
	{
		for (int j=0;j<events.EventListLength();j++)
		{
			if ((eventtrackingptr[j]==false)&&(preferenceptr[j]==preferenceptrsorted[i]))
			{
				eventtrackingptr[j]=true;
				return (j+1);
			}
		}
	}
	return 0;
}
void instructions()
{
	cout<<"\n\n\t\t\t   I N S T R U C T I O N S\n\n";
	cout<<"\n\tThis program will propose a suggested schedule of the events taking \n\tplace in the festival.\n";
	cout<<"\n\tFirst the program will ask for the festival name.\n";
	cout<<"\n\tThen you will need to enter the names of the events taking place.\n";
	cout<<"\tThe event id will be automatically generated\n";
	cout<<"\n\tThis will be followed by displaying the event list\n";
	cout<<"\n\tThen you will need to enter the details of the participants taking \n\tpart.\n";
	cout<<"\tThe participant id will be automatically generated.\n";
	cout<<"\tEach participant can enter upto three preferences.\n";
	cout<<"\n\tThis will be followed by displaying the event list\n";
	cout<<"\n\tThen a proposed schedule of the event will be generated and displayed.\n";
	cout<<"\n\tAt the end the program will save the event list, participant list and \n\tschedule in separate text files.\n";
	cout<<"\n\n\n\tNOTE : The program tries to maximize the happiness of each participant \n\twhich is defined as each participant gets to participate in his first \n\tpreference event.\n";
	cout<<"\n\n\t\t\t\tE N J O Y !\n\n\t\t       ";
	system("pause");
	system("cls");
}
