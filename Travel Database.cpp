// Name - Jha Piyush & UID - 3035342691
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

struct nullQuota
{
	string dest;
	int tprice,sold;
};

struct most
{	
	string country;
	int tprice,tsold;
};

struct airportcode
{
	string dest,country;
	int tprice,tsold;
};

struct mflight
{
	string dest,airline,fdate,tdate,enddate;
	int price,quota,sold,tprice;
};

struct intermed
{
	string dest,airline,fdate,tdate,enddate;
	int price,quota,sold,tprice;
};

struct promo
{
	string dest,airline,fdate,tdate,enddate;
	int price,quota;
};

struct searchcommand
{
	string dest,airline,fdate,tdate,enddate;
	int price,quota;
};


void updatePromo (promo p,int&,mflight a[],ofstream&);
void appendDB (intermed im, mflight a[],int&);
void readMain (mflight a[], ifstream&, int&);
void readInterMed (intermed a, ifstream&, mflight m[],int&,nullQuota n[],int&);
void displayall (mflight a[], int& );
void convDate (string&);
void readPromo (promo a, ifstream&,int&,mflight p[],ofstream&);
void todayDate(string,mflight a[],int&);
void buy(promo p,mflight a[],int&,ofstream&,int&, nullQuota n[]);
void airportFile (ifstream&, airportcode ac[],mflight a[],int&,int&,most m[],int&, nullQuota n[],ofstream&);

void readMain (mflight a[], ifstream& fin, int& c)
{	
	fin.clear();
	fin.seekg(0,ios::beg);
	string temporary;
	getline(fin,temporary);
	c=0;
	while(fin.good())
	{
		getline(fin,a[c].dest,',');
		getline(fin,a[c].airline,',');
		getline(fin,a[c].fdate,',');
		getline(fin,a[c].tdate,',');
		string temp;
		getline(fin,temp,',');
		stringstream no;
		no << temp;
		no >> a[c].price;
		getline(fin,a[c].enddate,',');
		string temp1;
		getline(fin,temp1);
		stringstream no1;
		no1 << temp1;
		no1 >> a[c].quota;
		if (a[c].quota == 0)
		{
			a[c].dest = "";
			a[c].airline = "";
			a[c].fdate = "";
			a[c].tdate = "";
			a[c].price = 0;
			c--;
		}
		a[c].sold = 0;
		a[c].tprice = 0;
		c++;
	}
}

void readInterMed (intermed a, ifstream& fin, mflight m[],int& c,nullQuota n[],int& nc)
{	
		char check;
		fin >> check;
		if(check == '#')
		{ 
			string space;
			getline(fin,space);
		}
		else if(check >= 'A' && check <= 'Z')
		{
			string temp4;	
			getline(fin,temp4,',');
			a.dest = check + temp4;
			getline(fin,a.airline,',');
			getline(fin,a.fdate,',');
			getline(fin,a.tdate,',');
			string temp;
			getline(fin,temp,',');
			stringstream no;
			no << temp;
			no >> a.price;
			getline(fin,a.enddate,',');
			string temp2;
			getline(fin,temp2,',');
			stringstream no2;
			no2 << temp2;
			no2 >> a.quota;
			string temp1;
			getline(fin,temp1,',');
			stringstream no1;
			no1 << temp1;
			no1 >> a.sold;
			string ptemp;
			getline(fin,ptemp);
			stringstream nop;
			nop << ptemp;
			nop >> a.tprice;
			appendDB(a,m,c);
			if(a.quota == 0)
			{
				n[nc].dest = a.dest;
				n[nc].sold = a.sold;
				n[nc].tprice = a.tprice;
				nc++;
			}
		}
		else if(check >= '1' && check <= '9')
		{
			string tempdate;
			getline(fin,tempdate);
			string date;
			date = check + tempdate;
			int count = 0;
			for (int i = 0; i < c - count; i++)
			{	
				if(m[i].enddate < date)
				{	count++;
					for (int j = i; j < c-1 ; j++)
					{ 
						
							m[j].dest = m[j+1].dest;
							m[j].airline = m[j+1].airline;
							m[j].fdate = m[j+1].fdate;
							m[j].tdate = m[j+1].tdate;
							m[j].enddate = m[j+1].enddate;
							m[j].price = m[j+1].price;
							m[j].quota = m[j+1].quota;
							m[j].sold = m[j+1].sold;
							m[j].tprice = m[j+1].tprice;	
					
					}
				i=-1;
				}		
			}
			c = c - count;
		}
		
}

