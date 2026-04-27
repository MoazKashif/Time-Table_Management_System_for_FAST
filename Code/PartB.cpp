#include <iostream>
#include <fstream>
using namespace std;

const int MAX_DAYS = 6;
const int MAX_ROOMS = 50;
const int MAX_DAYLEN = 16;
const int MAX_ROOMLEN = 32;
const int MAX_TIMELEN = 16;
const int MAX_COURSE = 64;
const int MAX_CODE = 16;
const int MAX_LINE = 256;

int str_len(const char* s) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void str_copy(char* dest, const char* src) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0') ++i;
}

bool str_cmp(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return true;
}

//bool str_ncmp(const char* a, const char* b, int n) {
//    for (int i = 0; i < n; ++i) {
//        if (a[i] != b[i]) return false;
//        if (a[i] == '\0' && b[i] == '\0') return true;
//    }
//    return true;
//}

int str_find(const char* s, char c) {
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] == c) return i;
    return -1;
}

// trim leading & trailing spaces/tabs
void trim(char* s) {
    int start = 0;
    while (s[start] == ' ' || s[start] == '\t') ++start;
    int end = str_len(s) - 1;
    while (end >= start && (s[end] == ' ' || s[end] == '\t')) --end;
    char buf[MAX_LINE];
    int len = 0;
    for (int i = start; i <= end; ++i) buf[len++] = s[i];
    buf[len] = '\0';
    str_copy(s, buf);
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z')  return c + 32;
    return c;
}

// normalize day: lowercase + remove whitespace
void normalizeDay(const char* in, char* out) {
    int j = 0;
    for (int i = 0; in[i] != '\0'; ++i) {
        char c = in[i];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            out[j++] = to_lower(c);
        }
    }
    out[j] = '\0';
}

int dayIndex(const char* s) {
    char tmp[MAX_DAYLEN];
    normalizeDay(s, tmp);
    if (str_cmp(tmp, "monday"))    return 0;
    if (str_cmp(tmp, "tuesday"))   return 1;
    if (str_cmp(tmp, "wednesday")) return 2;
    if (str_cmp(tmp, "thursday"))  return 3;
    if (str_cmp(tmp, "friday"))    return 4;
    if (str_cmp(tmp, "saturday"))  return 5;
    return -1;
}

struct Session {
    char time[MAX_TIMELEN];
    char course[MAX_COURSE];
    char code[MAX_CODE];
    Session* next;
};

struct Room {
    char name[MAX_ROOMLEN];
    Session* head;
    Room() : head(nullptr) { name[0] = '\0'; }
};

struct Day {
    Room rooms[MAX_ROOMS];
    int  roomCount;
    Day() : roomCount(0) {}
};

class TTADT {
    Day days[MAX_DAYS];
public:
    ~TTADT() {
        for (int d = 0; d < MAX_DAYS; ++d)
            for (int r = 0; r < days[d].roomCount; ++r) {
                Session* cur = days[d].rooms[r].head;
                while (cur) {
                    Session* nxt = cur->next;
                    delete cur;
                    cur = nxt;
                }
            }
    }

    void load(const char filename[]) {
        ifstream fin(filename);
        if (!fin) {
            cerr << "Error: can't open " << filename << "\n";
            return;
        }
        char line[MAX_LINE];
        fin.getline(line, MAX_LINE);

        while (fin.getline(line, MAX_LINE)) {
            if (line[0] == '\0') continue;
            char f[5][MAX_LINE];
            int fld = 0, pos = 0;
            for (int i = 0; ; ++i) {
                char c = line[i];
                if ((c == ',' && fld < 4) || c == '\0') {
                    f[fld][pos] = '\0';
                    trim(f[fld]);
                    fld++; pos = 0;
                    if (c == '\0') break;
                }
                else {
                    f[fld][pos++] = c;
                }
            }
            if (fld < 5) continue;

            int d = dayIndex(f[0]);
            if (d < 0)
                continue;
            // fields: f[0]=day f[1]=room, f[2]=time, f[3]=course, f[4]=code
            // skip empty course
            if (f[3][0] == '\0') 
                continue;
            int r;
            for (r = 0; r < days[d].roomCount; ++r)
                if (str_cmp(days[d].rooms[r].name, f[1]))
                    break;
            if (r == days[d].roomCount && r < MAX_ROOMS) {
                str_copy(days[d].rooms[r].name, f[1]);
                days[d].roomCount++;
            }
            if (r >= MAX_ROOMS) continue;

            Session* s = new Session;
            str_copy(s->time, f[2]);
            str_copy(s->course, f[3]);
            str_copy(s->code, f[4]);
            s->next = nullptr;

            Room& room = days[d].rooms[r];
            if (!room.head) room.head = s;
            else {
                Session* t = room.head;
                while (t->next) t = t->next;
                t->next = s;
            }
        }
    }

