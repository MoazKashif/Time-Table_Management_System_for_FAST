//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
//
//const int MAX_DAYS = 6;
//const int MAX_ROOMS = 50;
//
//struct Session {
//    string time;
//    string course;
//    Session* next;
//};
//
//struct Room {
//    string name;  
//    Session* head = nullptr;
//};
//
//struct Day {
//    Room rooms[MAX_ROOMS];
//    int roomCount = 0;
//};
//
//class TTADT {
//    Day days[MAX_DAYS];
//
//    char toLower(char c) {
//        if (c >= 'A' && c <= 'Z')
//            return c + 32;
//        return c;
//    }
//
//    string normalizeDay(string str) {
//        string result = "";
//        for (int i = 0; i < str.length(); i++) {
//            if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
//                result += toLower(str[i]);
//        }
//        return result;
//    }
//
//    int dayIndex(string d) {
//        string day = normalizeDay(d);
//        if (day == "monday") return 0;
//        if (day == "tuesday") return 1;
//        if (day == "wednesday") return 2;
//        if (day == "thursday") return 3;
//        if (day == "friday") return 4;
//        if (day == "saturday") return 5;
//        return -1;
//    }
//
//    string trim(string str) {
//        int start = 0, end = str.length() - 1;
//        while (start <= end && (str[start] == ' ' || str[start] == '\t')) start++;
//        while (end >= start && (str[end] == ' ' || str[end] == '\t')) end--;
//        string result = "";
//        for (int i = start; i <= end; ++i) {
//            result += str[i];
//        }
//        return result;
//    }
//
//
//    void addSession(Room& room, const string& time, const string& course) {
//        Session* newSession = new Session{ time, course, nullptr };
//
//        if (room.head == nullptr) {
//            room.head = newSession;
//        }
//        else {
//            Session* temp = room.head;
//            while (temp->next != nullptr)
//                temp = temp->next;
//            temp->next = newSession;
//        }
//    }
//
//    void deleteSessions(Session* head) {
//        while (head != nullptr) {
//            Session* temp = head;
//            head = head->next;
//            delete temp;
//        }
//    }
//
//public:
//    ~TTADT() {
//        for (int d = 0; d < MAX_DAYS; d++) {
//            for (int r = 0; r < days[d].roomCount; r++) {
//                deleteSessions(days[d].rooms[r].head);
//            }
//        }
//    }
//
//    // Function to load timetable data from a file
//    void load(char filename[]) {
//        ifstream fin(filename);
//        if (!fin) {
//            cout << "Cannot open " << filename << endl;
//            return;
//        }
//
//        string line;
//        getline(fin, line); 
//
//        while (getline(fin, line)) {
//            if (line.empty()) continue;
//
//            string fields[4];
//            int fieldIndex = 0;
//            string currentField = "";
//            for (int i = 0; i < line.length(); i++) {
//                if (line[i] == ',') {
//                    if (fieldIndex < 4) {
//                        fields[fieldIndex++] = trim(currentField);
//                        currentField = "";
//                    }
//                }
//                else {
//                    currentField += line[i];
//                }
//            }
//            if (fieldIndex < 4) {
//                fields[fieldIndex] = trim(currentField);
//            }
//
//            if (fieldIndex < 3) continue;
//
//            int d = dayIndex(fields[0]);
//            if (d < 0) continue;
//
//            string roomName = fields[1];
//            string timeSlot = fields[2];
//            string course = fields[3];
//
//            if (course.find("Free slot") != string::npos || course.empty()) continue;
//
//            int r;
//            for (r = 0; r < days[d].roomCount; r++) {
//                if (days[d].rooms[r].name == roomName) break;
//            }
//            if (r == days[d].roomCount && r < MAX_ROOMS) {
//                days[d].rooms[r].name = roomName;
//                days[d].roomCount++;
//            }
//            if (r >= MAX_ROOMS) continue;
//
//            addSession(days[d].rooms[r], timeSlot, course);
//            cout << "Added session '" << course << "' on " << fields[0]
//                << " at " << timeSlot << " in room (" << roomName << ")." << endl;
//        }
//
//        fin.close();
//    }
//    void printSessions(Session* head) {
//        while (head != nullptr) {
//            cout << "  [" << head->time << "] " << head->course << "\n";
//            head = head->next;
//        }
//    }
//    void print() {
//        const char* dayNames[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
//
//        for (int d = 0; d < MAX_DAYS; d++) {
//            cout << "\n=== " << dayNames[d] << " ===\n";
//
//            if (days[d].roomCount == 0) {
//                cout << "No data for this day.\n";
//                continue;
//            }
//
//            for (int r = 0; r < days[d].roomCount; r++) {
//                cout << "Room " << days[d].rooms[r].name << ":\n";
//                printSessions(days[d].rooms[r].head);
//            }
//        }
//    }
//};
//
//int main() {
//    TTADT tt;
//    char filename[] = "File.csv";  
//    tt.load(filename);
//    tt.print();
//    return 0;
//}