void appendDB (intermed im, mflight a[],int& c)
{	bool valid = true;
	int count = 0;
	for (int i = 0; i < c; i++)
	{
		if((im.dest == a[i].dest) && (im.airline == a[i].airline) && (im.enddate == a[i].enddate) && (im.price == a[i].price) && (im.fdate == a[i].fdate) && (im.tdate == a[i].tdate) && (im.quota>0))
			{
				a[i].quota = im.quota;
				a[i].sold = im.sold;
				a[i].tprice = im.tprice;
				valid = false;
			}
	}

	for (int i = 0; i < c - count; i++)
		{
			if ((im.dest == a[i].dest) && (im.airline == a[i].airline) && (im.enddate == a[i].enddate) && (im.price == a[i].price) && (im.fdate == a[i].fdate) && (im.tdate == a[i].tdate) && (im.quota==0))
			{	
				valid = false;
				count++;
				for (int j = i; j < c-1; j++)
				{	
					
						a[j].dest = a[j+1].dest;
						a[j].airline = a[j+1].airline;
						a[j].fdate = a[j+1].fdate;
						a[j].tdate = a[j+1].tdate;
						a[j].enddate = a[j+1].enddate;
						a[j].price = a[j+1].price;
						a[j].quota = a[j+1].quota;
						a[j].sold = a[j+1].sold;
						a[j].tprice = a[j+1].tprice;
						
				}
				i=-1;	
			}		
		}
		c = c - count;	

	if(valid && im.quota>0)
	{
		a[c].dest = im.dest;
		a[c].airline = im.airline;
		a[c].fdate = im.fdate;
		a[c].tdate = im.tdate;
		a[c].enddate = im.enddate;
		a[c].price = im.price;
		a[c].quota = im.quota;
		a[c].sold = im.sold;
		a[c].tprice = im.tprice;
		c++;
	}
}

void displayall (mflight a[], int& c)
{	
	for (int i = 0; i < c; i++)
	{	
		cout << "["<<i << "]" << " " << a[i].dest << "-" << a[i].airline << "-" << a[i].fdate << "-" << a[i].tdate << " " << "HKD "<< a[i].price << ", promotion expires " <<  a[i].enddate << "," << a[i].quota <<" Quota" << endl;
	}
	cout << "total " << c << " records" << endl;
}


void convDate (string& date)
{	
	string temp = date.substr(5,3);
	if(temp == "Jan")
	{
		date.replace(4,5,"01");
	}
	else if(temp == "Feb")
	{
		date.replace(4,5,"02");
	}
	else if(temp == "Mar")
	{
		date.replace(4,5,"03");
	}
	else if(temp == "Apr")
	{
		date.replace(4,5,"04");
	}
	else if(temp == "May")
	{
		date.replace(4,5,"05");
	}
	else if(temp == "Jun")
	{
		date.replace(4,5,"06");
	}
	else if(temp == "Jul")
	{
		date.replace(4,5,"07");
	}
	else if(temp == "Aug")
	{
		date.replace(4,5,"08");
	}
	else if(temp == "Sep")
	{
		date.replace(4,5,"09");
	}
	else if(temp == "Oct")
	{
		date.replace(4,5,"10");
	}
	else if(temp == "Nov")
	{
		date.replace(4,5,"11");
	}
	else
	{
		date.replace(4,5,"12");
	}
}

