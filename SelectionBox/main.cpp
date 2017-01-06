/****************************************************
 * SelectionBox contains a pointer to a StatusBar list
 * the number of StatusBars are specified in the SelectionBox
 * constructor then details can be specified by setStatusBarDetails
 *
 * after building this it seems a rather cumbersome way to do it
 * having to access the details through two interfaces.
 ****************************************************/

#include <cstdio>

/****************************************************
 * StatusBar
 */
class StatusBar //: public SelectionBox
{
public:
	void setDetails(int i, bool v);
	int getID() {return id;};
	void setVis(bool);
private:
	int id;
	bool bVisible;
	//...
	//other stuff
	//...
};

//set the details of the status bar
void StatusBar::setDetails(int IDin, bool v) //why is ID a param? why whould you want to change the id of it, it has an array num!
{
	id = IDin;
	bVisible = v;
}

void StatusBar::setVis(bool on)
{
	if(on)
	{
		bVisible = true ;
	}
	else
	{
		bVisible = false ;
	}
}

/****************************************************
 * SelectionBox
 */
class SelectionBox
{
public:
	SelectionBox(int i);
	bool setStatusBarDetails(int bar, int IDin, bool v);
	int getStatusBarID(int bar);
	void setVis(bool);
	bool getVisState() {return bVisible;};
private:
	StatusBar* sb;
	int iNumBars;
	bool bVisible;
};

//specify the number of status bars for this SelectionBox
SelectionBox::SelectionBox(int i)
{
	iNumBars = i;
	sb = new StatusBar[iNumBars];
}

//sets the details for a specified status bar
bool SelectionBox::setStatusBarDetails(int bar, int IDin, bool v)
{
	if(bar >= iNumBars)
		return false;
	else
	{
		sb[bar].setDetails(IDin, v);
		return true;
	}
}

int SelectionBox::getStatusBarID(int bar)
{
	if(bar >= iNumBars)
		return false;
	else
		return sb[bar].getID();

}

void SelectionBox::setVis(bool on)
{
	if(on)
	{
		bVisible = true ;
		sb->setVis(true);
	}
	else
	{
		bVisible = false ;
		sb->setVis(false);
	}

//	bVisible = on ;
//  sb.setVis(on);
}


/****************************************************
 * Main
 */
void main()
{
	const MAX_SELECT = 10 ; 

	SelectionBox selectBox(3);	//create a selection box with 3 status bars

	SelectionBox *ship[MAX_SELECT] = { new SelectionBox(3) } ;

/*	for(int i = 0; i < MAX_SELECT; i++)
	{
		 new SelectionBox(3) } ;
	}
	ship->setVis(true);
*/	

	if(selectBox.setStatusBarDetails(0, 4, true))
	{
		printf("Status bar 0 has been set\nid is %d\n", selectBox.getStatusBarID(0));
	}
	else
		printf("Status bar 0 could not be set");

	printf("Status bar 0 is visable :%s\n", selectBox.getVisState() ? "true" : "false");
	selectBox.setVis(false);
	printf("Status bar 0 is visable :%s\n", selectBox.getVisState() ? "true" : "false");

	selectBox.setStatusBarDetails(0,4,false);

	delete ship;
}