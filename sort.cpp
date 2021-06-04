/*
 * CSc103 Project 4: Sorting with lists
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *I looked up how getopt worked which helped a lot because I learned about flags. Flags were really handy for this project
 * I don't think this many if statements is efficient.I also looked up what structures, class (public, private etc.) and constructors.
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:72 hours =_=
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;
#include <vector>
using std::vector;

/* doubly linked list node: */
struct node
{
	string data;
	node* prev;
	node* next;
	node(string s="", node* p=NULL, node* n=NULL) : data(s),prev(p),next(n) {}
};

void removenode(node*&rm);
int checkdup(node* qua);
node* resethead(node* any);
void nodeafter(node*& old,string x);
void nodebefore(node*& old,string x);

int main(int argc, char *argv[])
{
	/* define long options */
	static int unique=0;
	static int reverse=0;
	static struct option long_opts[] =
	{
		{"unique",   no_argument,       &unique,   'u'},
		{"reverse",  no_argument,       &reverse,  'r'},
		{0,0,0,0} // this denotes the end of our options.
	};
	// Flag here is &unique and &reverse, indicates it has been seen and puts in 'u' or 'r'
	/* process options */
	char c; /* holds an option */
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ur", long_opts, &opt_index)) != -1)
	{
		switch (c)
		{
			case 'u':
				unique = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case '?': /* this will catch unknown options. */
				return 1;
		}
	}



	/* NOTE: at this point, variables 'reverse' and 'unique' have been set
	 * according to the command line.  */
	/* TODO: finish writing this.  Maybe use while(getline(cin,line)) or
	 * similar to read all the lines from stdin. */
	node head;
	string line;
	node *prox;
	node* flag;
	prox = &head;
	int flag2 = 1;
	int nodeadded = 0;
	while(flag2)
	{
		getline(cin,line);
		if (line == "\0")
		{
			flag2 = 0;
		}
		/* this might produce an error when "" is inputed! Wait, no line is ""*/
		if (head.data == "")
		{
			head.data = line;
		}
		// if not flag2 then after line is \0 then this else will compare \0
		else if (flag2)
		{
			nodeadded = 0;
			prox = resethead(prox);
			flag = 0;
			while(prox != NULL && nodeadded == 0)
			{
				if (!(line < prox->data))
				{
					if (prox->next == NULL)
					{
						flag = prox;
					}
					if (line == prox->data)
					{
						nodeafter(prox, line);
						nodeadded = 1;
					}
					prox = prox->next;
				}
				else
				{
					nodebefore(prox,line);
					nodeadded = 1;
					flag = 0;
				}
			}
			if (flag !=0)
			{
				prox = flag;
				if(nodeadded == 0)
				{
					nodeafter(prox, line);
				}
			}
		}
	}
	node*last;
	int dup;
	prox = resethead(prox);
	if (unique == 1)
	{
		last = 0;
		while(prox->next != NULL)
		{
			dup = checkdup(prox);
			if (dup !=0)
			{
				removenode(prox);
				dup = 0;
			}
			else
			{
				if (prox->next == NULL)
				{
					last = prox;
				}
				prox = prox->next;
			}
			if (last != 0)
			{
				prox = last;
			}
		}
	}
	prox =resethead(prox);
	if (reverse == 1)
	{
		while (prox->next != NULL)
		{
			prox = prox->next;
		}
		for (node* i = prox; i != NULL; i = i->prev)
		{
			cout << i->data << endl;
		}
	}
	else
	{
		for (node* i = prox; i != NULL; i = i->next)
		{
			cout << i->data << endl;
		}
	}
	return 0;
}

//this will place nuevo node in front of old node. So if s2 is greater than s1 use this. Also, if they are equal, do this.
void nodebefore(node*& old,string x)
{
	node *nuevo = new node(x);
	if (old->prev != NULL)
	{
		nuevo->prev = old->prev;
		old->prev->next = nuevo;
		nuevo->next = old;
		old->prev = nuevo;
	}
	else if (old ->prev == NULL)
	{
		nuevo->prev = old->prev;
		nuevo->next = old;
		old->prev = nuevo;
	}
	else
	{
		cout << "DURR EEROR\n";
	}

}
void nodeafter(node*& old,string x)
{
	node *nuevo = new node(x);
	if (old ->next != NULL)
	{
		old->next->prev = nuevo;
		nuevo->next = old ->next;
		old->next = nuevo;
		nuevo->prev = old;
	}
	else if (old->next == NULL)
	{
		nuevo->next = old->next;
		nuevo->prev = old;
		old->next = nuevo;
	}
	else
	{
		cout << "ERROR IN AFTERNOD\n";
	}
}

node* resethead(node* any)
{
	node* head;
	node* flag = 0;
	if (any == NULL)
	{
		cout << "IT IS NULL\n";
	}
	while(any != NULL)
	{
		if(any->prev == NULL)
		{
			flag = any;
		}
		any = any->prev;
	}
	if (flag != 0)
	{
		any = flag;
	}
	head = any;
	return head;
}

void removenode(node*& rm)
{
	if (rm->prev == NULL)
	{
		rm = rm->next;
		rm->prev = NULL;
	}

	else
	{
		node *tmp = rm;
		rm = rm->next;
		rm->prev = tmp->prev;
		tmp->prev->next= rm;
	}
}

//must start at head of link!
int checkdup(node*qua)
{
	int counter= 0;
	if (qua == NULL)
	{
		return 0;
		cout <<"got a null at dup";
	}
	string comp = qua->data;
	//It counts itself >.>
	while(qua != NULL)
	{
		if (qua->data == comp)
		{
			counter++;
		}
		qua = qua->next;
	}
	return --counter;
}
