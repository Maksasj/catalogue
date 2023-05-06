#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>



// other includes and definitions

/* YOUR CODE HERE */

using namespace std;



/* DO NOT MODIFY THE CODE BELOW */

// data to be indexed
struct Data {
	int iField;
	string sField;
	double dField;	
	Data(int iField, string sField, double dField){
		this->iField = iField;
		this->sField = sField;
		this->dField = dField;
	}
	Data(const Data &d){
		iField = d.iField;
		sField = d.sField;
		dField = d.dField;
	}
	Data& operator=(const Data &d){
		iField = d.iField;
		sField = d.sField;
		dField = d.dField;
		return *this;
	}
};

class OutOfBoundsException {
};
class NotImplementedException {
};

// data structure
class Container {
	Data **data;
	int n;
public:
	Container(){
		data = NULL;
		n = 0;
	}
	Container(const Container &other){
		throw NotImplementedException(); // do not modify this, always pass by reference
	}
	Container & operator= (const Container &other){
		throw NotImplementedException(); // do not modify this, always pass by reference
	}
	int size() const {
		return getSize();
	}
	int getSize() const {
		return n;
	}
	Data* operator[](int i) const {
		if ((i < 0) || (i >= n))
			throw OutOfBoundsException();
		return getElement(i);
	}
	Data* getElement(int i) const {
		return data[i];
	}
	
	void add(int index, Data d){
		if ((index < 0) || (index > n))
			throw OutOfBoundsException();
		data = (Data **)realloc(data, ++n * sizeof(Data*));
		for(int i = n-1; i > index; --i){
			data[i] = data[i-1];
		}
		data[index] = new Data(d);
	}
	void remove(int index){
		if ((index < 0) || (index >= n))
			throw OutOfBoundsException();
		delete(data[index]);
		for(int i = index; i < n-1; ++i)
			data[i] = data[i+1];		
		data = (Data **)realloc(data, --n * sizeof(Data*));	
	}
	void edit(int index, Data d){
		if ((index < 0) || (index >= n))
			throw OutOfBoundsException();
		delete(data[index]);
		data[index] = new Data(d);
	}
	~Container(){
		for(int i = 0; i < n; ++i)
			delete(data[i]);
		free(data);
	}
};


// helper functions
Data input(){
	int i;
	cin >> i;
	string s;
	cin >> s;
	double d;
	cin >> d;
	return Data(i, s, d);
}
void output(const Data *d){
	if (d)
		cout << d->dField << " " << d->sField << " " << d->dField << endl;
	else
		cout << "NULL" << endl;
}

/* DO NOT MODIFY THE CODE ABOVE */







// your index structures defined as global variables
// up to three, one per field type

/* YOUR CODE HERE */

// throw the following class if function is not implemented
class NotImplementedException;

enum class DATATYPE { INT, STR, DBL }; // message codes
// rebuild indexes from scratch as necessary
// use size() and operator[] to access data elements in container
void createIndex(DATATYPE dt, const Container &c){
	/* YOUR CODE HERE */	
	if (dt == DATATYPE::INT){
		throw NotImplementedException();
	}
	if (dt == DATATYPE::STR){
		throw NotImplementedException();
	}
	if (dt == DATATYPE::DBL){
		throw NotImplementedException();
	}
}

enum class OPCODE { INS, DEL }; // message codes
// update your index structures as necessary
// without recreating them
void notify(OPCODE op, const Data *value){
	/* YOUR CODE HERE OR EMPTY */	
}


Data* searchByInt(int value){
	/* YOUR CODE HERE */
	throw NotImplementedException();
}
Data* searchByStr(string value){
	/* YOUR CODE HERE */
	throw NotImplementedException();
}
Data* searchByDbl(double value){
	/* YOUR CODE HERE */
	throw NotImplementedException();
}








/* DO NOT MODIFY CODE BELOW */

int main(){	
	try {
		Container container;
		int x = -1;
		while(1){
			cin >> x;
			if (x == 0){
				break;
			} else {
				switch(x){
					case 11:	{
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							int index;
							cin >> index;
							container.add(index, input());
							notify(OPCODE::INS, container[index]);
						}						
						break;
					}
					case 12:	{
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							int index;
							cin >> index;
							notify(OPCODE::DEL, container[index]);
							container.edit(index, input());
							notify(OPCODE::INS, container[index]);
						}						
						break;
					}
					case 13:	{
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							int index;
							cin >> index;
							notify(OPCODE::DEL, container[index]);
							container.remove(index);						
						}						
						break;
					}
					case 2:	{
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							int index;
							cin >> index;
							output(container[index]);
						}						
						break;
					}
					case 31: {
						createIndex(DATATYPE::INT, container);					
						break;
					}
					case 32: {
						createIndex(DATATYPE::STR, container);										
						break;
					}
					case 33: {
						createIndex(DATATYPE::DBL, container);									
						break;
					}
					case 41: {
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							int val;
							cin >> val;
							Data* d = searchByInt(val);
							output(d);
						}						
						break;
					}
					case 42: {
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							string val;
							cin >> val;
							Data* d = searchByStr(val);
							output(d);
						}						
						break;
					}
					case 43: {
						int n;
						cin >> n;						
						for (int i = 0; i < n; ++i){
							double val;
							cin >> val;
							Data* d = searchByDbl(val);
							output(d);
						}						
						break;
					}
				}
			}
				
		}
	} catch (NotImplementedException &e){
		return 2018;
	} catch (OutOfBoundsException &e){
		return 4321;
	} catch (...){
		return -1;
	}
					
	return 0;	
}

