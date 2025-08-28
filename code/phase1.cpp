#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

bool flag = true;
string error_label;

string binary_addition(string bin) {
    int carry = 1;
    for (int i = bin.length() - 1; i >= 0; i--) {
        if (bin[i] == '1' && carry == 1) {
            bin[i] = '0'; // 1 + 1 = 10, set bit to 0, carry remains 1
        } else if (bin[i] == '0' && carry == 1) {
            bin[i] = '1'; // 0 + 1 = 1, carry becomes 0
            carry = 0;
        }
    }
    return bin;
}
string dword(const string &str) {
    string num = str;
    bool isNegative = (num[0] == '-'); // Check if number is negative

    if (isNegative) {
        num = num.substr(1); // Remove the negative sign
    }

    string binary = "";

    // Convert decimal string to binary string
    while (num != "0") {
        int carry = 0;
        string quotient = "";
        
        for (size_t i = 0; i < num.length(); i++) {
            int current = carry * 10 + (num[i] - '0');
            quotient += (current / 2) + '0';
            carry = current % 2;
        }

        binary = (carry ? '1' : '0') + binary;

        size_t pos = quotient.find_first_not_of('0');
        if (pos != string::npos) {
            num = quotient.substr(pos);
        } else {
            num = "0";
        }
    }

    // Ensure the binary string is exactly 64 bits long
    while (binary.length() < 64) {
        binary = "0" + binary;
    }
    if (binary.length() > 64) {
        binary = binary.substr(binary.length() - 64);
    }

    // If the original number was negative, apply two’s complement
    if (isNegative) {
        for (size_t i = 0; i < binary.length(); i++) {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
        binary = binary_addition(binary);
    }

    return binary;
}
string word(const string &str) {
    string num = str;
    bool isNegative = (num[0] == '-');

    if (isNegative) {
        num = num.substr(1);
    }

    string binary = "";

    while (num != "0") {
        int carry = 0;
        string quotient = "";

        for (size_t i = 0; i < num.length(); i++) {
            int current = carry * 10 + (num[i] - '0');
            quotient += (current / 2) + '0';
            carry = current % 2;
        }

        binary = (carry ? '1' : '0') + binary;

        size_t pos = quotient.find_first_not_of('0');
        if (pos != string::npos) {
            num = quotient.substr(pos);
        } else {
            num = "0";
        }
    }

    while (binary.length() < 32) {
        binary = "0" + binary;
    }
    if (binary.length() > 32) {
        binary = binary.substr(binary.length() - 32);
    }

    if (isNegative) {
        for (size_t i = 0; i < binary.length(); i++) {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
        binary = binary_addition(binary);
    }

    return binary;
}
string half(const string &str) {
    string num = str;
    bool isNegative = (num[0] == '-');

    if (isNegative) {
        num = num.substr(1);
    }

    string binary = "";

    while (num != "0") {
        int carry = 0;
        string quotient = "";

        for (size_t i = 0; i < num.length(); i++) {
            int current = carry * 10 + (num[i] - '0');
            quotient += (current / 2) + '0';
            carry = current % 2;
        }

        binary = (carry ? '1' : '0') + binary;

        size_t pos = quotient.find_first_not_of('0');
        if (pos != string::npos) {
            num = quotient.substr(pos);
        } else {
            num = "0";
        }
    }

    while (binary.length() < 16) {
        binary = "0" + binary;
    }
    if (binary.length() > 16) {
        binary = binary.substr(binary.length() - 16);
    }

    if (isNegative) {
        for (size_t i = 0; i < binary.length(); i++) {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
        binary = binary_addition(binary);
    }

    return binary;
}
string bite(const string &str) {
    string num = str;
    bool isNegative = (num[0] == '-');

    if (isNegative) {
        num = num.substr(1);
    }

    string binary = "";

    while (num != "0") {
        int carry = 0;
        string quotient = "";

        for (size_t i = 0; i < num.length(); i++) {
            int current = carry * 10 + (num[i] - '0');
            quotient += (current / 2) + '0';
            carry = current % 2;
        }

        binary = (carry ? '1' : '0') + binary;

        size_t pos = quotient.find_first_not_of('0');
        if (pos != string::npos) {
            num = quotient.substr(pos);
        } else {
            num = "0";
        }
    }

    while (binary.length() < 8) {
        binary = "0" + binary;
    }
    if (binary.length() > 8) {
        binary = binary.substr(binary.length() - 8);
    }

    if (isNegative) {
        for (size_t i = 0; i < binary.length(); i++) {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
        binary = binary_addition(binary);
    }

    return binary;
}
string bin4_to_Hex(const string &str) {
	int out = 0;
	for (size_t i = 0; i < 4; i++) {
		if (str[i] == '1') {
			out += pow(2,3-i);
		}
	}
	if (out < 10) {
		return to_string(out);
	}
	else {
		if (out == 10) {
			return "A";
		}
		else if (out == 11) {
			return "B";
		}
		else if (out == 12) {
			return "C";
		}
		else if (out == 13) {
			return "D";
		}
		else if (out == 14) {
			return "E";
		}
		else {
			return "F";
		}
	}
}

set<string> define_r_format() {
	set<string> out;
	out.insert("add");
	out.insert("and");
	out.insert("or");
	out.insert("sll");
	out.insert("slt");
	out.insert("sra");
	out.insert("srl");
	out.insert("sub");
	out.insert("xor");
	out.insert("mul");
	out.insert("div");
	out.insert("rem");
	return out;
}
set<string> define_i_format() {
    set<string> out;
    out.insert("addi");
    out.insert("andi");
    out.insert("ori");
    out.insert("lb");
    out.insert("ld");
    out.insert("lh");
    out.insert("lw");
    out.insert("jalr");
    return out;
}
set<string> define_s_format() {
    set<string> out;
    out.insert("sb");
    out.insert("sw");
    out.insert("sd");
    out.insert("sh");
    return out;
}
set<string> define_sb_format() {
    set<string> out;
    out.insert("beq");
    out.insert("bne");
    out.insert("bge");
    out.insert("blt");
    return out;
}
set<string> define_u_format() {
    set<string> out;
    out.insert("auipc");
    out.insert("lui");
    return out;
}
set<string> define_uj_format() {
    set<string> out;
    out.insert("jal");
    return out;
}
set<string> define_assembler_directives() {
	set<string> out;
	out.insert(".text");
	out.insert(".data");
	out.insert(".bite");
	out.insert(".half");
	out.insert(".word");
	out.insert(".dword");
	out.insert(".asciiz");
	return out;
}
set<string> define_registers() {
	string initial = "x";
	set<string> out;
	for (int i = 0; i < 32; i++) {
		out.insert(initial + to_string(i));
	}
	return out;
}

string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

string get_instruction(const string &str) {
	string out;
	int x = str.length();
	for (int i = 0; i < x; i++){
		if (isalnum(str[i]) || str[i] == '_'){
			out += str[i];
		}
		else{break;}
	}
	return out;
}
string remove_instruction(const string &str) {
	int i = 0;
	while (isalnum(str[i]) || str[i] == '_') {
		i++;}
	while (str[i] == ',' || str[i] == ' '){
		i++;
	}

	int j = str.find('#');
	while (str[j] == ',' || str[j] == ' ' || str[j] == '#') {
		j--;
	}

	return str.substr(i, j-i+1);
}
int get_format(const string& instruction, const set<string>& r_format, const set<string>& i_format, const set<string>& s_format, const set<string>& sb_format, const set<string>& u_format, const set<string>& uj_format) {
	if (r_format.find(instruction) != r_format.end()) {
		return 1;}
	else if (i_format.find(instruction) != i_format.end()) {
		return 2;}
	else if (s_format.find(instruction) != s_format.end()) {
		return 3;}
	else if (sb_format.find(instruction) != sb_format.end()) {
		return 4;}
	else if (u_format.find(instruction) != u_format.end()) {	
		return 5;}
	else if (uj_format.find(instruction) != uj_format.end()) {
		return 6;}
	else {
		return 0;}
}

bool in_registers(const string &str) {
	if (str.length() == 0){
		return false;
	}
	else if (str.length() == 1){
		return false;
	}
	else if (str[0] != 'x'){
		return false;
	}
	else if (str.length() == 2){
		if (!(str[1] == '0' || str[1] == '1' || str[1] == '2' || str[1] == '3' || str[1] == '4' || str[1] == '5' || str[1] == '6' || str[1] == '7' || str[1] == '8' || str[1] == '9')) {
			return false;
		}
	}
	else if (str.length() == 3){
		if (str[1] == '1' || str[1] == '2'){
			if (!(str[2] == '0' || str[2] == '1' || str[2] == '2' || str[2] == '3' || str[2] == '4' || str[2] == '5' || str[2] == '6' || str[2] == '7' || str[2] == '8' || str[2] == '9')){
				return false;
			}
		}
		else if (str[1] == '3'){
			if (!(str[2] == '0' || str[2] == '1')){
				return false;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
	return true;
}
bool check_r(const string &str) {
    for (size_t i = 0; i < str.size(); i++) {
        char ch = str[i];
        if (!(isalnum(ch) || isspace(ch) || ch == ',')) {
            return false;
        }
    }
    return true;
}
bool check_r_args(vector<string> arguments) {
	if (arguments.size() != 3) {
		return false;
	}

	for (int i = 0; i < 3; i++) {
		if (! in_registers(arguments[i])){
			return false;
		}
	}
	return true;
}
vector<string> get_r_args(const string &str) {
	vector<string> out;
	int i = 0;
	for (int j = 0; j < 3; j++) {
		string temp = "";
		while (isalnum(str[i])) {
			temp += str[i];
			i++;
		}
		while (str[i] == ' ' || str[i] == ',') {
			i++;
		}
		out.push_back(temp);
	}
	return out;
}

bool is_immediate(const string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			if (i == 0) {
				if (str[i] != '-') {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

	int x = stoi(str);
	if (x < -2048 || x > 2047) {
		return false;
    }
	else{
		return true;
	}
}
bool is_label(const string &str) {
	if (str.length() == 0){
		return false;
	}
	if (isdigit(str[0])){
		return false;
	}
	for (size_t i = 0; i < str.length(); i++) {
		if (!(isalnum(str[i]) || str[i] == '_')){
			return false;
		}
	}
	return true;
}
bool check_i(const string &str) {
    for (size_t i = 0; i < str.size(); i++) {
        char ch = str[i];
        if (!(isalnum(ch) || isspace(ch) || ch == '_' || ch == ',' || ch == '(' || ch == ')' || ch == '-')) {
            return false;
        }
    }
    return true;
}
bool check_i_args(const string &instruction, vector<string> arguments) {
	if (instruction == "addi" || instruction == "andi" || instruction == "ori" || instruction == "jalr") {
		if (arguments.size() != 3) {
			return false;
		}
		for (int i = 0; i < 2; i++) {
			if (! in_registers(arguments[i])){
				return false;
			}
		}
		if (instruction == "jalr") {
			if (!(is_immediate(arguments[2]) || is_label(arguments[2]))) {
				return false;
			}
		}
		else if (! is_immediate(arguments[2])){
			return false;
		}
	}
	else {
		if (arguments.size() == 5) {
			if (in_registers(arguments[0]) && in_registers(arguments[3]) && is_immediate(arguments[1])) {
				if (arguments[2] == "(" && arguments[4] == ")") {
					return true;
				}
			}
			else{
				return false;
			}
		}
		if (arguments.size() != 3) {
			return false;
		}
		if (!(in_registers(arguments[0]) && in_registers(arguments[2]) && is_immediate(arguments[1]))) {
			return false;
		}
	}
	return true;
}
vector<string> get_i_args(const string &str) {
	vector<string> out;
	int i = 0;
	for (int j = 0; j < 5; j++) {
		string temp = "";
		while (isalnum(str[i]) || str[i] == '_' || str[i] == '(' || str[i] == ')' || str[i] == '-') {
			if (str[i] == '(' or str[i] == ')') {
				if (temp.length() != 0) {
					out.push_back(temp);
				}
				temp = "";
				temp += str[i];
				out.push_back(temp);
				temp = "";
				i++;
				continue;
			}

			else if (str[i] == '-'){
				if (! (temp.length() == 0 && isdigit(str[i+1]))) {
					vector<string> v;
					return v;
				}
				else {
					temp += str[i];
					i++;
					continue;
				}
			}

			temp += str[i];
			i++;
		}
		while (str[i] == ' ' || str[i] == ',') {
			i++;
		}
		if (temp.length() != 0) {
			out.push_back(temp);
		}
	}
	return out;
}

bool is_offset(const string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			if (i == 0) {
				if (str[i] != '-') {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

	int x = stoi(str);
	if (x < -4096 || x > 4095) {
		return false;
    }
	else{
		return true;
	}
}
bool check_sb(const string &str) {
	for (size_t i = 0; i < str.size(); i++) {
		char ch = str[i];
		if (!(isalnum(ch) || isspace(ch) || ch == ',' || ch == '_' || ch == '-')) {
			return false;
		}
	}
	return true;
}
bool check_sb_args(vector<string> &arguments) {
	if (arguments.size() != 3) {
		return false;
	}
	if (!(in_registers(arguments[0]) && in_registers(arguments[1]) && (is_label(arguments[2]) || is_offset(arguments[2])))) {
		return false;
	}
	return true;
}
vector<string> get_sb_args(const string &str) {
	vector<string> out;
	int i = 0;
	for (int j = 0; j < 3; j++) {
		string temp = "";
		while (isalnum(str[i]) || str[i] == '_' || str[i] == '-') {
			temp += str[i];
			i++;
		}
		while (str[i] == ' ' || str[i] == ',') {
			i++;
		}
		out.push_back(temp);
	}
	return out;
}

bool is_ui(const string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			if (i == 0) {
				if (str[i] != '-') {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

	long int x = stol(str);
	if (x < 0 || x > 1048575) {
		return false;
    }
	else{
		return true;
	}
}
bool check_u(const string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		char ch = str[i];
		if (!(isalnum(ch) || isspace(ch) || ch == ',' || ch == '_' || ch == '-')) {
			return false;
		}
	}
	return true;
}
bool check_u_args(vector<string> arguments) {
	if (arguments.size() != 2) {
		return false;
	}
	else if (!(in_registers(arguments[0]) && is_ui(arguments[1]))) {
		return false;
	}
	return true;
}
vector<string> get_u_args(const string &str) {
	vector<string> out;
	int i = 0;
	for (int j = 0; j < 2; j++){
		string temp = "";
		while (isalnum(str[i]) || str[i] == '_' || str[i] == '-') {
			if (str[i] == '-'){
				if (! (temp.length() == 0 && isdigit(str[i+1]))) {
					vector<string> v;
					return v;
				}
				else {
					temp += str[i];
					i++;
					continue;
				}
			}
			temp += str[i];
			i++;
		}
		while (str[i] == ' ' || str[i] == ',') {
			i++;
		}
		if (temp.length() != 0) {
			out.push_back(temp);
		}
	}
	return out;
}

bool is_uj(const string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			if (i == 0) {
				if (str[i] != '-') {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

	long int x = stol(str);
	if (x < -1048576 || x > 1048575) {
		return false;
    }
	else{
		return true;
	}
}
bool check_uj_args(vector<string> arguments) {
	if (arguments.size() != 2) {
		return false;
	}
	else if (!(in_registers(arguments[0]) && (is_uj(arguments[1]) || is_label(arguments[1])))) {
		return false;
	}
	return true;
}

string get_directive(const string &str) {
	string out = ".";
	for (size_t i = 1; i < str.length(); i++){
		if (isalpha(str[i]) || str[i] == '_'){
			out += str[i];
		}
		else{break;}
	}
	return out;
}
string remove_directive(const string &str) {
	int i = 1;
	while (isalpha(str[i]) || str[i] == '_') {
		i++;}
	while (str[i] == ',' || str[i] == ' '){
		i++;
	}

	int j = str.find('#');
	while (str[j] == ',' || str[j] == ' ' || str[j] == '#') {
		j--;
	}

	return str.substr(i, j-i+1);
}
bool is_number(const string &str) {
	int len = str.length();
	if (len == 0) {
		return false;
	}
	if (str[0] == '-') {
		if (len < 2) {
			return false;
		}
		for (size_t i = 1; i < len; i++) {
			if (!isdigit(str[i])) {
				return false;
			}
		}
	}
	else {
		for (size_t i = 0; i < len; i++) {
			if (!isdigit(str[i])) {
				return false;
			}
		}
	}
	return true;
}
bool check_directive_number_args(const string &directive, vector<string> input) {
	size_t len = input.size();
	for (size_t i = 0; i < len; i++) {
		if (! is_number(input[i])) {
			return false;
		}
	}
	return true;
}
vector<string> get_directive_number_args(const string &str) {
	vector<string> out;
	size_t i = 0;
	size_t len = str.length();
	while (i < len) {
		string temp = "";
		while (i < len && !(isspace(str[i]) || str[i] == ',')) {
			temp += str[i];
			i++;
		}
		while (i < len && (str[i] == ' ' || str[i] == ',')) {
			i++;
		}
		if (!temp.empty()) {out.push_back(temp);}
	}
	return out;
}

string decimalToHex(int num) {
    stringstream ss;
    ss << "0x" << hex << uppercase << num;
    return ss.str();
}
string binaryToHex(const string &binaryStr) {
    unsigned long num = bitset<32>(binaryStr).to_ulong();
    
    stringstream ss;
    ss << uppercase << hex << num;
    
    string out = ss.str();
    int extra = 8 - out.length();
    string prefix(extra, '0');

    return "0x" + prefix +  out;
}

string register_to_bin5(const string &reg) {
	int temp = stoi(reg.substr(1));
	bitset<5> out(temp);
	return out.to_string();
}
string immediate_to_ascii(int imm) {
	bitset<8> imm_bin(imm);
	string bin_string =  imm_bin.to_string();
	return bin4_to_Hex(bin_string.substr(0,4)) + bin4_to_Hex(bin_string.substr(4,4));
}
string immediate_to_bin12(int imm) {
    if (imm < 0) {
        imm += 4096;
    }
    bitset<12> imm_bin(imm);
    return imm_bin.to_string();
}
string immediate_to_bin13(int imm) {
	if (imm < 0) {
		imm += 8192;
	}
	bitset<13> imm_bin(imm);
	return imm_bin.to_string();
}
string immediate_to_bin20(int imm) {
	bitset<20> imm_bin(imm);
	return imm_bin.to_string();
}
string immediate_to_bin21(long int imm) {
	if (imm < 0){
		imm += 2097152;
	}
	bitset<21> imm_bin(imm);
	return imm_bin.to_string();
}

vector<string> extract_labels(const string &str) {
	vector<string> out;

	string temp = trim(str);
	while (temp.size() > 0){
		string label = get_instruction(temp);
		temp = remove_instruction(temp);
		int i = 0;

		if (temp[0] == ':'){
			out.push_back(label);
			while (temp[i] == ' ' || temp[i] == ',' || temp[i] == ':'){
				i++;
			}
			temp = temp.substr(i);
		}
		else{
			return out;
		}
	}
	return out;
}
string remove_labels(const string &str) {
	size_t pos = str.rfind(':');
	while (str[pos] == ':' || str[pos] == ' '){
		pos++;
	}
	if (pos == str.length() || pos == -1){
		return "";
	}
	return str.substr(pos);
}
bool good_label_line(const string &str) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	string temp;
	while (getline(ss, token, ':')) {
        tokens.push_back(token);
    }

	for (int i = 0; i < tokens.size() - 1; i++){
		temp = tokens[i];
		temp = trim(temp);
		if (! is_label(temp)){
			return false;
		}
	}
	return true;
}

map<string,int> get_labels() {
	set<string> r_format = define_r_format();
	set<string> i_format = define_i_format();
	set<string> s_format = define_s_format();
	set<string> u_format = define_u_format();
	set<string> uj_format = define_uj_format();
	set<string> sb_format = define_sb_format();
	set<string> registers = define_registers();
	set<string> directives = define_assembler_directives();

	bool segment = true;	// True means text segment.

	string filename = "input.asm";
	ifstream file(filename);

	map<string,int> out;
	
	if (!file.is_open()) { cerr << "Error extracting labels : file couldn't be opened!" << endl; return out;}
	string temp;

	int pc = -4;
	long memory_counter = 268435456;

	while (getline(file, temp)) {
		if (segment) {
			string line = trim(temp);
			if (line.empty()) {continue;}
			if (isalpha(line[0]) || line[0] == '_'){
				string instruction = get_instruction(line);
				
				int format = get_format(instruction, r_format, i_format, s_format, sb_format, u_format, uj_format);

				if (format != 0) {
					pc += 4;
				}

				else {
					vector<string> labels_in_line = extract_labels(line);
					for (int i = 0; i < labels_in_line.size(); i++){
						if (out.find(labels_in_line[i]) == out.end()){
							out[labels_in_line[i]] = pc + 4;
						}
						else{
							flag = false;
							error_label = labels_in_line[i];
							return out;
						}
					}
					string new_line = remove_labels(line);
					string instruction = get_instruction(new_line);
					int format = get_format(instruction, r_format, i_format, s_format, sb_format, u_format, uj_format);
					if (format != 0){
						pc += 4;
					}
				}
			}
			else if (line[0] == '.') {
				string directive = get_directive(line);
				string remaining = remove_directive(line);

				if (directive == ".data" && remaining.empty()) {
					segment = false;
				}
			}
		}
		else {
			string line = trim(temp);
			if (line.empty()) {continue;}
			if (line[0] == '.') {
				string directive = get_directive(line);
				string remaining = remove_directive(line);

				if (directive == ".text" && remaining.empty()) {
					segment = true;
				}
				else if (directive == ".dword") {
					vector<string> arguments = get_directive_number_args(remaining);
					memory_counter += arguments.size() * 8;
				}
				else if (directive == ".word") {
					vector<string> arguments = get_directive_number_args(remaining);
					memory_counter += arguments.size() * 4;
				}
				else if (directive == ".half") {
					vector<string> arguments = get_directive_number_args(remaining);
					memory_counter += arguments.size() * 2;
				}
				else if (directive == ".bite") {
					vector<string> arguments = get_directive_number_args(remaining);
					memory_counter += arguments.size();
				}
				else if (directive == ".asciiz") {
					bool slash = false;
					int len = remaining.length();

					if (len < 2 && remaining[0] == '\"' && remaining[len-1] != '\"') {
						for (size_t i = 1; i < len-1; i++) {
							int ascii_value = int(remaining[i]);
							if (ascii_value == 92) {
								if (!slash) {
									slash = true;
								}
								else {
									slash = false;
									memory_counter++;
								}
							}
							else if (ascii_value == 34) {
								if (slash) {
									slash = false;
									memory_counter++;
								}
							}
							else {
								if (slash) {
									slash = false;
									memory_counter++;
								}
								memory_counter++;
							}
						}
					}
				}
			}
			if (isalpha(line[0]) || line[0] == '_') {
				vector<string> labels_in_line = extract_labels(line);
				for (int i = 0; i < labels_in_line.size(); i++){
					if (out.find(labels_in_line[i]) == out.end()){
						out[labels_in_line[i]] = memory_counter;
						string new_line = remove_labels(line);
						string directive = get_directive(new_line);
						string remaining = remove_directive(new_line);

						if (directive == ".text" && remaining.empty()) {
							segment = true;
						}
						else if (directive == ".dword") {
							vector<string> arguments = get_directive_number_args(remaining);
							memory_counter += arguments.size() * 8;
						}
						else if (directive == ".word") {
							vector<string> arguments = get_directive_number_args(remaining);
							memory_counter += arguments.size() * 4;
						}
						else if (directive == ".half") {
							vector<string> arguments = get_directive_number_args(remaining);
							memory_counter += arguments.size() * 2;
						}
						else if (directive == ".bite") {
							vector<string> arguments = get_directive_number_args(remaining);
							memory_counter += arguments.size();
						}
						else if (directive == ".asciiz") {
							bool slash = false;
							int len = remaining.length();
		
							if (len < 2 && remaining[0] == '\"' && remaining[len-1] != '\"') {
								for (size_t i = 1; i < len-1; i++) {
									int ascii_value = int(remaining[i]);
									if (ascii_value == 92) {
										if (!slash) {
											slash = true;
										}
										else {
											slash = false;
											memory_counter++;
										}
									}
									else if (ascii_value == 34) {
										if (slash) {
											slash = false;
											memory_counter++;
										}
									}
									else {
										if (slash) {
											slash = false;
											memory_counter++;
										}
										memory_counter++;
									}
								}
							}
						}
					}
					else{
						flag = false;
						error_label = labels_in_line[i];
						return out;
					}
				}
			}
		}
	}

	file.close();
	return out;
}

int main() {
	set<string> r_format = define_r_format();
	set<string> i_format = define_i_format();
	set<string> s_format = define_s_format();
	set<string> u_format = define_u_format();
	set<string> uj_format = define_uj_format();
	set<string> sb_format = define_sb_format();
	set<string> registers = define_registers();
	set<string> directives = define_assembler_directives();

	bool segment = true;	// True means text segment.

	map<string, string> opcode;
	map<string, string> func3;
	map<string, string> func7;

	for (int i = 0; i < 1; i++) {
		// R-Type InstructionsNULL
		opcode["add"] = "0110011";  func3["add"] = "000";  func7["add"] = "0000000";
		opcode["and"] = "0110011";  func3["and"] = "111";  func7["and"] = "0000000";
		opcode["or"]  = "0110011";  func3["or"]  = "110";  func7["or"]  = "0000000";
		opcode["sll"] = "0110011";  func3["sll"] = "001";  func7["sll"] = "0000000";
		opcode["slt"] = "0110011";  func3["slt"] = "010";  func7["slt"] = "0000000";
		opcode["sra"] = "0110011";  func3["sra"] = "101";  func7["sra"] = "0100000";
		opcode["srl"] = "0110011";  func3["srl"] = "101";  func7["srl"] = "0000000";
		opcode["sub"] = "0110011";  func3["sub"] = "000";  func7["sub"] = "0100000";
		opcode["xor"] = "0110011";  func3["xor"] = "100";  func7["xor"] = "0000000";
		opcode["mul"] = "0110011";  func3["mul"] = "000";  func7["mul"] = "0000001";
		opcode["div"] = "0110011";  func3["div"] = "100";  func7["div"] = "0000001";
		opcode["rem"] = "0110011";  func3["rem"] = "100";  func7["rem"] = "0000011";

		// I-Type Instructions
		opcode["addi"] = "0010011"; func3["addi"] = "000";  func7["addi"] = "NULL";
		opcode["andi"] = "0010011"; func3["andi"] = "111";  func7["andi"] = "NULL";
		opcode["ori"]  = "0010011"; func3["ori"]  = "110";  func7["ori"]  = "NULL";
		opcode["lb"]   = "0000011"; func3["lb"]   = "000";  func7["lb"]   = "NULL";
		opcode["ld"]   = "0000011"; func3["ld"]   = "011";  func7["ld"]   = "NULL";
		opcode["lh"]   = "0000011"; func3["lh"]   = "001";  func7["lh"]   = "NULL";
		opcode["lw"]   = "0000011"; func3["lw"]   = "010";  func7["lw"]   = "NULL";
		opcode["jalr"] = "1100111"; func3["jalr"] = "000";  func7["jalr"] = "NULL";

		// S-Type Instructions
		opcode["sb"]   = "0100011"; func3["sb"]   = "000";  func7["sb"]   = "NULL";
		opcode["sw"]   = "0100011"; func3["sw"]   = "010";  func7["sw"]   = "NULL";
		opcode["sd"]   = "0100011"; func3["sd"]   = "011";  func7["sd"]   = "NULL";
		opcode["sh"]   = "0100011"; func3["sh"]   = "001";  func7["sh"]   = "NULL";

		// SB-Type Instructions
		opcode["beq"]  = "1100011"; func3["beq"]  = "000";  func7["beq"]  = "NULL";
		opcode["bne"]  = "1100011"; func3["bne"]  = "001";  func7["bne"]  = "NULL";
		opcode["bge"]  = "1100011"; func3["bge"]  = "101";  func7["bge"]  = "NULL";
		opcode["blt"]  = "1100011"; func3["blt"]  = "100";  func7["blt"]  = "NULL";

		// U-Type Instructions
		opcode["auipc"] = "0010111"; func3["auipc"] = "NULL";  func7["auipc"] = "NULL"; 
		opcode["lui"]   = "0110111"; func3["lui"]   = "NULL";  func7["lui"]   = "NULL"; 

		// UJ-Type Instructions
		opcode["jal"] = "1101111"; func3["jal"] = "NULL";  func7["jal"] = "NULL"; 
	}

	string filename = "input.asm";
	ifstream file(filename);
	
	if (!file.is_open()) { cerr << "Error opening input file!" << endl; return 1;}
	string temp;

	string output_filename = "output.mc";
	ofstream outputFile(output_filename);

	if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

	string data_filename = "data.mc";
	ofstream dataFile(data_filename);

	if (!dataFile.is_open()) {
		cerr << "Error opening output file!" << endl;
		return 1;
	}

	map<string,int> counter = get_labels();
	if (!flag){
		outputFile << "Error : label \'" << error_label << "\' defined multiple times." << endl;
		return 1;
	}

	int pc = -4;
	long memory_counter = 268435456;

	while (getline(file, temp)) {
		if (segment) {
			string line = trim(temp);
			if (line.empty()) {continue;}
			if (isalpha(line[0]) || line[0] == '_') {
				string instruction = get_instruction(line);
				string remaining = remove_instruction(line);
				
				int format = get_format(instruction, r_format, i_format, s_format, sb_format, u_format, uj_format);

				if (format == 1) {
					if (! check_r(remaining)){
						outputFile << "Error found in line : " << temp << endl;
						return 1;
					}

					vector<string> arguments = get_r_args(remaining);

					if (! check_r_args(arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					pc += 4;
					string bin_mc = func7[instruction] + register_to_bin5(arguments[2]) + register_to_bin5(arguments[1]) + func3[instruction] + register_to_bin5(arguments[0]) + opcode[instruction];

					string initial = decimalToHex(pc);
					string mc = binaryToHex(bin_mc);
					string instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + arguments[2];
					string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-" + register_to_bin5(arguments[0]) + "-" + register_to_bin5(arguments[1]) + "-" + register_to_bin5(arguments[2]) + "-NULL";

					outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
				}

				else if (format == 2) {
					if (! check_i(remaining)){
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					vector<string> arguments = get_i_args(remaining);
					if (! check_i_args(instruction, arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					pc += 4;
					string imm; string rs1; string rd = arguments[0];
					if (arguments.size() == 5){
						imm = arguments[1];
						rs1 = arguments[3];}else{
						if (instruction == "addi" || instruction == "andi" || instruction == "ori"){
							rs1 = arguments[1];
							imm = arguments[2];
						}
						else if (instruction == "jalr") {
							if (is_label(arguments[2])) {
								rs1 = arguments[1];
								imm = to_string(counter[arguments[2]]);
							}
							else {
								rs1 = arguments[1];
								imm = arguments[2];
							}
						}
						else{
							rs1 = arguments[2];
							imm = arguments[1];
						}
					}
					int x = stoi(imm);

					string bin_mc = immediate_to_bin12(x) + register_to_bin5(rs1) + func3[instruction] + register_to_bin5(rd) + opcode[instruction];

					string initial = decimalToHex(pc);
					string mc = binaryToHex(bin_mc);

					string instruction_code;
					if (instruction == "jalr") {
						instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + to_string(counter[arguments[2]]);
					}
					else if (arguments.size() == 5){
						instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + arguments[2] + arguments[3] + arguments[4];}else{
						instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + arguments[2];
					}

					string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-" + register_to_bin5(rd) + "-" + register_to_bin5(rs1) + "-NULL-" + immediate_to_bin12(x);
					outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
				}

				else if (format == 3) {
					if (! check_i(remaining)){
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					vector<string> arguments = get_i_args(remaining);
					if (! check_i_args(instruction, arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					pc += 4;
					string rs2 = arguments[0]; string imm = arguments[1]; string rs1;
					if (arguments.size() == 5){
						rs1 = arguments[3];}else{
						rs1 = arguments[2];
					}
					int x = stoi(imm);
					string mc_imm = immediate_to_bin12(x);

					string bin_mc = mc_imm.substr(0,7) + register_to_bin5(rs2) + register_to_bin5(rs1) + func3[instruction] + mc_imm.substr(7,5) + opcode[instruction];

					string initial = decimalToHex(pc);
					string mc = binaryToHex(bin_mc);

					string instruction_code;
					if (arguments.size() == 5){
						instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + arguments[2] + arguments[3] + arguments[4];}else{
						instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + arguments[2];
					}

					string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-NULL-" + register_to_bin5(rs1) + "-" + register_to_bin5(rs2) + "-" + immediate_to_bin12(x);
					outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
				}

				else if (format == 4) {
					if (! check_sb(remaining)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					vector<string> arguments = get_sb_args(remaining);
					if (! check_sb_args(arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					if (is_label(arguments[2])){
						if (counter.find(arguments[2]) == counter.end()){
							outputFile << "Error found in line : " << line << endl;
							return 1;
						}
					}

					pc += 4;
					string rs1 = arguments[0]; string rs2 = arguments[1]; int offset;
					if (is_label(arguments[2])){
						int label_position = counter[arguments[2]];
						offset = label_position - pc;}else{
						offset = stoi(arguments[2]);
					}
					string str_offset = immediate_to_bin13(offset);

					string bin_mc = str_offset.substr(0,1) + str_offset.substr(2,6) + register_to_bin5(rs2) + register_to_bin5(rs1) + func3[instruction] + str_offset.substr(8,4) + str_offset.substr(1,1) + opcode[instruction];
					
					string initial = decimalToHex(pc);
					string mc = binaryToHex(bin_mc);
					string instruction_code = instruction + " " + rs1 + " " + rs2 + " " + to_string(offset - (abs(offset) % 2));
					string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-NULL-" + register_to_bin5(rs1) + "-" + register_to_bin5(rs2) + "-" + str_offset;

					outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
				}

				else if (format == 5) {
					if (! check_u(remaining)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					vector<string> arguments = get_u_args(remaining);
					if (! check_u_args(arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					pc += 4;
					long int x = stol(arguments[1]);

					string bin_mc = immediate_to_bin20(x) + register_to_bin5(arguments[0]) + opcode[instruction];

					string initial = decimalToHex(pc);
					string mc = binaryToHex(bin_mc);
					string instruction_code = instruction + " " + arguments[0] + " " + arguments[1];
					string executor = opcode[instruction] + "-NULL" + "-NULL-" + register_to_bin5(arguments[0]) + "-NULL" + "-NULL-" + immediate_to_bin20(x);

					outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
				}

				else if (format == 6) {
					if (! check_u(remaining)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					vector<string> arguments = get_u_args(remaining);
					if (! check_uj_args(arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					pc += 4;
					long int x;

					if (is_label(arguments[1])){
						if (counter.find(arguments[1]) == counter.end()){
							outputFile << "Error found in line : " << line << endl;
							return 1;
						}
					}

					if (is_label(arguments[1])){
						int label_position = counter[arguments[1]];
						x = label_position - pc;}else{
						x = stol(arguments[1]);
					}
					string str_offset = immediate_to_bin21(x);

					string bin_mc = str_offset.substr(0,1) + str_offset.substr(10,10) + str_offset.substr(9,1) + str_offset.substr(1,8) + register_to_bin5(arguments[0]) + opcode[instruction];

					string initial = decimalToHex(pc);
					string mc = binaryToHex(bin_mc);
					string instruction_code = instruction + " " + arguments[0] + " " + to_string(x);
					string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-" + register_to_bin5(arguments[0]) + "-NULL-NULL-" + str_offset;

					outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
				}

				else {
					if (remaining[0] == ':') {
						remaining = "label" + remaining;
						if (! good_label_line(remaining)) {
							outputFile << "Error found in line : " << instruction << remaining << endl;
							return 1;
						}
						string new_line;
						new_line = remove_labels(remaining);

						if (new_line.empty()) {continue;}
						if (isalpha(new_line[0]) || new_line[0] == '_') {
							string instruction = get_instruction(new_line);
							string remaining = remove_instruction(new_line);
							
							int format = get_format(instruction, r_format, i_format, s_format, sb_format, u_format, uj_format);
				
							if (format == 1) {
								if (! check_r(remaining)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
				
								vector<string> arguments = get_r_args(remaining);
				
								if (! check_r_args(arguments)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								pc += 4;
								string bin_mc = func7[instruction] + register_to_bin5(arguments[2]) + register_to_bin5(arguments[1]) + func3[instruction] + register_to_bin5(arguments[0]) + opcode[instruction];
				
								string initial = decimalToHex(pc);
								string mc = binaryToHex(bin_mc);
								string instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + arguments[2];
								string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-" + register_to_bin5(arguments[0]) + "-" + register_to_bin5(arguments[1]) + "-" + register_to_bin5(arguments[2]) + "-NULL";
				
								outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
							}
				
							else if (format == 2) {
								if (! check_i(remaining)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
				
								vector<string> arguments = get_i_args(remaining);
								if (! check_i_args(instruction, arguments)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								pc += 4;
								string imm; string rs1; string rd = arguments[0];
								if (arguments.size() == 5) {
									imm = arguments[1];
									rs1 = arguments[3];}else {
									if (instruction == "addi" || instruction == "andi" || instruction == "ori"){
										rs1 = arguments[1];
										imm = arguments[2];
									}
									else {
										rs1 = arguments[2];
										imm = arguments[1];
									}
								}
								int x = stoi(imm);
				
								string bin_mc = immediate_to_bin12(x) + register_to_bin5(rs1) + func3[instruction] + register_to_bin5(rd) + opcode[instruction];
				
								string initial = decimalToHex(pc);
								string mc = binaryToHex(bin_mc);
				
								string instruction_code;
								if (arguments.size() == 5){
									instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + arguments[2] + arguments[3] + arguments[4];}else{
									instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + arguments[2];
								}
				
								string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-" + register_to_bin5(rd) + "-" + register_to_bin5(rs1) + "-NULL-" + immediate_to_bin12(x);
								outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
							}
				
							else if (format == 3) {
								if (! check_i(remaining)){
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
				
								vector<string> arguments = get_i_args(remaining);
								if (! check_i_args(instruction, arguments)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								pc += 4;
								string rs2 = arguments[0]; string imm = arguments[1]; string rs1;
								if (arguments.size() == 5){
									rs1 = arguments[3];}else{
									rs1 = arguments[2];
								}
								int x = stoi(imm);
								string mc_imm = immediate_to_bin12(x);
				
								string bin_mc = mc_imm.substr(0,7) + register_to_bin5(rs2) + register_to_bin5(rs1) + func3[instruction] + mc_imm.substr(7,5) + opcode[instruction];
				
								string initial = decimalToHex(pc);
								string mc = binaryToHex(bin_mc);
				
								string instruction_code;
								if (arguments.size() == 5){
									instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + arguments[2] + arguments[3] + arguments[4];}else{
									instruction_code = instruction + " " + arguments[0] + " " + arguments[1] + " " + arguments[2];
								}
				
								string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-NULL-" + register_to_bin5(rs1) + "-" + register_to_bin5(rs2) + "-" + immediate_to_bin12(x);
								outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
							}
				
							else if (format == 4) {
								if (! check_sb(remaining)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
				
								vector<string> arguments = get_sb_args(remaining);
								if (! check_sb_args(arguments)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								pc += 4;
								string rs1 = arguments[0]; string rs2 = arguments[1]; int offset;
								if (is_label(arguments[2])){
									int label_position = counter[arguments[2]];
									offset = label_position - pc;}else{
									offset = stoi(arguments[2]);
								}
								string str_offset = immediate_to_bin13(offset);
				
								string bin_mc = str_offset.substr(0,1) + str_offset.substr(2,6) + register_to_bin5(rs2) + register_to_bin5(rs1) + func3[instruction] + str_offset.substr(8,4) + str_offset.substr(1,1) + opcode[instruction];
								
								string initial = decimalToHex(pc);
								string mc = binaryToHex(bin_mc);
								string instruction_code = instruction + " " + rs1 + " " + rs2 + " " + to_string(offset - (abs(offset) % 2));
								string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-NULL-" + register_to_bin5(rs1) + "-" + register_to_bin5(rs2) + "-" + str_offset;
				
								outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
							}
				
							else if (format == 5) {
								if (! check_u(remaining)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								vector<string> arguments = get_u_args(remaining);
								if (! check_u_args(arguments)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								pc += 4;
								long int x = stol(arguments[1]);
				
								string bin_mc = immediate_to_bin20(x) + register_to_bin5(arguments[0]) + opcode[instruction];
				
								string initial = decimalToHex(pc);
								string mc = binaryToHex(bin_mc);
								string instruction_code = instruction + " " + arguments[0] + " " + arguments[1];
								string executor = opcode[instruction] + "-NULL" + "-NULL-" + arguments[0] + "-NULL" + "-NULL-" + immediate_to_bin20(x);
				
								outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
							}
				
							else if (format == 6) {
								if (! check_u(remaining)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								vector<string> arguments = get_u_args(remaining);
								if (! check_uj_args(arguments)) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								pc += 4;
								long int x;

								if (is_label(arguments[1])){
									if (counter.find(arguments[1]) == counter.end()){
										outputFile << "Error found in line : " << line << endl;
										return 1;
									}
								}
			
								if (is_label(arguments[1])){
									int label_position = counter[arguments[1]];
									x = label_position - pc;}else{
									x = stol(arguments[1]);
								}
								string str_offset = immediate_to_bin21(x);
				
								string bin_mc = str_offset.substr(0,1) + str_offset.substr(10,10) + str_offset.substr(9,1) + str_offset.substr(1,8) + register_to_bin5(arguments[0]) + opcode[instruction];
				
								string initial = decimalToHex(pc);
								string mc = binaryToHex(bin_mc);
								string instruction_code = instruction + " " + arguments[0] + " " + to_string(x);
								string executor = opcode[instruction] + "-" + func3[instruction] + "-" + func7[instruction] + "-" + arguments[0] + "-NULL-NULL-" + str_offset;
				
								outputFile << initial << " " << mc << " , " << instruction_code << " # " << executor << endl;
							}
				
							else {
								outputFile << "Error found in line : " << line << endl;
								return 1;
							}
						}
						else if (new_line[0] == '.') {
							string directive = get_directive(new_line);
							string remaining = remove_directive(new_line);
							if (!(directive == ".data" && remaining.empty())) {
								outputFile << "Error found in line" << line << endl;
							}
							else {
								segment = false;
							}
						}
						else {
							outputFile << "Error found in line : " << line << endl;
							return 1;
						}
					}
					else{
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
				}
			}
			else if (line[0] == '.'){
				string directive = get_directive(line);
				string remaining = remove_directive(line);

				if (!((directive == ".data" || directive == ".text") && remaining.empty())) {
					outputFile << "Error found in line : " << line << endl;
					return 1;
				}
				else {
					if (directive == ".text") {
						continue;
					}
					else {
						segment = false;
					}
				}
			}
			else if (line[0] == '#'){
				continue;
			}
			else{
				outputFile << "Error found in line : " << line << endl;
				return 1;
			}
		}
		else {
			string line = trim(temp);
			if (line.empty()) {continue;}
			if (line[0] == '.') {
				string directive = get_directive(line);
				string remaining = remove_directive(line);

				if (directive == ".data" && remaining.empty()) {
					continue;
				}
				else if (directive == ".text" && remaining.empty()) {
					segment = true;
				}
				else if (directive == ".dword") {
					vector<string> arguments = get_directive_number_args(remaining);
					if (!check_directive_number_args(directive, arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					int len = arguments.size();
					for (size_t i = 0; i < len; i++) {
						string initial = decimalToHex(memory_counter);

						string mc = dword(arguments[i]);
						string final = "0x";
						int j_limit = mc.size() / 4;
						for (size_t j = 0; j < j_limit; j++) {
							final += bin4_to_Hex(mc.substr(4*j,4));
						}
						dataFile << initial << ' ' << final << endl;
						
						memory_counter += 8;
					}
				}
				else if (directive == ".word") {
					vector<string> arguments = get_directive_number_args(remaining);
					if (!check_directive_number_args(directive, arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					int len = arguments.size();
					for (size_t i = 0; i < len; i++) {
						string initial = decimalToHex(memory_counter);

						string mc = word(arguments[i]);
						string final = "0x";
						int j_limit = mc.size() / 4;
						for (size_t j = 0; j < j_limit; j++) {
							final += bin4_to_Hex(mc.substr(4*j,4));
						}
						dataFile << initial << ' ' << final << endl;
						
						memory_counter += 4;
					}
				}
				else if (directive == ".half") {
					vector<string> arguments = get_directive_number_args(remaining);
					if (!check_directive_number_args(directive, arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					int len = arguments.size();
					for (size_t i = 0; i < len; i++) {
						string initial = decimalToHex(memory_counter);

						string mc = half(arguments[i]);
						string final = "0x";
						int j_limit = mc.size() / 4;
						for (size_t j = 0; j < j_limit; j++) {
							final += bin4_to_Hex(mc.substr(4*j,4));
						}
						dataFile << initial << ' ' << final << endl;

						memory_counter += 2;
					}
				}
				else if (directive == ".bite") {
					vector<string> arguments = get_directive_number_args(remaining);
					if (!check_directive_number_args(directive, arguments)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}

					int len = arguments.size();
					for (size_t i = 0; i < len; i++) {
						string initial = decimalToHex(memory_counter);

						string mc = bite(arguments[i]);
						string final = "0x";
						int j_limit = mc.size() / 4;
						for (size_t j = 0; j < j_limit; j++) {
							final += bin4_to_Hex(mc.substr(4*j,4));
						}
						dataFile << initial << ' ' << final << endl;

						memory_counter += 1;
					}
				}
				else if (directive == ".asciiz") {
					bool slash = false;
					int len = remaining.length();

					if (len < 2) {
						outputFile << "Error found in line : " << line << endl;
					}

					if (remaining[0] != '\"' || remaining[len-1] != '\"') {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					else {
						for (size_t i = 1; i < len-1; i++) {
							int ascii_value = int(remaining[i]);
							if (ascii_value == 92) {
								if (!slash) {
									slash = true;
									if (i == len-2) {
										outputFile << "Error foud in line : " << line << endl;
										return 1;
									}
								}
								else {
									slash = false;
									string initial = decimalToHex(memory_counter);
									string final = immediate_to_ascii(ascii_value);
									dataFile << initial << " 0x" << final << endl;
									memory_counter++;
								}
							}
							else if (ascii_value == 34) {
								if (!slash) {
									outputFile << "Error found in line : " << line << endl;
									return 1;
								}
								else {
									slash = false;
									string initial = decimalToHex(memory_counter);
									string final = immediate_to_ascii(34);
									dataFile << initial << " 0x" << final << endl;
									memory_counter++;
								}
							}
							else {
								if (slash) {
									slash = false;
									string initial = decimalToHex(memory_counter);
									string final = immediate_to_ascii(92);
									dataFile << initial << " 0x" << final << endl;
									memory_counter++;
								}
								string initial = decimalToHex(memory_counter);
								string final = immediate_to_ascii(ascii_value);
								dataFile << initial << " 0x" << final << endl;
								memory_counter++;
							}
						}
					}
				}
				else {
					outputFile << "Error found in line : " << line << endl;
					return 1;
				}
			}
			if (isalpha(line[0]) || line[0] == '_') {
				string instruction = get_instruction(line);
				string remaining = remove_instruction(line);

				if (remaining[0] == ':'){
					remaining = "label" + remaining;
					if (! good_label_line(remaining)) {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
					string new_line = remove_labels(remaining);
					if (new_line.empty()) {continue;}
					if (new_line[0] == '.') {
						string directive = get_directive(new_line);
						string remaining = remove_directive(new_line);

						if (directive == ".data" && remaining.empty()) {
							continue;
						}
						else if (directive == ".text" && remaining.empty()) {
							segment = true;
						}
						else if (directive == ".dword") {
							vector<string> arguments = get_directive_number_args(remaining);
							if (!check_directive_number_args(directive, arguments)) {
								outputFile << "Error found in line : " << line << endl;
								return 1;
							}

							int len = arguments.size();
							for (size_t i = 0; i < len; i++) {
								string initial = decimalToHex(memory_counter);

								string mc = dword(arguments[i]);
								string final = "0x";
								int j_limit = mc.size() / 4;
								for (size_t j = 0; j < j_limit; j++) {
									final += bin4_to_Hex(mc.substr(4*j,4));
								}
								dataFile << initial << ' ' << final << endl;

								memory_counter += 8;
							}
						}
						else if (directive == ".word") {
							vector<string> arguments = get_directive_number_args(remaining);
							if (!check_directive_number_args(directive, arguments)) {
								outputFile << "Error found in line : " << line << endl;
								return 1;
							}

							int len = arguments.size();
							for (size_t i = 0; i < len; i++) {
								string initial = decimalToHex(memory_counter);

								string mc = word(arguments[i]);
								string final = "0x";
								int j_limit = mc.size() / 4;
								for (size_t j = 0; j < j_limit; j++) {
									final += bin4_to_Hex(mc.substr(4*j,4));
								}
								dataFile << initial << ' ' << final << endl;

								memory_counter += 4;
							}
						}
						else if (directive == ".half") {
							vector<string> arguments = get_directive_number_args(remaining);
							if (!check_directive_number_args(directive, arguments)) {
								outputFile << "Error found in line : " << line << endl;
								return 1;
							}

							int len = arguments.size();
							for (size_t i = 0; i < len; i++) {
								string initial = decimalToHex(memory_counter);

								string mc = half(arguments[i]);
								string final = "0x";
								int j_limit = mc.size() / 4;
								for (size_t j = 0; j < j_limit; j++) {
									final += bin4_to_Hex(mc.substr(4*j,4));
								}
								dataFile << initial << ' ' << final << endl;

								memory_counter += 2;
							}
						}
						else if (directive == ".bite") {
							vector<string> arguments = get_directive_number_args(remaining);
							if (!check_directive_number_args(directive, arguments)) {
								outputFile << "Error found in line : " << line << endl;
								return 1;
							}

							int len = arguments.size();
							for (size_t i = 0; i < len; i++) {
								string initial = decimalToHex(memory_counter);
				
								string mc = bite(arguments[i]);
								string final = "0x";
								int j_limit = mc.size() / 4;
								for (size_t j = 0; j < j_limit; j++) {
									final += bin4_to_Hex(mc.substr(4*j,4));
								}
								dataFile << initial << ' ' << final << endl;

								memory_counter += 1;
							}
						}
						else if (directive == ".asciiz") {
							bool slash = false;
							int len = remaining.length();
		
							if (len < 2) {
								outputFile << "Error found in line : " << line << endl;
							}
		
							if (remaining[0] != '\"' || remaining[len-1] != '\"') {
								outputFile << "Error found in line : " << line << endl;
								return 1;
							}
							else {
								for (size_t i = 1; i < len-1; i++) {
									int ascii_value = int(remaining[i]);
									if (ascii_value == 92) {
										if (!slash) {
											slash = true;
											if (i == len-2) {
												outputFile << "Error foud in line : " << line << endl;
												return 1;
											}
										}
										else {
											slash = false;
											string initial = decimalToHex(memory_counter);
											string final = immediate_to_ascii(ascii_value);
											dataFile << initial << " 0x" << final << endl;
											memory_counter++;
										}
									}
									else if (ascii_value == 34) {
										if (!slash) {
											outputFile << "Error found in line : " << line << endl;
											return 1;
										}
										else {
											slash = false;
											string initial = decimalToHex(memory_counter);
											string final = immediate_to_ascii(34);
											dataFile << initial << " 0x" << final << endl;
											memory_counter++;
										}
									}
									else {
										if (slash) {
											slash = false;
											string initial = decimalToHex(memory_counter);
											string final = immediate_to_ascii(92);
											dataFile << initial << " 0x" << final << endl;
											memory_counter++;
										}
										string initial = decimalToHex(memory_counter);
										string final = immediate_to_ascii(ascii_value);
										dataFile << initial << " 0x" << final << endl;
										memory_counter++;
									}
								}
							}
						}
						else {
							outputFile << "Error found in line : " << line << endl;
							return 1;
						}
					}
					else {
						outputFile << "Error found in line : " << line << endl;
						return 1;
					}
				}
				else {
					outputFile << "Error found in line : " << line << endl;
					return 1;
				}
			}
		}
	}

	pc += 4;
	string initial = decimalToHex(pc);
	outputFile << initial << " <textTerminator>" << endl << endl;
	initial = decimalToHex(memory_counter);
	dataFile << initial << " <dataTerminator>";
	dataFile.close();

	ifstream read_dataFile(data_filename);
	if (!read_dataFile.is_open()) { cout << "Error reading .data segment : data.mc file couldn't be opened!";}
	while (getline(read_dataFile, temp)) { outputFile << temp << endl;}

	file.close();
	outputFile.close();
	read_dataFile.close();

	const char* remover = "data.mc";
	remove(remover);
	return 0;
}
