#include <iostream>
#include <map>
#include <climits>
#include <numeric>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

map<int,string> make_registers(){
    map<int,string> out;
    string temp;
    for (int i = 0; i < 2; i++) {
        out[i] = "0x00000000";
    }
    out[2] = "0x7FFFFFD8";
    out[3] = "0x10000000";
    for (int i = 4; i < 32; i++) {
        out[i] = "0x00000000";
    }
    return out;
}

int hex_to_int(const string &str) {
    int len = str.length();
    int out = 0;

    for (int i = 2; i < len; i++) {
        char ch = str[i];
        int val = 0;

        if (ch >= '0' && ch <= '9') val = ch - '0';
        else if (ch >= 'A' && ch <= 'F') val = ch - 'A' + 10;
        else if (ch >= 'a' && ch <= 'f') val = ch - 'a' + 10;

        out = (out * 16) + val;
    }

    return out;
}
int bin_to_int(const string &str, bool sign_extend = false) {
    int result = 0;
    int n = str.size();

    for (int i = 0; i < n; i++) {
        result = result * 2 + (str[i] - '0');
    }

    if (sign_extend && str[0] == '1') {
        result -= (1 << n);
    }

    return result;
}
string hex_to_bin(const string &str) {
    int len = str.length();
    string out;
    for (int i = 2; i < len; i++) {
        if (str[i] == '0') {out += "0000";}
        else if (str[i] == '1') {out += "0001";}
        else if (str[i] == '2') {out += "0010";}
        else if (str[i] == '3') {out += "0011";}
        else if (str[i] == '4') {out += "0100";}
        else if (str[i] == '5') {out += "0101";}
        else if (str[i] == '6') {out += "0110";}
        else if (str[i] == '7') {out += "0111";}
        else if (str[i] == '8') {out += "1000";}
        else if (str[i] == '9') {out += "1001";}
        else if (str[i] == 'A') {out += "1010";}
        else if (str[i] == 'B') {out += "1011";}
        else if (str[i] == 'C') {out += "1100";}
        else if (str[i] == 'D') {out += "1101";}
        else if (str[i] == 'E') {out += "1110";}
        else if (str[i] == 'F') {out += "1111";}
        else if (str[i] == 'a') {out += "1010";}
        else if (str[i] == 'b') {out += "1011";}
        else if (str[i] == 'c') {out += "1100";}
        else if (str[i] == 'd') {out += "1101";}
        else if (str[i] == 'e') {out += "1110";}
        else if (str[i] == 'f') {out += "1111";}
        else {
        }
    }
    return out;
}
string decimal_to_hex8(const int &num) {
    stringstream ss;
    ss << hex << uppercase << num;
    string temp = ss.str();
    int len = temp.length();

    string out = "0x" + string(8 - len, '0') + temp;
    return out;
}

