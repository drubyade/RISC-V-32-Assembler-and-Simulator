#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

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

vector<string> read_line(const string &temp) {
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
map<int,string> read_data() {
    map<int,string> out;

    string  mc_filename = "output.mc";
    ifstream mcFile(mc_filename);
    if(!mcFile.is_open()) {cerr << "Error opening mc file" << endl;return out;}

    string temp;
    while (getline(mcFile, temp)) {
        vector<string> pc_mc = read_line(temp);
        int pc = hex_to_int(pc_mc[0]);
        string mc = pc_mc[1];
        if (mc == "<textTerminator>") {
            getline(mcFile,temp);
            while (getline(mcFile,temp)) {
                vector<string> pc_mc = read_line(temp);
                int pc = hex_to_int(pc_mc[0]);
                string mc = pc_mc[1];

                if (mc == "<dataTerminator>") break;
                out[pc] = mc;
            }
            break;
        }
    }
    mcFile.close();
    return out;
}
map<int,string> read_text(string &EndPC) {
    map<int,string> out;

    string  mc_filename = "output.mc";
    ifstream mcFile(mc_filename);
    if(!mcFile.is_open()) {cerr << "Error opening mc file" << endl;return out;}

    string temp;
    while (getline(mcFile, temp)) {
        vector<string> pc_mc = read_line(temp);
        int pc = hex_to_int(pc_mc[0]);
        string mc = pc_mc[1];

        if (mc == "<textTerminator>") {
            out[pc] = mc;
            EndPC = decimal_to_hex8(pc) + '0';

            getline(mcFile,temp);

            mcFile.close();
            return out;
        }
        else {
            out[pc] = mc;
        }
    }
    mcFile.close();
    return out;
}

string fetch(const map<int,string> &text_map, int &PC) {
    string out = text_map.at(PC);
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
void control_path(const int &format, const int &command, int &control_line_ALU, int &MuxA, int &MuxB, int &MuxY, int &MuxPC, int&MuxINC, bool &load, bool &store, int &size, bool &rd_switch) {
    switch (format) {
        case 1:
            control_line_ALU = command;
            MuxA = 1;
            MuxB = 0;
            MuxY = 0;
            MuxPC = 1;
            MuxINC = 0;
            load = false;
            store = false;
            rd_switch = true;
            break;

        case 2:
            switch (command) {
                case 1:
                case 2:
                case 3:
                    control_line_ALU = command;
                    MuxA = 1;
                    MuxB = 1;
                    MuxY = 0;
                    MuxPC = 1;
                    MuxINC = 0;
                    load = false;
                    store = false;
                    rd_switch = true;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    control_line_ALU = 1;
                    MuxA = 1;
                    MuxB = 1;
                    MuxY = 1;
                    MuxPC = 1;
                    MuxINC = 0;
                    load = true;
                    store = false;
                    rd_switch = true;
                    break;
                case 8:
                    control_line_ALU = 1;
                    MuxA = 1;
                    MuxB = 1;
                    MuxY = 2;
                    MuxPC = 0;
                    load = false;
                    store = false;
                    rd_switch = true;
                    break;
                default: break;
            }
            switch (command) {
                case 1:
                case 2:
                case 3:
                    break;
                case 4: size = 1; break;
                case 5: size = 8; break;
                case 6: size = 2; break;
                case 7: size = 4; break;
                case 8:
                    break;
                default: break;
            }
            break;

        case 3:
            control_line_ALU = 1;
            MuxA = 1;
            MuxB = 1;
            MuxY = -1;
            MuxPC = 1;
            MuxINC = 0;
            load = false;
            store = true;
            rd_switch = false;
            switch (command) {
                case 1: size = 1; break;
                case 2: size = 4; break;
                case 3: size = 8; break;
                case 4: size = 2; break;
                default: break;
            }
            break;

        case 4:
            control_line_ALU = command + 12;
            MuxA = 1;
            MuxB = 0;
            MuxY = -1;
            MuxPC = 1;
            MuxINC = -1;
            load = false;
            store = false;
            rd_switch = false;
            break;

        case 5:
            switch (command) {
                case 1:
                    control_line_ALU = 18;
                    MuxA = 0;
                    MuxB = 1;
                    MuxY = 0;
                    MuxPC = 1;
                    MuxINC = 0;
                    load = false;
                    store = false;
                    rd_switch = true;
                    break;
                case 2:
                    control_line_ALU = 17;
                    MuxA = 0;
                    MuxB = 1;
                    MuxY = 0;
                    MuxPC = 1;
                    MuxINC = 0;
                    load = false;
                    store = false;
                    rd_switch = true;
                    break;
            }
            break;

        case 6:
            control_line_ALU = 19;
            MuxA = 0;
            MuxB = 1;
            MuxY = 0;
            MuxPC = 1;
            MuxINC = 1;
            load = false;
            store = false;
            rd_switch = true;
            break;

        default: break;
    }
}

string decode(const string &IR, int &RA, int &RB, int &imm, int &RM, int &PC, int &control_line_ALU, int &MuxA, int &MuxB, int &MuxY, int &MuxPC, int&MuxINC, bool &load, bool &store, int &size, bool &rd_switch, map<int,string> &registers) {
    // 0 and 1  : RD register (in decimal)
    // 2        : load switch
    // 3        : store switch
    // 4        : size
    // 5        : rd_switch
    // 6        : MuxY
    // 7 to 16  : current pc

    string bin_ir = hex_to_bin(IR);
    vector<int> instruction = get_instruction(bin_ir);
    int format = instruction[0]; int command = instruction[1];

    vector<int> fields = get_fields(bin_ir, instruction);

    RA = hex_to_int(registers.at(fields[1]));
    RB = hex_to_int(registers.at(fields[2]));
    imm = fields[3];

    control_path(format, command, control_line_ALU, MuxA, MuxB, MuxY, MuxPC, MuxINC, load, store, size, rd_switch);

    string ssize = to_string(size);
    if (ssize.length() != 1) ssize = ssize[ssize.length() - 1];

    string out = to_string(fields[0]);
    if (out.length() == 0) out = "00";
    else if (out.length() == 1) out = "0" + out;
    else out = out;

    if (load) out += "10" + ssize + "11";
    else if (store) out += "01" + ssize + "00";
    else if (rd_switch) out += "00" + ssize + "1" + to_string(MuxY);
    else out += "00" + ssize + "00";

    out += decimal_to_hex8(PC);

    return out;
}
void ALU(const int &control_line_ALU, const int &R_ALU_A, const int &R_ALU_B, int &RZ) {
    switch (control_line_ALU) {
        case 1: RZ = R_ALU_A + R_ALU_B; break;
        case 2: RZ = R_ALU_A & R_ALU_B; break;
        case 3: RZ = R_ALU_A | R_ALU_B; break;
        case 4: RZ = R_ALU_A << R_ALU_B; break;
        case 5: RZ = R_ALU_A < R_ALU_B ? 1 : 0; break;
        case 6: RZ = R_ALU_A >> R_ALU_B; break;
        case 7: RZ = (unsigned int) R_ALU_A >> R_ALU_B; break;
        case 8: RZ = R_ALU_A - R_ALU_B; break;
        case 9: RZ = R_ALU_A ^ R_ALU_B; break;
        case 10: RZ = R_ALU_A * R_ALU_B; break;
        case 11: RZ = R_ALU_B != 0 ? R_ALU_A / R_ALU_B : 0; break;
        case 12: RZ = R_ALU_B != 0 ? R_ALU_A % R_ALU_B : 0; break;
        case 13: RZ = (R_ALU_A == R_ALU_B) ? 1 : 0; break;
        case 14: RZ = (R_ALU_A != R_ALU_B) ? 1 : 0; break;
        case 15: RZ = (R_ALU_A >= R_ALU_B) ? 1 : 0; break;
        case 16: RZ = (R_ALU_A < R_ALU_B) ? 1 : 0; break;
        case 17: RZ = (R_ALU_B << 12); break;
        case 18: RZ = (R_ALU_B << 12) + R_ALU_A; break;
        case 19: RZ = (R_ALU_A) + 4; break;
        default: break;
    }
}
void IAG(const int &MuxPC, const int &MuxINC, int &PC, int &PC_Temp, const int &RZ, const int &imm) {
    PC_Temp = PC;
    if (MuxPC == 0) PC = RZ;
    else if (MuxINC) PC = PC + imm;
    else PC = PC + 4;
}

string execute(const int &control_line_ALU, const int &MuxA, const int &MuxB, int &R_ALU_A, int &R_ALU_B, const int &RA, const int &RB, int &RM, const int &imm, int &PC, int &PC_Temp, int &RZ, int &MuxPC, int &MuxINC, const string &decode_result) {
    RM = RB;

    if (MuxA) R_ALU_A = RA;
    else R_ALU_A = PC;

    if (MuxB) R_ALU_B = imm;
    else R_ALU_B = RB;

    ALU(control_line_ALU, R_ALU_A, R_ALU_B, RZ);

    if (MuxINC == -1) {
        if (RZ) MuxINC = 1;
        else MuxINC = 0;
    }

    IAG(MuxPC, MuxINC, PC, PC_Temp, RZ, imm);

    return decode_result;
}
string memory_access(int &RZ, int &RM, int &MAR, int &MDR, int &RY, map<int,string> &data_map, const string &execute_result) {
    // 0 and 1  : RD register (in decimal)
    // 2        : rd_switch

    string out = execute_result.substr(0,2) + execute_result.substr(5,12);

    MAR = RZ;
    int pseudo = 4 * ((int) (MAR / 4));
    int size = stoi(execute_result.substr(4,1));

    if (execute_result[2] == '1') {
        string temp;
        if (size <= 4 + pseudo - MAR) {
            if (data_map.find(pseudo) != data_map.end()) {
                temp = "0x" + string(8 - (2 * size), '0') + data_map[pseudo].substr(10 + 2 * (pseudo - MAR - size), 2 * size);
            }
            else {
                temp = "0x00000000";
            }
        }
        else {
            int extra = 2 * (size + MAR - 4 - pseudo);
            temp = "0x";
            if (data_map.find(pseudo + 4) != data_map.end()) {
                temp += data_map[pseudo + 4].substr(10 - extra);
                if (data_map.find(pseudo) != data_map.end()) {
                    temp += data_map[pseudo].substr(2, 2 * (pseudo + 4 - MAR));
                }
                else {
                    temp += string(2 * (pseudo + 4 - MAR), '0');
                }
            }
            else {
                temp += string(extra, '0');
                if (data_map.find(pseudo) != data_map.end()) {
                    temp += data_map[pseudo].substr(2, 2 * (pseudo + 4 - MAR));
                }
                else {
                    temp += string(2 * (pseudo + 4 - MAR), '0');
                }
            }
        }
        MDR = hex_to_int(temp);
    }
    else if (execute_result[3] == '1') {
        MDR = RM;
        string tempo = decimal_to_hex8(MDR);
        string temp = "0x" + tempo.substr(10 - (2 * size));

        if (MAR == pseudo) {
            if (data_map.find(MAR) != data_map.end()) {
                data_map[MAR] = "0x" + data_map[MAR].substr(2, 10 - temp.length()) + temp.substr(2);
            }
            else {
                data_map[MAR] = "0x" + string(10 - temp.length(), '0') + temp.substr(2);
            }
        }
        else {
            int off = MAR - pseudo;
            if (data_map.find(pseudo) != data_map.end()) {
                if (temp.length() <= 10 - (2 * off)) {
                    data_map[pseudo] = "0x" + string(8 - (2 * off) - (temp.length() - 2), '0') + temp.substr(2 ) + data_map[pseudo].substr(10 - (2 * off));
                }
                else {
                    data_map[pseudo] = "0x" + temp.substr(temp.length() - (8 - (2 * off))) + data_map[pseudo].substr(10 - (2 * off));
                    string rem = temp.substr(2, temp.length() - (8 - (2 * off)) - 2);
                    int rem_len = rem.length();

                    if (data_map.find(pseudo + 4) != data_map.end()) {
                        data_map[pseudo + 4] = data_map[pseudo + 4].substr(0, 10 - rem_len) + rem;
                    }
                    else {
                        data_map[pseudo + 4] = "0x" + string(8 - rem_len, '0') + rem;
                    }
                }
            }
            else {
                if (temp.length() <= 10 - (2 * off)) {
                    data_map[pseudo] = "0x" + string(8 - (2 * off) - (temp.length() - 2), '0') + temp.substr(2 ) + string(2 * off, '0');
                }
                else {
                    data_map[pseudo] = "0x" + temp.substr(temp.length() - (8 - (2 * off))) + string(2 * off, '0');
                    string rem = temp.substr(2, temp.length() - (8 - (2 * off)) - 2);
                    int rem_len = rem.length();

                    if (data_map.find(pseudo + 4) != data_map.end()) {
                        data_map[pseudo + 4] = data_map[pseudo + 4].substr(0, 10 - rem_len) + rem;
                    }
                    else {
                        data_map[pseudo + 4] = "0x" + string(8 - rem_len, '0') + rem;
                    }
                }
            }
        }
    }

    if (out[2] != '0') {
        int current_PC;

        int MuxY = stoi(out.substr(3,1));
        if (stoi(out.substr(0,2)) != 0) {
            switch (MuxY) {
                case 0:
                    RY = RZ;
                    break;
                case 1:
                    RY = MDR;
                    break;
                case 2:
                    current_PC = hex_to_int(out.substr(4,10));
                    RY = current_PC + 4;
                    break;
                default: break;
            }
        }
    }

    return out.substr(0,3);
}
void writeback(const int &RY, const string &memory_result, map<int,string> &registers) {
    if (memory_result[2] == '0') return;

    int rerd = stoi(memory_result.substr(0,2));

    if (rerd == 0) return;
    else registers[rerd] = decimal_to_hex8(RY);
}

void fetch_pipeline(const map<int,string> &text_map, vector<string> &pipeline, const int &stall, const string &EndPC) {
    string pipeline_command = pipeline[0];
    if (pipeline_command.length() != 11) return;

    if (stall != 0) {
        int wait_key = stoi(pipeline_command.substr(10,1));
        wait_key = wait_key - 1;

        pipeline_command = pipeline_command.substr(0,10) + to_string((wait_key + stall));
        pipeline[0] = pipeline_command;

        return;
    }

    if (pipeline_command[10] != '0') {
        int wait_key = stoi(pipeline_command.substr(10,1));
        wait_key = wait_key - 1;

        pipeline_command = pipeline_command.substr(0,10) + to_string(wait_key);
        pipeline[0] = pipeline_command;

        return;
    }
    else {
        int PC = hex_to_int(pipeline_command.substr(0,10));
        if (pipeline_command == EndPC) {
            pipeline[1] = "";
            pipeline[0] = "";
        }
        else {
            pipeline[1] = fetch(text_map, PC) + '0';
            PC += 4;
            pipeline[0] = decimal_to_hex8(PC) + '0';
        }
    }
}
void decode_pipeline(vector<string> &pipeline, int &RA, int &RB, int &imm, int &RM, int &PC, int &control_line_ALU, int &MuxA, int &MuxB, int &MuxY, int &MuxPC, int &MuxINC, bool &load, bool &store, int &size, bool &rd_switch, map<int,string> &registers, int &back1, int &back2, int &stall, int &flush) {

    string pipeline_command = pipeline[1];
    if (pipeline_command.length() != 11) {
        back2 = back1;
        back1 = 32;

        return;
    }

    if (pipeline_command[10] != '0') {
        stall = 0;
        
        int wait_key = stoi(pipeline_command.substr(10,1));
        wait_key = wait_key - 1;

        pipeline_command = pipeline_command.substr(0,10) + to_string(wait_key);
        pipeline[1] = pipeline_command;

        back2 = back1;
        back1 = 32;

        return;
    }
    else {
        string bin_ir = hex_to_bin(pipeline_command.substr(0,10));
        vector<int> instruction = get_instruction(bin_ir);
        int format = instruction[0]; int command = instruction[1];

        vector<int> fields = get_fields(bin_ir, instruction);

        if (format == 5 || format == 6) {
            // In this case there is no register access
            if (format == 6) {
                if (fields[3] != 4) flush = 1;
            }
            pipeline[2] = decode(pipeline_command.substr(0,10), RA, RB, imm, RM, PC, control_line_ALU, MuxA, MuxB, MuxY, MuxPC, MuxINC, load, store, size, rd_switch, registers) + '0';
            pipeline[1] = "";
            
            back2 = back1;
            if (fields[0] == 0) back1 = 32;
            else back1 = fields[0];

            return;
        }

        int rd = fields[0];
        int rs1 = fields[1];
        int rs2 = fields[2];

        if (rs1 == back1 || rs2 == back1) {
            stall = 2;
            pipeline[1] = pipeline_command.substr(0,10) + '1';
            pipeline[2] = "";

            back2 = back1;
            back1 = 32;
        }
        else if (rs1 == back2 || rs2 == back2) {
            stall = 1;
            pipeline[1] = pipeline_command.substr(0,10) + '0';
            pipeline[2] = "";
            
            back2 = back1;
            back1 = 32;
        }
        else {
            stall = 0;
            pipeline[2] = decode(pipeline_command.substr(0,10), RA, RB, imm, RM, PC, control_line_ALU, MuxA, MuxB, MuxY, MuxPC, MuxINC, load, store, size, rd_switch, registers) + '0';
            pipeline[1] = "";
            if (format == 3 || format == 4) {
                back2 = back1;
                back1 = 32;
            }
            else {
                back2 = back1;
                if (rd == 0) back1 = 32;
                else back1 = rd;
            }
        }

        return;
    }
}
void execute_pipeline(const int &control_line_ALU, const int &MuxA, const int &MuxB, int &R_ALU_A, int &R_ALU_B, const int &RA, const int &RB, int &RM, const int &imm, int &PC, int &PC_Temp, int &RZ, int &MuxPC, int &MuxINC, vector<string> &pipeline) {
    string pipeline_command = pipeline[2];
    if (pipeline_command.length() != 18) return;

    if (pipeline_command[17] != '0') {
        int wait_key = stoi(pipeline_command.substr(17,1));
        wait_key = wait_key - 1;

        pipeline_command = pipeline_command.substr(0,17) + to_string(wait_key);
        pipeline[2] = pipeline_command;

        return;
    }
    else {
        pipeline[3] = execute(control_line_ALU, MuxA, MuxB, R_ALU_A, R_ALU_B, RA, RB, RM, imm, PC, PC_Temp, RZ, MuxPC, MuxINC, pipeline_command.substr(0,17)) + '0';
        pipeline[2] = "";

        return;
    }
}
void memory_access_pipeline(int &RZ, int &RM, int &MAR, int &MDR, int &RY, map<int,string> &data_map, vector<string> &pipeline) {
    string pipeline_command = pipeline[3];
    if (pipeline_command.length() != 18) return;

    if (pipeline_command[17] != '0') {
        int wait_key = stoi(pipeline_command.substr(17,1));
        wait_key = wait_key - 1;

        pipeline_command = pipeline_command.substr(0,17) + to_string(wait_key);
        pipeline[3] = pipeline_command;

        return;
    }
    else {
        pipeline[4] = memory_access(RZ, RM, MAR, MDR, RY, data_map, pipeline_command.substr(0,17)) + '0';
        pipeline[3] = "";

        return;
    }
}
void writeback_pipeline(const int &RY, vector<string> &pipeline, map<int,string> &registers) {
    string pipeline_command = pipeline[4];
    if (pipeline_command.length() != 4) return;

    if (pipeline_command[3] != '0') {
        int wait_key = stoi(pipeline_command.substr(3,1));
        wait_key = wait_key - 1;

        pipeline_command = pipeline_command.substr(0,3) + to_string(wait_key);
        pipeline[4] = pipeline_command;

        return;
    }
    else {
        writeback(RY, pipeline_command.substr(0,3), registers);
        pipeline[4] = "";
        
        return;
    }
}
void flush_pipeline(vector<string> &pipeline, const int &flush, const int &PC, const int &imm) {
    switch (flush) {
        case 2:
            pipeline[0] = decimal_to_hex8(PC) + '0';
            pipeline[1] = "";
            pipeline[2] = "";
            break;
        case 1:
            pipeline[0] = decimal_to_hex8(PC + imm) + '0';
            pipeline[1] = "";
            break;
        default: break;
    }
}

int main() {

    string EndPC;
    map<int,string> registers = make_registers();
    map<int,string> text_map = read_text(EndPC);
    map<int,string> data_map = read_data();

    int clock = 0;

    // Data path elements
    int RA;
    int RB;
    int imm;
    int MuxA;
    int MuxB;
    int RM;
    int R_ALU_A;
    int R_ALU_B;
    int RZ;
    int MuxY;
    int MAR;
    int MDR;
    int RY;

    int control_line_ALU;
    bool load;
    bool store;
    int size;
    bool rd_switch;

    // IAG elements
    int PC = 0;
    int PC_Temp;
    int MuxPC;
    int MuxINC;
    string IR;

    // Memory Buffers


    bool knob1;         //  Pipeline
    bool knob2;         //  Data Forwarding
    bool knob3;         //  Print BPU (PC, PHT, BTB) after each cycle

    cout << "Knob 1 : "; cin >> knob1;
    cout << "Knob 2 : "; cin >> knob2;
    cout << "Knob 3 : "; cin >> knob3;

    string nothing;

    if (knob1) {
        vector<string> pipeline;
        for (int i = 0; i < 5; i++) { pipeline.push_back(string()); }

        // FETCH        :   PC (hexadecimal)
        // DECODE       :   IR content (hexadecimal) + wait_key
        // EXECUTE      :   decode_result
        // MEMORY       :   execute_result
        // WRITEBACK    :   memory_result

        if (knob2) {
            int back1 = 32;
            int back2 = 32;
            pipeline[0] = "0x000000000";

            int stall;
            int flush = 0;

            while (true) {
                // Doing all operations
                fetch_pipeline(text_map, pipeline, stall, EndPC);

                // Flushing pipeline when needed

                clock ++;

                if (pipeline[0] == "") if (pipeline[1] == "") if (pipeline[2] == "") if (pipeline[3] == "") if (pipeline[4] == "") break;

                cout << "fetch   : " << pipeline[0] << endl;
                cout << "decode  : " << pipeline[1] << endl;
                cout << "execute : " << pipeline[2] << endl;
                cout << "meomory : " << pipeline[3] << endl;
                cout << "wrtback : " << pipeline[4] << endl;

                for (int _ = 0; _ < 1; _++){
                    map<int, string>::const_iterator it;
                    for (it = registers.begin(); it != registers.end(); ++it) {
                        cout << it->first << " : " << it->second << endl;
                    }
        
                    cout << endl;
                    map<int, string>::const_iterator that;
                    for (that = data_map.begin(); that != data_map.end(); ++that) {
                        cout << that->first << " : " << that->second << endl;
                    }
                }
            }
        }
        else {
            int back1 = 32;
            int back2 = 32;
            pipeline[0] = "0x000000000";

            int stall;
            int flush = 0;

            while (true) {
                writeback_pipeline(RY, pipeline, registers);
                memory_access_pipeline(RZ, RM, MAR, MDR, RY, data_map, pipeline);
                execute_pipeline(control_line_ALU, MuxA, MuxB, R_ALU_A, R_ALU_B, RA, RB, RM, imm, PC, PC_Temp, RZ, MuxPC, MuxINC, pipeline);
                decode_pipeline(pipeline, RA, RB, imm, RM, PC, control_line_ALU, MuxA, MuxB, MuxY, MuxPC, MuxINC, load, store, size, rd_switch, registers, back1, back2, stall, flush);
                fetch_pipeline(text_map, pipeline, stall, EndPC);

                // Flushing the pipeline when needed.
                if (PC_Temp + 4 != PC  && pipeline[3] != "") {
                    if (flush == 1) flush = 0;
                    else {
                        flush_pipeline(pipeline, 2, PC, imm);
                        back1 = 32; back2 = 32;
                    }
                }
                else if (flush == 1) {
                    flush_pipeline(pipeline, flush, PC, imm);
                }

                clock ++;

                if (pipeline[0] == "") if (pipeline[1] == "") if (pipeline[2] == "") if (pipeline[3] == "") if (pipeline[4] == "") break;

                cout << "fetch   : " << pipeline[0] << endl;
                cout << "decode  : " << pipeline[1] << endl;
                cout << "execute : " << pipeline[2] << endl;
                cout << "meomory : " << pipeline[3] << endl;
                cout << "wrtback : " << pipeline[4] << endl;

                for (int _ = 0; _ < 1; _++){
                    map<int, string>::const_iterator it;
                    for (it = registers.begin(); it != registers.end(); ++it) {
                        cout << it->first << " : " << it->second << endl;
                    }
        
                    cout << endl;
                    map<int, string>::const_iterator that;
                    for (that = data_map.begin(); that != data_map.end(); ++that) {
                        cout << that->first << " : " << that->second << endl;
                    }
                }
            }
        }
    }
    else {
        while (true) {
            IR = fetch(text_map,PC); clock ++;
            if (IR == "<textTerminator>") break;
            string decode_result = decode(IR, RA, RB, imm, RM, PC, control_line_ALU, MuxA, MuxB, MuxY, MuxPC, MuxINC, load, store, size, rd_switch, registers); clock ++;
            string execute_result = execute(control_line_ALU, MuxA, MuxB, R_ALU_A, R_ALU_B, RA, RB, RM, imm, PC, PC_Temp, RZ, MuxPC, MuxINC, decode_result); clock ++;
            string memory_result = memory_access(RZ, RM, MAR, MDR, RY, data_map, execute_result); clock ++;
            writeback(RY, memory_result, registers); clock ++;

            for (int _ = 0; _ < 1; _++){
                cout << PC << ':' << decimal_to_hex8(PC) << endl;
                map<int, string>::const_iterator it;
                for (it = registers.begin(); it != registers.end(); ++it) {
                    cout << it->first << " : " << it->second << endl;
                }
    
                cout << endl;
                map<int, string>::const_iterator that;
                for (that = data_map.begin(); that != data_map.end(); ++that) {
                    cout << that->first << " : " << that->second << endl;
                }
            }
        }
    }
    for (int _ = 0; _ < 1; _++){
        cout << PC << ':' << decimal_to_hex8(PC) << endl;
        map<int, string>::const_iterator it;
        for (it = registers.begin(); it != registers.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }

        cout << endl;
        map<int, string>::const_iterator that;
        for (that = data_map.begin(); that != data_map.end(); ++that) {
            cout << that->first << " : " << that->second << endl;
        }
        cout << endl;
        cout << endl;
    }
}
