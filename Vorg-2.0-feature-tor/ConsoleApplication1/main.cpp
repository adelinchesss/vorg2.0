#include <iostream>
#include <sstream>
#include <windows.h> 
#include <string>
#include <cmath>
#include <map>
#include <iterator>
#include <vector> 
#include <fstream>
#include <limits>
#include <process.h>


using namespace std;

class C2Ppn {
	char curc;                   //the current character
	string str_in, str_out;     //input & output strings          
	int iin;                     //the index of the input string

	char nextChar();           //get the next character from str_in
	bool isXorY(char c); 
	int prior(char c);            //get the priority of the character  

public:
	long long Fruction(long long x_in, long long y_in, int n);
	long long calculate(string out, long long x_in, int n);
	//map<int, int> automat(string func, int x_in, int y_in, int iteration_count);
	void convert(string);        //convert to PPN                                          
	string get_str_out() const;   //get the output string
};

//stack
template <class T>
class Stack {
	T* pstack;
	int istack;
	int size;

	friend class C2Ppn;

	void push(T x) {
		if (istack < size) pstack[istack++] = x;
		else {
			MessageBox(NULL, (LPCWSTR)"Переполнение стека!", (LPCWSTR)"Error", MB_OK);
		}
	}
	T pop() {
		return (istack > 0) ? pstack[--istack] : EOS;
	}
	T top()const {
		return (istack > 0) ? pstack[istack - 1] : EOS;
	}
public:
	const char EOS;
	Stack() : EOS(0x1), size(50) {
		istack = 0;
		pstack = new T[size];
	}
	~Stack() { if (pstack) delete[] pstack; }
};


//if the character is a digit
inline bool C2Ppn::isXorY(char c) {
	return (c == 'x'  || c == 'X' || (c >= '0' && c <= '9'));
}

//the priopity of the operation
inline int C2Ppn::prior(char c) {
	switch (c) {
	case '(': return 1;
	case '|': case '&': case '#': return 2; //#-xor
	case '<': case '>': return 3;
	case '+': case '-': return 4;
	case '*': case '/': return 5;
	case '^': return 6;
	default: return 0;
	}
}

//get the next character from str_in
inline char C2Ppn::nextChar() {
	if (iin < str_in.length()) {
		return curc = str_in[iin++];
	}
	else return curc = '\0';
}

//get the output string
inline string C2Ppn::get_str_out()const {
	return str_out;
}

//convert to PPN
void C2Ppn::convert(string str) {
	int was_op = 0, np = 0;    //these flags show if there were 
							   //operations & brackets  
	iin = 0;                   //index of input string  
	Stack<char> op_stack;
	str_in = str;
	str_out = "";

	if ((!isXorY(str_in[0])) && str_in[0] != '(')
		throw (string)"Syntax error";

	while (nextChar() != '\0') {
		if (isXorY(curc)) {
			str_out += curc;
			was_op = 0;
			continue;
		}
		else str_out += ' ';

		switch (curc) {
		case '(':
			op_stack.push(curc);
			++np;
			was_op = 0;
			break;
		case '*': case '/': case '+': case '-': case '>':  case '<': case '#': case '&': case '|': case '^':
			if (iin == str_in.length())
				throw (string)"Syntax error";

			if (!was_op) {
				was_op = 1;
				while (prior(curc) <= prior(op_stack.top())) {
					str_out += op_stack.pop();
				}
				if (prior(curc) > prior(op_stack.top())) {
					op_stack.push(curc);
				}
				break;
			}
			else throw (string)"Syntax error";

		case ')':
			if (was_op)
				throw (string)"Syntax error";
			else
				while ((curc = op_stack.pop()) != '(' && np > 0) {
					str_out += curc;
				}
			--np;
			break;
		default: {
			throw (string)"Error: invalid symbol in the string";
		}
		}
	}
	while (op_stack.top() != op_stack.EOS)
		str_out += op_stack.pop();
	if (np)
		throw (string)"Error: wrong number of brackets";
}