vector<string> fetch_line(const string &temp) {
    vector<string> out;
    stringstream ss(temp);
    string word;

    while (ss >> word) {
        if (word == ",") {
            break;
        }
        out.push_back(word);
    }
    return out;
}
map<int,string> fetch() {
    map<int,string> out;

    string  mc_filename = "output.mc";
    ifstream mcFile(mc_filename);
    if(!mcFile.is_open()) {cerr << "Error opening mc file" << endl;return out;}

    string temp;
    while (getline(mcFile, temp)) {
        vector<string> pc_mc = fetch_line(temp);
        int pc = hex_to_int(pc_mc[0]);
        int pseudo_pc = pc / 4;
        string mc = pc_mc[1];

        if (mc == "<textTerminator>") {
            out[pc] = mc;
            getline(mcFile, temp);

            while (getline(mcFile, temp)) {
                vector<string> pc_mc = fetch_line(temp);
                int pc = hex_to_int(pc_mc[0]);
                int pseudo_pc = pc / 4;
                pseudo_pc = pseudo_pc * 4;
                string mc = pc_mc[1];

                if (mc == "<dataTerminator>") {
                    return out;
                }
                else if (pc == pseudo_pc) {
                    if (out.find(pc) != out.end()) {
                        out[pc] = "0x" + out[pc].substr(2, 10 - mc.length()) + mc.substr(2);
                    }
                    else {
                        out[pc] = "0x" + string(10 - mc.length(), '0') + mc.substr(2);
                    }
                }
                else {
                    int off = pc - pseudo_pc;
                    if (out.find(pseudo_pc) != out.end()) {
                        if (mc.length() <= 10 - (2 * off)) {
                            out[pseudo_pc] = "0x" + string(8 - (2 * off) - (mc.length() - 2), '0') + mc.substr(2 ) + out[pseudo_pc].substr(10 - (2 * off));
                        }
                        else {
                            out[pseudo_pc] = "0x" + mc.substr(mc.length() - (8 - (2 * off))) + out[pseudo_pc].substr(10 - (2 * off));
                            string rem = mc.substr(2, mc.length() - (8 - (2 * off)) - 2);
                            int rem_len = rem.length();

                            if (out.find(pseudo_pc + 4) != out.end()) {
                                out[pseudo_pc + 4] = out[pseudo_pc + 4].substr(0, 10 - rem_len) + rem;
                            }
                            else {
                                out[pseudo_pc + 4] = "0x" + string(8 - rem_len, '0') + rem;
                            }
                        }
                    }
                    else {
                        if (mc.length() <= 10 - (2 * off)) {
                            out[pseudo_pc] = "0x" + string(8 - (2 * off) - (mc.length() - 2), '0') + mc.substr(2 ) + string(2 * off, '0');
                        }
                        else {
                            out[pseudo_pc] = "0x" + mc.substr(mc.length() - (8 - (2 * off))) + string(2 * off, '0');
                            string rem = mc.substr(2, mc.length() - (8 - (2 * off)) - 2);
                            int rem_len = rem.length();

                            if (out.find(pseudo_pc + 4) != out.end()) {
                                out[pseudo_pc + 4] = out[pseudo_pc + 4].substr(0, 10 - rem_len) + rem;
                            }
                            else {
                                out[pseudo_pc + 4] = "0x" + string(8 - rem_len, '0') + rem;
                            }
                        }
                    }
                }
            }
        }
        else {
            if (out.find(pc) != out.end()) {
                out[pc] = "0x" + out[pc].substr(2,10 - mc.length()) + mc.substr(2);
            }
            else {
                out[pc] = "0x" + string(10 - mc.length(), '0') + mc.substr(2);
            }
        }
    }

    return out;
}