void readPromo (promo a, ifstream& fin,int& c,mflight p[],ofstream& fout2)
{	
	char check;	
	string air;
	getline(fin,air);
	a.airline = air.substr(8);
	string deal;
	getline(fin,deal);
	deal = deal.substr(10);
	if(deal.length() > 10)
	{
		convDate(deal);
	}
	else
	{
		string temp;
		temp = deal.substr(9);
		string temp1;
		temp1 = "0" + temp;
		deal.replace(9,2,temp1);
		convDate(deal);
	}
	a.enddate = deal;
	fin >> check;
	while(fin.good())
	{	
		if(check != '#')
		{	
		string temp;
		getline(fin,temp,',');
		a.dest = check + temp;
		string temp1;
		getline(fin,temp1,',');
		string d1,d2;
		int pos = temp1.find("to");
		if(pos == 11)
		{
			d1 = temp1.substr(0,10);
			string num = d1.substr(9);
			string newnum = "0" + num;
			d1.replace(9,2,newnum);
			d2 = temp1.substr(14);
			string dtemp = d2.substr(9);
			stringstream conv;
			conv << dtemp;
			int temd;
			conv >> temd;
			if(temd < 10)
			{	
				string num = d2.substr(9,1);
				string newnum = "0" + num;
				d2.replace(9,2,newnum);
			}	
		}
		else
		{
			d1 = temp1.substr(0,11);
			d2 = temp1.substr(15);
			string dtemp = d2.substr(9);
			stringstream conv;
			conv << dtemp;
			int temd;
			conv >> temd;
			if(temd < 10)
			{	
				string num = d2.substr(9,1);
				string newnum = "0" + num;
				d2.replace(9,2,newnum);
			}	
		}
		
		convDate(d1);
		convDate(d2);
		a.fdate = d1;
		a.tdate = d2;
		string temp2;
		getline(fin,temp2,',');
		temp2 = temp2.substr(4);
		stringstream no;
		no << temp2;
		no >> a.price;
		string temp3;
		getline(fin,temp3);
		temp3 = temp3.substr(6);
		stringstream no1;
		no1 << temp3;
		no1 >> a.quota;
		}
		if(check == '#')
		{
		string edate;
		getline(fin,edate);
		edate = edate.substr(10);
		if(edate.length() > 10)
		{
			convDate(edate);
		}
		else
		{
			string temp;
			temp = edate.substr(9);
			string temp1;
			temp1 = "0" + temp;
			edate.replace(9,2,temp1);
			convDate(edate);
		}
		a.enddate = edate;
		string temp;
		getline(fin,temp,',');
		a.dest = temp;
		string temp1;
		getline(fin,temp1,',');
		string d1,d2;
		int pos = temp1.find("to");
		if(pos == 11)
		{
			d1 = temp1.substr(0,10);
			string num = d1.substr(9,1);
			string newnum = "0" + num;
			d1.replace(9,2,newnum);
			d2 = temp1.substr(14);
			string dtemp = d2.substr(9);
			stringstream conv;
			conv << dtemp;
			int temd;
			conv >> temd;
			if(temd < 10)
			{	
				string num = d2.substr(9,1);
				string newnum = "0" + num;
				d2.replace(9,2,newnum);
			}	
		}
		else
		{
			d1 = temp1.substr(0,11);
			d2 = temp1.substr(15);
			string dtemp = d2.substr(9);
			stringstream conv;
			conv << dtemp;
			int temd;
			conv >> temd;
			if(temd < 10)
			{	
				string num = d2.substr(9,1);
				string newnum = "0" + num;
				d2.replace(9,2,newnum);
			}	
		}
		convDate(d1);
		convDate(d2);
		a.fdate = d1;
		a.tdate = d2;
		string temp2;
		getline(fin,temp2,',');
		temp2 = temp2.substr(4);
		stringstream no;
		no << temp2;
		no >> a.price;
		string temp3;
		getline(fin,temp3);
		temp3 = temp3.substr(6);
		stringstream no1;
		no1 << temp3;
		no1 >> a.quota;
		}
		fin >> check;
		if(check == '#')
		{	string temp4;
			getline(fin,temp4);
		}

		updatePromo(a,c,p,fout2);
	}
}

void updatePromo (promo p,int& c,mflight a[],ofstream& fout2)
{	bool valid = false;
	for (int i = 0; i < c; i++)
	{
		if( (p.dest == a[i].dest) && (p.airline == a[i].airline) && (p.enddate == a[i].enddate) && (p.price == a[i].price) && (p.fdate == a[i].fdate) && (p.tdate == a[i].tdate))
		{	
			valid = true;
			a[i].quota += p.quota;

			fout2 << a[i].dest << "," << a[i].airline << "," << a[i].fdate << "," << a[i].tdate << "," << a[i].price << "," << a[i].enddate << "," << a[i].quota << "," << a[i].sold << "," << a[i].tprice << endl;

		}

	}
	if(!valid)
	{	
		
		a[c].dest = p.dest;
		a[c].airline = p.airline;
		a[c].fdate = p.fdate;
		a[c].tdate = p.tdate;
		a[c].enddate = p.enddate;
		a[c].price = p.price;
		a[c].quota = p.quota;
		fout2 << a[c].dest << "," << a[c].airline << "," << a[c].fdate << "," << a[c].tdate << "," << a[c].price << "," << a[c].enddate << "," << a[c].quota << "," << a[c].sold << "," << a[c].tprice << endl;
		c++;
	}
}