long long C2Ppn::Fruction(long long x_in, long long y_in, int n) {
	if (y_in == 3) {
		switch (n) {
		case 5:
			return 11;
		case 6:
			return 43;
		case 7:
			return 43;
		case 8:
			return 171;
		case 9:
			return 171;
		case 10:
			return 683;
		case 11:
			return 683;
		case 12:
			return 2731;
		case 13:
			return 2731;
		case 14:
			return 10923;
		case 15:
			return 10923;
		case 16:
			return 43691;
		}
	}
	if (y_in == 5) {
		switch (n) {
		case 5:
			return 13;
		case 6:
			return 13;
		case 7:
			return 77;
		case 8:
			return 205;
		case 9:
			return 205;
		case 10:
			return 205;
		case 11:
			return 1229;
		case 12:
			return 3277;
		case 13:
			return 3277;
		case 14:
			return 3277;
		case 15:
			return 19661;
		case 16:
			return 52429;
		}
	}
	if (y_in == 7) {
		switch (n) {
		case 5:
			return 23;
		case 6:
			return 55;
		case 7:
			return 55;
		case 8:
			return 183;
		case 9:
			return 439;
		case 10:
			return 439;
		case 11:
			return 1463;
		case 12:
			return 3511;
		case 13:
			return 3511;
		case 14:
			return 11703;
		case 15:
			return 28087;
		case 16:
			return 28087;
		}
	}
}

long long C2Ppn::calculate(string str_out, long long x_in, int n) {
	Stack <long long> stk;
	long long numerator = 0;
	char check = str_out[numerator];
	long long x = 0, y = 0;
	long long result = 0;
	while (check != EOF && check != '\n' && check != '\0') {
		bool flag = true;
		string num = "";
		while (check == ' ' || check == '\t') {
			check = str_out[++numerator];
		}
		if (check == 'x' || check == 'X') stk.push(x_in);
		else if (check <= '9' && check >= '0') {
			while (check <= '9' && check >= '0') {
				num += check;
				check = str_out[++numerator];
				flag = false;
			}
			stk.push(stoi(num));
		}
		else {
			y = stk.top(); stk.pop();
			x = stk.top(); stk.pop();
			switch (check) {
			case '+':
				stk.push(x + y); break;
			case '-':
				stk.push(x - y); break;
			case '*':
				stk.push(x * y); break;
			case '/': //or 
				stk.push(Fruction(x,y,n)); break;
			case '|': 
				stk.push(x | y); break;
			case '#': //xor
				stk.push(x ^ y); break;
			case '&': //and
				stk.push(x & y); break;
			case '<':
				stk.push(x << y); break;
			case '>':
				stk.push(x >> y); break;
			case '^':
				stk.push((long long)(pow((double)x, (double)y))); break;
			}
		}
		if (flag) numerator++;
		check = str_out[numerator];
	}
	return stk.top();
}

string removeSpaces(string input)
{
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	return input;
}