vector<int> get_instruction(const string &bin32) {
    string opcode = bin32.substr(25);
    vector<int> out;
    if (opcode == "0110011") {
        out.push_back(1);
        string func3 = bin32.substr(17, 3);
        string func7 = bin32.substr(0,7);
		if (func3 == "000" && func7 == "0000000")       out.push_back(1);
		else if (func3 == "111" && func7 == "0000000")  out.push_back(2);
		else if (func3 == "110" && func7 == "0000000")  out.push_back(3);
		else if (func3 == "001" && func7 == "0000000")  out.push_back(4);
		else if (func3 == "010" && func7 == "0000000")  out.push_back(5);
		else if (func3 == "101" && func7 == "0100000")  out.push_back(6);
		else if (func3 == "101" && func7 == "0000000")  out.push_back(7);
		else if (func3 == "000" && func7 == "0100000")  out.push_back(8);
		else if (func3 == "100" && func7 == "0000000")  out.push_back(9);
		else if (func3 == "000" && func7 == "0000001")  out.push_back(10);
		else if (func3 == "100" && func7 == "0000001")  out.push_back(11);
		else if (func3 == "100" && func7 == "0000011")  out.push_back(12);
    }

    else if (opcode == "0010011") {
        out.push_back(2);
        string func3 = bin32.substr(17,3);
        if (func3 == "000")         out.push_back(1);
        else if (func3 == "111")    out.push_back(2);
        else if (func3 == "110")    out.push_back(3);
    }

    else if (opcode == "0000011") {
        out.push_back(2);
        string func3 = bin32.substr(17,3);  
        if (func3 == "000")         out.push_back(4);
        else if (func3 == "011")    out.push_back(5);
        else if (func3 == "001")    out.push_back(6);
        else if (func3 == "010")    out.push_back(7);
    }

    else if (opcode == "1100111") {
        out.push_back(2);
        string func3 = bin32.substr(17,3);  
        if (func3 == "000") out.push_back(8);
    }

    else if (opcode == "0100011") {
        out.push_back(3);
        string func3 = bin32.substr(17,3);
        if (func3 == "000")         out.push_back(1);
        else if (func3 == "010")    out.push_back(2);
        else if (func3 == "011")    out.push_back(3);
        else if (func3 == "001")    out.push_back(4);
    }

    else if (opcode == "1100011") {
        out.push_back(4);
        string func3 = bin32.substr(17,3);
        if (func3 == "000")         out.push_back(1);
        else if (func3 == "001")    out.push_back(2);
        else if (func3 == "101")    out.push_back(3);
        else if (func3 == "100")    out.push_back(4);
    }

    else if (opcode == "0010111") {
        out.push_back(5);
        out.push_back(1);
    }

    else if (opcode == "0110111") {
        out.push_back(5);
        out.push_back(2);
    }

    else if (opcode == "1101111") {
        out.push_back(6);
        out.push_back(1);
    }

    return out;
}
vector<int> get_fields(const string &bin32, const vector<int> &format_and_instruction) {
    int format = format_and_instruction[0];
    int instruction = format_and_instruction[1];
    
    int rd = 0;
    int rs1 = 0;
    int rs2 = 0;
    int imm = 0;
    switch (format) {
        case 1:
            rd  = bin_to_int(bin32.substr(20, 5));
            rs1 = bin_to_int(bin32.substr(12, 5));
            rs2 = bin_to_int(bin32.substr(7, 5));
            break;
        case 2:
            rd  = bin_to_int(bin32.substr(20, 5));
            rs1 = bin_to_int(bin32.substr(12, 5));
            imm = bin_to_int(bin32.substr(0, 12), true);
            break;
        case 3:
            rs1 = bin_to_int(bin32.substr(12, 5));
            rs2 = bin_to_int(bin32.substr(7, 5));
            imm = bin_to_int(bin32.substr(0, 7) + bin32.substr(20, 5), true);
            break;
        case 4:
            rs1 = bin_to_int(bin32.substr(12, 5));
            rs2 = bin_to_int(bin32.substr(7, 5));
            imm = bin_to_int(string(1, bin32[0]) + bin32.substr(24, 1) + bin32.substr(1, 6) + bin32.substr(20, 4) + "0", true);
            break;
        case 5:
            rd  = bin_to_int(bin32.substr(20, 5));
            imm = bin_to_int(bin32.substr(0, 20));
            break;
        case 6:
            rd = bin_to_int(bin32.substr(20, 5));
            imm = bin_to_int(string(1, bin32[0]) + bin32.substr(12, 8) + string(1, bin32[11]) + bin32.substr(1, 10) + "0", true);
            break;
        default:
            break;
    }

    vector<int> out;
    out.push_back(rd);
    out.push_back(rs1);
    out.push_back(rs2);
    out.push_back(imm);

    return out;
}

