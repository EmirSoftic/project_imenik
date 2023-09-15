Imenik - Phonebook Management System.

Imenik is a robust C++ implementation of a phonebook management system. This project aims to develop a strong understanding of data structures and their application in real-world scenarios. The Phonebook class is designed as a doubly-linked list, with each node containing a Contact structure.

Key Features
Contact Management: Easily add, delete, update, and retrieve contact information in the phonebook.

Sorted Order: Contacts are always stored in sorted order based on the name of the person or company.

Data Integrity: Imenik enforces data integrity rules. Each contact must have a name, and at least one of the following: a mobile phone number or a landline phone number. Invalid phone numbers are not accepted.

Exception Handling: Robust exception handling ensures that the program gracefully handles errors, such as duplicate names.

Functionality
Imenik offers the following functionality:

Add Contact: Add a new contact to the phonebook. If a contact with the same name already exists, an exception is raised.

Delete Contact: Remove an existing contact from the phonebook.

Update Contact: Modify contact details, including name and phone numbers.

Partial Name Search: Search for contacts by entering a partial name, and Imenik will return a list of matching contacts, sorted by name.

Partial Phone Number Search: Search for contacts by entering a partial phone number, and Imenik will return a list of matching contacts, sorted by name.

Constructor: Initialize the phonebook with an array (vector) of contacts. The constructor takes care of sorting and removing duplicates.

Merge Phonebooks: Merge two sorted phonebooks into a new sorted phonebook, following specific rules for handling duplicate contacts.

Implementation Details
The project is implemented in C++ to provide a practical demonstration of data structure concepts.

Imenik ensures efficient operations with a time complexity of O(n ^ 2) for sorting and initialization.