    void printCourseInfo(const char coursename[]) {
        static const char* names[MAX_DAYS] = {
            "Monday","Tuesday","Wednesday",
            "Thursday","Friday","Saturday"
        };
        cout << "\nSections teaching \"" << coursename << "\":\n";
        bool any = false;

        for (int d = 0; d < MAX_DAYS; ++d) {
            for (int r = 0; r < days[d].roomCount; ++r) {
                for (Session* s = days[d].rooms[r].head; s; s = s->next) {
                    int p = str_find(s->course, '(');
                    char base[MAX_COURSE];
                    if (p >= 0) {
                        for (int i = 0; i < p; ++i) base[i] = s->course[i];
                        base[p] = '\0';
                        trim(base);
                    }
                    else {
                        str_copy(base, s->course);
                    }
                    if (str_cmp(base, coursename)) {
                        any = true;
                        char sec[MAX_CODE] = "";
                        if (p >= 0) {
                            int end = str_find(s->course + p + 1, ')');
                            if (end >= 0) {
                                for (int i = 0; i < end; ++i)
                                    sec[i] = s->course[p + 1 + i];
                                sec[end] = '\0';
                            }
                        }
                        cout << "  Code: " << sec
                            << " | Day: " << names[d]
                            << " | Time: " << s->time
                                << " | Room: " << days[d].rooms[r].name
                                << "\n";
                    }
                }
            }
        }
        if (!any) cout << "  (none)\n";
    }

    void DetermineFreeClassrooms(const char day[], const char timeslot[]) {
        static const char* names[MAX_DAYS] = {
            "Monday","Tuesday","Wednesday",
            "Thursday","Friday","Saturday"
        };
        int d = dayIndex(day);
        if (d < 0) {
            cout << "\nInvalid day\n";
            return;
        }
        cout << "\nFree rooms on " << day << " at " << timeslot << ":\n";
        cout << "===================Free Rooms========================\n";
        bool any = false;
        for (int r = 0; r < days[d].roomCount; ++r) {
            for (Session* s = days[d].rooms[r].head; s; s = s->next) {
                if (str_cmp(s->time, timeslot) && str_cmp(s->course, "Free slot")) {
                    cout << "  " << days[d].rooms[r].name << "\n";
                    any = true;
                    break;
                }

            }
        }
        if (!any) cout << "  (none)\n";
        cout << "=====================================================\n";
    }
    void PrintTimetableOfSection(const char section[]) {
        static const char* names[MAX_DAYS] = {
            "Monday","Tuesday","Wednesday",
            "Thursday","Friday","Saturday"
        };
        cout << "\nTimetable for section " << section << ":\n";
        cout << "Day       | Time    | Room    | Course\n";
        cout << "----------+---------+---------+---------------\n";
        bool any = false;
        for (int d = 0; d < MAX_DAYS; ++d) {
            for (int r = 0; r < days[d].roomCount; ++r) {
                for (Session* s = days[d].rooms[r].head; s; s = s->next) {
                    if (str_cmp(s->code, section)) {
                        any = true;
                        cout << names[d] << " | "
                            << s->time << " | "
                            << days[d].rooms[r].name << " | "
                            << s->course << "\n";
                    }
                }
            }
        }
        if (!any) cout << "  (none)\n";
    }
};

int main() {
    TTADT tt;
    const char filename[] = "File1.csv";
    tt.load(filename);
    tt.printCourseInfo("Data Structures");
    tt.DetermineFreeClassrooms("Thursday", "6:00pm-7:30pm");
    tt.PrintTimetableOfSection("BDS-4A");

    return 0;
}