void control_path(const int &format, const int &command, int &MuxB, int &ALU_switch, int &IAG_switch, bool &Memory_required, int &Writeback_switch, bool &load, int &size) {
    switch (format) {
        case 1:
            MuxB = 0;
            ALU_switch = command;
            IAG_switch = 1;
            Memory_required = false;
            Writeback_switch = 1;
            break;
        case 2:
            MuxB = 1;
            switch (command) {
                case 1:
                case 2:
                case 3:
                    ALU_switch = command;
                    IAG_switch = 1;
                    Memory_required = false;
                    Writeback_switch = 1;
                    break;
                case 4:
                    ALU_switch = 1;
                    IAG_switch = 1;
                    Memory_required = true;
                    load = true;
                    size = 1;
                    Writeback_switch = 2;
                    break;
                case 5:
                    ALU_switch = 1;
                    IAG_switch = 1;
                    Memory_required = true;
                    load = true;
                    size = 8;
                    Writeback_switch = 2;
                    break;
                case 6:
                    ALU_switch = 1;
                    IAG_switch = 1;
                    Memory_required = true;
                    load = true;
                    size = 2;
                    Writeback_switch = 2;
                    break;
                case 7:
                    ALU_switch = 1;
                    IAG_switch = 1;
                    Memory_required = true;
                    load = true;
                    size = 4;
                    Writeback_switch = 2;
                    break;
                case 8:
                    ALU_switch = 1;
                    IAG_switch = 3;
                    Memory_required = false;
                    Writeback_switch = 3;
                    break;
                default: break;
            }
            break;
        case 3:
            MuxB = 1;
            ALU_switch = 1;
            IAG_switch = 1;
            Memory_required = true;
            load = false;
            Writeback_switch = 0;
            switch (command) {
                case 1: size = 1; break;
                case 2: size = 4; break;
                case 3: size = 8; break;
                case 4: size = 2; break;
                default: break;
            }
            break;
        case 4:
            MuxB = 0;
            ALU_switch = command + 12;
            IAG_switch = 2;
            Memory_required = false;
            Writeback_switch = 0;
            break;
        case 5:
            MuxB = 1;
            Memory_required = false;
            switch (command) {
                case 1:
                    ALU_switch = 0;
                    IAG_switch = 4;
                    Writeback_switch = 3;
                    break;
                case 2:
                    ALU_switch = 17;
                    IAG_switch = 1;
                    Writeback_switch = 1;
                    break;
                default: break;
            }
            break;
        case 6:
            MuxB = 1;
            ALU_switch = 0;
            IAG_switch = 2;
            Memory_required = false;
            Writeback_switch = 3;
            break;
        default: break;
    }
}

int ALU(const int &ALU_code, const int &a, const int &b) {
    int result;
    switch (ALU_code) {
        case 1: result = a + b; break;
        case 2: result = a & b; break;
        case 3: result = a | b; break;
        case 4: result = a << b; break;
        case 5: result = a < b ? 1 : 0; break;
        case 6: result = a >> b; break;
        case 7: result = (unsigned int) a >> b; break;
        case 8: result = a - b; break;
        case 9: result = a ^ b; break;
        case 10: result = a * b; break;
        case 11: result = b != 0 ? a / b : 0; break;
        case 12: result = b != 0 ? a % b : 0; break;
        case 13: result = (a == b) ? 1 : 0; break;
        case 14: result = (a != b) ? 1 : 0; break;
        case 15: result = (a >= b) ? 1 : 0; break;
        case 16: result = (a < b) ? 1 : 0; break;
        case 17: result = (b << 12); break;
        default: break;
    }
    return result;
}
int IAG(const int &IAG_code, const int &val, const int &branch_offset, int &pc) {
    // Return value of this function is the Return Address.
    int temp;

    // MuxPC and MuxINC are included in these lines automatically.
    switch (IAG_code) {
        case 1:
            temp = pc + 4;
            pc += 4;
            break;
        case 2:
            temp = pc + 4;
            pc += branch_offset;
            break;
        case 3:
            temp = pc + 4;
            pc = val;
            break;
        case 4:
            temp = (branch_offset << 12);
            temp += pc;
            pc += 4;
            break;
        default: break;
    }

    return temp;
}

