This challenge tests your ability to apply Week 1 skills in a practical scenario. It’s slightly more complex than the mini-project to push your limits, but still within your grasp as an advanced Python developer transitioning to C.

Task: Write a C program that simulates a simple grade calculator for a class of students. The program should:

Accept the number of students (via scanf).
For each student, input their name (as a string) and three test scores (integers between 0 and 100).
Calculate the average score for each student and assign a letter grade (A: 90–100, B: 80–89, C: 70–79, D: 60–69, F: <60).
Print a formatted report with each student’s name, average score, and letter grade.
Handle errors: reject invalid scores (outside 0–100) and ensure the number of students is positive.
Requirements:

Use functions to modularize your code (e.g., one for calculating the average, one for determining the grade).
Use a switch or if statements for grade assignment.
Store names in character arrays (e.g., char name[50]).
Commit your code to your Git repo with clear comments and a README explaining how to compile and run it.

Example Output:
- Enter number of students: 2
- Enter name for student 1: Alice
- Enter 3 test scores for Alice: 95 88 92
- Enter name for student 2: Bob
- Enter 3 test scores for Bob: 75 80 82

--- Grade Report ---

Alice: Average = 91.67, Grade = A

Bob: Average = 79.00, Grade = C

Challenge Extension (Optional): Add a function to calculate the class average (across all students) and print it at the end of the report. This will test your ability to work with arrays and loops more deeply.

Submission:

Share your Git repo link or upload the source file (grade_calculator.c).
Include a brief note on any difficulties you faced (e.g., handling string input, debugging loops).