void todayDate(string date,mflight a[],int& c)
{	int count = 0;
	for (int i = 0; i < c - count; i++)
	{	
		if(a[i].enddate < date)
		{	count++;
			
			for (int j = i; j < c-1 ; j++)
			{
				
						a[j].dest = a[j+1].dest;
						a[j].airline = a[j+1].airline;
						a[j].fdate = a[j+1].fdate;
						a[j].tdate = a[j+1].tdate;
						a[j].enddate = a[j+1].enddate;
						a[j].price = a[j+1].price;
						a[j].quota = a[j+1].quota;
						a[j].sold = a[j+1].sold;
						a[j].tprice = a[j+1].tprice;
			}
			i=-1;
		}		
	}
	c = c - count;	
}


void buy(promo p,mflight a[],int& c,ofstream& fout,int& nc, nullQuota n[])
{
	bool valid = false;
	for (int i = 0; i < c; i++)
	{	
		if( (p.dest == a[i].dest) && (p.airline == a[i].airline) && (p.price == a[i].price) && (p.fdate == a[i].fdate) && (p.tdate == a[i].tdate))
		{	
			if(a[i].quota >= p.quota)
			{	
				valid = true;
				a[i].quota = a[i].quota - p.quota;
				a[i].sold += p.quota;
				a[i].tprice = (a[i].price)*a[i].sold*(0.9);
				fout << a[i].dest << "," << a[i].airline << "," << a[i].fdate << "," << a[i].tdate << "," << a[i].price << "," << a[i].enddate << "," << a[i].quota << "," << a[i].sold << "," << a[i].tprice << endl;
				cout << "purchased " << p.quota << " tickets" << endl;
				if(a[i].quota == 0)
				{	
					n[nc].dest = a[i].dest;
					n[nc].tprice = a[i].tprice;
					n[nc].sold = a[i].sold;
					nc++;
				}
			}
			else
			{
				cout << "not enough tickets" << endl;
				valid = true;
			}
		}
	}
	int count = 0;
	for (int i = 0; i < c - count; i++)
			{	
				if(a[i].quota == 0)
				{	count++;
					for (int j = i; j < c-1 ; j++)
					{
						
						a[j].dest = a[j+1].dest;
						a[j].airline = a[j+1].airline;
						a[j].fdate = a[j+1].fdate;
						a[j].tdate = a[j+1].tdate;
						a[j].enddate = a[j+1].enddate;
						a[j].price = a[j+1].price;
						a[j].quota = a[j+1].quota;
						a[j].sold = a[j+1].sold;
						a[j].tprice = a[j+1].tprice;
						
					}
				i=-1;
				}		
			}
	c = c - count;

	if(!valid)
	{
		cout << "Not available to purchase" << endl;
	}
}

void airportFile (ifstream& fin, airportcode ac[],mflight a[],int& c,int& cap,most m[],int& nc, nullQuota n[],ofstream& fout)
{
	fin.clear();
	fin.seekg(0,ios::beg);
	cap = 0;
	while(fin.good())
	{
		getline(fin,ac[cap].dest,',');
		getline(fin,ac[cap].country);
		ac[cap].tprice = 0;
		ac[cap].tsold = 0;
		cap++;
	}
	
	for (int i = 0; i < cap; i++)
	{	
		for (int j = 0; j < c; j++)
		{	
			if (ac[i].dest == a[j].dest)
			{
				 ac[i].tprice += a[j].tprice;
				 ac[i].tsold += a[j].sold;
			}
		}
	}

	for (int i = 0; i < cap; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (ac[i].dest == n[j].dest)
			{
				ac[i].tprice += n[j].tprice;
				ac[i].tsold += n[j].sold;
			}
		}
	}

	for (int i = 0; i < cap ; i++)
	{
		m[i].country = ac[i].country;
		for (int j = 0; j < cap; j++)
		{	
			if(m[i].country == ac[j].country)
			{
				m[i].tprice += ac[j].tprice;
				m[i].tsold += ac[j].tsold;
			}
		}
	}

	int index,count=0;
    for (int i = 0; i < cap; i++)
    {   count = 0;
        for (int j = 0; j < cap; j++)
        {   
            if(m[i].tsold >= m[j].tsold)
            {
                count++;
            }
            if(count == cap)
            {
                index = i;
            }  
        }
    }
    
    string country = m[index].country;
    int price = m[index].tprice;
    int sold = m[index].tsold;

    fout << country << endl;
    fout << "#" << sold << endl;
    fout << "$" << price << endl;

    for (int i = 0; i < cap; i++)
    {
    	ac[i].tprice = 0;
    	ac[i].tsold = 0;
    	m[i].tsold = 0;
    	m[i].tprice = 0;
    }
}


