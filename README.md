📅 Timetable Management System

A robust C++ console-based application designed to automate the scheduling of academic lectures, lab sessions, and section-wise timetables.
The project emphasizes low-level system design, manual memory management, and file-based data persistence without STL containers, showcasing core programming fundamentals.

🚀 Key Features
📌 Automated Scheduling Engine
Generates conflict-free timetables for multiple courses, sections, and labs
Ensures no overlap between:
Classrooms
Faculty assignments
Time slots
🧠 Manual Data Processing
No use of STL containers (vector, string, etc.)
Custom implementation of:
String handling using character arrays (char*)
CSV parsing logic
Data indexing and storage mechanisms
💾 Persistent File Storage
Uses CSV-based storage system for:
Courses
Faculty data
Room allocations
Generated timetables
🏫 Academic Resource Management
Handles:
Faculty workload distribution
Classroom availability
Lecture and lab scheduling constraints
🛠️ Tech Stack
Language: C++
Data Storage: CSV (Comma Separated Values)
Core Concepts:
File Handling (I/O Streams)
Pointer Arithmetic
Manual Memory Management
Custom String Parsing
Algorithm Design for Scheduling
📁 Project Structure
Timetable-Management-System/
│
├── PartA.cpp        # Data initialization & base system setup
├── PartB.cpp        # Scheduling algorithm & timetable generation logic
│
├── File.csv         # Course and scheduling data
├── File1.csv        # Faculty & room allocation data
│
└── README.md        # Project documentation
⚙️ How It Works
1. Data Loading

The system reads academic data from CSV files, including:

Courses
Faculty members
Rooms
Section requirements
2. Scheduling Algorithm

The core engine:

Assigns time slots iteratively
Checks constraints dynamically:
No room conflicts
No teacher double-booking
Proper sequencing of lectures/labs
3. Output Generation

Final timetables are generated and stored back into structured CSV files.

▶️ How to Run
1. Compile the project
g++ PartA.cpp PartB.cpp -o TimetableSystem
2. Execute the program
./TimetableSystem
🎯 Learning Outcomes

This project demonstrates:

Strong foundation in C++ programming
Understanding of system-level design
Ability to build logic without high-level abstractions
Practical implementation of scheduling algorithms
File-based database handling
📌 Future Improvements
GUI-based timetable visualization
Migration to database (MySQL / SQLite)
Web-based interface for faculty access
Dynamic constraint optimization (AI-based scheduling)
👨‍💻 Author

Moaz Kashif
Data Science Student | Software & AI Enthusiast
GitHub: github.com/moazkashif