void execute(int &rd, int &rs1, int &rs2, int &imm, int &rm, int &rz, int &pc, int &Return_Address, int &MuxB, int &ALU_switch, int &IAG_switch, const map<int,string> &register_file, const map<int,string> memory) {
    if (ALU_switch) {
        int x = hex_to_int(register_file.at(rs1));
        int y; if (MuxB) y = imm; else y = hex_to_int(register_file.at(rs2));

        rz = ALU(ALU_switch, x, y);
        if (ALU_switch == 13 || ALU_switch == 14 || ALU_switch == 15 || ALU_switch == 16) {
            if (rz == 1) {IAG_switch = 2;}
            else {IAG_switch = 1;}
        }
    }

    rm = hex_to_int(register_file.at(rs2));
    Return_Address = IAG(IAG_switch, rz, imm, pc);
}

void memory_access(int &mar, int &mdr, int &rz, int &rm, const bool &load, int &size, map<int,string> &memory) {
    mar = rz;
    int pseudo = 4 * ((int) (mar / 4));

    if (load) {
        string temp;
        if (size <= 4 + pseudo - mar) {
            if (memory.find(pseudo) != memory.end()) {
                temp = "0x" + string(8 - (2 * size), '0') + memory[pseudo].substr(10 + 2 * (pseudo - mar - size), 2 * size);
            }
            else {
                temp = "0x00000000";
            }
        }
        else {
            int extra = 2 * (size + mar - 4 - pseudo);
            temp = "0x";
            if (memory.find(pseudo + 4) != memory.end()) {
                temp += memory[pseudo + 4].substr(10 - extra);
                if (memory.find(pseudo) != memory.end()) {
                    temp += memory[pseudo].substr(2, 2 * (pseudo + 4 - mar));
                }
                else {
                    temp += string(2 * (pseudo + 4 - mar), '0');
                }
            }
            else {
                temp += string(extra, '0');
                if (memory.find(pseudo) != memory.end()) {
                    temp += memory[pseudo].substr(2, 2 * (pseudo + 4 - mar));
                }
                else {
                    temp += string(2 * (pseudo + 4 - mar), '0');
                }
            }
        }
        mdr = hex_to_int(temp);
    }
    else {
        mdr = rm;
        string tempo = decimal_to_hex8(mdr);
        string temp = "0x" + tempo.substr(10 - (2 * size));

        if (mar == pseudo) {
            if (memory.find(mar) != memory.end()) {
                memory[mar] = "0x" + memory[mar].substr(2, 10 - temp.length()) + temp.substr(2);
            }
            else {
                memory[mar] = "0x" + string(10 - temp.length(), '0') + temp.substr(2);
            }
        }
        else {
            int off = mar - pseudo;
            if (memory.find(pseudo) != memory.end()) {
                if (temp.length() <= 10 - (2 * off)) {
                    memory[pseudo] = "0x" + string(8 - (2 * off) - (temp.length() - 2), '0') + temp.substr(2 ) + memory[pseudo].substr(10 - (2 * off));
                }
                else {
                    memory[pseudo] = "0x" + temp.substr(temp.length() - (8 - (2 * off))) + memory[pseudo].substr(10 - (2 * off));
                    string rem = temp.substr(2, temp.length() - (8 - (2 * off)) - 2);
                    int rem_len = rem.length();

                    if (memory.find(pseudo + 4) != memory.end()) {
                        memory[pseudo + 4] = memory[pseudo + 4].substr(0, 10 - rem_len) + rem;
                    }
                    else {
                        memory[pseudo + 4] = "0x" + string(8 - rem_len, '0') + rem;
                    }
                }
            }
            else {
                if (temp.length() <= 10 - (2 * off)) {
                    memory[pseudo] = "0x" + string(8 - (2 * off) - (temp.length() - 2), '0') + temp.substr(2 ) + string(2 * off, '0');
                }
                else {
                    memory[pseudo] = "0x" + temp.substr(temp.length() - (8 - (2 * off))) + string(2 * off, '0');
                    string rem = temp.substr(2, temp.length() - (8 - (2 * off)) - 2);
                    int rem_len = rem.length();

                    if (memory.find(pseudo + 4) != memory.end()) {
                        memory[pseudo + 4] = memory[pseudo + 4].substr(0, 10 - rem_len) + rem;
                    }
                    else {
                        memory[pseudo + 4] = "0x" + string(8 - rem_len, '0') + rem;
                    }
                }
            }
        }
    }
}
void get_ir(string &ir, const int &pc, map<int,string> &memory) {
    int temp = 4 * ((int) (pc / 4));
    ir = memory[temp];
}