int main ()

{	
	int c=0; // counter for main database (c-counter)
	int nc = 0; // counter for null Quota (nc)
	int cap=0; // counter for airport code file (cap)
	int cs = 1; // counter for search
	mflight a[500]; // main dabatase
	airportcode ac[200]; // airport code file database
	most m[200]; // most file database
	nullQuota n[500]; // all the null quota entries holder
	searchcommand s[500]; // for search and refined search
	promo p; // reading promo and also used for buy
	intermed im; // reading intermediate file
	string command; // the command as an input from user
	ifstream fin;
	ofstream fout;
	ifstream fin1;
	ifstream fin2;
	ofstream fout2;
	ofstream fout3;
	ifstream fin3;
	fin2.open("intermed.txt");
	fin.open("mainDB.csv");
	if(fin2.fail()) 
	{	
		readMain (a,fin,c);
	}
	else
	{	
		readMain (a,fin,c);
		while(fin2.good())
		{
			readInterMed (im,fin2,a,c,n,nc);
		}
		fin2.close();
	}

	cin >> command;

	while(command != "end")
	{
		if(command == "all")
		{	
			displayall (a,c);
		}
		if(command == "add")
		{	string temp,filename;
			cin >> temp >> filename;
			fin1.open(filename.c_str());
			if (fin1.fail())
			{
				cout << "Error opening file" << endl;
				exit(1);	
			}
			fout2.open("intermed.txt", ios::app);
			readPromo(p,fin1,c,a,fout2);
			fin1.close();
			fout2.close();
		}
		if(command == "today")
		{	
			string curdate;
			cin >> curdate;
			fout2.open("intermed.txt", ios::app);
			fout2 << curdate << endl;
			todayDate(curdate,a,c);
			fout2.close();
		}
		
		if(command == "buy")
		{	
			char check ;
			cin >> check;
			fout2.open("intermed.txt", ios::app);
			if(check != '#')
			{
				string temp;
				getline(cin,temp,'-');
				p.dest = check + temp;
				getline(cin,p.airline,'-');
				getline(cin,p.fdate,'-');
				getline(cin,p.tdate,'-');
				cin >> p.price;
				cin >> p.quota;
				buy(p,a,c,fout2,nc,n);
			}
			else
			{
				int index, num;
				cin >> index >> num;
				
				
					p.dest = s[index].dest;
					p.airline = s[index].airline;
					p.fdate = s[index].fdate;
					p.tdate = s[index].tdate;
					p.enddate = s[index].enddate;
					p.price = s[index].price;
					p.quota = num;

					buy(p,a,c,fout2,nc,n);	
				
				
			}
			fout2.close();
		}

		if(command == "most")
		{	
			fin3.open("airportcode.txt");
			fout3.open("most.txt");
			fout3.clear();
			airportFile(fin3,ac,a,c,cap,m,nc,n,fout3);
			fin3.close();
			fout3.close();
			
		}

		if(command == "clear")
		{
			for (int i = 1; i < cs; i++)
			{
				s[i].dest = "";
				s[i].airline = "";
				s[i].fdate = "";
				s[i].tdate = "";
				s[i].enddate = "";
				s[i].price = 0;
				s[i].quota = 0;
			}
			cs = 1;
			
		}

		if (command == "search")
		{	
			string word1,word2;
			cin >> word1 >> word2;
			if (word1 == "dest")
			{	cs = 1;
				for (int i = 0; i < c; i++)
				{
					if(a[i].dest == word2)
					{
						s[cs].dest = a[i].dest;
						s[cs].airline = a[i].airline;
						s[cs].fdate = a[i].fdate;
						s[cs].tdate = a[i].tdate;
						s[cs].enddate = a[i].enddate;
						s[cs].price = a[i].price;
						s[cs].quota = a[i].quota;
						cs++;
					}
				}

				for (int i = 1; i < cs; i++)
				{
					cout <<"   <"<<i << ">" << " " << s[i].dest << "-" << s[i].airline << "-" << s[i].fdate << "-" << s[i].tdate << " " << "HKD "<< s[i].price << ", promotion expires " <<  s[i].enddate << "," << s[i].quota <<" Quota" << endl;
				}
			}

			if (word1 == "date")
			{	cs = 1;
				for (int i = 0; i < c; i++)
				{
					if( (word2 >= a[i].fdate) && (word2 <= a[i].tdate) ) 
					{	
						s[cs].dest = a[i].dest;
						s[cs].airline = a[i].airline;
						s[cs].fdate = a[i].fdate;
						s[cs].tdate = a[i].tdate;
						s[cs].enddate = a[i].enddate;
						s[cs].price = a[i].price;
						s[cs].quota = a[i].quota;
						cs++;

					}				
				}
				for (int i = 1; i < cs; i++)
				{
					cout <<"   <"<<i << ">" << " " << s[i].dest << "-" << s[i].airline << "-" << s[i].fdate << "-" << s[i].tdate << " " << "HKD "<< s[i].price << ", promotion expires " <<  s[i].enddate << "," << s[i].quota <<" Quota" << endl;
				}
			}
		}

		if (command == "no")
		{	
			string word1,word2;
			cin >> word1 >> word2;
			if(word1 == "airline")
			{	int count = 0;
				for (int i = 1; i < cs - count; i++)
				{	
					if(s[i].airline == word2)
					{	count++;
						for (int j = i; j < cs-1 ; j++)
						{
						
						s[j].dest = s[j+1].dest;
						s[j].airline = s[j+1].airline;
						s[j].fdate = s[j+1].fdate;
						s[j].tdate = s[j+1].tdate;
						s[j].enddate = s[j+1].enddate;
						s[j].price = s[j+1].price;
						s[j].quota = s[j+1].quota;
						}
						i=0;
					}		
				}
				cs = cs - count;
				
				for (int i = 1; i < cs; i++)
				{
					cout <<"   <"<<i << ">" << " " << s[i].dest << "-" << s[i].airline << "-" << s[i].fdate << "-" << s[i].tdate << " " << "HKD "<< s[i].price << ", promotion expires " <<  s[i].enddate << "," << s[i].quota <<" Quota" << endl;
				}

			}
		}

		if (command == "prefer")
		{	
			
			string word1,word2;
			cin >> word1 >> word2;
			
			if(word1 == "airline")
			{	
				int count = 0;
				for (int i = 1; i < cs - count; i++)
				{	
					if(s[i].airline != word2)
					{	count++;
						for (int j = i; j < cs-1 ; j++)
						{
						
						s[j].dest = s[j+1].dest;
						s[j].airline = s[j+1].airline;
						s[j].fdate = s[j+1].fdate;
						s[j].tdate = s[j+1].tdate;
						s[j].enddate = s[j+1].enddate;
						s[j].price = s[j+1].price;
						s[j].quota = s[j+1].quota;
						}
						i=0;
					}		
				}
				cs = cs - count;

				for (int i = 1; i < cs; i++)
				{
					cout <<"   <"<<i << ">" << " " << s[i].dest << "-" << s[i].airline << "-" << s[i].fdate << "-" << s[i].tdate << " " << "HKD "<< s[i].price << ", promotion expires " <<  s[i].enddate << "," << s[i].quota <<" Quota" << endl;
				}

			}
		}

		/* if(command == "lowest")
		{
			string word;
			cin >> word;
			int temp[500] = {0};
			int temp1=0,inx = 0;
			for (int i = 0; i < c; i++)
			{
				if(word == a[i].dest)
				{	
					
					temp[i] = a[i].price;
					temp1 = temp[i];
					inx = i;
				}
			}

			
   			for (int i = 0; i < 500; i++)
    		{
    			if (temp[i] != 0)
    			{
    				int temp2 = temp[i];
    				if (temp2 < temp1)
    				{
    					temp1 = temp2;
    					inx = i;
    				}
    			}
        	}
    		

    		for (int i = 0; i < c; i++)
    		{
    			if(i == inx)
    			{
    				cout <<"   <"<< i << ">" << " " << a[i].dest << "-" << a[i].airline << "-" << a[i].fdate << "-" << a[i].tdate << " " << "HKD "<< a[i].price << ", promotion expires " <<  a[i].enddate << "," << a[i].quota <<" Quota" << endl;
    			}
    		}
		}
		*/

		cin >> command;
	}
	
	if(command == "end")
	{	
		fout2.open("intermed.txt", ios::app);
		fout2 << "#\n";
		fout2.close();
		fin.close();
		exit (1);
	}
}