/*
string to_2adic_Reverse(long long x) {
	string buffer;
	buffer.reserve(numeric_limits<unsigned long long>::digits);
	bool neg = false;
	if (x < 0) {
		x = -x;
		neg = true;
	}
	do
	{
		buffer += char('0' + x % 2);
		x /= 2;
	} while (x > 0);
	string s = string(buffer.crbegin(), buffer.crend());
	size_t pos = 0;
	if (neg) {
		for (long long i = 0; i < s.length(); i++) {
			s[i] = (char)(1 - (int)(s[i] - '0') + '0');
		}
		for (int i = s.length() - 1; i > 0; i--) {
			if (s[i] == '0') {
				s[i] = '1'; break;
			}
			else s[i] = '0';
		}
	}
	s.insert(pos, "0"); pos++;
	s.insert(pos, ".");
	return s;
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
long long Reverse_again(string str) {
	long long result = 0;
	for (long long i = 2; i < str.length(); i++){
	result += (int)(str[i] - '0') * (long long)pow(2, i - 2);
    }
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


string to_2adic_Reverse_func(long long x, long long x_len) {
	string buffer;
	buffer.reserve(numeric_limits<unsigned long long>::digits);
	bool neg = false;
	if (x < 0) {
		x = -x;
		neg = true;
	}
	long long j = 0;
	do
	{
		j++;
		buffer += char('0' + x % 2);
		x /= 2;
	} while (x > 0 && j < x_len);
	if (j < (x_len)) {
		for (long long i = 0; i < ((x_len) - j); i++){
			buffer += '0';
		}
	}
	string s = string(buffer.crbegin(), buffer.crend());
	size_t pos = 0;
	if (neg) {
		for (long long i = 0; i < s.length(); i++) {
			s[i] = (char)(1 - (int)(s[i] - '0') + '0');
		}
		for (int i = s.length() - 1; i > 0; i--) {
			if (s[i] == '0') {
				s[i] = '1'; break;
			}
			else s[i] = '0';
		}
	}
	s.insert(pos, "0"); pos++;
	s.insert(pos, ".");
	return s;
}


string to_2adic_Mon(long long x) {
	string buffer; 
	buffer.reserve(numeric_limits<unsigned long long>::digits);
	bool neg = false;
	if (x < 0) {
		x = -x;
		neg = true;
	}
	do
	{
		buffer += char('0' + x % 2);
		x /= 2;
	} while (x > 0);
	size_t pos = 0;
	if (neg) {
		for (long long i = 0; i < buffer.length(); i++) {
			buffer[i] = (char)(1 - (int)(buffer[i] - '0') + '0');
		}
		for (int i = buffer.length() - 1; i > 0; i--) {
			if (buffer[i] == '0') {
				buffer[i] = '1'; break;
			}
			else buffer[i] = '0';
		}
	}
	buffer.insert(pos, "0"); pos++;
	buffer.insert(pos, ".");
	return buffer;
}


int main()
{
	std::fstream debug;
	debug.open("mydebug.txt", ios::out);
	string str_in, rubish;

	std::string func, line;
	int mode, number_graphs, mapp_style;
	std::ifstream data;
	data.open("pyconfig.txt", ios::in);
	
	getline(data, str_in, ';');
	str_in = str_in + '\0';
	debug << "str_in=" << str_in << endl;
	getline(data, line, ';');
	mode = stoi(line) - 1;
	debug << "mode=" << mode << endl;
	getline(data, line, ';');
	mapp_style = stoi(line);
	debug << "mapp_style=" << mapp_style << endl;
	getline(data, line, ';');
	number_graphs = stoi(line);
	debug << "number_graphs=" << number_graphs << endl;

	vector <long long> x, y;
	int in_value_type = 0;
	int N;  // count of args
	
	fstream FILE;
	FILE.open(string("number_graphs.txt"), std::fstream::out);
	FILE << number_graphs;
	FILE.close();

	FILE.open(string("config.txt"), std::fstream::out);
	FILE << mode;
	FILE.close(); 

	for (int i = 0; i < number_graphs; i++) {
		debug << "loop" << endl;
		fstream FILE; 
		FILE.open(string("Values" + to_string(i) + ".txt").c_str(), std::fstream::out);

		C2Ppn ppn;
		ppn.convert(removeSpaces(str_in));
		string function = (string)ppn.get_str_out();
		map<long long, string> iter_value;
		long long numerator = 0;
		if (x.size() == 0 || y.size() == 0) {
			int word_len = 0;
			//cout << "Enter degree of word Lengt:" << '\n' << endl;
			//cin >> word_len;
			getline(data, line, ';');
			word_len = stoi(line);
			debug << "word_len=" << word_len << endl;
			for (long long i = 0; i < (long long)pow(2, word_len); i++) {
				//long long calc = ppn.calculate(function, i);
				if (mapp_style == 1) {
					iter_value[numerator] = to_2adic_Mon(i);numerator++;
					long long calc = ppn.calculate(function, i, word_len);
					iter_value[numerator] = to_2adic_Mon(calc);numerator++;
				}
				if (mapp_style == 2) {
					/*iter_value[numerator] = to_2adic_Reverse(i);
					long long xi = Reverse_again(iter_value[numerator]); numerator++;
					long long calc = ppn.calculate(function, xi); */
					///////////////////////////////////////////////////////////////////////////
					iter_value[numerator] = to_2adic_Mon(i); numerator++;
					//long long i_length = iter_value[numerator].length(); 
					string to_2adic_rev = to_2adic_Reverse_func(i, word_len);
					long long xi = Reverse_again(to_2adic_rev);
					long long calc = ppn.calculate(function, xi, word_len);
					//////////////////////////////////////////////////////////////////////////
					iter_value[numerator] = to_2adic_Reverse_func(calc, word_len); numerator++;
				}
			}
		}
		/*else {
			long long numerator = 0;
			for (long long i = 0; i < N; i++) {
				long long calc = ppn.calculate(function, x[i]);
				if (mapp_style == 1) {
					iter_value[numerator] = to_2adic_Mon(x[i]); numerator++;
					iter_value[numerator] = to_2adic_Mon(calc); numerator++;
				}
				if (mapp_style == 2) {
					iter_value[numerator] = to_2adic_Reverse(x[i]); numerator++;
					iter_value[numerator] = to_2adic_Reverse(calc); numerator++;
				}
			}
		} */
		numerator = 0;
		for (long long i = 0; i < iter_value.size() / 2; i++) {
			FILE << iter_value[numerator] << "   "; numerator++;
			FILE << iter_value[numerator] << "   " << endl; numerator++;
		}
		FILE.close();
	}
	
	
//drawing
	const char* const argv[] = { "python","graph_torus.py", 0 };
	if (_execvp(argv[0], argv) == -1)
	{
		perror("init_compile(): execvp()");
		return 1;
	}

return 0;
}