void writeback(map<int,string> &register_file, int &Writeback_switch, const int &rd, int rz, const int &mdr, const int &Return_Address) {
    switch (Writeback_switch) {
        case 1:
            register_file[rd] = decimal_to_hex8(rz);
            break;
        case 2:
            register_file[rd] = decimal_to_hex8(mdr);
            break;
        case 3:
            register_file[rd] = decimal_to_hex8(Return_Address);
            break;
        default: break;
    }
}

int main() {
    int clock = 0;

    // Control Path variables.
    int MuxB;
    int ALU_switch;
    int IAG_switch;
    int Return_Address;
    int MuxY;

    // Storage Units.
    int rm;
    int rz;

    bool Memory_required;
    int Writeback_switch;
    bool load;
    int mar;
    int mdr;
    int size;

    map<int,string> register_file = make_registers();
    map<int,string> memory = fetch();

    int pc = 0;
    string ir = memory[0];
    string bin_ir = hex_to_bin(ir);

    while (ir != "<textTerminator>") {

        clock ++;

        // Decoding
        bin_ir = hex_to_bin(ir);
        vector<int> instruction = get_instruction(bin_ir);
        vector<int> fields = get_fields(bin_ir, instruction);

        int format = instruction[0]; int command = instruction[1];
        int rd = fields[0]; int rs1 = fields[1]; int rs2 = fields[2]; int imm = fields[3];

        control_path(format, command, MuxB, ALU_switch, IAG_switch, Memory_required, Writeback_switch, load, size);

        clock ++;
        
        // Executing
        execute(rd, rs1, rs2, imm, rm, rz, pc, Return_Address, MuxB, ALU_switch, IAG_switch, register_file, memory);
        
        clock ++;

        // Memory Access
        if (Memory_required) {
            memory_access(mar, mdr, rz, rm, load, size, memory);
        }
        get_ir(ir, pc, memory);
        cout << ir << endl;

        clock ++;

        // Register Update / Writeback
        if (Writeback_switch) {
            writeback(register_file, Writeback_switch, rd, rz, mdr, Return_Address);
        }

        clock ++;

        register_file[0] = "0x00000000";
        // cout << "clock : " << clock << endl;

        for (int _ = 0; _ < 1; _++){
            cout << pc << endl;
            map<int, string>::const_iterator it;
            for (it = register_file.begin(); it != register_file.end(); ++it) {
                cout << it->first << " : " << it->second << endl;
            }

            cout << endl;
            map<int, string>::const_iterator that;
            for (that = memory.begin(); that != memory.end(); ++that) {
                cout << that->first << " : " << that->second << endl;
            }
            cout << endl;
            cout << endl;
        }
    }

    for (int _ = 0; _ < 1; _++){
        cout << pc << endl;
        map<int, string>::const_iterator it;
        for (it = register_file.begin(); it != register_file.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }

        cout << endl;
        map<int, string>::const_iterator that;
        for (that = memory.begin(); that != memory.end(); ++that) {
            cout << that->first << " : " << that->second << endl;
        }
    }
}
